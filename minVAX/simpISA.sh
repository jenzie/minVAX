#!/bin/csh

more dummest.cpp \
	includes.h globals.h \
	globals.cpp make_connections.cpp \
	prototypes.h execute.cpp fetch_into.cpp > dummest.code
more prog1.obj dummest.out > dummest.run
