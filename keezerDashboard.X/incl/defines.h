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

typedef struct {
    union {
        U32 all;
        struct {
            U32 writeMuxRow:1;
            U32 enableMuxRow:1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
            U32 :1;
        };
    };
} event_flags;

//Mux Common
#define LOW_OIL     0x4000
#define LOW_FUEL    0x8000
#define SEGMENT_A   0x0001
#define SEGMENT_B   0x0002
#define SEGMENT_C   0x0004
#define SEGMENT_D   0x0008
#define SEGMENT_E   0x0010
#define SEGMENT_F   0x0020
#define SEGMENT_G   0x0040
#define SEGMENT_DP  0x0080

//Mux Row 0
#define FILL_4  0x0100
#define ABV_0   0x0200
#define ABV_3   0x0400
#define ABV_6   0x0800
#define ABV_9   0x1000

//Mux Row 1
#define FILL_3  0x0100
#define ABV_1   0x0200
#define ABV_4   0x0400
#define ABV_7   0x0800
#define ABV_10  0x1000

//Mux Row 2
#define FILL_2  0x0100
#define ABV_2   0x0200
#define ABV_5   0x0400
#define ABV_8   0x0800
#define ABV_11  0x1000

//Mux Row 3
#define FILL_1  0x0100
#define AUX_R   0x0200
#define AUX_M   0x0400
#define AUX_L   0x0800
#define HOT     0x1000

//Mux Row 4
#define COLON_T 0x0001
#define COLON_B 0x0002
#define FILL_0  0x0100
#define NOT_OK  0x0200
#define OK      0x0400

//Seven Segment bitmasks
#define DIGIT_DASH  (SEGMENT_G)
#define DIGIT_0     (SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F)
#define DIGIT_1     (SEGMENT_B|SEGMENT_C)
#define DIGIT_2     (SEGMENT_A|SEGMENT_B|SEGMENT_D|SEGMENT_E|SEGMENT_G)
#define DIGIT_3     (SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_G)
#define DIGIT_4     (SEGMENT_B|SEGMENT_C|SEGMENT_F|SEGMENT_G)
#define DIGIT_5     (SEGMENT_A|SEGMENT_C|SEGMENT_D|SEGMENT_F|SEGMENT_G)
#define DIGIT_6     (SEGMENT_A|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_7     (SEGMENT_A|SEGMENT_B|SEGMENT_C)
#define DIGIT_8     (SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_9     (SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_F|SEGMENT_G)
#define DIGIT_A     (SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_B     (SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F)
#define DIGIT_C     (SEGMENT_A|SEGMENT_D|SEGMENT_E|SEGMENT_F)
#define DIGIT_D     (SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_G)
#define DIGIT_E     (SEGMENT_A|SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_F     (SEGMENT_A|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_G     (SEGMENT_A|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F)
#define DIGIT_H     (SEGMENT_C|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_I     (SEGMENT_E|SEGMENT_F)
#define DIGIT_J     (SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E)
#define DIGIT_K     (SEGMENT_A|SEGMENT_C|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_L     (SEGMENT_D|SEGMENT_E|SEGMENT_F)
#define DIGIT_M     (SEGMENT_A|SEGMENT_C|SEGMENT_E)
#define DIGIT_N     (SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_E|SEGMENT_F)
#define DIGIT_O     (DIGIT_0)
#define DIGIT_P     (SEGMENT_A|SEGMENT_B|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_Q     (SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_F|SEGMENT_G)
#define DIGIT_R     (SEGMENT_A|SEGMENT_B|SEGMENT_E|SEGMENT_F)
#define DIGIT_S     (DIGIT_5)
#define DIGIT_T     (SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_U     (SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F)
#define DIGIT_V     (SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E)
#define DIGIT_W     (SEGMENT_B|SEGMENT_D|SEGMENT_F)
#define DIGIT_X     (SEGMENT_B|SEGMENT_C|SEGMENT_E|SEGMENT_F|SEGMENT_G)
#define DIGIT_Y     (SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_G)
#define DIGIT_Z     (SEGMENT_A|SEGMENT_B|SEGMENT_D|SEGMENT_G)
#define DIGIT_ALL   (DIGIT_8|SEGMENT_DP)


#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */
