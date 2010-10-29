cmake_minimum_required(VERSION 2.6)

PROJECT(FreePhyloTree CXX)

SET(STRGY SphereMakeTree)
SET(SRC Clade Engine EventManager SphereMakeTree CladeViewer program)

ADD_EXECUTABLE(FreePhyloTree ${SRC})

TARGET_LINK_LIBRARIES(FreePhyloTree OgreMain OIS SDL)
