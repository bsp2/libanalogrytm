/* ----
 * ---- file   : types.h
 * ---- author : bsp
 * ---- legal  : Distributed under terms of the MIT LICENSE (MIT).
 * ----
 * ---- Permission is hereby granted, free of charge, to any person obtaining a copy
 * ---- of this software and associated documentation files (the "Software"), to deal
 * ---- in the Software without restriction, including without limitation the rights
 * ---- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * ---- copies of the Software, and to permit persons to whom the Software is
 * ---- furnished to do so, subject to the following conditions:
 * ----
 * ---- The above copyright notice and this permission notice shall be included in
 * ---- all copies or substantial portions of the Software.
 * ----
 * ---- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * ---- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * ---- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * ---- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * ---- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * ---- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * ---- THE SOFTWARE.
 * ----
 * ---- info   : This is part of the "libanalogrytm" package.
 * ----
 * ---- changed: 30Jul2014, 01Aug2014, 04Aug2014
 * ----
 * ----
 */

#ifndef __AR_TYPES_H__
#define __AR_TYPES_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


/* build system should define endianess, default is little endian */
#if !defined(S_BIG_ENDIAN) && !defined(S_LITTLE_ENDIAN)
#define S_LITTLE_ENDIAN defined
#endif


/* Determine C compiler */
#if defined(__GNUC__)
#undef HAVE_CC_GCC
#define HAVE_CC_GCC defined

#elif defined(_MSC_VER)
#undef HAVE_CC_MSVC
#define HAVE_CC_MSVC defined

#else
#undef HAVE_CC_UNKNOWN
#define HAVE_CC_UNKNOWN defined
#endif


/* Determine OS */
#if defined(__linux__)
#undef HAVE_OS_LINUX
#define HAVE_OS_LINUX defined

#elif defined(__CYGWIN32__)
#undef HAVE_OS_CYGWIN
#define HAVE_OS_CYGWIN defined

#elif defined(_WIN32) || defined(WIN32)
#undef HAVE_OS_WIN32
#define HAVE_OS_WIN32 defined

#else
#undef HAVE_OS_UNKNOWN
#define HAVE_OS_UNKNOWN defined
#endif


#ifndef LIBANALOGRYTM_SKIP_TYPEDEFS

typedef char                sChar; /* (note) system dependent: either signed or unsigned */
typedef unsigned char       sU8;
typedef signed char         sS8;
typedef unsigned short      sU16;
typedef signed short        sS16;
typedef unsigned int        sU32;
typedef unsigned int        sUI;
typedef signed int          sS32;
typedef signed int          sSI;
typedef unsigned long long  sU64;
typedef signed long long    sS64;
typedef sSI                 sBool;

typedef sU32                sFix; /* 1:15:16 fixed point */
typedef sUI                 sSize;
typedef sSI                 s_error_t;

typedef float               sF32;
typedef double              sF64;

#endif // LIBANALOGRYTM_SKIP_TYPEDEFS


#define S_TRUE   (1)
#define S_FALSE  (0)

#define S_ERR_OK (0)

#ifndef NULL
#define NULL  ((void*)0)
#endif

#define S_PI     (3.1415926f)
#define S_2PI    (6.2831853f)
#define S_PI2    (1.5707963f)
#define S_E      (2.7182818f)
#define S_SQRT2  (1.4142135f)


/* How to declare global functions and variables */
#define S_EXTERN  extern

/* Calling convention (empty = use compiler default) */
#define S_CALL
//#define S_CALL __cdecl

/* How to declare inline functions */
#define S_INLINE static inline


/* portable multi-byte structs
 *
 *  (note) the AR is big-endian
 */
typedef union {
   struct {
      sU8 hi;
      sU8 lo;
   } b;

   sU8 a[2];

   sU16 v; /* only access for RAM copies, endianess is undefined */
} s_u16_t;

#define S_U16_SET(Xu, Xu16) (Xu).b.lo = ((Xu16) & 255u); (Xu).b.hi = (sU8) ((Xu16) >> 8u)
#define S_U16_GET(Xu) ((sU16) ((Xu).b.lo | ((Xu).b.hi << 8)))
#define S_U14_SET(Xu, Xu14) (Xu).b.lo = ((Xu14) & 127u); (Xu).b.hi = ( ((Xu14) >> 7u) & 127u)
#define S_U14_GET(Xu) ((sU16) ((Xu).b.lo | ((((Xu).b.hi)&127u) << 7)))


#ifdef HAVE_CC_MSVC
#define Dsnprintf _snprintf
#else
#define Dsnprintf snprintf
#endif // HAVE_CC_MSVC


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_TYPES_H__ */
