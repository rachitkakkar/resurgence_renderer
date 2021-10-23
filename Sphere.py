from math import sqrt #Square root

class Sphere:  # Sphere class
    def __init__(self, center, radius, color, ambient, diffuse, specular):
        self.center = center  # Center of sphere
        self.radius = radius  # Radius of sphere

        self.color = color  # Color of sphere
        self.ambient = ambient  # Ambience of sphere
        self.diffuse = diffuse  # Diffusion of sphere
        self.specular = specular  # Specular lighting of sphere

    def add_camera(self, camera):
        return Sphere(self.center - camera, self.radius, self.color, self.ambient, self.diffuse, self.specular)

    def intersects(self, ray): #Checks if the ray intersects ray and returns distance or -1
        sphere_to_ray = ray.origin - self.center
        b = 2 * ray.direction.dot_product(sphere_to_ray)
        c = sphere_to_ray.dot_product(sphere_to_ray) - self.radius * self.radius
        discriminant = b * b - 4 * c

        if (discriminant >= 0):
            distance = (-b - sqrt(discriminant)) / 2
            if (distance > 0):
                return distance

        return -1

    def normal_at(self, hit_point):  # Get normal at point on sphere
        return (hit_point - self.center).normalize()
