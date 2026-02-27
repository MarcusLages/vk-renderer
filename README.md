# vk-renderer
Experimentation Vulkan renderer.
Base of a future project and used to learn graphics programming, game engine development and Vulkan API.

Initial code and implementation based on [tinyrenderer](https://haqr.eu/tinyrenderer/).

# How to Run
The executable is compiled to `/build` and to the root folder.
Linux:
```bash
export CMAKE_PREFIX_PATH='WHEREVER SDL AND OTHER LIBRARIES CMAKE ARE'
cmake -Bbuild
cmake --build build -j
build/vkr obj/diablo3_pose/diablo3_pose.obj obj/floor.obj
```

Windows:
```bash
set CMAKE_PREFIX_PATH='WHEREVER SDL AND OTHER LIBRARIES CMAKE ARE'
cmake -Bbuild
cmake --build build -j
build\vkr.exe obj\diablo3_pose\diablo3_pose.obj obj\floor.obj
```

# References
- [tinyrenderer](https://haqr.eu/tinyrenderer/) by [Dmitry V. Sokolov](https://github.com/ssloy)
- [3D Math Primer for Graphics and Game Development](https://gamemath.com/book/) by [Fletcher Dunn](https://github.com/zpostfacto) and [Ian Parberry](https://ianparberry.com/)