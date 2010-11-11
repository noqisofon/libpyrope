#ifndef pyrope__w32_h
#define pyrope__w32_h

#include "config/pyrope_prefix.h"

#include <cast.h>
#include <garnet/garnet.h>

#include <sys/types.h>

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>


#ifdef _MSC_VER
typedef     int                 ssize_t;
typedef     long long           offset_t;
#endif  /* _MSC_VER */


#endif  /* pyrope__w32_h */
