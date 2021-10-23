# DISCALIMER
This is a python pygame library I made for raytracing a long time ago. It never evolved to reach my offical goals, and I gave up on it after a while. I have decided to put the code up because it taught me a lot about raytracing, and I hope it can help others too.
The original readme I made for this project can be found below:

# About
resurgence_renderer is a simple to use **3D render**, that can be easily extended using **python**.
The render uses **raytracing** to render 3D, and uses **pygame** for the window and displaying of the final image.
The render is lightweight and easy to use, however since it uses raytracing, it can be **quite slow**.
This is only in **beta** and right now only has the ability to render spheres.
This project is licensed under the **MIT License** and was made by **Rachit Kakkar**.

# HELP
**DOCS CAN BE FOUND IN docs/docs.text**

# Examples
**Examples can be found in the examples folder**
**The images from those examples can be found in the images folder**

This is an example output (can be found under images/output.png):
![Example Output](images/output.png)

This is the code used to generate the output (can be found under examples/output.pyw):

```python
from resurgence_renderer import Sphere, Vector3, Light, Scene

objects = [Sphere(Vector3(250, 250, 150), 120, Vector3(255, 255, 0), 0.5, 0.0001, 0.7)]
lights = [Light(Vector3(250, 250, -200), Vector3(255, 255, 255))]
camera = Vector3(0, 0, 0)

scene = Scene(500, 500, "Demo", 1000, camera, objects, lights)
scene.ray_trace()

while True:
    scene.update()
```

# ROAD MAP (NO PARTICULAR ORDER):
Add reflections
Add cones, planes, cubes, ect.
Add triangles and loading from obj files
Convert to C
Multiprocessing
Add Lua bindings
