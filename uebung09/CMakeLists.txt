###############################################################################
# Declare the minimum cmake version required
###############################################################################
cmake_minimum_required(VERSION 3.0.2)

###############################################################################
# The name of out project
###############################################################################
project(CPP18_ASTEROIDS)
project(CPP18_FUNCTIONALS)

###############################################################################
# Now you would normally declare additional linker and include directories.
# We don't need this at this moment, just to show you how its done
###############################################################################

#link_directories("${CMAKE_SOURCE_DIR}/lib")
#link_directories("$ENV{HOME}/local/lib")

#include_directories(${CMAKE_SOURCE_DIR}/ext/Eigen)
#include_directories(${CMAKE_SOURCE_DIR})
#include_directories(${CMAKE_SOURCE_DIR}/src/lib)

###############################################################################
# Extend path to search for local cmake modules
###############################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

###############################################################################
# With cmake we can define additional compiler flags for different 
# configurations. CMAKE_CXX_FLAGS are for the default case. The debug config
# can be used to generate debug symbols for gdb. The release option uses
# special optimization flags
###############################################################################

set( CMAKE_CXX_FLAGS         "-O3 -Wall" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3 -msse3 -Wno-deprecated-declarations -Wno-unused -Wcpp" )
set( CMAKE_CXX_FLAGS_DEBUG   "-g -Wall" )
set( CMAKE_CXX_STANDARD 11)
set( CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
# Find required libraries.Right now we need glut and OpenGL. The required 
# options forces this packages to be present. For non-mandatory packages you 
# can leave this flag out. The can then check if they were found by using
# IF(OpenGL_found) etc.
###############################################################################

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/ext/load3ds)
include_directories(${CMAKE_SOURCE_DIR}/ext/load3ds/math3d++)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED) 
find_package(JPEG REQUIRED)

# Add SDL2 include directory to search path
include_directories(${SDL2_INCLUDE_DIR})

if(OpenGL_FOUND)
    link_directories(${OpenGL_LIBRARY_DIRS})
    include_directories(${OpenGL_INCLUDE_DIRS})
endif(OpenGL_FOUND)

if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif(GLEW_FOUND)

set(Boost_USE_MULTITHREADED     ON)

find_package( Boost 1.54
    COMPONENTS
    program_options
    filesystem
    system
    thread
    serialization
    REQUIRED )

link_directories(${Boost_LIBRARY_DIR})
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})


###############################################################################
# Compile external libraries
###############################################################################

add_subdirectory(ext/load3ds)

###############################################################################
# Variable for the sources of the binary. In larger projects it is often a 
# good idea to use such variables because it is easy to add more source files
# and you can reuse it for several targets (maybe you want to build a library
# some day ;-)
###############################################################################
set(FUNCTIONALS_SOURCES
    Functionals.cpp)

set(ASTEROID_SOURCES
    Main.cpp
    #io/PLYIO.cpp #old ply loader
    io/PLYTraits.cpp
    io/ReadPPM.cpp
    io/ReadTGA.cpp
    io/ReadJPG.cpp
    io/ReadPLY.cpp
    io/Read3DS.cpp
    io/ReadOBJ.cpp
    io/TextureFactory.cpp
    io/TriangleMeshFactory.cpp
    math/Matrix.cpp
    math/Quaternion.cpp
    math/Randomizer.cpp
    rendering/Rectangle.cpp
    rendering/Renderable2D.cpp 
    rendering/Renderable3D.cpp
    rendering/Circle.cpp
    rendering/Sphere.cpp
    rendering/Texture.cpp
    rendering/TriangleMesh.cpp
    rendering/TexturedMesh.cpp
    rendering/Skybox.cpp
    rendering/SpaceCraft.cpp
    rendering/Asteroid.cpp
    rendering/AsteroidField.cpp    
    util/Util.cpp
    view/MainWindow.cpp 
    view/Camera.cpp  
)

set(ASTEROID_DEPENDS     
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${GLEW_LIBRARIES} 
    ${GLUT_LIBRARY} 
    ${OPENGL_LIBRARY} 
    ${SDL2_LIBRARY}
    ${JPEG_LIBRARIES}
    c3dsreader
)

###############################################################################
# The executable fpr our project
###############################################################################

add_executable(asteroids ${ASTEROID_SOURCES} ${C3DSREADER_SOURCES})
add_executable(functionals ${FUNCTIONALS_SOURCES})

###############################################################################
# External library dependencys
###############################################################################

message(STATUS ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${SDL2_LIBRARY})
target_link_libraries(asteroids ${ASTEROID_DEPENDS})
