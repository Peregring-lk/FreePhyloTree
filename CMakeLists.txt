cmake_minimum_required(VERSION 2.6)

PROJECT(FreePhyloTree CXX)

SET(SRC Clade StandardCladeViewer Engine EventManager program)

ADD_EXECUTABLE(FreePhyloTree ${SRC})

TARGET_LINK_LIBRARIES(FreePhyloTree OgreMain OIS SDL)
