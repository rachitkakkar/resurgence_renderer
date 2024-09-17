#ifndef CAMERA
#define CAMERA

#include "Vector.hpp"
#include "Ray.hpp"

class Camera {
public:
    Vector3 origin;
    Vector3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;

    Camera(double aspectRatio) {
        float viewportHeight = 2.0f;
        float viewportWidth = aspectRatio * viewportHeight;
        float focalLength = 1.0f;

        origin = Vector3();
        horizontal = Vector3(viewportWidth, 0, 0);
        vertical = Vector3(0, viewportHeight, 0);
        lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vector3(0, 0, focalLength);
    }

    Ray getRay(double u, double v) const {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }
};

#endif