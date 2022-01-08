/*
   test9.c

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
#include <time.h>

#include "../imm.h"
#define malloc(n) imm_malloc(n)
#define free(p) imm_free(p)

int
main (void)
{
  char *p;
  FILE *fp;
  register int i, s;

  srand ((unsigned int) time ((time_t *) NULL));

  imm_verbose_on ();

  fp = fopen ("test9.immout", "w+");
  if (fp)
    imm_set_output (fp);

  for (i = 0; i < 94; i++)
    {
      p = malloc ((rand () % 1024) + 1);
      for (s = imm_get_chunk_size (p) - 1; s > 0; s--)
	{
	  p[s] = 33 + i;
	  putchar (p[s]);
	}
      imm_test_chunk (p);
      free (p);
    }

  putchar ('\n');
  imm_summary (1);

  for (i = 0; i < 94; i++)
    {
      p = malloc ((rand () % 1024) + 1);
      for (s = imm_get_chunk_size (p) - 1; s > 0; s--)
	{
	  p[s] = 33 + i;
	  putchar (p[s]);
	}
    }
  putchar ('\n');

  imm_summary (1);
  imm_test_all_chunks ();
  imm_free_all ();
  imm_summary (1);

  fprintf (fp, "largest allocated size: %lu\n",
	   (unsigned long) imm_get_largest_size ());

  printf ("TEST9: read the `test9.immout' file!\n");
  if (fp)
    fclose (fp);
  return 0;
}

/* EOF */

