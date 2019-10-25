/* ----
 * ---- file   : pattern.h
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
 * ---- changed: 30Jul2014, 01Aug2014, 04Aug2014, 07Jul2017, 21Oct2019, 24Oct2019
 * ----
 * ----
 */

#ifndef __AR_PATTERN_H__
#define __AR_PATTERN_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


/*
 *
 ** Some natural constants
 *
 */
#define AR_PATTERN_SYX_PATNR        (0x0009u)  /* offset of pattern number (byte) in sysex data     */
#define AR_PATTERN_SYX_DATA         (0x000Au)  /* start of (encoded) 'raw' bytes in sysex data      */

#if 0
// v1
#define AR_PATTERN_SYX_CHECKSUM     (0x3AEDu)  /* offset to 2 byte (14bit) checksum (sum of 'raw' data bytes) */
#define AR_PATTERN_SYX_DATASIZE     (0x3AEFu)  /* offset to 2 byte (14bit) data size (size includes data+chksum+data size) */
#else
// v4 (FW v1.50)
#define AR_PATTERN_SYX_CHECKSUM     (0x3AFEu)  /* offset to 2 byte (14bit) checksum (sum of 'raw' data bytes) */
#define AR_PATTERN_SYX_DATASIZE     (0x3AB0u)  /* offset to 2 byte (14bit) data size (size includes data+chksum+data size) */
#endif

#define AR_PATTERN_SYX_V1_SZ        (0x3AF2u)  /* total size of pattern sysex dump (starting with 0xF0, ending with 0xF7) */
#define AR_PATTERN_SYX_V4_SZ        (0x3B03u)  /* v1.50 (starting with 0xF0, ending with 0xF7) */
#define AR_PATTERN_SYX_MIN_SZ       (0x3AF2u)
#define AR_PATTERN_SYX_MAX_SZ       (0x3B03u)

#define AR_PATTERN_V1_SZ  (0x3386u)  /* total size of pattern 'raw' 8bit data                */
#define AR_PATTERN_V4_SZ  (0x3395u)  /* total size of pattern 'raw' 8bit data                */
#define AR_PATTERN_MIN_SZ (0x3386u)  /*                 */
#define AR_PATTERN_MAX_SZ (0x3395u)  /*                 */

#if 0
// v1 (original FW)
#define AR_TRACK_SZ      (0x0288u)   /* total size of track 'raw' 8bit data                  */
#else
// v4 (FW v1.50)
#define AR_TRACK_SZ      (0x0289u)   /* total size of track 'raw' 8bit data                  */
#endif

#define AR_PLOCK_SEQ_SZ  (0x0042u)   /* total size of pattern plock sequence 'raw' 8bit data */

#define AR_NUM_TRACKS                  (13u)   /* trk1..trk12, fx */
#define AR_NUM_PLOCK_SEQS_PER_PATTERN  (72u)


/*
 *
 ** Pattern (+ in future OS versions maybe track) speeds
 *
 */
#define AR_SPD_2X     (0u)  /* 2x   */
#define AR_SPD_3B2X   (1u)  /* 3/2x */
#define AR_SPD_1X     (2u)  /* 1x   */
#define AR_SPD_3B4X   (3u)  /* 3/4x */
#define AR_SPD_1B2X   (4u)  /* 1/2x */
#define AR_SPD_1B4X   (5u)  /* 1/4x */
#define AR_SPD_1B8X   (6u)  /* 1/8x */


/*
 *
 ** Filter types  
 *
 */
#define AR_FLT_TYPE_LP2  (0u)  /* 24db lowpass  */
#define AR_FLT_TYPE_LP1  (1u)  /* 12db lowpass  */
#define AR_FLT_TYPE_BP   (2u)  /* 12db lowpass  */
#define AR_FLT_TYPE_HP1  (3u)  /* 12db highpass */
#define AR_FLT_TYPE_HP2  (4u)  /* 24db highpass */
#define AR_FLT_TYPE_BS   (5u)  /* bandstop      */
#define AR_FLT_TYPE_PK   (6u)  /* peak          */


/*
 *
 ** LFO waveform types
 *
 */
#define AR_LFO_WAVEFORM_TRI   (0u)  /* triangle    */
#define AR_LFO_WAVEFORM_SIN   (1u)  /* sine        */
#define AR_LFO_WAVEFORM_SQR   (2u)  /* square      */
#define AR_LFO_WAVEFORM_SAW   (3u)  /* sawtooth    */
#define AR_LFO_WAVEFORM_EXP   (4u)  /* exponential */
#define AR_LFO_WAVEFORM_RMP   (5u)  /* ramp up     */
#define AR_LFO_WAVEFORM_RND   (6u)  /* random      */

