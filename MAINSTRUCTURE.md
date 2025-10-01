
**Disclaimer**  
This project was developed in part with the assistance of AI language models. This should not be seen as an issue, since the primary goal of the project was to gain practical experience with real-time physics simulation. At the beginning, I had no prior background in this field (as noted in the README.md). The documentation has also been written as part of the learning process, with the aim of consolidating and deepening my understanding of the techniques applied.

---

**L13:** Creates `ObjectsSystemPBD`, a class that includes a vector of `objectPBD`.  
**L18:** Creates a vector of `objectEuler`.  
**L19:** Creates a vector of `Brush` (used as an eraser).  
These lines all introduce containers for core objects used in this project.

**L26–38:** Gets the mouse position, runtime values, and utilizes the camera.

**L41–73:** Sets up physics. Lines 41–49 handle basic Euler calculations, and lines 51–73 use multiple iterations for more accurate behavior with more complicated functions.

**L101–148:** Handles drawing. First, the background and info attached to the camera are drawn. Line 111 draws `objPBD`, followed by barriers, `objEuler`, and finally the brush (or just rigid body).

**L154–194:** Calculates the eraser, with two loops checking if the mouse is over objects—one for PBD, one for Euler.

**L198–229:** Handles simple input. It is also worth noting that the main `while` loop running this project is inside another loop. This allows pressing "Q" to break the inner loop and reset the application without closing it entirely.


