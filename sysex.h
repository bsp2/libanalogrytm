/* ----
 * ---- file   : sysex.h
 * ---- author : bsp, void (joint rev.eng efforts)
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
 * ---- changed: 30Jul2014, 01Aug2014, 02Aug2014, 04Aug2014
 * ----
 * ----
 */

#ifndef __AR_SYSEX_H__
#define __AR_SYSEX_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


/*
 *
 ** Manufacturer and product id
 *
 *   Elektron devices use an extended 3 byte manufacturer id (0x00 0x20 0x3c).
 *
 */
#define AR_ELEKTRON_MANUFACTURER_ID_1  (0x20u)
#define AR_ELEKTRON_MANUFACTURER_ID_2  (0x3Cu)

#define AR_PRODUCT_ID  (0x07u)


/*
 *
 ** Sysex dump ids
 *
 */
typedef enum {
   AR_TYPE_KIT      = 0,
   AR_TYPE_SOUND    = 1,
   AR_TYPE_PATTERN  = 2,
   AR_TYPE_SONG     = 3,
   AR_TYPE_SETTINGS = 4,
   AR_TYPE_GLOBAL   = 5,

   PAD_AR_TYPE
} ar_sysex_id_t;


#define AR_SYSEX_DUMP_ID_BASE      (0x52u)
#define AR_SYSEX_DUMPX_ID_BASE     (0x58u)

#define AR_SYSEX_REQUEST_ID_BASE   (0x62u)
#define AR_SYSEX_REQUESTX_ID_BASE  (0x68u)


/*
 *
 ** Per project limits
 *
 */
#define AR_NUM_KITS      (128u)
#define AR_NUM_SOUNDS    (128u)
#define AR_NUM_PATTERNS  (128u)
#define AR_NUM_SONGS     ( 16u)
#define AR_NUM_SETTINGS  (  1u)
#define AR_NUM_GLOBALS   (  4u)  /* global slots / settings */

#define AR_NUM_STEPS_PER_PATTERN  (64u)


/*
 *
 ** Sysex dump ids
 *
 */
typedef enum {
   AR_SYSEX_DUMP_ID_KIT      = (AR_SYSEX_DUMP_ID_BASE + AR_TYPE_KIT),      /* 0x52 */
   AR_SYSEX_DUMP_ID_SOUND    = (AR_SYSEX_DUMP_ID_BASE + AR_TYPE_SOUND),    /* 0x53 */
   AR_SYSEX_DUMP_ID_PATTERN  = (AR_SYSEX_DUMP_ID_BASE + AR_TYPE_PATTERN),  /* 0x54 */
   AR_SYSEX_DUMP_ID_SONG     = (AR_SYSEX_DUMP_ID_BASE + AR_TYPE_SONG),     /* 0x55 */
   AR_SYSEX_DUMP_ID_SETTINGS = (AR_SYSEX_DUMP_ID_BASE + AR_TYPE_SETTINGS), /* 0x56 */
   AR_SYSEX_DUMP_ID_GLOBAL   = (AR_SYSEX_DUMP_ID_BASE + AR_TYPE_GLOBAL),   /* 0x57 */

   AR_SYSEX_DUMPX_ID_KIT      = (AR_SYSEX_DUMPX_ID_BASE + AR_TYPE_KIT),      /* 0x58 */
   AR_SYSEX_DUMPX_ID_SOUND    = (AR_SYSEX_DUMPX_ID_BASE + AR_TYPE_SOUND),    /* 0x59 */
   AR_SYSEX_DUMPX_ID_PATTERN  = (AR_SYSEX_DUMPX_ID_BASE + AR_TYPE_PATTERN),  /* 0x5A */
   AR_SYSEX_DUMPX_ID_SONG     = (AR_SYSEX_DUMPX_ID_BASE + AR_TYPE_SONG),     /* 0x5B */
   AR_SYSEX_DUMPX_ID_SETTINGS = (AR_SYSEX_DUMPX_ID_BASE + AR_TYPE_SETTINGS), /* 0x5C */
   AR_SYSEX_DUMPX_ID_GLOBAL   = (AR_SYSEX_DUMPX_ID_BASE + AR_TYPE_GLOBAL),   /* 0x5D */

   PAD_AR_SYSEX_DUMP_ID
} ar_sysex_dump_id_t;



/*
 *
 ** Sysex request ids
 *
 */
