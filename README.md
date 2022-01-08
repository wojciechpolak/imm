Overview
========

IMM is a memory testing tool that not only allows developers
to find eventual memory leaks, but also helps to locate other
difficult to find errors in memory management, such as memory
overruns and memory block corruptions. The tool is designed
as a wrapper around the standard libc memory allocation
routines malloc, calloc, realloc and free, which makes it
easy to use in packages written in ANSI C and C++.

The package provides routines for inspecting the memory
allocation and displaying their contents via user-supplied
callback functions. The debugging hooks can be turned on and
off without the need of recompilation, thereby providing a
compromise between extensive debugging information and performance.

You are welcome to use IMM in your own programs, please see
the examples subdirectory or these other applications.

Disclaimer: This small tool was written in 2003.

License
=======

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
The complete text of the corresponding licence is included in
the file "COPYING.LIB".
