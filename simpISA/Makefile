#
# Created by gmakemake (Ubuntu Sep  7 2011) on Mon Mar  3 13:55:30 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

BASE = /home/course/csci453
ARCHVER = arch2-5a
CXX = g++
CCFLAGS = -g -I$(BASE)/include/$(ARCHVER)
CXXFLAGS = $(CCFLAGS)
LIBFLAGS = -g -L$(BASE)/lib/$(SYS_TYPE) -l$(ARCHVER)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES =	execute.cpp fetch_into.cpp globals.cpp make_connections.cpp run_simulation.cpp simpISA.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	globals.h includes.h prototypes.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	execute.o fetch_into.o globals.o make_connections.o run_simulation.o 

#
# Main targets
#

all:	simpISA 

simpISA:	simpISA.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o simpISA simpISA.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

execute.o:	globals.h includes.h prototypes.h
fetch_into.o:	globals.h includes.h prototypes.h
globals.o:	globals.h includes.h prototypes.h
make_connections.o:	globals.h includes.h prototypes.h
run_simulation.o:	globals.h includes.h prototypes.h
simpISA.o:	globals.h includes.h prototypes.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) simpISA.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf simpISA 
