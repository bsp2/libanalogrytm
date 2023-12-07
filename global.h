/* ----
 * ---- file   : global.h
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
 * ---- changed: 29Nov2023, 01Dec2023
 * ----
 * ----
 */

#ifndef __AR_GLOBAL_H__
#define __AR_GLOBAL_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


#define AR_GLOBAL_SYX_V5_SZ  (107)    /* SysEx size, including F0 / F7 (FW1.70) */
#define AR_GLOBAL_SYX_SZ  AR_GLOBAL_SYX_V5_SZ

#define AR_GLOBAL_V5_SZ   (80u)       /* Raw, decoded size (FW1.70) */
#define AR_GLOBAL_SZ AR_GLOBAL_V5_SZ  /* == sizeof(ar_global_t) */


/*
 *
 ** Global menu structure
 *
 *    0x4F(80) bytes (v5/FW1.70)
 *
 */
typedef struct {
   sU8 version[4];             /* @0x00..0x03  32 bit version number (0x00, 0x00, 0x00, 0x02) */

   /* Click Menu */
   sU8 click_active;           /* @0x04         0=OFF, 1=ON                                */
   sU8 click_time_sig_num;     /* @0x05         range=0..15 maps to 1..16 on device        */
   sU8 click_time_sig_den;     /* @0x06         0=1, 1=2, 2=4, 3=8, 4=16                   */
   sU8 pre_roll;               /* @0x07         0=OFF, range=0..15 maps to 1..16 on device */
   sU8 volume;                 /* @0x08         range=0..127                               */

   sU8 __unknown0x09_0x0A[2];  /* @?0x09..0x0A  Currently reads  0x40, 0x00 */

   /* Midi Channels Menu */
   sU8 auto_channel;           /* @0x0B         255=OFF  range=0..15  */
   sU8 track_channels[12];     /* @0x0C..0x17   255=OFF  range=0..15  */
   sU8 track_fx_channel;       /* @0x18         255=OFF  range=0..15  */
   sU8 prog_ch_in_channel;     /* @0x19         255=auto range=0..15  */
   sU8 prog_ch_out_channel;    /* @0x1A         255=auto range=0..15  */
   sU8 perf_channel;           /* @0x1B         255=OFF  range=0..15  */

   /* Midi Port Config Menu Part 1 */
   sU8 out_port_func;          /* @0x1C         0=MIDI, 1=DIN24, 2=DIN48               */
   sU8 thru_port_func;         /* @0x1D         0=MIDI, 1=DIN24, 2=DIN48               */
   sU8 input_from;             /* @0x1E         0=DISABLED, 1=MIDI, 2=USB. 3=MIDI+USB  */
   sU8 output_to;              /* @0x1F         0=DISABLED, 1=MIDI, 2=USB, 3=MIDI+USB  */
   sU8 param_output;           /* @0x20         0=NRPN, 1=CC                           */

   /* Midi Sync Menu */
   sU8 clock_receive;          /* @0x21         0=OFF, 1=ON */
   sU8 clock_send;             /* @0x22         0=OFF, 1=ON */
   sU8 transport_receive;      /* @0x23         0=OFF, 1=ON */
   sU8 transport_send;         /* @0x24         0=OFF, 1=ON */
   sU8 program_change_receive; /* @0x25         0=OFF, 1=ON */
   sU8 program_change_send;    /* @0x26         0=OFF, 1=ON */

   /* Midi Port Config Menu Part 2 */
   sU8 receive_notes;          /* @0x27         0=OFF, 1=ON */
   sU8 receive_cc_nrpn;        /* @0x28         0=OFF, 1=ON */

   /* I believe this is `TURBO SPEED` since it is the only one left in the menu. */
   /* But since I can not enable it without connecting a turbo speed capable MIDI interface I can not be sure.. */
   sU8 __unknown0x29;          /* ?@0x29        0=OFF, 1=ON */

   sU8 pad_dest;               /* @0x2A         0=INT, 1=INT+EXT, 2=EXT */
   sU8 pressure_dest;          /* @0x2B         0=INT, 1=INT+EXT, 2=EXT */
   sU8 encoder_dest;           /* @0x2C         0=INT, 1=INT+EXT        */
   sU8 mute_dest;              /* @0x2D         0=INT, 1=INT+EXT, 2=EXT */
   sU8 ports_output_channel;   /* @0x2E         0=AUTO CH, 1=TRK_CH     */

   /* Sequencer Config Menu Part 1 */
   sU8 kit_reload_on_chg;      /* @0x2F         0=OFF, 1=ON */
   sU8 quantize_live_rec;      /* @0x30         0=OFF, 1=ON */

   sU8 __unknown0x31;          /* ?@0x31        */

   /* Routing Menu Part 1 (the semantics are not discovered yet) */
   sU8 route_to_main_msb;      /* @?0x32        */
   sU8 route_to_main_lsb;      /* @?0x33        */
   sU8 send_to_fx_msb;         /* @?0x34        */
   sU8 send_to_fx_lsb;         /* @?0x35        */

   /* All zeros. It is suspicious since it is exactly 16 bytes long, maybe related to midi channels? */
   sU8 __unknown0x36_0x45[16]; /* @?0x36..0x45  */

   /* Sequencer Config Menu Part 2 */
   sU8 auto_trk_switch;        /* @0x46         0=OFF, 1=ON */

   /* Routing Menu Part 2 */
   sU8 usb_in;                 /* ?@0x47        (the semantics are not discovered yet) */
   sU8 usb_out;                /* ?@0x48        (the semantics are not discovered yet) */
   sU8 usb_to_main_db;         /* @0x49         0=0, 1=+6, 2=+12, 3=+18                */

   /* All zeros. */
   sU8 __unknown0x50_0x4F[6];  /* @?0x50..0x4F  */

} ar_global_t;


/*
 * Create global sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *  _globalSlot - Determine global slot. 0,1,2 or 3.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_global_request (sU8 *_dstBuf, sU8 _devId, sU8 _globalSlot);


/*
 * Create global workbuffer sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_global_request_x (sU8 *_dstBuf, sU8 _devId, sU8 _globalSlot);


/*
 * Convert global sysex dump (starting with 0xF0) to 'raw' 8bit data.
 *
 *  Arguments:
 *          _rawBuf - Destination buffer. Must be large enough to hold the decoded 'raw' 8bit data.
 *                     Pass NULL to query the required buffer size.
 *          _syxBuf - Source buffer that stores the encoded 7bit MIDI data (starting with 0xF0)
 *      _syxBufSize - Size of the source buffer (number of bytes)
 *   _retRawBufSize - If not NULL, returns the required size of the 'raw' 8bit data buffer.
 *         _retMeta - If not NULL, returns additional meta data like version / global slot.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_global_syx_to_raw (sU8             *_rawBuf,
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
 *            _meta - Determines global slot number, format version(s). Must not be NULL.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_global_raw_to_syx (sU8                   *_syxBuf,
                                          const sU8             *_rawBuf,
                                          sU32                   _rawBufSize,
                                          sU32                  *_retSyxBufSize,
                                          const ar_sysex_meta_t *_meta
                                          );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_GLOBAL_H__ */
