# Light-Field-Viewer

This is a light field viewer implemented in OpenGL based on Levoy and Hanrahan paper [1] using the light field dataset in [2]. The light field rendering calculation is done with shaders to ensure fast rendering. The code can only handle square image grids. The light field samples are loaded as a texture atlas. All the light fields in the result have 17x17 grid.

[1] Levoy, Marc, and Pat Hanrahan. "Light field rendering." Proceedings of the 23rd annual conference on Computer graphics and interactive techniques. 1996.

[2] Jarabo, Adrian, et al. "How do people edit light fields." ACM Transactions on Graphics (Proc. SIGGRAPH). Vol. 33. No. 4. 2014.

## Results
![Lobby Light Field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/lobby.gif)
![Head Light Field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/head.gif)
![Garden Light field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/green.gif)
![Tea Pots Light Field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/pots.gif)
![Light Field Viewer](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/fullLook.PNG)

The rendering is done at about 60 FPS. The loading of 4 textures takes about 19 sec.
The program is tested on the machine with the following specifications:
* CPU: Intel Xeon 2.8 GHz
* RAM: 64 GB
* GPU: NVIDIA Quadro K620

## Dependencies
- IMGUI: library for GUI rendering library
- stb_image: library for loading texture images
- GLM : library for Geometry computation
- GLFW: library for window creation

## The control keys

To control the camera position:
 - A: move camera to right
 - D: move camera to left 
 - S: move camera Down
 - W: move camera Up
 - Z: move camera Inward
 - X: move camera Outward
 - P: print camera information

To control the Image Plane:
- I: move Image Plane Up
- K: move Image Plane Down
- L: move Image Plane Right 
- J: move Image Plane Left
- M: move Image Plane Outward
- N: move Image Plane Inward

Light field control Panel

![Control Panel](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/cp.PNG)

- With the control panel area, you can change the Z position of the camera plane and the focal plane.
- The 0 button shows the camera plane, 1,2,3,4 are different bilinear interpolation, 5 is the quad-linear interpolation
- The buttons on that last row allow for the user to switch to a different light field.

## Manifestation
* LightField Atlas Generator :
    *  ImageAtlas.py: Combine Stanford dataset images into one image atlas
* res: Contains resources
    * shaders
        * Basic.shader: vertex and fragment shader 
    * textures: contains all the textures
* src: OpenGL Code
    * Camera.h: class for handling camera movement and calculation
    * CameraPlane.cpp: Debug code for camera Plane 
    * CameraPlane.h
    * IndexBuffer.cpp : Class for handling the index buffer
    * IndexBuffer.h
    * main.cpp: Code entry point
    * Plane.cpp: Class for Image plane generation at different sizes
    * Plane.h
    * Renderer.cpp: Rendering class (currently support OpenGL, support for other renders can be added here such as direct 3D)
    * Renderer.h
    * Shader.cpp: Class for reading and parsing the shaders. The shader should be in one file and be separated by # followed by the shader name.
    * Shader.h
    * Texture.cpp: Class for reading the textures
    * Texture.h
    * VertexArray.cpp: Class for handling the vertex array
    * VertexArray.h
    * VertexBuffer.cpp: Class for handling the vertex buffer
    * VertexBuffer.h
    * VertexBufferLayout.h: Helper class for defining the layout of vertex buffer
- vendor: contains third-party libraries (glm and GLFW not here)
- README.md
