import pygame #Library to create window
import pygame.gfxdraw #Needed to draw pixels

from .Vector3 import Vector3 #See Vector3 class
from .Ray import Ray #See Ray class

class Scene:
    def __init__(self, width, height, title, max_distance, camera, objects, lights):
        #Width, height, and title
        self.width = width
        self.height = height
        self.title = title

        self.max_distance = max_distance #If objects are further than max distance, they will be ignored
        self.camera = camera #Position of camera (a Vector3)
        self.objects = objects #Objects 

        for object_ in self.objects: #Offsetting objects by camera
            object_ = object_.add_camera(self.camera)

        self.lights = lights #Light positions

        pygame.init() #Initialize pygame

        #Set up window
        self.screen = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption(self.title)

    def update(self): #Handle quitting window and update screen
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()

        pygame.display.flip()

    def ray_trace(self): #Ray trace
        for x in range(self.width):
            for y in range(self.height): #Loop over pixels
                pixel_color = Vector3(0, 0, 0) #Set pixel color to black
                colors = [] #Will be the 4 colours we take the average of (anti-aliasing)
                rays = [Ray(Vector3(x, y, 0), Vector3(0, 0, 1)), Ray(Vector3(x + 0.25, y, 0), Vector3(0, 0, 1)), Ray(Vector3(x, y + 0.25, 0), Vector3(0, 0, 1)), Ray(Vector3(x + 0.25, y + 0.25, 0), Vector3(0, 0, 1))] #Four rays for pixel, then take the average of those four colors (anti-aliasing)

                distance = self.max_distance #Distance that the closest object is. Starts at max distance.
                selected_object = None #The selected object
                object_hit = False #Determines if object is hit

                for ray in rays:
                    for object_ in self.objects:
                        if (object_.intersects(ray) > 0 and object_.intersects(ray) < distance):
                            distance = object_.intersects(ray)
                            selected_object = object_
                            object_hit = True

                    if (object_hit):
                        color = selected_object.color * selected_object.ambient
                        hit_pos = ray.origin + ray.direction * distance
                        hit_normal = selected_object.normal_at(hit_pos)
                        to_cam = Vector3(0, 0, 0) - hit_pos

                        for light in self.lights:
                            to_light = Ray(hit_pos, light.position - hit_pos)
                            color += selected_object.color * selected_object.diffuse * max(hit_normal.dot_product(to_light.direction), 0)
                            half_vector = (to_light.direction + to_cam).normalize()
                            color += light.color * selected_object.specular * max(hit_normal.dot_product(half_vector), 0)

                            for object_ in self.objects:
                                if (object_.intersects(to_light)):
                                    color = Vector3(color.x / 2, color.y / 2, color.z / 2)
                                    
                        colors.append(color)

                        for color_ in colors:
                            pixel_color += color_

                pixel_color = Vector3(pixel_color.x / 4, pixel_color.y / 4, pixel_color.z / 4)
                
                pygame.gfxdraw.pixel(self.screen, x, y, pixel_color.to_color().to_tuple())


                        


