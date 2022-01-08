/*
   imm.c

   IMM 0.3 -- Internal Memory Manager.
   Copyright (C) 2003, 2004 Wojciech Polak <polak@gnu.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef NOGETPID
# include <unistd.h>
# include <sys/types.h>
#endif

#ifndef	NULL
# define NULL 0
#endif

#include "imm.h"

const char imm_version[] = "IMM 0.3";

/*
  IMM internal data
*/

struct chunk
{
  struct chunk *prev;
  struct chunk *next;
  void *internal_id;
  void *external_id;
  size_t size;
};

struct internal_memory
{
  struct chunk *head;
  struct chunk *tail;
  size_t count;
  size_t malloc_size;
  size_t largest_size;
} static IMM = { NULL, NULL, 0, 0, 0 };

enum toggle
{
  OFF, ON
};

struct env_struct
{
  FILE *output;
  enum toggle logging;
  enum toggle verbose;
} static IMM_env = { NULL, ON, OFF };

/*
  IMM Core
*/

#define IMM_EXTRA_ZONE 16

void *
imm_malloc (size_t size)
{
  void *ptr;

  if (size == 0)
    return NULL;

  ptr = malloc (size + 2*IMM_EXTRA_ZONE);
  if (ptr == NULL)
    {
      imm_message ("malloc() failed. Cannot allocate enough memory.");
      return NULL;
    }
  else
    {
      struct chunk *newchunk;

      memset (ptr, 'A', IMM_EXTRA_ZONE);
      memset (ptr + size + IMM_EXTRA_ZONE, 'Z', IMM_EXTRA_ZONE);

      newchunk = malloc (sizeof (struct chunk));
      if (newchunk == NULL)
	{
	  imm_message ("Can't allocate a new chunk register.");
	  free (ptr);
	  return NULL;
	}
      else
	{
	  newchunk->next = NULL;
	  newchunk->prev = IMM.tail;
	  newchunk->size = size;
	  newchunk->internal_id = ptr;
	  newchunk->external_id = ptr + IMM_EXTRA_ZONE;
	  if (IMM.head == NULL)
	    IMM.head = IMM.tail = newchunk;
	  else
	    IMM.tail->next = newchunk;
	  IMM.tail = newchunk;
	  IMM.count++;
	  IMM.malloc_size += size;

	  if (IMM.malloc_size > IMM.largest_size)
	    IMM.largest_size = IMM.malloc_size;

	  if (IMM_env.verbose == ON)
	    imm_message ("registering chunkID %p (size %luB)",
			 newchunk->external_id, size);

	  return (void *)newchunk->external_id;
	}
    }
}

void *
imm_calloc (size_t nmemb, size_t size)
{
  void *c = imm_malloc (nmemb * size);
  if (c)
    memset (c, 0, nmemb * size);
  return c;
}

void *
imm_realloc (void *ptr, size_t size)
{
  struct chunk *c;

  if (ptr == NULL)
    return imm_malloc (size);

  if (size == 0)
    {
      imm_free (ptr);
      return NULL;
    }

  for (c = IMM.head; c; c = c->next)
    {
      if (c->external_id == ptr)
	{
	  ptr = realloc (c->internal_id, size + 2*IMM_EXTRA_ZONE);
	  if (ptr == NULL)
	    {
	      imm_message ("realloc() failed. Cannot reallocate enough memory.");
	      return NULL;
	    }
	  else
	    {
	      if (IMM_env.verbose == ON)
		imm_message ("reallocating chunkID %p -> %p (size %luB -> %luB)",
			     c->external_id, (ptr + IMM_EXTRA_ZONE), c->size, size);

	      memset (ptr, 'A', IMM_EXTRA_ZONE);
	      memset (ptr + size + IMM_EXTRA_ZONE, 'Z', IMM_EXTRA_ZONE);
	      IMM.malloc_size -= c->size;
	      IMM.malloc_size += size;
	      c->size = size;
	      c->internal_id = ptr;
	      c->external_id = ptr + IMM_EXTRA_ZONE;
	    }
	  return (void *)c->external_id;
	}
    }
  imm_message ("imm_realloc() failed: couldn't reallocate unregistered chunkID %p", ptr);
  return NULL;
}

void
imm_free (void *ptr)
{
  struct chunk *c, *nextc;

  if (ptr == NULL)
    return;

  for (c = IMM.head; c; c = nextc)
    {
      nextc = c->next;
      if (c->external_id == ptr)
	{
	  if (IMM_env.verbose == ON)
	    imm_message ("freeing chunkID %p (size %luB)",
			 c->external_id, c->size);

	  if (c->prev)
	    c->prev->next = c->next;
	  else
	    IMM.head = c->next;
	  if (c->next)
	    c->next->prev = c->prev;
	  else
	    IMM.tail = c->prev;

	  IMM.count--;
	  IMM.malloc_size -= c->size;

	  free (c->internal_id);
	  free (c);
	  return;
	}
    }
  imm_message ("imm_free() failed: couldn't free unregistered chunkID %p", ptr);
}

