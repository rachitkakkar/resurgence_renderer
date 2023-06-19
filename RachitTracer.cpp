#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include <string>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "Vector.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Objects.hpp"
#include "Scene.hpp"
#include "Utilities.hpp"

// Function to clear the screen based on the operating system
void clearScreen() {
#ifdef _WIN32
    // For Windows
    std::system("cls");
#else
    // For Unix/Linux
    std::system("clear");
#endif
}

// Function to create a progress bar given current progress (based on the ratio of progress / total) and elapsed seconds
void updateProgressBar(int progress, int total, double elapsedSeconds) 
{
    const int barWidth = 50;
    float percent = (float)progress / total;
    int filledWidth = percent * barWidth;

    std::cout << "[";
    for (int i = 0; i < barWidth; i++) {
        if (i < filledWidth) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "] " << percent * 100 << "% (" << elapsedSeconds << " seconds)\r";
    std::cout.flush();
}

bool hitSphere(const Vector3& center, double radius, const Ray& ray) {
    Vector3 sphereToRay = ray.origin - center;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * sphereToRay.dot(ray.direction);
    double c = sphereToRay.dot(sphereToRay) - radius*radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

Vector3 rayColor(const Ray& ray, const Scene& world) {
    Hit hit = world.hit(ray, 0.0, std::numeric_limits<double>::infinity());
    if (hit.occured)
        return 0.5 * (hit.normal + Vector3(1.0, 1.0, 1.0));
    Vector3 unitDirection = ray.direction.normalize();
    double t = 0.5 * (unitDirection.y + 1.0);
    return (1.0-t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
    // Image
    const float aspectRatio = 16.0f / 9.0f; 
    const int imageWidth = 1000;
    const int imageHeight = (int)(imageWidth / aspectRatio);
    std::string imageName = argv[1];

    unsigned char pixels[imageWidth * imageHeight * 3];
    const int samplesPerPixel = 500;
    int pixelIndex = 0;
    
    // Camera
    Camera camera(aspectRatio);

    // World
    Scene world;
    world.add(std::make_shared<Sphere>(Vector3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Vector3(0,-100.5,-1), 100));

    // Render
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = imageHeight-1; j >= 0; j--) {
        std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
        updateProgressBar((imageHeight-j), imageHeight, elapsed.count());
        
        for (int i = 0; i < imageWidth; i++) {
            double u = (double)i / (imageWidth-1);
            double v = (double)j / (imageHeight-1);

            Vector3 color;
            for (int s = 0; s < samplesPerPixel; s++) {
                double u = ((double)i + randomDouble())  / (imageWidth-1);
                double v = ((double)j + randomDouble())  / (imageHeight-1);
                
                Ray ray = camera.getRay(u, v);
                color = color + rayColor(ray, world);
            }

            double scale = 1.0 / samplesPerPixel;
            double r = color.x * scale;
            double g = color.y * scale;
            double b = color.z * scale;

            pixels[pixelIndex++] = (unsigned char)(256 * clamp(r, 0.0, 0.999));
            pixels[pixelIndex++] = (unsigned char)(256 * clamp(g, 0.0, 0.999));
            pixels[pixelIndex++] = (unsigned char)(256 * clamp(b, 0.0, 0.999));
        }
    }
    
    stbi_write_png(imageName.c_str(), imageWidth, imageHeight, 3, pixels, imageWidth * 3);

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // Create a window
    SDL_Window* window = SDL_CreateWindow(("[IMAGE PREVIEW] - " + imageName).c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, imageWidth, imageHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load the PNG image
    SDL_Surface* imageSurface = IMG_Load(imageName.c_str());
    if (!imageSurface) {
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        return 1;
    }

    // Create a texture from the image surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the texture onto the window's surface
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Event loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Clean up resources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    IMG_Quit();
    SDL_Quit();

    return 0;
}