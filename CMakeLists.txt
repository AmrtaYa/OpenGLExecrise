cmake_minimum_required(VERSION 3.24)
project(Execrise2)

set(CMAKE_CXX_STANDARD 17)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(D:/TA/Pagram/glm-master/glm-master)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(Execrise2 main.cpp Component/Shader.cpp Component/Shader.h Test.cpp include/glad.c Component/Camera.cpp Component/Camera.h Component/Material.cpp Component/Material.h)
target_link_libraries(Execrise2 ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(Execrise2 opengl32.lib ${PROJECT_SOURCE_DIR}/lib/glew32.dll)