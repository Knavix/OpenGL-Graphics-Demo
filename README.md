# OpenGL Textured Cubes

A 3D graphics project built with C++ and OpenGL while working through the fundamentals of the graphics programming.

The project renders multiple textured cubes in 3D space, with each cube constructed from triangles and transformed independently. The cubes are positioned throughout the scene and rotate at different speeds using model transformations.

<p align="center">
  <img src="demo\graphics-demo.gif" width="700">
</p>

## Features

- Renders multiple 3D cubes using OpenGL
- Applies textures to cube surfaces
- Uses model, view, and projection matrices
- Positions cubes independently in 3D space
- Animates each cube with different rotation speeds
- Uses perspective projection to create depth
- Uses GLSL vertex and fragment shaders
- Manages geometry through VAOs and VBOs

## What I Learned

This project helped me understand how OpenGL takes vertex data and transforms it from local object coordinates into a 3D scene.

I practiced:

- Creating and rendering 3D geometry
- Loading and applying textures
- Using transformation matrices
- Combining translation and rotation
- Working with the OpenGL rendering pipeline
- Passing data between C++ and GLSL shaders
- Animating multiple objects independently

## Technologies

- C++
- OpenGL
- GLFW
- GLAD
- GLM
- GLSL
