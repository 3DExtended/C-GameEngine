cmake_minimum_required(VERSION 3.2)

set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/include)

#when a header only file was programmed we have to add its path as follows
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/Util)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/Util/Curves)


#add every cpp file to this line
add_library(engine STATIC 
	Engine/Util/FileSystem.cpp 
	Engine/Util/lodepng.cpp 
	Engine/Util/Math.cpp 
	Engine/Util/Rect.cpp 
	Engine/Util/Util.cpp 
	Engine/Util/Generators/CylinderGenerator.cpp
	Engine/Util/Generators/IcosphereGenerator.cpp
	Engine/Util/Generators/PerlinNoise.cpp
	Engine/Camera.cpp
	Engine/Display.cpp
	Engine/Engine.cpp
	Engine/Input.cpp
	Engine/Mesh.cpp
	Engine/Model.cpp
	Engine/Scene.cpp
	Engine/SceneHandler.cpp
	Engine/Shader.cpp
	Engine/Texture.cpp
	Engine/Components/Renderer.cpp
	Engine/ComponentBased/Component.cpp
	Engine/ComponentBased/GameObject.cpp
	Engine/ComponentBased/Transform.cpp
	Engine/GUI/FontHandler.cpp
	Engine/GUI/GUIRenderer.cpp
	Engine/GUI/Text.cpp
)

target_link_libraries(engine lib)
