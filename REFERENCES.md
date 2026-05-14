# References
1. [tinyrenderer](https://haqr.eu/tinyrenderer/)
2. [3D Math Primer for Graphics and Game Development](https://gamemath.com/book/)
	1. [Multiple Coordinate Spaces](https://gamemath.com/book/multiplespaces.html#why)
3. [Scratchapixel](https://www.scratchapixel.com/index.html)
4. [Must-read and classic books of computational geometry and computer graphics (repo)](https://github.com/HW140701/Book-list-of-computational-geometry-and-computer-graphics)

## Rasterization
1. [Optimizing the basic rasterizer | The ryg blog](https://fgiesen.wordpress.com/2013/02/10/optimizing-the-basic-rasterizer/)

#### Clipping
1. [Polygon Clipping by Sutherland & Hodgman](https://dl.acm.org/doi/10.1145/360767.360802)
    - Original article
2. [Clipping using Homogeneous Coordinates by Blinn and Newell](https://www.microsoft.com/en-us/research/wp-content/uploads/1978/01/p245-blinn.pdf)
    - Good article
3. [Computer Graphics - Clipping by Haowei Hsieh](https://sites.cc.gatech.edu/grads/h/Hao-wei.Hsieh/Haowei.Hsieh/mm.html#sec3)
    - Pseudocode for Cohen-Sutherland and Sutherland-Hodgman
4. [Clipping by Gabriel Gambetta](https://gabrielgambetta.com/computer-graphics-from-scratch/11-clipping.html)
5. [3D Clipping and Other Topics (Drexel University).pdf](https://www.cs.drexel.edu/~deb39/Classes/CS430/Lectures/L-14_CullingZbufRays.6.pdf)
6. [Back-face Culling and Clipping | The ryg blog](https://fgiesen.wordpress.com/2011/07/05/a-trip-through-the-graphics-pipeline-2011-part-5/)

## Coordinate Space Transformations

#### Transforms and Matrices
1. [The Transformation Pipeline | Dave Kilian's Blog](https://davekilian.com/transformation-pipeline.html)
	- Best for intuition
2. [transforms-2x2.pdf](https://www.cs.ubc.ca/~tmm/courses/314-13/slides/transforms-2x2.pdf)
3. [06-Vertex Transformations.pdf](https://user.xmission.com/~legalize/book/download/06-Vertex%20Transformations.pdf)
	- Still have
4. [NVIDIA Dev Zone Tutorial - Chapter 4. Transformations](https://developer.download.nvidia.com/CgTutorial/cg_tutorial_chapter04.html)
5. [Unity - Scripting API: Transform](https://docs.unity3d.com/6000.3/Documentation/ScriptReference/Transform.html)
	- For reference
  
#### Projection and NDC
1. [Better camera by tinyrenderer](https://haqr.eu/tinyrenderer/camera/)
	- Not great, but good for building intuition with code
2. [Perspective and Orthographic Projection Matrix by Scratchapixel](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/projection-matrix-introduction.html)
3. [Homogeneous Coordinates, Clip Space, and NDC by Carmen's Graphics Blog](https://carmencincotti.com/2022-05-02/homogeneous-coordinates-clip-space-ndc/)

#### LookAt and Rotation
1. [Placing a Camera: the LookAt Function by Scratchapixel](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function/framing-lookat-function.html)
2. [Geometry by Scratchapixel](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/creating-an-orientation-matrix-or-local-coordinate-system.html)

## Shading
1. #todo [Shading by Scratchapixel](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/what-is-shading-light-matter-interaction.html)
2. [Mathematics of Shading by Scratchapixel](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/mathematics-of-shading/mathematics-of-shading.html)
3. #todo [Advanced Computer Graphics Summary by Uni Freiburg.pdf](https://cg.informatik.uni-freiburg.de/course_notes/graphics2_99_summary.pdf)
4. #todo [Computer Graphics Shading by Uni Freiburg.pdf](https://cg.informatik.uni-freiburg.de/course_notes/graphics_02_shading.pdf)
5. #todo [Shading by CMU.pdf](https://www.cs.cmu.edu/afs/cs/academic/class/15462-s10/www/lec-slides/lec11.pdf)
6. #todo [Shading by Gabriel Gambetta](https://gabrielgambetta.com/computer-graphics-from-scratch/13-shading.html)
    - Mostly for intuition
7. #todo [Shading and Lighting - CGLearn by UniTartu/Raimond Tunnel](https://cglearn.eu/pub/computer-graphics/shading-and-lighting)

#### Lighting
1. #todo [Introduction to Lighting by Scratchapixel](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-lighting/introduction-to-lighting.html)
2. #todo [A Creative Dive into BRDF, Linearity, and Exposure](https://www.scratchapixel.com/lessons/3d-basic-rendering/brdf-linear-exposure/intro-brdf.html)
3. #todo [Lighting by Uni Freiburg.pdf](https://cg.informatik.uni-freiburg.de/course_notes/graphics_04_lighting.pdf)

## Math
1. [3D Math Primer for Graphics and Game Development](https://gamemath.com/book/)
	1. [Multiple Coordinate Spaces](https://gamemath.com/book/multiplespaces.html#why)
2. [Mathematics of Shading by Scratchapixel](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/mathematics-of-shading/mathematics-of-shading.html)
3. [Space Vectors, Lines, and Planes by Carleton University.pdf](https://people.math.carleton.ca/~angelo/calculus/vectors-lines-planes.pdf)

#### Quaternion Rotation
1. [Explorable video series in Quaternion by Ben Eater and ThreeBlueOneBrown](https://eater.net/quaternions)
	- Other videos by ThreeBlueOneBrown
2. [Euler vs Quaternion - What's the difference?](https://www.youtube.com/watch?v=sJcVJEOwLUs)
3. [How quaternions produce 3D rotation](https://www.youtube.com/watch?v=jTgdKoQv738)
4. [How to Use Quaternions](https://www.youtube.com/watch?v=bKd2lPjl92c&t=3s)

## Testing
1. [GoogleTest Primer](https://google.github.io/googletest/primer.html)
2. [GoogleTest - Google Testing and Mocking Framework](https://github.com/google/googletest)
3. [Catch2](https://catch2.org/)
4. [Catch2/docs/tutorial.md](https://github.com/catchorg/catch2/blob/devel/docs/tutorial.md)