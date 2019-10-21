/* ----
 * ---- file   : kit.h
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
 * ---- changed: 28Feb2016, 29Mar2016, 04Apr2016, 21Nov2016, 07Jul2017, 09Jul2017, 21Aug2017
 * ----          19Nov2018, 21Oct2019
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
#define AR_KIT_SYX_V1_SZ  (0x0C17u)  /* total size of pattern sysex dump (starting with 0xF0, ending with 0xF7) */
#define AR_KIT_SYX_V2_SZ  (0x0BE1u)  /* os v1.31b */
#define AR_KIT_SYX_V3_SZ  (0x0c07u)  /* os v1.45b */
#define AR_KIT_SYX_V4_SZ  (0x0c09u)  /* os v1.50 */

#define AR_KIT_SYX_MIN_SZ  AR_KIT_SYX_V2_SZ
#define AR_KIT_SYX_MAX_SZ  AR_KIT_SYX_V1_SZ

#define AR_KIT_V1_SZ      (0x0A87u)  /* total size of pattern 'raw' 8bit data  */
#define AR_KIT_V2_SZ      (0x0A57u)  /* os v1.31b                              */
#define AR_KIT_V3_SZ      (0x0A79u)  /* os v1.45b                              */
#define AR_KIT_V4_SZ      (0x0A7Au)  /* os v1.50                               */
#define AR_KIT_MAX_SZ     AR_KIT_V1_SZ

#define AR_KIT_TRACK_SZ  (168u)   /* total size of per track 'raw' kit data (v2) (v1=0xAC bytes) */

#define AR_KIT_TRACK1_SAMPLE_START_OFFSET  (0x62)  /* offset to first track sample start offset (byte) */
#define AR_KIT_TRACK1_SAMPLE_END_OFFSET    (0x64)  /* offset to first track sample end offset (byte) */


