/*
   test4.c

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
#define calloc(n,s) imm_calloc(n,s)
#define free(p) imm_free(p)

int
main (void)
{
  char *p1, *p2;
  int i;

  printf ("TEST4: allocating memory p1,p2 using calloc()...\n");
  p1 = calloc (3, 100);
  p2 = calloc (1, 200);

  for (i = 0; i < 300; i++)
    {
      p1[i] = '+';
      putchar (p1[i]);
    }

  for (i = 0; i < 200; i++)
    {
      p2[i] = '.';
      putchar (p2[i]);
    }

  putchar ('\n');
  imm_summary (1);
  imm_test_all_chunks ();

  printf ("TEST4: freeing memory p1,p2...\n");
  free (p1);
  free (p2);

  imm_summary (1);
  return 0;
}

/* EOF */