typedef enum {
   AR_SYSEX_REQUEST_ID_KIT      = (AR_SYSEX_REQUEST_ID_BASE + AR_TYPE_KIT),        /* 0x62 */
   AR_SYSEX_REQUEST_ID_SOUND    = (AR_SYSEX_REQUEST_ID_BASE + AR_TYPE_SOUND),      /* 0x63 */
   AR_SYSEX_REQUEST_ID_PATTERN  = (AR_SYSEX_REQUEST_ID_BASE + AR_TYPE_PATTERN),    /* 0x64 */
   AR_SYSEX_REQUEST_ID_SONG     = (AR_SYSEX_REQUEST_ID_BASE + AR_TYPE_SONG),       /* 0x65 */
   AR_SYSEX_REQUEST_ID_SETTINGS = (AR_SYSEX_REQUEST_ID_BASE + AR_TYPE_SETTINGS),   /* 0x66 */
   AR_SYSEX_REQUEST_ID_GLOBAL   = (AR_SYSEX_REQUEST_ID_BASE + AR_TYPE_GLOBAL),     /* 0x67 */

   /* X = work buffer (potentially unsaved) */
   AR_SYSEX_REQUESTX_ID_KIT      = (AR_SYSEX_REQUESTX_ID_BASE + AR_TYPE_KIT),      /* 0x68 */
   AR_SYSEX_REQUESTX_ID_SOUND    = (AR_SYSEX_REQUESTX_ID_BASE + AR_TYPE_SOUND),    /* 0x69 */
   AR_SYSEX_REQUESTX_ID_PATTERN  = (AR_SYSEX_REQUESTX_ID_BASE + AR_TYPE_PATTERN),  /* 0x6A */
   AR_SYSEX_REQUESTX_ID_SONG     = (AR_SYSEX_REQUESTX_ID_BASE + AR_TYPE_SONG),     /* 0x6B */
   AR_SYSEX_REQUESTX_ID_SETTINGS = (AR_SYSEX_REQUESTX_ID_BASE + AR_TYPE_SETTINGS), /* 0x6C */
   AR_SYSEX_REQUESTX_ID_GLOBAL   = (AR_SYSEX_REQUESTX_ID_BASE + AR_TYPE_GLOBAL),   /* 0x6D */

   PAD_AR_SYSEX_REQUEST_ID
} ar_sysex_request_id_t;



#define AR_SYSEX_REQUEST_MSG_SZ  (15u)   /* F0 00 20 3c 07 00 <id> 01 01 <nr> 00 00 00 05 F7 */


/* Default sysex container version number */
#define AR_SYSEX_DEF_VERSION   (0x0101u)


#define AR_SYSEX_META_INIT(Xst, Xdev, Xobjtype, Xobjnr)      \
   S_U16_SET((Xst).container_version, AR_SYSEX_DEF_VERSION); \
   (Xst).dev_id   = Xdev; \
   (Xst).obj_type = Xobjtype; \
   (Xst).obj_nr   = Xobjnr


/*
 *
 ** Sysex meta data (library-specific)
 *
 */
typedef struct {
   s_u16_t container_version; /* currently [0x01 0x01] (OS 1.02c) */
   sU8     dev_id;            /* device id (0..15) */
   sU8     obj_type;          /* 'object' type id (pattern, kit, ..). See AR_TYPE_xxx */
   sU16    obj_nr;            /* 'object' number (e.g. pattern number). Range is type dependent.
                                 If obj_nr >= 128, the object is a RAM / workbuffer object ("X").
                               */
   s_u16_t chksum;
   s_u16_t data_size;         /* excluding header, including chksum+data_size fields */
} ar_sysex_meta_t;


/*
 * Calculate sysex request id by type id and object number.
 *
 *  Called by <ar_sysex_request>()
 *
 *  Arguments:
 *      _meta - See <ar_sysex_meta_t>
 *
 */
S_EXTERN sU8 ar_sysex_meta_get_request_id(const ar_sysex_meta_t *_meta);


/*
 * Check whether sysex dump_header is valid and extract meta/container information.
 *
 */
S_EXTERN ar_error_t ar_sysex_parse_dump_header(const sU8 **_srcBuf, sU32 *_srcBufSize, ar_sysex_meta_t *_retMeta);


/*
 * Check whether the meta information is valid (e.g. object type and object number range)
 *
 */
S_EXTERN ar_error_t ar_sysex_meta_is_valid(const ar_sysex_meta_t *_meta);


/*
 * Query the sysex dump id for the given object.
 *
 *  Returns:
 *      (AR_SYSEX_DUMP_ID_KIT  .. AR_SYSEX_DUMP_ID_GLOBAL)   (flash objects)
 *   or (AR_SYSEX_DUMPX_ID_KIT .. AR_SYSEX_DUMPX_ID_GLOBAL)  (RAM objects)
 *
 */