#if 0
//
// (note) [21Aug2017] see "sound.h":ar_sound_t
//
typedef struct { /* 0xA8 (168) bytes */

   sU8 __unknown_arr1[0x1c];  /* @0x002E  (track1)    name@0x2e+0xc
                               */

   sU8 synth_param_8;         /* @0x004a  sdhard: level (8)
                                          bdhard: level (8)
                               */
   sU8 __unused_pad1;         /* @0x004b  (lsb, unused) */

   sU8 synth_param_1;         /* @0x004c  sdhard: tune  (1)
                               *          bdhard: tune  (1)
                               */
   sU8 __unused_pad2;         /* @0x004d */

   sU8 synth_param_4;         /* @0x004e  sdhard: dec   (4)
                                          bdhard: dec   (4)
                               */
   sU8 __unused_pad3;         /* @0x004f */

   sU8 synth_param_3;         /* @0x0050  sdhard: swd   (3)
                                          bdhard: hld   (6)
                               */
   sU8 __unused_pad4;         /* @0x0051 */

   sU8 synth_param_5;         /* @0x0052  sdhard: tic   (5)
                                          bdhard: swt   (2)
                               */
   sU8 __unused_pad5;         /* @0x0053 */

   sU8 synth_param_6;         /* @0x0054  sdhard: nod   (6)
                                          bdhard: snp   (3)
                               */
   sU8 __unused_pad6;         /* @0x0055 */

   sU8 synth_param_7;         /* @0x0056  sdhard: nol   (7)
                                          bdhard: wav   (5)  (0..2)
                               */
   sU8 __unused_pad7;         /* @0x0057 */

   sU8 synth_param_2;         /* @0x0058  sdhard: swt   (8)
                                          bdhard: tic   (7)
                               */
   sU8 __unused_pad8;         /* @0x0059 */

   sU8 sample_tune;           /* @0x005a  0x40=0, 0x41=+1, .. */
   sU8 __unused_pad9;         /* @0x005b */

   sU8 sample_fine_tune;      /* @0x005c  0x40=0, 0x41=+1, .. */
   sU8 __unused_pad10;        /* @0x005d */

   sU8 sample_nr;             /* @0x005e  0=off, 1..127
                                          (note) changing the sample also changes:
                                                  smp 83->82:
                                                   off=94  (0x5e) a=0x53 b=0x52
                                                   off=184 (0xb8) a=0x10 b=0x12   chksum 0xB8..0xC5 ?! (14 bytes)
                                                   off=185 (0xb9) a=0xcf b=0xe0
                                                   off=186 (0xba) a=0x4c b=0xad
                                                   off=187 (0xbb) a=0x0e b=0xfa
                                                   off=188 (0xbc) a=0x6d b=0x65
                                                   off=189 (0xbd) a=0xdb b=0x07
                                                   off=192 (0xc0) a=0xab b=0xbb
                                                   off=193 (0xc1) a=0x10 b=0xd0
                                                   off=196 (0xc4) a=0x12 b=0x14
                                                   off=197 (0xc5) a=0x16 b=0x27

                                                  smp 82->83:
                                                   off=94  (0x5e) a=0x52 b=0x53
                                                   off=184 (0xb8) a=0x12 b=0x10
                                                   off=185 (0xb9) a=0xe0 b=0xcf
                                                   off=186 (0xba) a=0xad b=0x4c
                                                   off=187 (0xbb) a=0xfa b=0x0e
                                                   off=188 (0xbc) a=0x65 b=0x6d
                                                   off=189 (0xbd) a=0x07 b=0xdb
                                                   off=192 (0xc0) a=0xbb b=0xab
                                                   off=193 (0xc1) a=0xd0 b=0x10
                                                   off=196 (0xc4) a=0x14 b=0x12
                                                   off=197 (0xc5) a=0x27 b=0x16

                                                  smp 83->80:
                                                   off=94  (0x5e) a=0x53 b=0x50
                                                   off=184 (0xb8) a=0x10 b=0x13
                                                   off=185 (0xb9) a=0xcf b=0xa8
                                                   off=186 (0xba) a=0x4c b=0xa7
                                                   off=187 (0xbb) a=0x0e b=0xd6
                                                   off=188 (0xbc) a=0x6d b=0xa4
                                                   off=189 (0xbd) a=0xdb b=0x43
                                                   off=191 (0xbf) a=0x00 b=0x01
                                                   off=192 (0xc0) a=0xab b=0x33
                                                   off=193 (0xc1) a=0x10 b=0xd0
                                                   off=196 (0xc4) a=0x12 b=0x14
                                                   off=197 (0xc5) a=0x16 b=0xef
                               */
   sU8 __unused_pad11;        /* @0x005f */

   sU8 sample_br;             /* @0x0060  */
   sU8 __unused_pad12;        /* @0x0061 */

   sU8 sample_start_offset;   /* @0x0062 */
   sU8 __unused_pad13;        /* @0x0063 */

   sU8 sample_end_offset;     /* @0x0064 */
   sU8 __unused_pad14;        /* @0x0065 */

   sU8 sample_loop_flag;      /* @0x0066  0x00=off, 0x01=on */
   sU8 __unused_pad15;        /* @0x0067 */

   sU8 sample_volume;         /* @0x0068 */
   sU8 __unused_pad16;        /* @0x0069 */

   sU8 flt_attack;            /* @0x006a */
   sU8 __unused_pad17;        /* @0x006b */

   sU8 flt_sustain;           /* @0x006c */
   sU8 __unused_pad18;        /* @0x006d */

   sU8 flt_decay;             /* @0x006e */
   sU8 __unused_pad19;        /* @0x006f */

   sU8 flt_release;           /* @0x0070 */
   sU8 __unused_pad20;        /* @0x0071 */

   sU8 flt_cutoff;            /* @0x0072 */
   sU8 __unused_pad21;        /* @0x0073 */

   sU8 flt_res;               /* @0x0074 */
   sU8 __unused_pad22;        /* @0x0075 */

   sU8 flt_type;              /* @0x0076 */
   sU8 __unused_pad23;        /* @0x0077 */

   sU8 flt_env;               /* @0x0078 */
   sU8 __unused_pad24;        /* @0x0079 */

   sU8 amp_attack;            /* @0x007A */
   sU8 __unused_pad25;        /* @0x007B */

   sU8 amp_hold;              /* @0x007C */
   sU8 __unused_pad26;        /* @0x007D */

   sU8 amp_decay;             /* @0x007E */
   sU8 __unused_pad27;        /* @0x007F */

   sU8 amp_overdrive;         /* @0x0080 */
   sU8 __unused_pad28;        /* @0x0081 */

   sU8 amp_delay_send;        /* @0x0082 */
   sU8 __unused_pad29;        /* @0x0083 */

   sU8 amp_reverb_send;       /* @0x0084 */
   sU8 __unused_pad30;        /* @0x0085 */

   sU8 amp_pan;               /* @0x0086 */
   sU8 __unused_pad31;        /* @0x0087 */

   sU8 amp_volume;            /* @0x0088 */
   sU8 __unused_pad32;        /* @0x0089 */

   sU8 __unknown2;            /* @0x008A */
   sU8 __unknown3;            /* @0x008B */

   sU8 lfo_speed;             /* @0x008C */
   sU8 __unused_pad33;        /* @0x008D */

   sU8 lfo_multiplier;        /* @0x008E */
   sU8 __unused_pad34;        /* @0x008F */

   sU8 lfo_fade;              /* @0x0090  0x40=0 */
   sU8 __unused_pad35;        /* @0x0091 */

   sU8 lfo_dest;              /* @0x0092  0x29=none, 0x0=BDHD:Level, .. */
   sU8 __unused_pad36;        /* @0x0093 */

   sU8 lfo_wav;               /* @0x0094  0x0=tri, 0x1=sin, .. */
   sU8 __unused_pad37;        /* @0x0095 */

   sU8 lfo_start_phase;       /* @0x0096   */
   sU8 __unused_pad38;        /* @0x0097 */

   sU8 lfo_mode;              /* @0x0098  0x0=free, 0x1=trg, .. */
   sU8 __unused_pad39;        /* @0x0099 */

   sU8 lfo_depth_msb;         /* @0x009A  */
   sU8 lfo_depth_lsb;         /* @0x009B  */

   sU8 def_note;              /* @0x009c  0x3c=0, 0x3d=+1, 0x3b=-1 (initially 0x00 == +0 ?!) */
   sU8 __unknown_arr2[0xd];   /* @0x009d..0x00A9  (correct location of trig/vel/def_len/.. ?) */
   sU8 machine_type;          /* @0x00AA   0:bdhard     1:bd classic   2:sd hard    3:sd classic
                                           4:           5:             6:           7:
                                           8:           9:            10:          11:
                                          12:          13:bd fm       14:sd fm     15:noise gen
                                          16:impulse   17:            18:          19:
                                          20:          21:bd plastic  22:bd silky  23:sd natural
                                          24:          25:            26:bd sharp  27:disable
                                          28:dual vco  29:            30:          31:
                              */
   sU8 __unknown_arr3[43 /*0xA8-0x7b*/];
} ar_kit_track_t;
#else
#define ar_kit_track_t ar_sound_t
#endif


