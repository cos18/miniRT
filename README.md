# miniRT
The goal of this project is to generate images
using the Raytracing protocol. Those computer
generated images will each represent a scene, as
seen from a specific angle and position, defined
by simple geometric objects, and each with its own
lighting system.

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
TBD

