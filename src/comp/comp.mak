#############################################################################
# comp.mak
# 	makefile for building of the compiler from refal-2 language, 
# 	result - bin/refal2 executable module.
#       Version for UNIX ( FreeBSD, Linux )
#
# Copyright (C) Refal-2 Team
# Author: Leonid Belous (aka BLF) 
# E-mail: belous@ilt.kharkov.ua
# Date: 28.05.2005
#############################################################################

####### Compiler, tools and options

.SUFFIXES: .c 

CC		=	gcc
CFLAGS		=	-pipe -w -O2 -DNO_DEBUG
LINK		=	gcc

S		=	src/comp
BIN_DIR		=	bin

####### Files

SOURCES =			\
		$(S)/ccst1.c 	\
		$(S)/ccst2.c 	\
		$(S)/cerr.c 	\
		$(S)/cgop.c 	\
		$(S)/cj.c 	\
		$(S)/clu.c 	\
		$(S)/cs.c 	\
		$(S)/plc.c 	\
		$(S)/refal.c

OBJECTS =			\
		$(S)/ccst1.o 	\
		$(S)/ccst2.o 	\
		$(S)/cerr.o 	\
		$(S)/cgop.o 	\
		$(S)/cj.o 	\
		$(S)/clu.o 	\
		$(S)/cs.o 	\
		$(S)/plc.o 	\
		$(S)/refal.o

TARGET =	refal2


####### Implicit rules

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

####### Build rules

all:	$(TARGET)

$(TARGET): $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJECTS) 

####### Dependences

$(S)/ccst1.o: $(S)/ccst1.c

$(S)/ccst2.o: $(S)/ccst2.c

$(S)/cerr.o: $(S)/cerr.c $(S)/refal.def

$(S)/cgop.o: $(S)/cgop.c $(S)/refal.def

$(S)/cj.o: $(S)/cj.c $(S)/refal.def

$(S)/clu.o: $(S)/clu.c $(S)/refal.def

$(S)/cs.o: $(S)/cs.c $(S)/refal.def

$(S)/plc.o: $(S)/plc.c

$(S)/refal.o: $(S)/refal.c $(S)/refal.def

### End of Makefile