/*
 *
 ** Kit v4 (v1.5.0) structure
 *
 */
typedef struct { /* 0x0A87 bytes in v1, 0x0a57 bytes in v2, 0x0a79 bytes in v3, 0x0a7a bytes in v4(1.5.0) */
   sU8 __unknown_arr1[0x14];

   struct {                    /* @0x0014..0x002b */
      sU8 level;               /*  actually BIG ENDIAN shorts but LSB is unused (always 0x00) */
      sU8 __unused_pad1;
   } track_levels[12];

   sU8 __unknown_arr1b[0x2];   /* @0x002c..0x002d */

   ar_sound_t tracks[12];  /* @0x002E..0x080f */

   sU8 __unknown_arr2[0x4];    /* @0x080E..0x0812 */

   /* FX-track parameters: */
   sU8 fx_delay_time;          /* @0x0812   */
   sU8 __unused_pad1;          /* @0x0813   */

   sU8 fx_delay_pingpong;      /* @0x0814  0x00=off, 0x01=on */
   sU8 __unused_pad2;          /* @0x0815   */

   sU8 fx_delay_stereo_width;  /* @0x0816  0x40=+0 */
   sU8 __unused_pad3;          /* @0x0817   */

   sU8 fx_delay_feedback;      /* @0x0818   */
   sU8 __unused_pad4;          /* @0x0819   */

   sU8 fx_delay_hpf;           /* @0x081a   */
   sU8 __unused_pad5;          /* @0x081b   */

   sU8 fx_delay_lpf;           /* @0x081c   */
   sU8 __unused_pad6;          /* @0x081d   */

   sU8 fx_delay_reverb_send;   /* @0x081e   */
   sU8 __unused_pad7;          /* @0x081f   */

   sU8 fx_delay_volume;        /* @0x0820   */
   sU8 __unused_pad8;          /* @0x0821   */

   sU8 fx_dist_reverb_send;    /* @0x0822   */
   sU8 __unused_pad9;          /* @0x0823   */

   sU8 fx_dist_delay_pre_post; /* @0x0824   */
   sU8 __unused_pad11;         /* @0x0825   */

   sU8 fx_reverb_pre;          /* @0x0826   */
   sU8 __unused_pad12;         /* @0x0827   */

   sU8 fx_reverb_decay;        /* @0x0828   */
   sU8 __unused_pad13;         /* @0x0829   */

   sU8 fx_reverb_freq;         /* @0x082a   */
   sU8 __unused_pad14;         /* @0x082b   */

   sU8 fx_reverb_gain;         /* @0x082c   */
   sU8 __unused_pad15;         /* @0x082d   */

   sU8 fx_reverb_hpf;          /* @0x082e   */
   sU8 __unused_pad16;         /* @0x082f   */

   sU8 fx_reverb_lpf;          /* @0x0830   */
   sU8 __unused_pad17;         /* @0x0831   */

   sU8 fx_reverb_volume;       /* @0x0832   */
   sU8 __unused_pad18;         /* @0x0833   */

   sU8 fx_dist_reverb_pre_post; /* @0x0834  */
   sU8 __unused_pad19;          /* @0x0835  */

   sU8 fx_dist_amount;         /* @0x0836   */
   sU8 __unused_pad20;         /* @0x0837   */

   sU8 fx_dist_sym;            /* @0x0838   */
   sU8 __unused_pad21;         /* @0x0839   */

   sU8 __unknown_fx_1;         /* @0x083A   */
   sU8 __unknown_fx_2;         /* @0x083B   */

   sU8 fx_comp_threshold;      /* @0x083C   */
   sU8 __unused_pad22;         /* @0x083D   */

   sU8 fx_comp_attack;         /* @0x083E   */
   sU8 __unused_pad23;         /* @0x083F   */

   sU8 fx_comp_release;        /* @0x0840   */
   sU8 __unused_pad24;         /* @0x0841   */

   sU8 fx_comp_ratio;          /* @0x0842   */
   sU8 __unused_pad25;         /* @0x0843   */

   sU8 fx_comp_seq;            /* @0x0844   */
   sU8 __unused_pad26;         /* @0x0845   */

   sU8 fx_comp_gain;           /* @0x0846   */
   sU8 __unused_pad27;         /* @0x0847   */

   sU8 fx_comp_mix;            /* @0x0848   */
   sU8 __unused_pad28;         /* @0x0849   */

   sU8 fx_comp_volume;         /* @0x084a   */
   sU8 __unused_pad29;         /* @0x084b   */

   sU8 fx_lfo_speed;           /* @0x084c   */
   sU8 __unused_pad30;         /* @0x084d   */

   sU8 fx_lfo_multiplier;      /* @0x084e   */
   sU8 __unused_pad31;         /* @0x084f   */

   sU8 fx_lfo_fade;            /* @0x0850   */
   sU8 __unused_pad32;         /* @0x0851   */

   sU8 fx_lfo_dest;            /* @0x0852   */
   sU8 __unused_pad33;         /* @0x0853   */

   sU8 fx_lfo_wave;            /* @0x0854   */
   sU8 __unused_pad34;         /* @0x0855   */

   sU8 fx_lfo_start_phase;     /* @0x0856   */
   sU8 __unused_pad35;         /* @0x0857   */

   sU8 fx_lfo_mode;            /* @0x0858   */
   sU8 __unused_pad36;         /* @0x0859   */

   sU8 fx_lfo_depth_msb;       /* @0x085a   */
   sU8 fx_lfo_depth_lsb;       /* @0x085b   */

   sU8 __unknown_arr3[0x2E];   /* @0x085c..0x088A */

   sU8 perf_ctl[48 * 4];       /* @0x088a..0x0949 */

   /* @0x08ba: perf1: (clear)
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

   sU8 __unknown_arr4[0x15];   /* @0x094a..0x095e */

   sU8 scene_ctl[48 * 4];      /* @0x095f..0x0A1e */

   /*          scene1: (assign sample tune +1)
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

   sU8 __unknown_pad37;        /* @0x0a1f (scene_id MSB?) */
   sU8 current_scene_id;       /* @0x0a20 */

   /* (note) 54 unknown bytes not present in v1 kit data */
   sU8 __unknown_arr5[54];     /* @0x0a21..0x0a56 */

   sU8 __unknown_arr6[36];     /* 0xa57..0x0a79 */
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
S_EXTERN ar_error_t ar_kit_request(sU8 *_dstBuf, sU8 _devId, sU8 _kitNr);


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
S_EXTERN ar_error_t ar_kit_request_x(sU8 *_dstBuf, sU8 _devId, sU8 _kitNr);


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
S_EXTERN ar_error_t ar_kit_syx_to_raw(sU8             *_rawBuf,
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
S_EXTERN ar_error_t ar_kit_raw_to_syx(sU8                   *_syxBuf,
                                      const sU8             *_rawBuf,
                                      sU32                   _rawBufSize,
                                      sU32                  *_retSyxBufSize,
                                      const ar_sysex_meta_t *_meta
                                      );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_KIT_H__ */
