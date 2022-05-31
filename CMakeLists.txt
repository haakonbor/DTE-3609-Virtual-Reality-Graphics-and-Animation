project(GameApp)
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARIES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARIES})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)



set( INCLUDE
        include/Plane.hpp
        include/Camera.hpp
        include/Clock.hpp
        include/FpsCounter.hpp
        include/GameManager.hpp
        include/Input.hpp
        include/SceneObject.hpp
        include/Character.hpp
        include/Utils.hpp
        include/Snow.hpp
        include/Text.hpp
        include/ScoreText.hpp
        include/Minimap.hpp
        include/IndexBuffer.h
        include/Shader.h
        include/VertexArray.h
        include/VertexBuffer.h
        include/VertexBufferLayout.h
        include/Texture.h
        include/Projection.h
        include/Skybox.h
        include/Obstacle.h

        include/GLErrorHandler.h
        include/stb_image.h
)
set( SRCS
        src/Plane.cpp
        src/Camera.cpp
        src/GameManager.cpp
        src/SceneObject.cpp
        src/Character.cpp
        src/Snow.cpp
        src/Text.cpp
        src/ScoreText.cpp
        src/Minimap.cpp
        src/IndexBuffer.cpp
        src/Shader.cpp
        src/VertexArray.cpp
        src/VertexBuffer.cpp
        src/Texture.cpp
        src/Skybox.cpp
        src/Obstacle.cpp

        src/GLErrorHandler.cpp
        src/stb_image.cpp

        app/main.cpp


)

add_executable(${PROJECT_NAME} ${INCLUDE} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