#define NUM_AR_LFO_WAVEFORMS  (7u)


/*
 *
 ** LFO trigger modes
 *
 */
#define AR_LFO_TRIGMODE_FRE  (0u)  /* free running                                           */
#define AR_LFO_TRIGMODE_TRG  (1u)  /* restart when note is triggered                         */
#define AR_LFO_TRIGMODE_HLD  (2u)  /* free running but latch and hold when note is triggered */
#define AR_LFO_TRIGMODE_ONE  (3u)  /* oneshot                                                */
#define AR_LFO_TRIGMODE_HLF  (4u)  /* halfwave oneshot                                       */

#define NUM_AR_LFO_TRIGMODES (5u)


/*
 *
 ** P-Lock sequence types
 *
 */
#define AR_PLOCK_TYPE_UNUSED        (0xFFu)

#define AR_PLOCK_TYPE_MP0           (0x00u)  /* <syn> first machine parameter.  Also see e.g. AR_M_BDCLASSIC_P* */
#define AR_PLOCK_TYPE_MP1           (0x01u)  /* <syn> second machine parameter                                  */
#define AR_PLOCK_TYPE_MP2           (0x02u)  /* ..                                                              */
#define AR_PLOCK_TYPE_MP3           (0x03u)  /* ..                                                              */
#define AR_PLOCK_TYPE_MP4           (0x04u)  /* ..                                                              */
#define AR_PLOCK_TYPE_MP5           (0x05u)  /* ..                                                              */
#define AR_PLOCK_TYPE_MP6           (0x06u)  /* ..                                                              */
#define AR_PLOCK_TYPE_MP7           (0x07u)  /* <syn> 8th machine parameter                                     */

#define AR_PLOCK_TYPE_SMP_TUNE      (0x08u)  /* <sample> tune (0x28=-24, 0x40=+0, 0x58=+24) */
#define AR_PLOCK_TYPE_SMP_FINE      (0x09u)  /* <sample> fine (0x00=-64, 0x40=+0, 0x7F=+63) */
#define AR_PLOCK_TYPE_SMP_NR        (0x0Au)  /* <sample> nr (0(off), 1..127)                */
#define AR_PLOCK_TYPE_SMP_BITRDC    (0x0Bu)  /* <sample> bitreduction (0..127)              */
#define AR_PLOCK_TYPE_SMP_START     (0x0Cu)  /* <sample> start (0..120)                     */
#define AR_PLOCK_TYPE_SMP_END       (0x0Du)  /* <sample> end (0..120)                       */
#define AR_PLOCK_TYPE_SMP_LOOPSW    (0x0Eu)  /* <sample> loopsw (0..1)                      */
#define AR_PLOCK_TYPE_SMP_LEVEL     (0x0Fu)  /* <sample> level (0..127)                     */

#define AR_PLOCK_TYPE_FLT_ATTACK    (0x10u)  /* <filter> attacktime (0..127)                                    */
#define AR_PLOCK_TYPE_FLT_SUSTAIN   (0x11u)  /* <filter> sustainlevel (0..127)                                  */
#define AR_PLOCK_TYPE_FLT_DECAY     (0x12u)  /* <filter> decaytime (0..127)                                     */
#define AR_PLOCK_TYPE_FLT_RELEASE   (0x13u)  /* <filter> releasetime (0..127)                                   */
#define AR_PLOCK_TYPE_FLT_FREQ      (0x14u)  /* <filter> frequency (0..127)                                     */
#define AR_PLOCK_TYPE_FLT_RESO      (0x15u)  /* <filter> resonance (0..127)                                     */
#define AR_PLOCK_TYPE_FLT_TYPE      (0x16u)  /* <filter> type (0=lp2, 1=lp1, 2=bp, 3=hp1, 4=hp2, 5=bs, 6=pk).
                                             *                Also see AR_FLT_TYPE_xxx
                                             */
#define AR_PLOCK_TYPE_FLT_ENV       (0x17u)  /* <filter> envdepth (0(-64)..64(0)..127(+63))                     */

