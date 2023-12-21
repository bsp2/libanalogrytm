/* ----
 * ---- file   : kit.h
 * ---- author : bsp, alisomay
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
 * ---- created: 28Feb2016
 * ---- changed: 29Mar2016, 04Apr2016, 21Nov2016, 07Jul2017, 09Jul2017, 21Aug2017, 19Nov2018
 * ----          21Oct2019, 25Nov2023, 07Dec2023, 08Dec2023, 21Dec2023
 * ----
 * ----
 * ----
 */

#ifndef __AR_KIT_H__
#define __AR_KIT_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


/*
 *
 ** Some natural constants
 *
 */
#define AR_KIT_SYX_V1_SZ  0x0C17u  /* total size of pattern sysex dump (starting with 0xF0, ending with 0xF7) */
#define AR_KIT_SYX_V2_SZ  0x0BE1u  /* os v1.31b */
#define AR_KIT_SYX_V3_SZ  0x0c07u  /* os v1.45b */
#define AR_KIT_SYX_V4_SZ  0x0c09u  /* os v1.50 */
#define AR_KIT_SYX_V5_SZ  0x0BB6u  /* os v1.70 */

#define AR_KIT_SYX_MIN_SZ  AR_KIT_SYX_V5_SZ
#define AR_KIT_SYX_MAX_SZ  AR_KIT_SYX_V1_SZ

#define AR_KIT_V1_SZ      0x0A87u  /* total size of pattern 'raw' 8bit data  */
#define AR_KIT_V2_SZ      0x0A57u  /* os v1.31b                              */
#define AR_KIT_V3_SZ      0x0A79u  /* os v1.45b                              */
#define AR_KIT_V4_SZ      0x0A7Au  /* os v1.50                               */
#define AR_KIT_V5_SZ      0x0A32u  /* os v1.70                               */
#define AR_KIT_MAX_SZ     AR_KIT_V1_SZ

#define AR_KIT_TRACK_SZ  (162u)   /* total size of per track 'raw' kit data (v5/FW1.70) (v1=172/$AC bytes, v2..v4=168/$A8 bytes) */

#define AR_KIT_TRACK1_SAMPLE_START_OFFSET  (0x62u)  /* offset to first track sample start offset (MSB, LSB@0x63) */
#define AR_KIT_TRACK1_SAMPLE_END_OFFSET    (0x64u)  /* offset to first track sample end offset (MSB, LSB@0x65) */


#define ar_kit_track_t ar_sound_t


/*
 * <ali> FX LFO destinations
 *
 */
#define AR_FX_LFO_DEST_NONE                 37u

#define AR_FX_LFO_DEST_DELAY_TIME            0u
#define AR_FX_LFO_DEST_DELAY_PINGPONG        1u
#define AR_FX_LFO_DEST_DELAY_STEREOWIDTH     2u
#define AR_FX_LFO_DEST_DELAY_FEEDBACK        3u
#define AR_FX_LFO_DEST_DELAY_HPFILTER        4u
#define AR_FX_LFO_DEST_DELAY_LPFILTER        5u
#define AR_FX_LFO_DEST_DELAY_REVERBSEND      6u
#define AR_FX_LFO_DEST_DELAY_MIXVOLUME       7u
#define AR_FX_LFO_DEST_DELAY_OVERDRIVE       8u

#define AR_FX_LFO_DEST_REV_PREDELAY         10u
#define AR_FX_LFO_DEST_REV_DECAY            11u
#define AR_FX_LFO_DEST_REV_SHELVINGFREQ     12u
#define AR_FX_LFO_DEST_REV_SHELVINGGAIN     13u
#define AR_FX_LFO_DEST_REV_HPFILTER         14u
#define AR_FX_LFO_DEST_REV_LPFILTER         15u
#define AR_FX_LFO_DEST_REV_MIXVOLUME        16u

