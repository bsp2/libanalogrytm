/* ----
 * ---- file   : error.h
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
 * ---- changed: 01Aug2014, 02Aug2014, 04Aug2014, 28Feb2016, 21Aug2017
 * ----
 * ----
 */

#ifndef __AR_ERROR_H__
#define __AR_ERROR_H__

#include "cplusplus_begin.h"


/* library error codes */
typedef enum {
   AR_ERR_OK                      =  0,

   AR_ERR_NOT_A_SYSEX_MSG         =  1,
   AR_ERR_SHORT_READ              =  2,  /* srcbuffer too small */
   AR_ERR_END_OF_MSG              =  3,  /* found 0xF7 terminator */
   AR_ERR_ABORT                   =  4,  /* premature end of sysex message */
   AR_ERR_INVALID_MANUFACTURER_ID =  5,  /* wrong manufacturer id */
   AR_ERR_INVALID_PRODUCT_ID      =  6,  /* wrong product id */
   AR_ERR_INVALID_DUMP_MSG_ID     =  7,  /* invalid dump message id */
   AR_ERR_INVALID_OBJ_TYPE        =  8,  /* invalid object type */
   AR_ERR_CHKSUM                  =  9,  /* checksum error */
   AR_ERR_NULLPTR                 = 10,  /* unexpected NULL pointer */
   AR_ERR_INVALID_OBJ_NR          = 11,  /* invalid object number (out of range) */
   AR_ERR_NOT_A_PATTERN           = 12,  /* trying to convert syx that does not contain pattern data */
   AR_ERR_NOT_A_KIT               = 13,  /* trying to convert syx that does not contain kit data */
   AR_ERR_NOT_A_SOUND             = 14,  /* trying to convert syx that does not contain sound data */

   NUM_AR_ERROR_CODES
} ar_error_t;


#include "cplusplus_end.h"

#endif /* __AR_ERROR_H__ */
