/* ----
 * ---- file   : settings.h
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
 * ---- THE SOFTWARE. * ----
 * ---- info   : This is part of the "libanalogrytm" package.
 * ----
 * ---- created: 29Nov2023
 * ---- changed: 01Dec2023
 * ----
 * ----
 */

#ifndef __AR_SETTINGS_H__
#define __AR_SETTINGS_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


#define AR_SETTINGS_SYX_V5_SZ  (2401)    /* SysEx size, including F0 / F7 (FW1.70) */
#define AR_SETTINGS_SYX_SZ  AR_SETTINGS_SYX_V5_SZ

#define AR_SETTINGS_V5_SZ   (2087u)      /* Raw, decoded size (FW1.70) */
#define AR_SETTINGS_SZ AR_SETTINGS_V5_SZ /* == sizeof(ar_settings_t) */


/*
 *
 ** Settings structure
 *
 *    0x0827(2087) bytes (v5/FW1.70)
 *
 */
typedef struct {
   sU8 version[4];                       /* @0x0000..0x0003  32 bit version number (0x00, 0x00, 0x00, 0x03) */

   sU8 bpm_msb;                          /* @0x0004          multiplied by 120. (used when BPM mode=PRJ)                                      */
   sU8 bpm_lsb;                          /* @0x0005                                                                                           */
   sU8 selected_track;                   /* @0x0006          range=0..11                                                                      */
   sU8 _selected_track_duplicate;        /* @0x0007          duplicate of the selected_track, I don't know why it exists.                     */
   sU8 selected_trig_or_parameter_menu;  /* @0x0008          range=0..5, 0=TRIG, 1=SRC, 2=SMPL, 3=FLTR, 4=AMP, 5=LFO                          */
   sU8 selected_fx_menu;                 /* @0x0009          range=0..5, 0=TODO, 1=Delay, 2=Reverb, 3=Dist, 4=Comp, 5=LFO                     */
   sU8 selected_page;                    /* @0x000A          range=0..3, 0=Page 1, 1=Page 2, 2=Page 3, 3=Page 4, only when manually selected. */

   sU8 __unknown_0x000B;                 /* ?@0x000B         Reads 0x00 */

   sU8 track_mute_msb;                   /* ?@0x000C         (semantics not decoded yet) */
   sU8 track_mute_lsb;                   /* ?@0x000D         (semantics not decoded yet) */

   sU8 __unknown0x000E_0x0014[7];        /* ?@0x000E..0x0014 All zeros. */

   sU8 selected_mode;                    /* @0x0015          range=0..2, 0=NORMAL, 1=CHAIN, 2=SONG */
   /* I'd expect 0..3 for the range of this parameter but it stops at 2. It might be a bug in elektron. */
   sU8 selected_pattern_transition_mode; /* @0x0016          range=0..2, 0=Sequential, 1=Direct Start, 2=Direct Jump or Temp Jump */

   sU8 __unknown0x0017_0x0019[3];        /* ?@0x0017..0x0019 All zeros. */

   sU8 fixed_velocity_enable;            /* @0x001A          0=OFF, 1=ON */
   sU8 fixed_velocity_amount;            /* @0x001B          range=0..127 */

   sU8 sample_recorder_src;              /* @0x001C          range=0..14, 0=AUD L+R, 1=AUD L, 2=AUD R, 3=BD, 4=SD, 5=RS/CP, 6=BT, 7=LT, */
                                         /*                        8=MT/HT, 9=CH/OH, 10=CY/CB, 11=MAIN, 12=USB L, 13=USB R, 14=USB L+R, */
   sU8 sample_recorder_thr;              /* @0x001D          range=0..127  Threshold                                                    */
   sU8 sample_recorder_monitor;          /* @0x001E          range=0..1, 0=OFF, 1=ON                                                    */

   sU8 __unknown0x001F[16 * 128];        /* ?@0x001F..0x081E sample infos / checksums ? (16 bytes per slot. first dword $FFFFffff=slot is unused) */

   sU8 __unknown0x081F;                  /* ?@0x081F         Always 0x01 */

   sU8 sample_recorder_rlen;             /* @0x0820          range=0..8  Recording length */

   sU8 __unknown0x0821_0x0826[6];        /* ?@0x0821..0x0826 All zeros. */

} ar_settings_t;


/*
 * Create settings sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_settings_request (sU8 *_dstBuf, sU8 _devId);


/*
 * Convert settings sysex dump (starting with 0xF0) to 'raw' 8bit data.
 *
 *  Arguments:
 *          _rawBuf - Destination buffer. Must be large enough to hold the decoded 'raw' 8bit data.
 *                     Pass NULL to query the required buffer size.
 *          _syxBuf - Source buffer that stores the encoded 7bit MIDI data (starting with 0xF0)
 *      _syxBufSize - Size of the source buffer (number of bytes)
 *   _retRawBufSize - If not NULL, returns the required size of the 'raw' 8bit data buffer.
 *         _retMeta - If not NULL, returns additional meta data like version.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_settings_syx_to_raw (sU8             *_rawBuf,
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
 *            _meta - Determines format version(s). Must not be NULL.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_settings_raw_to_syx (sU8                   *_syxBuf,
                                            const sU8             *_rawBuf,
                                            sU32                   _rawBufSize,
                                            sU32                  *_retSyxBufSize,
                                            const ar_sysex_meta_t *_meta
                                            );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_SETTINGS_H__ */
