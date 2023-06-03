from resurgence_renderer import Sphere, Vector3, Light, Scene

objects = [Sphere(Vector3(250, 250, 150), 120, Vector3(255, 255, 0), 0.5, 0.0001, 0.7)]
lights = [Light(Vector3(250, 250, -200), Vector3(255, 255, 255))]
camera = Vector3(0, 0, 0)

scene = Scene(500, 500, "Demo", 1000, camera, objects, lights)
scene.ray_trace()

while True:
    scene.update()