#define AR_PLOCK_TYPE_AMP_ATTACK    (0x18u)  /* <amp> attacktime (0..127)                 */
#define AR_PLOCK_TYPE_AMP_HOLD      (0x19u)  /* <amp> holdtime (0..127)                   */
#define AR_PLOCK_TYPE_AMP_DECAY     (0x1Au)  /* <amp> decaytime (0..126,127=inf)          */
#define AR_PLOCK_TYPE_AMP_DRIVE     (0x1Bu)  /* <amp> overdrive (0..127)                  */
#define AR_PLOCK_TYPE_AMP_DELAY     (0x1Cu)  /* <amp> delaysend (0..127)                  */
#define AR_PLOCK_TYPE_AMP_REVERB    (0x1Du)  /* <amp> reverbsend (0..127)                 */
#define AR_PLOCK_TYPE_AMP_PAN       (0x1Eu)  /* <amp> pan (0(left)..64(ctr)..127(right))  */
#define AR_PLOCK_TYPE_AMP_VOLUME    (0x1Fu)  /* <amp> volume (0..127)                     */

#define AR_PLOCK_TYPE_UNKNOWN_20    (0x20u)

#define AR_PLOCK_TYPE_LFO_SPEED     (0x21u)  /* <lfo> speed (0(-63),64(0),127(+63))                              */
#define AR_PLOCK_TYPE_LFO_MULTIPLY  (0x22u)  /* <lfo> multiplier (0=1, .., 0xb=2k)                               */
#define AR_PLOCK_TYPE_LFO_FADE      (0x23u)  /* <lfo> fade (0(-63),64(0),127(+63))                               */
#define AR_PLOCK_TYPE_LFO_DEST      (0x24u)  /* <lfo> dest (0=off, .., 0x29=reverbsend).
                                             *             Also seee AR_LFO_DEST_xxx
                                             */
#define AR_PLOCK_TYPE_LFO_WAVEFORM  (0x25u)  /* <lfo> waveform (0=tri, 1=sin, 2=sqr, 3=saw, 4=exp, 5=rmp, 6=rnd).
                                             *                 Also see AR_LFO_WAVEFORM_xxx
                                             */
#define AR_PLOCK_TYPE_LFO_PHASE     (0x26u)  /* <lfo> startphase (0..127)                                         */
#define AR_PLOCK_TYPE_LFO_TRIGMODE  (0x27u)  /* <lfo> trigmode (0=fre, 1=trg, 2=hld, 3=one, 4=hlf)
                                             *                 Also see AR_LFO_TRIGMODE_xxx
                                             */
#define AR_PLOCK_TYPE_LFO_DEPTH     (0x28u)  /* <lfo> depth (0..127)                                              */


/*
 *
 ** Track trigger types  (see ar_pattern_track_t.trigs)
 *
 */

/* trigger flags. 
 *
 * examples:
 *                                                   data byte examples
 *  note trig:           on: 2nd step byte | 0x01     0x03 0x81
 *                      off: 2nd step byte & ~0x01    0x03 0x80
 *
 *  synswitch: plock enable: 1st step byte | 0x08
 *                   sw.off: 2nd step byte & ~0x80    0x0B 0x01
 *                    sw.on: 2nd step byte | 0x80     0x0B 0x81
 *
 *  smpswitch: plock enable: 1st step byte | 0x10
 *                   sw.off: 1st step byte & ~0x01    0x12 0x81
 *                    sw.on: 1st step byte | 0x01     0x13 0x81
 *
 *  env.f trig: plock enable: 1st step byte | 0x20
 *                    sw.off: 1st step byte & ~0x02   0x21 0x81
 *                     sw.on: 1st step byte | 0x02    0x23 0x81
 *
 *  lfo trig plock enable: 1st step byte | 0x40
 *                 sw.off: 1st step byte & ~0x04      0x43 0x81
 *                  sw.on: 1st step byte | 0x04       0x47 0x81
 */

