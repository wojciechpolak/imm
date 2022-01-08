/*
   test1.c

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

  printf ("TEST1: allocating memory p1,p2...\n");
  p1 = malloc (100);
  p2 = malloc (250);
  printf ("TEST1: total allocated size: %lu bytes\n",
	  (unsigned long) imm_get_malloc_size ());

  printf ("TEST1: allocating memory p3,p4...\n");
  p3 = malloc (20 * 1024);    /* 20 kB */
  p4 = malloc (16 * 1048576); /* 16 MB */
  if (p4 == NULL)
    printf ("TEST1: Can't allocate 16MB!\n");

  printf ("TEST1: total allocated size: %lu bytes\n",
	  (unsigned long) imm_get_malloc_size ());
  imm_summary (1);

  printf ("TEST1: freeing p1,p4...\n");
  free (p1);
  free (p4);

  printf ("TEST1: freeing p3,p2...\n");
  free (p3);
  free (p2);

  imm_summary (1);

  printf ("TEST1: largest allocated size: %lu bytes\n",
	  (unsigned long) imm_get_largest_size ());
  return 0;
}

/* EOF */