#define AR_FX_LFO_DEST_DIST_AMOUNT          18u
#define AR_FX_LFO_DEST_DIST_SYMMETRY        19u

#define AR_FX_LFO_DEST_COMP_THRESHOLD       21u
#define AR_FX_LFO_DEST_COMP_ATTACK_MS       22u
#define AR_FX_LFO_DEST_COMP_RELEASE_S       23u
#define AR_FX_LFO_DEST_COMP_RATIO           24u
#define AR_FX_LFO_DEST_COMP_SIDECHAINEQ     25u
#define AR_FX_LFO_DEST_COMP_MAKEUPGAIN      26u
#define AR_FX_LFO_DEST_COMP_DRYWETMIX       27u
#define AR_FX_LFO_DEST_COMP_VOLUME          28u


/*
 *
 * Per-track retrig settings
 *
 *    0x0004 bytes in v5(FW1.70)
 *
 */
typedef struct {
   /*
       - @0x09DF: track 1 retrig ($00=1/1, $09=1/16, .., $10=1/80)
       - @0x09E0: track 1 retrig length ($00=0.125, ..)
       - @0x09E1: track 1 retrig vel curve (-128..127)
       - @0x09E2: ?
       - @0x09E3: track 2 retrig ($0B=1/24, ..)
       - @0x09E4: track 2 retrig length ($2E=1/4, ..)
       - @0x09E5: track 2 retrig vel curve
       - @0x09E6: ?
   */
   sU8 retrig;          /* @0x09DF: track 1 retrig ($00=1/1, $09=1/16, .., $10=1/80) */
   sU8 length;          /* @0x09E0: track 1 retrig length ($00=0.125, ..)            */
   sS8 vel_curve;       /* @0x09E1: track 1 retrig vel curve (-128..127)             */
   sU8 __unknown_09E2;  /* @0x09E2: ?                                                */
} ar_retrig_t;


/*
 *
 ** Kit v5 (FW1.70) structure
 *
 *    0x0A32(2610) bytes in v5(FW1.70)
 *    0x0A7A(2682) bytes in v4(FW1.50..1.61B)
 *    0x0A79(2681) bytes in v3
 *    0x0A57(2647) bytes in v2
 *    0x0A87(2695) bytes in v1
 *
 */
