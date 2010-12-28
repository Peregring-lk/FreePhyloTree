cmake_minimum_required(VERSION 2.6)

PROJECT(FreePhyloTree CXX)

INCLUDE_DIRECTORIES(/usr/include/freetype2/)

AUX_SOURCE_DIRECTORY(Tree TREE)
AUX_SOURCE_DIRECTORY(Strategies STRGY)

SET(TREES PhyloTree ${TREE} ${STRGY})
SET(SRC Viewer Engine EventManager ${TREES} program)

ADD_EXECUTABLE(FreePhyloTree ${SRC})

TARGET_LINK_LIBRARIES(FreePhyloTree SDL SDL_image GL GLU ftgl m)