/* re-test [07Jul2017]:
 *
 *      off: 0x0200
 *           0x0300
 *           0x0000 (after pattern clear)
 *  regular: 0x0201
 *           0x0301
 *      syn: 0x0b81 (on)
 *      syn: 0x0b01 (off)
 *      smp: 0x1a01 (off)
 *      smp: 0x1b01 (on)
 *      env: 0x2101 (off)
 *      env: 0x2301 (on)
 *      lfo: 0x4301 (off)
 *      lfo: 0x4701 (on)
 *    slide: 0x0321 (on)
 *    swing: 0x0311 (on)
 *     mute: 0x0305 (on)
 *   accent: 0x0309 (on)
 *   retrig: 0x8301 (on)
 * trigless: 0x7801 (on) (retrig etc is off)
 *
 *
 *

/* (note) big endian */
#define AR_TRIG_SWING     (0x0010u)  /* <void> swing                       */
#define AR_TRIG_NOTE_ON   (0x0001u)  /* note trig ("enable")               */
#define AR_TRIG_SLIDE     (0x0020u)  /* <void> slide                       */
#define AR_TRIG_UNKNOWN1  (0x0002u)  /* ?                                  */
#define AR_TRIG_UNKNOWN6  (0x0040u)  /* ?                                  */
#define AR_TRIG_MUTE      (0x0004u)  /* <void> mute                        */
#define AR_TRIG_ACCENT    (0x0008u)  /* <void> accent                      */
#define AR_TRIG_SYN_EN    (0x0800u)  /* enable synswitch p-lock            */
#define AR_TRIG_SYN_SW    (0x0080u)  /* synswitch bit (set=on, unset=off)  */
#define AR_TRIG_SMP_EN    (0x1000u)  /* enable smpswitch p-lock            */
#define AR_TRIG_SMP_SW    (0x0100u)  /* smpswitch bit (set=on, unset=off)  */
#define AR_TRIG_ENVF_EN   (0x2000u)  /* enable filter env p-lock           */
#define AR_TRIG_ENVF_SW   (0x0200u)  /* filter env bit (set=on, unset=off) */
#define AR_TRIG_LFO_EN    (0x4000u)  /* enable LFO p-lock                  */
#define AR_TRIG_LFO_SW    (0x0400u)  /* LFO bit (set=on, unset=off)        */
#define AR_TRIG_RETRIG    (0x8000u)  /* <void> retrig                      */
#define AR_TRIG_TRIGLESS  (0x7801u)  /* trigless trig (mask=0x7801)        */



/*
 *
 ** Track structure
 *
 */
typedef struct { /* 0x288 bytes (v1), 0x289 bytes (v4 / v1.50) */
   s_u16_t trigs[64];                   /* @0x0004..0x0083.  See AR_TRIG_xxx flags. (BIG ENDIAN!)     */
   sU8     notes[64];                   /* @0x0084..0x00C3.  0xFF=unset, MIDI note otherwise (lower 7 bits)
                                         *                    (default is C-4 == 0x3C, 0x3B="-1", 0x3D="+1")
                                         *                   bit7: 1=no trig condition, 0=have trig condition
                                         *                          ==> 0x7F = default note with trig cond
                                         *                          ==> 0xFF = default note without trig cond
                                         */
   sU8     velocities[64];              /* @0x00C4..0x0103.  0xFF=unset, 0x00=0, 0x7F=127             */
   sU8     note_lengths[64];            /* @0x0104..0x0143.  0=0.125 (1/128), 1=0.1875, 
                                                             2=1/64 (0.25), 3=0.3125, 4=0.375, 5=0.4375, 
                                                             6=1/32, 7=0.5625, 8=0.625, 9=0.6875, .., 13=0.9375,
                                                             14=1/16, 15=1.0625, 16=1.25, .., 29=1.9375,
                                                             30=1/8, 31=2.125, 32=2.25, .., 38=3, 39=3.125, .., 45=3.875
                                                             46=1/4 47=4.25, .., 61=7.75
                                                             62=1/2, 63=8.5, .., 77=15.5,
                                                             78=16 (1/1), 79=17, .., 93=31,
                                                             94=32 (2/1), 95=34, .., 109=62, 
                                                             110=64 (4/1), 111=68, .., 121=108, 122=112, 123=116, 124=120, 125=124,
                                                             126=128 (8/1),
                                                             127=inf 
                                        */
   sS8     micro_timings[64];           /* @0x0144..0x0183.  Micro timing (0xE9..0xFF => -23..-1, 0xC0..0xD7 => +0..+23) */
   sU8     retrig_lengths[64];          /* @0x0184..0x01C3.  Retrig lengths (0..126(=128), 127=inf)   */
   sU8     retrig_rates[64];            /* @0x01C4..0x0203.  Retrig rates (0(=1/1)..16(=1/80))
                                         *                    Changing the trig condition of step 1 updates 0x1c4
                                         */
   sS8     retrig_velocity_offsets[64]; /* @0x0204..0x0243.  Retrig velocity offsets (-128..+127)     */
   sU8     trig_note;                   /* @0x0244           <void> trigNote                          */
   sU8     trig_velocity;               /* @0x0245           <void> trigVelocity                      */
   sU8     trig_note_length;            /* @0x0246           <void> trigLength                        */
   s_u16_t trig_flags;                  /* @0x0247           <void> trigFlags (BIG ENDIAN!)           */
   sU8     __unknown1;                  /* @0x0249           <void> unknown                           */
   sU8     num_steps;                   /* @0x024A           Number of steps (1..64)                  */
   sU8     quantize_amount;             /* @0x024B           <void> quantizeAmount                    */
   sU8     sound_locks[64];             /* @0x024C..0x028B   <void> soundLocks                        */
   sU8     flags_and_speed;             /* @0x028C. bit7=send MIDI. 
                                                    bit2..0: speed, 0=2x, 1=3/2x, 2=1x, 3=3/4x, 4=1/2x, 5=1/4x, 6=1/8x
                                        */
} ar_pattern_track_t;