typedef struct {
   sU8 __unknown_arr1[0x4];    /* @0x0000 (reads 00 00 00 06 in FW1.70 -- version nr?) */

   sU8 name[15];               /* @0x0004 */
   sU8 __pad_name;             /* @0x0013  (ASCIIZ?) */

   s_u16_t track_levels[13];   /* @0x0014..0x002b   (note) LSB (track_levels[i].b.hi) is unused (always 0x00) */

   ar_sound_t tracks[12];      /* @0x002E..0x07C5 (12*162=1944($798) bytes */

   sU8 __unknown_arr2[0x4];    /* @0x07C6..0x07C9 */

   /* FX-track parameters: */
   sU8 fx_delay_time;          /* @0x07CA   */
   sU8 __unused_pad1;          /* @0x07CB   */

   sU8 fx_delay_pingpong;      /* @0x07CC  0=off, 1=on */
   sU8 __unused_pad2;          /* @0x07CD   */

   sU8 fx_delay_stereo_width;  /* @0x07CE  0x40=+0 */
   sU8 __unused_pad3;          /* @0x07CF   */

   sU8 fx_delay_feedback;      /* @0x07D0   */
   sU8 __unused_pad4;          /* @0x07D1   */

   sU8 fx_delay_hpf;           /* @0x07D2   */
   sU8 __unused_pad5;          /* @0x07D3   */

   sU8 fx_delay_lpf;           /* @0x07D4   */
   sU8 __unused_pad6;          /* @0x07D5   */

   sU8 fx_delay_reverb_send;   /* @0x07D6   */
   sU8 __unused_pad7;          /* @0x07D7   */

   sU8 fx_delay_volume;        /* @0x07D8   */
   sU8 __unused_pad8;          /* @0x07D9   */

   sU8 fx_dist_reverb_send;    /* @0x07DA ? */
   sU8 __unused_pad9;          /* @0x07DB ? */

   sU8 fx_dist_delay_pre_post; /* @0x07DC ? */
   sU8 __unused_pad11;         /* @0x07DD ? */

   sU8 fx_reverb_pre;          /* @0x07DE   */
   sU8 __unused_pad12;         /* @0x07DF   */

   sU8 fx_reverb_decay;        /* @0x07E0   */
   sU8 __unused_pad13;         /* @0x07E1   */

   sU8 fx_reverb_freq;         /* @0x07E2   */
   sU8 __unused_pad14;         /* @0x07E3   */

   sU8 fx_reverb_gain;         /* @0x07E4   */
   sU8 __unused_pad15;         /* @0x07E5   */

   sU8 fx_reverb_hpf;          /* @0x07E6   */
   sU8 __unused_pad16;         /* @0x07E7   */

   sU8 fx_reverb_lpf;          /* @0x07E8   */
   sU8 __unused_pad17;         /* @0x07E9   */

   sU8 fx_reverb_volume;       /* @0x07EA   */
   sU8 __unused_pad18;         /* @0x07EB   */

   sU8 fx_dist_reverb_pre_post;/* @0x07EC   */
   sU8 __unused_pad19;         /* @0x07ED   */

   sU8 fx_dist_amount;         /* @0x07EE   */
   sU8 __unused_pad20;         /* @0x07EF   */

   sU8 fx_dist_sym;            /* @0x07F0   */
   sU8 __unused_pad21;         /* @0x07F1   */

   sU8 __unknown_fx_1;         /* @0x07F2   */
   sU8 __unknown_fx_2;         /* @0x07F3   */

   sU8 fx_comp_threshold;      /* @0x07F4   */
   sU8 __unused_pad22;         /* @0x07F5   */

   sU8 fx_comp_attack;         /* @0x07F6   */
   sU8 __unused_pad23;         /* @0x07F7   */

   sU8 fx_comp_release;        /* @0x07F8   */
   sU8 __unused_pad24;         /* @0x07F9   */

   sU8 fx_comp_ratio;          /* @0x07FA   */
   sU8 __unused_pad25;         /* @0x07FB   */

   sU8 fx_comp_seq;            /* @0x07FC (0=off,1=lpf,2=hpf,3=hit) */
   sU8 __unused_pad26;         /* @0x07FD   */

   sU8 fx_comp_gain;           /* @0x07FE   */
   sU8 __unused_pad27;         /* @0x07FF   */

   sU8 fx_comp_mix;            /* @0x0800   */
   sU8 __unused_pad28;         /* @0x0801   */

   sU8 fx_comp_volume;         /* @0x0802   */
   sU8 __unused_pad29;         /* @0x0803   */

   sU8 fx_lfo_speed;           /* @0x0804   */
   sU8 __unused_pad30;         /* @0x0805   */

   sU8 fx_lfo_multiplier;      /* @0x0806   */
   sU8 __unused_pad31;         /* @0x0807   */

   sU8 fx_lfo_fade;            /* @0x0808   */
   sU8 __unused_pad32;         /* @0x0809   */

   sU8 fx_lfo_dest;            /* @0x080A (37/$25=off / "META:None") */
   sU8 __unused_pad33;         /* @0x080B   */

   sU8 fx_lfo_wave;            /* @0x080C   */
   sU8 __unused_pad34;         /* @0x080D   */

   sU8 fx_lfo_start_phase;     /* @0x080E   */
   sU8 __unused_pad35;         /* @0x080F   */

   sU8 fx_lfo_mode;            /* @0x0810   */
   sU8 __unused_pad36;         /* @0x0811   */

   sU8 fx_lfo_depth_msb;       /* @0x0812   */
   sU8 fx_lfo_depth_lsb;       /* @0x0813   */

   sU8 __unknown_arr3[0x2E];   /* @0x0814..0x0841 (all 0 in test kit) */

   sU8 perf_ctl[48 * 4];       /* @0x0842..0x0901 */

                     /* (old comment, offsets have changed by now)
                        @0x08ba: perf1: (clear)
                                   off=2234 (0x8ba) a=0x01 b=0x00   (note: pre OS1.31 debug output, perf_ctl are now at 0x88a)
                                   off=2235 (0x8bb) a=0x00 b=0xff
                                   off=2236 (0x8bc) a=0x08 b=0x00

                                 perf1: (assign sample tune +1)
                                   off=2234 (0x8ba) a=0x00 b=0x01  <-- signed delta value
                                   off=2235 (0x8bb) a=0xff b=0x00  <-- target id msb ?
                                   off=2236 (0x8bc) a=0x00 b=0x08  <-- target id (8=sample tune, 9=sample fine tune, ..)

                                 perf1: (assign sample tune -1)
                                   off=2234 (0x8ba) a=0x01 b=0xff

                                 perf1: (assign sample fine tune +1)
                                   off=2234 (0x8ba) a=0x00 b=0x01
                                   off=2235 (0x8bb) a=0xff b=0x00
                                   off=2236 (0x8bc) a=0x00 b=0x09 <--

                                 perf1: (assign 2nd target sample tune +1)
                                   off=2238 (0x8be) a=0x00 b=0x01
                                   off=2239 (0x8bf) a=0xff b=0x00
                                   off=2240 (0x8c0) a=0x00 b=0x08

                                 perf1: (assign 3rd target sample br +1)
                                   off=2242 (0x8c2) a=0x00 b=0x01
                                   off=2243 (0x8c3) a=0xff b=0x00
                                   off=2244 (0x8c4) a=0x00 b=0x0b

                                 perf2: (assign sample tune +1)
                                   off=2246 (0x8c6) a=0x00 b=0x01
                                   off=2247 (0x8c7) a=0xff b=0x00
                                   off=2248 (0x8c8) a=0x00 b=0x08
                                   off=2249 (0x8c9) a=0x00 b=0x01  <-- perf id
                     */

   sU8 __unknown_0902[0x15];   /* @0x0902..0x0916 */

   sU8 scene_ctl[48 * 4];      /* @0x0917..0x09D6 */

                     /* old comment, offsets have changed by now
                                 scene1: (assign sample tune +1)
                                   off=2447 (0x98f) a=0x00 b=0x41
                                   off=2448 (0x990) a=0xff b=0x00
                                   off=2449 (0x991) a=0x00 b=0x08
                                   off=2640 (0xa50) a=0x02 b=0x00  <-- current scene id ???

                                 scene1: (assign 2nd target sample fine tune +1)
                                   off=2451 (0x993) a=0x00 b=0x41
                                   off=2452 (0x994) a=0xff b=0x00
                                   off=2453 (0x995) a=0x00 b=0x09

                                 scene2: (assign sample tune +1)
                                   off=2455 (0x997) a=0x00 b=0x41
                                   off=2456 (0x998) a=0xff b=0x00
                                   off=2457 (0x999) a=0x00 b=0x08
                                   off=2458 (0x99a) a=0x00 b=0x01  <-- scene id
                                   off=2640 (0xa50) a=0x00 b=0x01
                     */

   sU8 __unknown_09D7;         /* @0x09D7 (scene_id MSB?) */
   sU8 current_scene_id;       /* @0x09D8 (0..11) */

   sU8 __unknown_09D9[4];      /* ?@0x09D9 */

   s_u16_t retrig_always_on;   /* @0x09DD..0x09DE  bit0=trk1($0001) .. bit11=trk12($0800) */

   ar_retrig_t retrig[12];     /* @0x09DF..0x0A0E  track 1..12 retrig / length / velcurve (4 bytes per track) */

   sU8 __unknown_arr6[3];      /* @0x0A0F..0x0A11 */

   /* note: mkII only ? */
   sU8 ctrl_in_mod_1_amt_1;    /* @0x0A12 (-128..127) */
   sU8 __unused_pad37;         /* @0x0A13 */
   sU8 ctrl_in_mod_1_target_1; /* @0x0A14 See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 ctrl_in_mod_1_amt_2;    /* @0x0A15 (-128..127) */
   sU8 __unused_pad38;         /* @0x0A16 */
   sU8 ctrl_in_mod_1_target_2; /* @0x0A17 See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 ctrl_in_mod_1_amt_3;    /* @0x0A18 (-128..127) */
   sU8 __unused_pad39;         /* @0x0A19 */
   sU8 ctrl_in_mod_1_target_3; /* @0x0A1A See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 ctrl_in_mod_1_amt_4;    /* @0x0A1B (-128..127) */
   sU8 __unused_pad40;         /* @0x0A1C */
   sU8 ctrl_in_mod_1_target_4; /* @0x0A1D See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 __unused_pad_group_1[4]; /* @0x0A1E..0x0A21 */

   sU8 ctrl_in_mod_2_amt_1;     /* @0x0A22 (-128..127) */
   sU8 __unused_pad41;          /* @0x0A23 */
   sU8 ctrl_in_mod_2_target_1;  /* @0x0A24 See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 ctrl_in_mod_2_amt_2;     /* @0x0A25 (-128..127) */
   sU8 __unused_pad42;          /* @0x0A26 */
   sU8 ctrl_in_mod_2__target_2; /* @0x0A27 See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 ctrl_in_mod_2_amt_3;     /* @0x0A28 (-128..127) */
   sU8 __unused_pad43;          /* @0x0A29 */
   sU8 ctrl_in_mod_2_target_3;  /* @0x0A2A See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 ctrl_in_mod_2_amt_4;     /* @0x0A2B (-128..127) */
   sU8 __unused_pad44;          /* @0x0A2C */
   sU8 ctrl_in_mod_2_target_4;  /* @0x0A2D See sound.h, same as AR_SOUND_MOD_DEST_XXX, AR_SOUND_MOD_DEST_SYN_X variants can not be used. */

   sU8 __unused_pad_group_2[4]; /* @0x0A2E..0x0A31 */

} ar_kit_t;


