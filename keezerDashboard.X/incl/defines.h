/*
 * File:   defines.h
 * Author: jerdmann
 *
 * Created on October 14, 2015, 3:52 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p24Fxxxx.h>
#include <xc.h>

// shorthand types
typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned long       U32;
typedef unsigned long long  U64;
typedef signed char         I8;
typedef signed short        I16;
typedef signed long         I32;
typedef signed long long    I64;

#define MAX_U8  (0xff)
#define MAX_I8  (0x7f)
#define MIN_I8  (0x80)
#define MAX_U16 (0xffff)
#define MAX_I16 (0x7fff)
#define MIN_I16 (0x8000)
#define MAX_U32 (0xffffffff)
#define MAX_I32 (0x7fffffff)
#define MIN_I32 (0x80000000)
#define MAX_U64 (0xffffffffffffffff)
#define MAX_I64 (0x7fffffffffffffff)
#define MIN_I64 (0x8000000000000000)

#define FALSE 0
#define TRUE (!FALSE)

#define ARRAY_COUNT(n) (sizeof(n)/sizeof(n[0]))
#define ABS_DIFF(a,b) (((a)>=(b))?((a)-(b)):((b)-(a)))


#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */
