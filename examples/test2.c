/*
   test2.c

   This file is part of IMM testsuite.
   Copyright (C) 2003, 2004 Wojciech Polak <polak@gnu.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <stdlib.h>

#include "../imm.h"
#define malloc(n) imm_malloc(n)
#define free(p) imm_free(p)

int
main (void)
{
  char *p1, *p2, *p3, *p4;

  printf ("TEST2: allocating memory p1,p2...\n");
  p1 = malloc (100);
  p2 = malloc (250);

  imm_summary (0);

  printf ("TEST2: allocating memory p3,p4...\n");
  p3 = malloc (20 * 1024);
  p4 = malloc (100 * 1024);

  printf ("TEST2: p1 is %lu bytes\n", (unsigned long) imm_get_chunk_size (p1));
  printf ("TEST2: p2 is %lu bytes\n", (unsigned long) imm_get_chunk_size (p2));
  printf ("TEST2: p3 is %lu bytes\n", (unsigned long) imm_get_chunk_size (p3));
  printf ("TEST2: p4 is %lu bytes\n", (unsigned long) imm_get_chunk_size (p4));

  printf ("TEST2: freeing all memory with imm_free_all().\n");
  imm_free_all();
  imm_summary (1);

  return 0;
}

/* EOF */

