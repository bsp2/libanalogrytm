/* ----
 * ---- file   : sound.h
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
 * ---- changed: 21Aug2017
 * ----
 * ----
 */

#ifndef __AR_SOUND_H__
#define __AR_SOUND_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


#define AR_SOUND_SYX_SZ  (207)   /* SysEx size, including F0 / F7 */

#define AR_SOUND_SZ      (168)   /* Raw, decoded size */


/* (note) request sound workbuffers 0..11 ("SOUNDX") to retrieve track sounds 1..12 */

typedef struct { /* 0xA8 (168) bytes */

   sU8 __unknown_arr1[0xc];

   sU8 name[0xf];
   sU8 __pad_name;            /* @0x001B  (ASCIIZ?) */

   sU8 synth_param_1;         /* @0x001C  sdhard: level */
   sU8 __pad1;

   sU8 synth_param_2;         /* @0x001E  sdhard: tune  */
   sU8 __pad2;

   sU8 synth_param_3;         /* @0x0020  sdhard: dcy   */
   sU8 __pad3;

   sU8 synth_param_4;         /* @0x0022  sdhard: swd   */
   sU8 __pad4;

   sU8 synth_param_5;         /* @0x0024  sdhard: tic   */
   sU8 __pad5;

   sU8 synth_param_6;         /* @0x0026  sdhard: nod   */
   sU8 __pad6;

   sU8 synth_param_7;         /* @0x0028  sdhard: nol   */
   sU8 __pad7;

   sU8 synth_param_8;         /* @0x002A  sdhard: swt   */
   sU8 __pad8;

   sU8 sample_tune;           /* @0x002c  0x40=0, 0x41=+1, .. */
   sU8 __unused_pad9;         /* @0x002d */

   sU8 sample_fine_tune;      /* @0x002e  0x40=0, 0x41=+1, .. */
   sU8 __unused_pad10;        /* @0x002f */

   sU8 sample_nr;             /* @0x0030  0=off, 1..127
                                          (note) changing the sample also changes:
                                                  smp OFF->6:
                                                   off=48 (0x30) a=0x00 b=0x06
                                                   off=132 (0x84) a=0xff b=0x00
                                                   off=133 (0x85) a=0xff b=0x00
                                                   off=134 (0x86) a=0xff b=0x10
                                                   off=135 (0x87) a=0xff b=0xef
                                                   off=136 (0x88) a=0x00 b=0x2c
                                                   off=137 (0x89) a=0x00 b=0x6f
                                                   off=138 (0x8a) a=0x00 b=0xa8
                                                   off=139 (0x8b) a=0x00 b=0x07
                                                   off=142 (0x8e) a=0x00 b=0x52
                                                   off=143 (0x8f) a=0x00 b=0x4e
                                                   off=146 (0x92) a=0x00 b=0x12
                                                   off=147 (0x93) a=0x00 b=0x36
                              */
   sU8 __unused_pad11;        /* @0x0031 */

   sU8 sample_br;             /* @0x0032  */
   sU8 __unused_pad12;        /* @0x0033 */

   sU8 sample_start_offset;   /* @0x0034 */
   sU8 __unused_pad13;        /* @0x0035 */

   sU8 sample_end_offset;     /* @0x0036 */
   sU8 __unused_pad14;        /* @0x0037 */

   sU8 sample_loop_flag;      /* @0x0038  0x00=off, 0x01=on */
   sU8 __unused_pad15;        /* @0x0039 */

   sU8 sample_volume;         /* @0x003a */
   sU8 __unused_pad16;        /* @0x003b */

   sU8 flt_attack;            /* @0x003c */
   sU8 __unused_pad17;        /* @0x003d */

   sU8 flt_sustain;           /* @0x003e */
   sU8 __unused_pad18;        /* @0x003f */

   sU8 flt_decay;             /* @0x0040 */
   sU8 __unused_pad19;        /* @0x0041 */

   sU8 flt_release;           /* @0x0042 */
   sU8 __unused_pad20;        /* @0x0043 */

   sU8 flt_cutoff;            /* @0x0044 */
   sU8 __unused_pad21;        /* @0x0045 */

   sU8 flt_res;               /* @0x0046 */
   sU8 __unused_pad22;        /* @0x0047 */

   sU8 flt_type;              /* @0x0048 */
   sU8 __unused_pad23;        /* @0x0049 */

   sU8 flt_env;               /* @0x004a    64=0, 127=+63, 0=-64*/
   sU8 __unused_pad24;        /* @0x004b */

   sU8 amp_attack;            /* @0x004c */
   sU8 __unused_pad25;        /* @0x004d */

   sU8 amp_hold;              /* @0x004e */
   sU8 __unused_pad26;        /* @0x004f */

   sU8 amp_decay;             /* @0x0050 */
   sU8 __unused_pad27;        /* @0x0051 */

   sU8 amp_overdrive;         /* @0x0052 */
   sU8 __unused_pad28;        /* @0x0053 */

   sU8 amp_delay_send;        /* @0x0054 */
   sU8 __unused_pad29;        /* @0x0055 */

   sU8 amp_reverb_send;       /* @0x0056 */
   sU8 __unused_pad30;        /* @0x0057 */

   sU8 amp_pan;               /* @0x0058 */
   sU8 __unused_pad31;        /* @0x0059 */

   sU8 amp_volume;            /* @0x005a */
   sU8 __unused_pad32;        /* @0x005b */

   sU8 __unknown2;            /* @0x005c */
   sU8 __unknown3;            /* @0x005d */

   sU8 lfo_speed;             /* @0x005e */
   sU8 __unused_pad33;        /* @0x005f */

   sU8 lfo_multiplier;        /* @0x0060 */
   sU8 __unused_pad34;        /* @0x0061 */

   sU8 lfo_fade;              /* @0x0062  0x40=0 */
   sU8 __unused_pad35;        /* @0x0063 */

   sU8 lfo_dest;              /* @0x0064  0x29=none, 0x0=BDHD:Level, .. */
   sU8 __unused_pad36;        /* @0x0065 */

   sU8 lfo_wav;               /* @0x0066  0x0=tri, 0x1=sin, .. */
   sU8 __unused_pad37;        /* @0x0067 */

   sU8 lfo_start_phase;       /* @0x0068   */
   sU8 __unused_pad38;        /* @0x0069 */

   sU8 lfo_mode;              /* @0x006a  0x0=free, 0x1=trg, .. */
   sU8 __unused_pad39;        /* @0x006b */

   sU8 lfo_depth_msb;         /* @0x006c  */
   sU8 lfo_depth_lsb;         /* @0x006d  */

   sU8 def_note;              /* @0x006e  0x3c=0, 0x3d=+1, 0x3b=-1 (initially 0x00 == +0 ?!)
                                   (note) not used in sound dump ? (only in kit?!!)
                               */
   sU8 __unknown_arr2[0xd];   /* @0x006f..0x007B  (correct location of trig/vel/def_len/.. ?) */

   sU8 machine_type;          /* @0x007C   0:bdhard    1:bdclassic    2:sdhard     3:sdclassic
                                           4:          5:             6:           7:
                                           8:          9:            10:          11:
                                          12:         13:bd fm       14:sd fm     15:noise gen
                                          16:impulse  17:            18:          19:
                                          20:         21:bd plastic  22:bd silky  23:sd natural
                                          24:         25:            26:bd sharp  27:DISABLE
                              */

   sU8 __unknown_arr3[43 /*0xA8-0x7d*/];

} ar_sound_t;