S_EXTERN sU8 ar_sysex_meta_get_dump_id(const ar_sysex_meta_t *_meta);


/*
 * Query the sysex object nr for the given object.
 *
 *  Returns:
 *   7bit object number (without RAM flag).
 *
 */
S_EXTERN sU8 ar_sysex_meta_get_object_nr(const ar_sysex_meta_t *_meta);




/*
 * Sysex request utility function.
 *
 *  Called by <ar_pattern_request>(), <ar_pattern_request_x>()
 *
 *  Arguments:
 *    _dstBuf - Where to place the sysex request message. Must be able to hold <AR_SYSEX_REQUEST_MSG_SZ> (15) bytes.
 *      _meta - Additional params like device id, type id, object number.
 *
 */
S_EXTERN ar_error_t ar_sysex_request(sU8 *_dstBuf, const ar_sysex_meta_t *_meta);


/*
 * Determine size of sysex dump.
 *
 *  This will seek until the end of the first sysex message found in the source buffer.
 *
 *  The source buffer must be a valid sysex buffer (i.e. ar_sysex_parse_dump_header() should be called to ensure that).
 *
 *  Arguments:
 *       _srcBuf - 7bit MIDI bytes (starting with 0xF0)
 *   _srcBufSize - Number of bytes available in the source buffer.
 *   _retMsgSize - Returns the size of the first sysex message in the buffer.
 *                  The returned size will include any realtime messages encountered while
 *                  scanning the source buffer.
 *
 *  Returns:
 *   AR_ERR_OK if end of message was found.
 *
 */
S_EXTERN ar_error_t ar_sysex_get_size(const sU8 *_srcBuf, sU32 _srcBufSize, sU32 *_retMsgSize);


/*
 * Return the next byte in the source buffer.
 *
 *  This will skip any realtime messages.
 *
 *  Arguments:
 *     bufPtr - Current buffer read pointer. Will be increased after reading bytes.
 *    bufSize - Remaining number of bytes in the buffer. Will be decreased after reading bytes.
 *    retByte - Returns the next MIDI byte (never a realtime message)
 *
 *  Returns:
 *   AR_ERR_OK or a read error code (see error.h)
 */
S_EXTERN ar_error_t ar_sysex_read_next_byte(const sU8 **_bufPtr, sU32 *_bufSize, sU8 *_retByte);


/*
 * Decode 7bit MIDI data packets to 8bit raw data.
 *
 *  (note) due to potential RT midi messages, the number of bytes read from 'src' may be larger than numSrcBytes.
 *
 */
S_EXTERN void ar_sysex_decode(sU8 *_dst, const sU8**_src, sU32 *_srcSize, sU32 _numSrcBytes, s_u16_t *_retChksum);


/*
 * Encode 8bit raw data to 7bit MIDI data packets.
 *
 */
S_EXTERN void ar_sysex_encode(sU8 *_dst, const sU8 *_src, sU32 _srcSize, s_u16_t *_retChksum);


/*
 * Convert sysex dump to raw 8bit data.
 *
 *  Arguments:
 *          _dstBuf - Where to place the raw 8bit data. If NULL, only query the buffer size (retRawBufSize).
 *          _srcBuf - 7bit MIDI bytes (starting with 0xF0)
 *      _srcBufSize - Number of bytes available in the source buffer.
 *   _retRawBufSize - Returns the number of raw 8bit data bytes.
 *            _meta - Returns additional information like device id, object type and number.
 *
 */
S_EXTERN ar_error_t ar_sysex_to_raw(sU8             *_dstBuf,
                                    const sU8      **_srcBuf,
                                    sU32            *_srcBufSize,
                                    sU32            *_retRawBufSize,
                                    ar_sysex_meta_t *_meta
                                    );


/*
 * Convert raw 8bit data to sysex message.
 *
 *  Arguments:
 *           _dstBuf - Where to place the 7bit MIDI sysex message data. If NULL, only query the buffer size (retSyxBufSize).
 *           _srcBuf - 8bit raw data
 *       _srcBufSize - Size of the raw buffer
 *    _retSyxBufSize - Return the number of sysex message bytes.
 *             _meta - Additional information like device id, object type and number.
 *
 */
S_EXTERN ar_error_t ar_raw_to_sysex(sU8                   *_dstBuf,
                                    const sU8             *_srcBuf,
                                    sU32                   _srcBufSize,
                                    sU32                  *_retSyxBufSize,
                                    const ar_sysex_meta_t *_meta
                                    );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_SYSEX_H__ */
