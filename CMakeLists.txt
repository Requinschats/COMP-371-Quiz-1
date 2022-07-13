cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)

project(A1)

include(ExternalProject)

# Set install directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
if (WIN32)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug;Release" FORCE)
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

include(BuildGLEW)
include(BuildGLFW)
include(BuildGLM)

set(EXEC A1)


file(GLOB SRC src/*.cpp src/*/*.cpp src/*/*.h src/sources/*/*.cpp src/sources/*/*.h)

add_executable(${EXEC} ${SRC} src/WorldCube/WorldCube.cpp src/WorldCube/WorldCube.h src/skateboard/Skateboard.cpp src/skateboard/Skateboard.h src/characters/Characters.cpp src/characters/Characters.h)
target_link_libraries(${EXEC} OpenGL::GL glew_s glfw glm)

list(APPEND BIN ${EXEC})

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})