void
imm_free_all (void)
{
  struct chunk *c, *nextc;

  for (c = IMM.head; c; c = nextc)
    {
      nextc = c->next;
      free (c->internal_id);
      free (c);
    }
  IMM.count = 0;
  IMM.malloc_size = 0;
  IMM.head = NULL;
  IMM.tail = NULL;
}

size_t
imm_get_malloc_size (void)
{
  return IMM.malloc_size;
}

size_t
imm_get_largest_size (void)
{
  return IMM.largest_size;
}

size_t
imm_get_chunk_size (void *ptr)
{
  struct chunk *c;

  if (ptr == NULL)
    return 0;

  for (c = IMM.head; c; c = c->next)
    {
      if (c->external_id == ptr)
	return c->size;
    }

  imm_message ("couldn't get the size of unregistered chunkID %p", ptr);
  return 0;
}

/*
  Test the memory chunks.
*/

void
imm_test_chunk (void *ptr)
{
  register int i;
  struct chunk *c;

  if (ptr == NULL)
    return;

  for (c = IMM.head; c; c = c->next)
    {
      if (c->external_id == ptr)
	{
	  ptr = c->internal_id;
	  for (i = 0; i < IMM_EXTRA_ZONE; i++, ptr++)
	    {
	      if (*(char *)ptr != 'A')
		{
		  imm_message ("memory corruption at %p, chunkID %p",
			       ptr, c->external_id);
		  abort ();
		}
	    }
	  ptr += c->size;
	  for (i = 0; i < IMM_EXTRA_ZONE; i++, ptr++)
	    {
	      if (*(char *)ptr != 'Z')
		{
		  imm_message ("memory corruption at %p, chunkID %p",
			       ptr, c->external_id);
		  abort ();
		}
	    }
	  return;
	}
    }
  imm_message ("couldn't test unregistered chunkID %p", ptr);
}

static void
_imm_test_registered_chunk (void *ptr, void *external_id,
			    size_t size)
{
  register int i;
  for (i = 0; i < IMM_EXTRA_ZONE; i++, ptr++)
    {
      if (*(char *)ptr != 'A')
	{
	  imm_message ("memory corruption at %p, chunkID %p",
		       ptr, external_id);
	  abort ();
	}
    }
  ptr += size;
  for (i = 0; i < IMM_EXTRA_ZONE; i++, ptr++)
    {
      if (*(char *)ptr != 'Z')
	{
	  imm_message ("memory corruption at %p, chunkID %p",
		       ptr, external_id);
	  abort ();
	}
    }
}

void
imm_test_all_chunks (void)
{
  struct chunk *c;
  for (c = IMM.head; c; c = c->next)
    {
      _imm_test_registered_chunk (c->internal_id,
				  c->external_id,
				  c->size);
    }
}

/*
  IMM supporting functions.
*/

static FILE *
_imm_get_output (void)
{
  if (IMM_env.output)
    return IMM_env.output;
  else
    return stderr;
}

void
imm_set_output (FILE *output)
{
  if (output)
    IMM_env.output = output;
}

void
imm_logging_off (void)
{
  IMM_env.logging = OFF;
}

void
imm_logging_on (void)
{
  IMM_env.logging = ON;
}

void
imm_verbose_off (void)
{
  IMM_env.verbose = OFF;
}

void
imm_verbose_on (void)
{
  IMM_env.verbose = ON;
}

void
imm_message (const char *fmt, ...)
{
  va_list arglist;
  FILE *output;
  char txt[256];

  if (IMM_env.logging == OFF)
    return;

  output = _imm_get_output ();

  va_start (arglist, fmt);
  vsnprintf (txt, 255, fmt, arglist);
  va_end (arglist);

#ifdef NOGETPID
  fputs ("IMM > ", output);
#else
  fprintf (output, "IMM [%d] > ", (int) getpid ());
#endif /* NOGETPID */

  fputs (txt, output);
  putc ('\n', output);
}

static void
_imm_list_registered_chunks (void)
{
  size_t i = 1;
  struct chunk *c;
  for (c = IMM.head; c; c = c->next)
    {
      imm_message ("%lu) chunkID: %p (size %luB)",
		   i++, c->external_id, c->size);
    }
}

void
imm_summary (int mode)
{
  if (IMM.head == NULL)
    {
      imm_message ("no registered chunks");
      return;
    }

  if (mode)
    _imm_list_registered_chunks ();

  imm_message ("count: %lu, malloc size: %luB + %luB IMM",
	       IMM.count, IMM.malloc_size,
	       IMM.count * (sizeof (struct chunk) + 2*IMM_EXTRA_ZONE));
}

/* EOF */

