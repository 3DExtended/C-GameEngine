# C-GameEngine ![Build status: ](https://travis-ci.org/3DExtended/C-GameEngine.svg?branch=master "Travis CI Test")


This GameEngine is based on a tutorial series and is a great introduction for beginners to OpenGL since I teach the basic concepts.
Following aspects can be learned:
  - Modern OpenGL
  - Object Oriented Programming concepts for OpenGL
  - Basic GameEngine features (e.g., Phyiscs, Shading and Component-Based Entity Systems)

## Features:

  - Opening a Window and setting its Clear-Color
  - Shader Class
    - A way to load and handle shaders
    - This class registers uniform variables on their own
    - If the "Bind(shaderObj)" macro is used, the shader is automatically unbind after the scope it was bind to.

# Dependencies

 - SDL2
 - GLM
 - OpenGL
 - GLEW

# Development

Want to use this engine? Great!

The project files for VisualStudio (2015) are included in this repository. For a more detailled explaination see this [video][devVid].

You may want to use other IDEs or Compilers; Therefore, add the Dependencies (listed above) to the linker and have fun.

# Todos

 - Write automated tests
 - Add samples for each component of the engine
 - Input Handler
   - Handle Key and Button inputs
 - Assets Loader
   - We need a way to load all kinds of stuff with only one loader 
   - Lets code a Asset Loader to store and load shaders, textures and models
 - Component based entity system
   - A system to handle entities and their components
 - Scene Handler
   - We need a way to handle different scenes 
   - Extract main function into the game project where the scenes are registered and than the main loop is called 
 - GUI
   - A way to create a GUI for games
   - We need: 
     - Text/Font-Handler
   - Window Handler
   - Event Handler
   - Image Handler
 - Add Deferred Shading
   - A method that simulates light and shadow casts
 - (3D Object MipMapping)

License
----

MIT

[devVid]: <https://www.youtube.com/watch?v=BYON4cKbxSc>
