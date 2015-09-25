cmake_minimum_required(VERSION 3.3)
project(netease_startup)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CURRENT_SOURCE_DIR "/home/manfred/workspace/cg/netease-startup")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/manfred/workspace/cg/netease-startup")


set(SOURCE_FILES main.cpp Canvas.h Canvas.cpp Pixel.h param.h Box.cpp Box.h utils.cpp utils.h Transform.cpp Transform.h Camera.cpp Camera.h)
add_executable(netease_startup ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

#set(OPENGL_LIBRARIES "/usr/lib/x86_64-linux-gnu/libGL.so")
#set(SDL_LIBRARY "/usr/lib/x86_64-linux-gnu/libSDL2.so")
#set(GLEW_LIBRARY "/usr/lib/x86_64-linux-gnu/libGLEW.so")
#target_link_libraries(netease_startup ${OPENGL_LIBRARIES} ${SDL_LIBRARY} ${GLEW_LIBRARY})

target_link_libraries (netease_startup libGL.so libglut.so libSDL2.so libGLEW.so libglfw.so)

