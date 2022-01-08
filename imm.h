/*
   imm.h

   This file is part of IMM.
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

#ifndef _IMM_H
#define _IMM_H

#ifdef __cplusplus
extern "C" {
#endif

extern void *imm_malloc (size_t);
extern void *imm_calloc (size_t, size_t);
extern void *imm_realloc (void *, size_t);
extern void imm_free (void *);
extern void imm_free_all (void);
extern void imm_test_chunk (void *);
extern void imm_test_all_chunks (void);
extern size_t imm_get_malloc_size (void);
extern size_t imm_get_largest_size (void);
extern size_t imm_get_chunk_size (void *);

extern void imm_set_output (FILE *);
extern void imm_logging_off (void);
extern void imm_logging_on (void);
extern void imm_verbose_off (void);
extern void imm_verbose_on (void);
extern void imm_message (const char *, ...);
extern void imm_summary (int);

#ifdef __cplusplus
}
#endif

#endif /* not _IMM_H */

/* EOF */

