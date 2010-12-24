cmake_minimum_required(VERSION 2.6)

PROJECT(FreePhyloTree CXX)

SET(STRGY GourceianMakeTree StrategyColor)
SET(SRC Clade Node Engine EventManager ${STRGY} CladeViewer program)

ADD_EXECUTABLE(FreePhyloTree ${SRC})

TARGET_LINK_LIBRARIES(FreePhyloTree SDL SDL_image GL GLU)
