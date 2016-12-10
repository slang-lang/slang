PROJECT(ObjectiveScript)

cmake_minimum_required(VERSION 2.8)

#INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)
INCLUDE(CMake/Base.cmake)

# this helps debugging dependencies - a lot :)
# SET_PROPERTY(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)

ADD_SUBDIRECTORY(Projects)
