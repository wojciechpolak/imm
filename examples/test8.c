/*
   test8.c

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
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../imm.h"
#define malloc(n) imm_malloc(n)
#define free(p) imm_free(p)

int
main (void)
{
  int i, status, parent = 0;
  char *p1, *p2;
  pid_t pid;
  FILE *fp;

  imm_verbose_on ();

  fp = fopen ("test8.immout", "w+");
  if (fp)
    imm_set_output (fp);

  printf ("TEST8: forking...\n");
  pid = fork ();
  if (pid == -1)
    {
      printf ("TEST8: Can't fork!\n");
      exit (1);
    }
  else if (pid > 0) /* parent */
    parent = 1;

  printf ("TEST8 [%d]: allocating memory p1,p2...\n", (int) getpid ());

  if (parent)
    {
      p1 = malloc (1024);
      p2 = malloc (4096);
      for (i = 0; i < 1024; i++)
	p1[i] = '+';
      for (i = 0; i < 4096; i++)
	p2[i] = '.';
    }
  else
    {
      p1 = malloc (4096);
      p2 = malloc (1024);
      for (i = 0; i < 4096; i++)
	p1[i] = '.';
      for (i = 0; i < 1024; i++)
	p2[i] = '+';
    }

  imm_summary (0);
  imm_test_all_chunks ();

  printf ("TEST8 [%d]: freeing p1,p2...\n", (int) getpid ());
  free (p1);
  free (p2);

  printf ("TEST8 [%d]: read the `test8.immout' file!\n", (int) getpid ());

  wait (&status);
  if (fp)
    fclose (fp);
  return 0;
}

/* EOF */

