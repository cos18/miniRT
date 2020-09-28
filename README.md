# miniRT
The goal of this project is to generate images using the Raytracing protocol. Those computer generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

[Subject](https://cdn.intra.42.fr/pdf/pdf/10458/en.subject.pdf)

### 🎯 Object
#### ✅ Mandatory part
- Project needs at least these 5 simple geometric objects: plane, sphere, cylinder, square and triangle
- If applicable, all possible intersections and the inside of the object must be handled correctly.
- Project must be able to resize the object’s unique properties: diameter for a sphere, side size for a square and the width and height for a cylinder.
- Project must be able to apply translation and rotation transformation to objects, lights and cameras (except for spheres, triangles and lights that cannot be rotated).
- Light management: spot brightness, hard shadows, ambience lighting (objects are never completely in the dark). Colored and multi-spot lights have to be handled correctly.
- Project must save the rendered image in bmp format when its second argument is "–-save".
- If no second argument is supplied, the program displays the image in a window using minilibX

#### 🎉 Bonus part
- [ ] Normal disruption e.g. using sine which gives a wave effect.
- [ ] Color disruption: checkerboard.
- [ ] Color disruption: rainbow effect using object’s normal.
- [ ] Parallel light following a precise direction.
- [ ] Compound element: Cube (6 squares).
- [ ] Compound element: Pyramid (4 triangles, 1 square).
- [ ] Putting caps on size-limited cylinders.
- [ ] One other 2nd degree object: Cone, Hyperboloid, Paraboloid..
- [ ] One color filter: Sepia, R/G/B filters..
- [ ] Anti-aliasing.
- [ ] Simple stereoscopy (like red/green glasses).
- [ ] Multithreaded rendering.
- [ ] Sphere texturing: uv mapping.
- [ ] Handle bump map textures.
- [ ] A beautiful skybox.
- [ ] Keyboard interactivity (translation/rotation) with camera.
- [ ] Keyboard interactivity (translation/rotation) with objects.
- [ ] Changing the camera rotation with the mouse.