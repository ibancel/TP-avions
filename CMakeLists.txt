CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT ( tp_avions )

FIND_PACKAGE( OpenSceneGraph REQUIRED osgDB osgViewer osgGA)

set(EXECUTABLE_OUTPUT_PATH bin)

file(
        GLOB_RECURSE
        source_files
        src/*
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable( tp_avions ${source_files})

INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIRS} include)
TARGET_LINK_LIBRARIES(tp_avions ${OPENSCENEGRAPH_LIBRARIES} )
