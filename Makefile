##
## Makefile
##
## This file is part of IMM.
## Copyright (C) 2003, 2004 Wojciech Polak <polak@gnu.org>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##

CC = gcc
CFLAGS = -Wall -Wstrict-prototypes -O2 -g

all: imm.o
imm.o: imm.c imm.h
	$(CC) $(CFLAGS) -c imm.c

examples: buildexamples
buildexamples:
	(cd examples; $(MAKE))

clean:
	rm -f *.o *.immout core
	(cd examples; $(MAKE) clean)

## EOF