/*
 * Create kit sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *  _patternNr - Determines kit number. 0=1, 1=2, .. 16=17, ..127=128.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_kit_request (sU8 *_dstBuf, sU8  _devId, sU8  _kitNr);


/*
 * Create kit workbuffer sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_kit_request_x (sU8 *_dstBuf, sU8  _devId, sU8  _kitNr);


/*
 * Convert kit sysex dump (starting with 0xF0) to 'raw' 8bit data.
 *
 *  Arguments:
 *          _rawBuf - Destination buffer. Must be large enough to hold the decoded 'raw' 8bit data.
 *                     Pass NULL to query the required buffer size.
 *          _syxBuf - Source buffer that stores the encoded 7bit MIDI data (starting with 0xF0)
 *      _syxBufSize - Size of the source buffer (number of bytes)
 *   _retRawBufSize - If not NULL, returns the required size of the 'raw' 8bit data buffer.
 *         _retMeta - If not NULL, returns additional meta data like version / pattern number.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_kit_syx_to_raw (sU8             *_rawBuf,
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
 *            _meta - Determines pattern number, format version(s). Must not be NULL.
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_kit_raw_to_syx (sU8                   *_syxBuf,
                                       const sU8             *_rawBuf,
                                       sU32                   _rawBufSize,
                                       sU32                  *_retSyxBufSize,
                                       const ar_sysex_meta_t *_meta
                                       );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_KIT_H__ */