/*
 *
 ** P-Lock sequence structure
 *
 */
typedef struct { /* 0x42 bytes */
   sU8 plock_type;  /* @0x20ec           0xFF=unused seq. See AR_PLOCK_TYPE_xxx               */
   sU8 track_nr;    /* @0x20ed           0xFF=unused seq. Tracknr (0..12)                     */
   sU8 data[64];    /* @0x20ee..0x212d.  Plock data (64 steps, value range is type dependent) */
} ar_plock_seq_t;
                    

/*
 *
 ** Pattern structure
 *
 */
typedef struct { /* 0x3386 bytes (v1),  0x3395 bytes (v4 / v1.50) */
   sU8                magic_header[4];  /* ??? a version number ??? reads '00 00 00 01' (v1) and '00 00 00 03' (v4 / v1.50) */
   ar_pattern_track_t tracks[13];       /* @0x0004..0x20F8 (0x289 bytes per track in v4, 0x288 in v1) */
   ar_plock_seq_t     plock_seqs[72];   /* @0x20F9..0x3388 */
   sU8                __unknown2;       /* @0x3389           Reads 0x00  */
   sU8                pattern_len;      /* @0x338A           Master length (in adv mode). 1=inf */
   sU8                master_chg_msb;   /* @0x338B           <void> masterChange MSB */
   sU8                master_chg_lsb;   /* @0x338C           <void> masterChange LSB (1=OFF, 2=2, 3=3, ..,  ) */
   sU8                __unknown5;       /* @0x338D           Reads 0x00 <void> kitnr */
   sU8                swing_amount;     /* @0x338E           <void> swingAmount (0..) */
   sU8                __unknown6;       /* @0x338F           Reads 0x00 <void> timeMode (normal or advanced) */
   sU8                pattern_speed;    /* @0x3390           See AR_SPD_xxx. */
   sU8                global_quantize;  /* @0x3391 */
   sU8                bpm_msb;          /* @0x3392 multiplied by 120 */
   sU8                bpm_lsb;          /* @0x3393                   */
   sU8                __unknown10;      /* @0x3394 */
} ar_pattern_t;


/*
 * Create pattern sysex request.
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
S_EXTERN ar_error_t ar_pattern_request(sU8 *_dstBuf, sU8 _devId, sU8 _patternNr);


/*
 * Create pattern workbuffer sysex request.
 *
 *  Arguments:
 *     _dstbuf - Destination buffer. Must be large enough to hold the request string (15 bytes, see AR_SYSEX_REQUEST_MSG_SZ).
 *      _devId - Sysex device id (0..15).
 *
 *  Returns:
 *   AR_ERR_OK if the request was created successfully.
 *
 */
S_EXTERN ar_error_t ar_pattern_request_x(sU8 *_dstBuf, sU8 _devId, sU8 _patternNr);


/*
 * Convert pattern sysex dump (starting with 0xF0) to 'raw' 8bit data.
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
S_EXTERN ar_error_t ar_pattern_syx_to_raw(sU8             *_rawBuf,
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
S_EXTERN ar_error_t ar_pattern_raw_to_syx(sU8                   *_syxBuf,
                                          const sU8             *_rawBuf,
                                          sU32                   _rawBufSize,
                                          sU32                  *_retSyxBufSize,
                                          const ar_sysex_meta_t *_meta
                                          );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_PATTERN_H__ */
