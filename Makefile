#############################################################################
# Makefile
#       Makefile for building refal2 system
#       for UNIX ( FreeBSD, Linux )
#
# Copyright (C) Refal-2 Team
# Author: Leonid Belous (aka BLF)
# E-mail: belous@ilt.kharkov.ua
# Date: 28.05.2005
#############################################################################

MAKE	=	make

all:

# PHASE I:
# Make the compiler from refal-2 language,
# result bin/refal2 executable module

	mkdir -p bin
	$(MAKE) -f src/comp/comp.mak

# PHASE II:
# Make the interpreter from "jazyk sborki",
# result lib/librefal2.a - set of object modules.
# Empty  lib/libr2user.a also created.

	mkdir -p lib/r2objects
	$(MAKE) -f src/inter/inter.mak

# Remove intermediate files

#	./delbin

clean:
	rm -rf bin lib src/comp/*.o src/inter/*.o src/inter/xcv.asm src/inter/*.log src/inter/*.lst

#### end of Makefile
