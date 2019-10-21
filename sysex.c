/* ----
 * ---- file   : sysex.c
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
 * ---- changed: 01Aug2014, 02Aug2014, 04Aug2014
 * ----
 * ----
 */

#include "types.h"
#include "debug.h"
#include "error.h"
#include "sysex.h"


/* ---------------------------------------------------------------------------- ar_sysex_meta_get_request_id */
sU8 ar_sysex_meta_get_request_id(const ar_sysex_meta_t *_meta) {
   sU8 r;

   if(_meta->obj_nr > 127)
   {
      /* Request workbuffer ("X") */
      r = AR_SYSEX_REQUESTX_ID_BASE + _meta->obj_type;
   }
   else
   {
      r = AR_SYSEX_REQUEST_ID_BASE + _meta->obj_type;
   }

   return r;
}

/* ---------------------------------------------------------------------------- ar_sysex_request */
ar_error_t ar_sysex_request(sU8 *_dstBuf, const ar_sysex_meta_t *_meta) {
   ar_error_t ret;

   if( (_meta->obj_type >= AR_TYPE_KIT) &&  (_meta->obj_type <= AR_TYPE_GLOBAL) )
   {
      _dstBuf[ 0] = 0xF0u;
      _dstBuf[ 1] = 0x00u;
      _dstBuf[ 2] = 0x20u;
      _dstBuf[ 3] = 0x3Cu;
      _dstBuf[ 4] = 0x07u;
      _dstBuf[ 5] = (_meta->dev_id & 15u);
      _dstBuf[ 6] = ar_sysex_meta_get_request_id(_meta);
      _dstBuf[ 7] = _meta->container_version.b.hi;
      _dstBuf[ 8] = _meta->container_version.b.lo;
      _dstBuf[ 9] = (_meta->obj_nr & 127u);
      _dstBuf[10] = 0x00u;
      _dstBuf[11] = 0x00u;
      _dstBuf[12] = 0x00u;
      _dstBuf[13] = 0x05u;
      _dstBuf[14] = 0xF7u;

      ret = AR_ERR_OK;
   }
   else
   {
      ret = AR_ERR_INVALID_OBJ_TYPE;
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sysex_read_next_byte */
ar_error_t ar_sysex_read_next_byte(const sU8 **_bufPtr, sU32 *_bufSize, sU8 *_retByte) {
   ar_error_t ret;
   const sU8 *b = *_bufPtr;
   sU32 sz = *_bufSize;

   *_retByte = 0xFFu;

   for(;;)
   {
      if(_bufSize > 0)
      {
         sU8 c = *b++;
         sz--;

         if(c < 0xF8u)
         {
            if(0xF7u == c)
            {
               /* End of sysex message */
               ret = AR_ERR_END_OF_MSG;
               break;
            }
            else
            {
               if(c <= 0x7F)
               {
                  /* Regular sysex message byte */
                  *_retByte = c;
                  ret = AR_ERR_OK;
                  break;
               }
               else
               {
                  /* Premature start of next regular MIDI message. Abort sysex. */
                  ret = AR_ERR_ABORT;
                  
                  /* Rewind */
                  b--;
                  sz++;

                  break;
               }
            }
         }
         else
         {
            /* System realtime message, skip */
         }
      }
      else
      {
         ret = AR_ERR_SHORT_READ;
         break;
      }
   }

   *_bufPtr  = b;
   *_bufSize = sz;
   
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sysex_parse_dump_header */
ar_error_t ar_sysex_parse_dump_header(const sU8**_srcBuf, sU32 *_srcBufSize, ar_sysex_meta_t *_retMeta) {
   ar_error_t ret;
   sU8 c;

   if(0xF0u == (*_srcBuf)[0])
   {
      (*_srcBuf)++;
      (*_srcBufSize)--;

      ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
      if(AR_ERR_OK == ret)
      {
         if(0 == c)  /* check extended manufacturer id */
         {
            ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
            if(AR_ERR_OK == ret)
            {
               if(AR_ELEKTRON_MANUFACTURER_ID_1 == c)
               {
                  ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
                  if(AR_ERR_OK == ret)
                  {
                     if(AR_ELEKTRON_MANUFACTURER_ID_2 == c)
                     {
                        ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
                        if(AR_ERR_OK == ret)
                        {
                           if(AR_PRODUCT_ID == c)
                           {
                              /* Read device id */
                              ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
                              if(AR_ERR_OK == ret)
                              {
                                 _retMeta->dev_id = c;

                                 /* Read message type */
                                 ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
                                 if(AR_ERR_OK == ret)
                                 {
                                    if( 
                                       ((c >= AR_SYSEX_DUMP_ID_KIT) && (c <= AR_SYSEX_DUMP_ID_GLOBAL)) ||
                                       ((c >= AR_SYSEX_DUMPX_ID_KIT) && (c <= AR_SYSEX_DUMPX_ID_GLOBAL))
                                        )
                                    {
                                       sU8 msgType = c;

                                       if(c >= AR_SYSEX_DUMPX_ID_KIT)
                                       {
                                          _retMeta->obj_type = (c - AR_SYSEX_DUMPX_ID_BASE);
                                       }
                                       else
                                       {
                                          _retMeta->obj_type = (c - AR_SYSEX_DUMP_ID_BASE);
                                       }

                                       /* Read container version hi/major */
                                       ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
                                       if(AR_ERR_OK == ret)
                                       {
                                          _retMeta->container_version.b.hi = c;

                                          /* Read container version lo/minor */
                                          ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
                                          if(AR_ERR_OK == ret)
                                          {
                                             _retMeta->container_version.b.lo = c;

                                             /* Read object number */
                                             ret = ar_sysex_read_next_byte(_srcBuf, _srcBufSize, &c);
                                             if(AR_ERR_OK == ret)
                                             {
                                                if(msgType >= AR_SYSEX_DUMPX_ID_KIT)
                                                {
                                                   /* RAM object */
                                                   _retMeta->obj_nr = c + 128u;
                                                }
                                                else
                                                {
                                                   _retMeta->obj_nr = c;
                                                }

                                                /* Succeeded */
                                                ret = AR_ERR_OK;
                                             }
                                          }
                                       }
                                    }
                                    else
                                    {
                                       ret = AR_ERR_INVALID_DUMP_MSG_ID;
                                    }
                                 }
                              }
                           }
                           else
                           {
                              ret = AR_ERR_INVALID_PRODUCT_ID;
                           }
                        }
                     }
                     else
                     {
                        ret = AR_ERR_INVALID_MANUFACTURER_ID;
                     }
                  }
               }
               else
               {
                  ret = AR_ERR_INVALID_MANUFACTURER_ID;
               }
            }
         }
         else
         {
            ret = AR_ERR_INVALID_MANUFACTURER_ID;
         }
      }
   }
   else
   {
      ret = AR_ERR_NOT_A_SYSEX_MSG;
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sysex_get_size */
ar_error_t ar_sysex_get_size(const sU8 *_srcBuf, sU32 _srcBufSize, sU32 *_retMsgSize) {
   ar_error_t ret;
   const sU8 *sb = _srcBuf;
   sU32 sbsz = _srcBufSize;

   /* Skip sysex message start (0xF0) */
   sb++;
   sbsz--;

   *_retMsgSize = 1;
   
   for(;;)
   {
      sU8 c;

      ret = ar_sysex_read_next_byte(&sb, &sbsz, &c);
      if(AR_ERR_OK == ret)
      {
         (*_retMsgSize)++;

         /* Continue until end of message is found */
      }
      else
      {
         break;
      }
   }

   if(AR_ERR_END_OF_MSG == ret)
   {
      (*_retMsgSize)++; /* count in 0xF7 message terminator */

      /* Succeeded */
      ret = AR_ERR_OK;
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sysex_decode */
void ar_sysex_decode(sU8 *_dst, const sU8**_src, sU32 *_srcSize, sU32 _numSrcBytes, s_u16_t *_retChksum) {
   
   sU16 chksum = 0u;

   sUI pkbNr = 0u;  /* 0..7 */

   sU8 msbs = 0u;  /* (note) must init to zero to prevent VS debug runtime error */

   while(_numSrcBytes > 0u)
   {
      if(0u == pkbNr)
      {
         (void)ar_sysex_read_next_byte(_src, _srcSize, &msbs);

         chksum += msbs;
      }
      else
      {
         sU8 c;

         (void)ar_sysex_read_next_byte(_src, _srcSize, &c);

         chksum += c;

         *_dst++ = c | (msbs & 0x80u);
      }
      
      msbs <<= 1;
      pkbNr = (pkbNr + 1) & 7u;
      _numSrcBytes--;
   }

   S_U14_SET(*_retChksum, chksum);
}

/* ---------------------------------------------------------------------------- ar_sysex_encode */
void ar_sysex_encode(sU8 *_dst, const sU8 *_src, sU32 _srcSize, s_u16_t *_retChksum) {
   sU16 chksum = 0u;
   sUI pkbNr = 0u;
   sU8 msbs;

#ifdef AR_DEBUG
   sU8 *dstOrig = _dst;
   sU32 srcSizeOrig = _srcSize;
#endif

   _dst++;

   while(_srcSize > 0u)
   {
      sU8 c = *_src++;

      if(0u == pkbNr)
      {
         msbs = (c & 0x80u) >> 1;
      }
      else
      {
         msbs |= (c & 0x80u) >> (1u + pkbNr);
      }

      *_dst++ = (c & 127u);

      chksum += (c & 127u);

      pkbNr++;

      if(7u == pkbNr)
      {
         chksum += msbs;
         _dst[-8] = msbs;
         pkbNr    = 0u;
         _dst++;
      }

      _srcSize--;
   }

   /* Finish last (partial) data packet */
   if(pkbNr > 0)
   {
      _dst[-(sSI)(pkbNr + 1u)] = msbs;
      chksum += msbs;
   }
#ifdef AR_DEBUG
   else
   {
      _dst--;
   }
#endif

#ifdef AR_DEBUG
   Dprintf("[dbg] ar_sysex_encode: encoded %u raw bytes to %u syx bytes\n", srcSizeOrig, (sUI)(_dst - dstOrig));
#endif

   S_U14_SET(*_retChksum, chksum);
}

/* ---------------------------------------------------------------------------- ar_sysex_to_raw */
ar_error_t ar_sysex_to_raw(sU8             *_dstBuf,
                           const sU8      **_srcBuf,
                           sU32            *_srcBufSize,
                           sU32            *_retRawBufSize,
                           ar_sysex_meta_t *_meta
                           ) {
   ar_error_t ret;
   const sU8 *sb = *_srcBuf;
   sU32 sbsz = *_srcBufSize;

   ret = ar_sysex_parse_dump_header(&sb, &sbsz, _meta);

   if(AR_ERR_OK == ret)
   {
      sU32 syxMsgSz; /* num valid sysex msg bytes, excluding RT messages */

      /* Determine sysex message size */
      ret = ar_sysex_get_size(*_srcBuf, *_srcBufSize, &syxMsgSz);

      if(AR_ERR_OK == ret)
      {
         sU32 syxDatSz = (syxMsgSz - 10u/*header*/ - 2u/*chksum*/ - 2u/*data_size*/ - 1u/*0xF7*/);
         sU32 rawDatSz;
         sU32 fullPkgSz = syxDatSz;
         sU32 partialPkgSz;

         fullPkgSz = (fullPkgSz >> 3) << 3;
         partialPkgSz = (syxDatSz - fullPkgSz);

         rawDatSz = (fullPkgSz >> 3) * 7u;

         if(partialPkgSz > 0u)
         {
            rawDatSz += (partialPkgSz - 1u);
         }

         if(NULL != _retRawBufSize)
         {
            *_retRawBufSize = rawDatSz;
         }

         Dprintf("[dbg] ar_sysex_to_raw: syxMsgSz=%u\n", syxMsgSz);
         Dprintf("[dbg] ar_sysex_to_raw: syxDatSz=%u\n", syxDatSz);

         if(NULL != _dstBuf)
         {
            sU8 c;
            s_u16_t chksum;

            /* Decode to raw bytes */
            ar_sysex_decode(_dstBuf, &sb, &sbsz, syxDatSz, &_meta->chksum);

            /* Read checksum */
            (void)ar_sysex_read_next_byte(&sb, &sbsz, &chksum.b.hi);
            (void)ar_sysex_read_next_byte(&sb, &sbsz, &chksum.b.lo);

            /* Read data size */
            (void)ar_sysex_read_next_byte(&sb, &sbsz, &_meta->data_size.b.hi);
            (void)ar_sysex_read_next_byte(&sb, &sbsz, &_meta->data_size.b.lo);

            /* Read sysex terminator (0xF7) */
            (void)ar_sysex_read_next_byte(&sb, &sbsz, &c);

            Dprintf("[dbg] ar_sysex_to_raw:  syx chksum= %08x %08x\n", chksum.b.hi, chksum.b.lo);
            Dprintf("[dbg] ar_sysex_to_raw: calc chksum= %08x %08x\n", _meta->chksum.b.hi, _meta->chksum.b.lo);
            Dprintf("[dbg] ar_sysex_to_raw: syx data size = 0x%08x 0x%08x (0x%04x)\n", _meta->data_size.b.hi, _meta->data_size.b.lo, S_U14_GET(_meta->data_size));

            *_srcBuf     = sb;
            *_srcBufSize = sbsz;

            ret = AR_ERR_OK;
         }
      }
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sysex_meta_is_valid */
ar_error_t ar_sysex_meta_is_valid(const ar_sysex_meta_t *_meta) {
   ar_error_t ret;

   if(NULL != _meta)
   {
      sU8 objNr = (_meta->obj_nr & 127u);  /* mask out RAM flag */

      ret = AR_ERR_OK;

      switch(_meta->obj_type)
      {
         default:
            ret = AR_ERR_INVALID_OBJ_TYPE;
            break;

         case AR_TYPE_KIT:
            if(objNr >= AR_NUM_KITS)
            {
               ret = AR_ERR_INVALID_OBJ_NR;
            }
            break;

         case AR_TYPE_SOUND:
            if(objNr >= AR_NUM_SOUNDS)
            {
               ret = AR_ERR_INVALID_OBJ_NR;
            }
            break;

         case AR_TYPE_PATTERN:
            if(objNr >= AR_NUM_PATTERNS)
            {
               ret = AR_ERR_INVALID_OBJ_NR;
            }
            break;

         case AR_TYPE_SONG:
            if(objNr >= AR_NUM_SONGS)
            {
               ret = AR_ERR_INVALID_OBJ_NR;
            }
            break;

         case AR_TYPE_SETTINGS:
            if(objNr >= AR_NUM_SETTINGS)
            {
               ret = AR_ERR_INVALID_OBJ_NR;
            }
            break;

         case AR_TYPE_GLOBAL:
            if(objNr >= AR_NUM_GLOBALS)
            {
               ret = AR_ERR_INVALID_OBJ_NR;
            }
            break;
      }
   }
   else
   {
      ret = AR_ERR_NULLPTR;
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sysex_meta_get_dump_id */
sU8 ar_sysex_meta_get_dump_id(const ar_sysex_meta_t *_meta) {
   sU8 dumpId = _meta->obj_type;

   if(_meta->obj_nr >= 128u)
   {
      /* RAM object */
      dumpId += AR_SYSEX_DUMPX_ID_BASE;
   }
   else
   {
      /* Flash object */
      dumpId += AR_SYSEX_DUMP_ID_BASE;
   }

   return dumpId;
}

/* ---------------------------------------------------------------------------- ar_sysex_meta_get_object_nr */
sU8 ar_sysex_meta_get_object_nr(const ar_sysex_meta_t *_meta) {

   /* Mask out RAM flag */
   return (_meta->obj_nr & 127u);
}

/* ---------------------------------------------------------------------------- ar_raw_to_sysex */
ar_error_t ar_raw_to_sysex(sU8                   *_dstBuf,
                           const sU8             *_srcBuf,
                           sU32                   _srcBufSize,
                           sU32                  *_retSyxBufSize,
                           const ar_sysex_meta_t *_meta
                           ) {
   ar_error_t ret;
   sU32 syxMsgSz;
   sU32 syxDatSz;
   s_u16_t chksum;

   ret = ar_sysex_meta_is_valid(_meta);

   if(AR_ERR_OK == ret)
   {
      sU32 partialPkgSz;

      syxMsgSz = 10u/*header*/ + 2u/*chksum*/ + 2u/*data_size*/ + 1u/*0xF7*/;
      
      syxDatSz = ( (_srcBufSize/* + 6u*/) / 7u ) << 3;  /* total size of data packets (including padding) */

      partialPkgSz = (_srcBufSize % 7);

      if(partialPkgSz > 0u)
      {
         syxDatSz += 1u + partialPkgSz;
      }
      
      if(NULL != _dstBuf)
      {
         _dstBuf[0] = 0xF0u;
         _dstBuf[1] = 0x00u;  /* extended manufacturer id */
         _dstBuf[2] = AR_ELEKTRON_MANUFACTURER_ID_1;
         _dstBuf[3] = AR_ELEKTRON_MANUFACTURER_ID_2;
         _dstBuf[4] = AR_PRODUCT_ID;
         _dstBuf[5] = _meta->dev_id;
         _dstBuf[6] = ar_sysex_meta_get_dump_id(_meta);
         _dstBuf[7] = _meta->container_version.b.hi;
         _dstBuf[8] = _meta->container_version.b.lo;
         _dstBuf[9] = ar_sysex_meta_get_object_nr(_meta);

         _dstBuf += 10u;

         /* Write encoded raw data bytes */
         ar_sysex_encode(_dstBuf, _srcBuf, _srcBufSize, &chksum);
         
         Dprintf("[dbg] ar_raw_to_sysex: chksum= 0x%08x 0x%08x\n", chksum.b.hi, chksum.b.lo);

         _dstBuf += syxDatSz;

         /* Write checksum */
         _dstBuf[0] = chksum.b.hi;
         _dstBuf[1] = chksum.b.lo;
         _dstBuf += 2;

         /* Write the data size */
         S_U14_SET(*((s_u16_t*)_dstBuf), syxDatSz + 2u/*chksum*/ + 2u/*data_size*/ + 1u/*0xF7*/);
         _dstBuf += 2;

         /* End of sysex message */
         _dstBuf[0] = 0xF7u;
      }
      
      if(NULL != _retSyxBufSize)
      {
         *_retSyxBufSize = (syxMsgSz + syxDatSz);
      }
      
      ret = AR_ERR_OK;
   }

   return ret;
}
