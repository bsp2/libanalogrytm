/* ----
 * ---- file   : global.c
 * ---- author : alisomay
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
 * ---- created: 28Nov2023
 * ---- changed: N/A
 * ----
 * ----
 */

// #define AR_DEBUG defined

#include "types.h"
#include "debug.h"
#include "error.h"
#include "sysex.h"
#include "global.h"

/* ---------------------------------------------------------------------------- ar_global_request */
ar_error_t ar_global_request(sU8 *_dstBuf, sU8 _devId, sU8 _globalSlot) {
   ar_sysex_meta_t meta;
   ar_error_t ret;

   AR_SYSEX_META_INIT(meta, _devId, AR_TYPE_GLOBAL, _globalSlot);

   ret = ar_sysex_request(_dstBuf, &meta);

   return ret;
}

/* ---------------------------------------------------------------------------- ar_global_request_x */
ar_error_t ar_global_request_x(sU8 *_dstBuf, sU8 _devId, sU8 _globalSlot) {
   ar_sysex_meta_t meta;
   ar_error_t ret;

   AR_SYSEX_META_INIT(meta, _devId, AR_TYPE_GLOBAL, (128u + (_globalSlot & 127u)));

   ret = ar_sysex_request(_dstBuf, &meta);

   return ret;
}

/* ---------------------------------------------------------------------------- ar_global_syx_to_raw */
ar_error_t ar_global_syx_to_raw(sU8             *_rawBuf,
                                const sU8       *_syxBuf,
                                sU32             _syxBufSize,
                                sU32            *_retRawBufSize,
                                ar_sysex_meta_t *_meta) {
   ar_error_t ret;
   sU32 datSz;
   ar_sysex_meta_t meta;

   ret = ar_sysex_to_raw(_rawBuf, &_syxBuf, &_syxBufSize, &datSz, &meta);

   Dprintf("xxx ar_global_syx_to_raw: syxSz=%u rawSz=%u  sizeof(global)=%lu\n", _syxBufSize, datSz, sizeof(ar_global_t));

   if(AR_ERR_OK == ret)
   {
      if(NULL != _retRawBufSize)
      {
         *_retRawBufSize = datSz;
      }

      if(NULL != _meta)
      {
         *_meta = meta;
      }

      if(AR_TYPE_GLOBAL == meta.obj_type)
      {
         /* Succeeded */
      }
      else
      {
         ret = AR_ERR_NOT_A_GLOBAL;
      }
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_global_raw_to_syx */
ar_error_t ar_global_raw_to_syx(sU8                   *_syxBuf,
                                const sU8             *_rawBuf,
                                sU32                   _rawBufSize,
                                sU32                  *_retSyxBufSize,
                                const ar_sysex_meta_t *_meta) {
   ar_error_t ret;

   if(NULL != _meta)
   {
      sU32 syxSz;

      ret = ar_raw_to_sysex(_syxBuf, _rawBuf, _rawBufSize, &syxSz, _meta);

      if(NULL != _retSyxBufSize)
      {
         *_retSyxBufSize = syxSz;
      }
   }
   else
   {
      ret = AR_ERR_NULLPTR;
   }

   return ret;
}
