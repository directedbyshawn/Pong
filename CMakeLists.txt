cmake_minimum_required(VERSION 3.20)
project(pong)

if (WIN32)
    set(FREEGLUT_INCLUDE_DIRS "C:/Program\ Files/Common\ Files/freeglut/include")
    set(FREEGLUT_LIBRARY_DIRS "C:/Program\ Files/Common\ Files/freeglut/lib/x64")
    set(INCLUDES "include")
endif (WIN32)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")

find_package (OpenGL REQUIRED)

if (APPLE)
    find_package(GLUT REQUIRED)
endif (APPLE)

if (WIN32)
    include_directories(${OPENGL_INCLUDE_DIR}  ${FREEGLUT_INCLUDE_DIRS} ${INCLUDES})
    link_directories(${FREEGLUT_LIBRARY_DIRS})
elseif (APPLE)
    include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})
endif()

file(GLOB SOURCE_FILES
        main.cpp
        include/*.h
        lib/*.cpp
        )

add_executable(pong ${SOURCE_FILES})

if (WIN32)
    target_link_libraries (pong ${OPENGL_LIBRARIES} freeglut winmm.lib)
elseif (APPLE)
    target_link_libraries (pong ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif()