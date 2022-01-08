##
## examples/Makefile
##
## This file is part of IMM testsuite.
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
IMM = ../imm.o

all: test1 test2 test3 test4 test5 test6 test7 test8 test9

test1: test1.c $(IMM)
	$(CC) $(CFLAGS) test1.c $(IMM) -o test1

test2: test2.c $(IMM)
	$(CC) $(CFLAGS) test2.c $(IMM) -o test2

test3: test3.c $(IMM)
	$(CC) $(CFLAGS) test3.c $(IMM) -o test3

test4: test4.c $(IMM)
	$(CC) $(CFLAGS) test4.c $(IMM) -o test4

test5: test5.c $(IMM)
	$(CC) $(CFLAGS) test5.c $(IMM) -o test5

test6: test6.c $(IMM)
	$(CC) $(CFLAGS) test6.c $(IMM) -o test6

test7: test7.c $(IMM)
	$(CC) $(CFLAGS) test7.c $(IMM) -o test7

test8: test8.c $(IMM)
	$(CC) $(CFLAGS) test8.c $(IMM) -o test8

test9: test9.c $(IMM)
	$(CC) $(CFLAGS) test9.c $(IMM) -o test9

clean:
	rm -f *.o *.immout test? core