/*
 * Create sound sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *  _patternNr - Determine pattern number. 0=A01, 1=A02, .. 16=B01, ..127=H15.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_sound_request(sU8 *_dstBuf, sU8 _devId, sU8 _patternNr);


/*
 * Create sound workbuffer sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_sound_request_x(sU8 *_dstBuf, sU8 _devId, sU8 _patternNr);


/*
 * Convert sound sysex dump (starting with 0xF0) to 'raw' 8bit data.
 *
 *  Arguments:
 *          _rawBuf - Destination buffer. Must be large enough to hold the decoded 'raw' 8bit data.
 *                     Pass NULL to query the required buffer size.
 *          _syxBuf - Source buffer that stores the encoded 7bit MIDI data (starting with 0xF0)
 *      _syxBufSize - Size of the source buffer (number of bytes)
 *   _retRawBufSize - If not NULL, returns the required size of the 'raw' 8bit data buffer.
 *         _retMeta - If not NULL, returns additional meta data like version / sound number.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_sound_syx_to_raw(sU8             *_rawBuf,
                                        const sU8       *_syxBuf,
                                        sU32             _syxBufSize,
                                        sU32            *_retRawBufSize,
                                        ar_sysex_meta_t *_meta
                                        );


/*
 * Convert 'raw' 8bit data to 7bit MIDI sysex data (starting with 0xF0).
 *
 *  Arguments:
 *          _syxBuf - Destination buffer. Must be large enough to hold the encoded 7bit MIDI sysex data.
 *                     Pass NULL to query the required buffer size.
 *          _rawBuf - Source buffer that stores the 'raw' 8bit data.
 *      _rawBufSize - Size of source buffer (number of bytes).
 *   _retSyxBufSize - If not NULL, returns the required size of the 7bit MIDI sysex data buffer.
 *            _meta - Determines sound number, format version(s). Must not be NULL.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_sound_raw_to_syx(sU8                   *_syxBuf,
                                        const sU8             *_rawBuf,
                                        sU32                   _rawBufSize,
                                        sU32                  *_retSyxBufSize,
                                        const ar_sysex_meta_t *_meta
                                        );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_SOUND_H__ */
