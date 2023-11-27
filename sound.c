/* ----
 * ---- file   : sound.c
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
 * ---- created: 21Aug2017
 * ---- changed: 25Oct2019, 26Oct2019, 15Jul2021, 25Nov2023, 27Nov2023
 * ----
 * ----
 */

#define AR_DEBUG  defined

#include <stdio.h>  /* for *snprintf() */

#include "types.h"
#include "debug.h"
#include "error.h"
#include "sysex.h"
#include "sound.h"


/* ---------------------------------------------------------------------------- vars */
const char *const ar_sound_machine_names[AR_NUM_SOUND_MACHINES] = {
   "bd hard",      //  0
   "bd classic",   //  1
   "sd hard",      //  2
   "sd classic",   //  3
   "rs hard",      //  4
   "rs classic",   //  5
   "cp classic",   //  6
   "bt classic",   //  7
   "xt classic",   //  8
   "ch classic",   //  9
   "oh classic",   // 10
   "cy classic",   // 11
   "cb classic",   // 12
   "bd fm",        // 13
   "sd fm",        // 14
   "ut noise",     // 15  (note) renamed from "noise gen" in FW1.70
   "ut impulse",   // 16  (note) renamed from "impulse" in FW1.70
   "ch metallic",  // 17
   "oh metallic",  // 18
   "cy metallic",  // 19
   "cb metallic",  // 20
   "bd plastic",   // 21
   "bd silky",     // 22
   "sd natural",   // 23
   "hh basic",     // 24
   "cy ride",      // 25
   "bd sharp",     // 26
   "DISABLE",      // 27
   "sy dual vco",  // 28  (note) renamed from "dual vco" in FW1.70
   "sy chip",      // 29  (note) added in FW1.70
   "bd acoustic",  // 30  (note) added in FW1.70
   "sd acoustic",  // 31  (note) added in FW1.70
   "sy raw",       // 32  (note) added in FW1.70
   "hh lab",       // 33  (note) added in FW1.70
};


static const sSI ar_sound_compatible_machines_01[] =
   // 01: BD  (bd_sd_dualvco_noise_impulse)
   {
      AR_SOUND_MACHINE_BD_HARD,
      AR_SOUND_MACHINE_BD_CLASSIC,
      AR_SOUND_MACHINE_BD_FM,
      AR_SOUND_MACHINE_BD_PLASTIC,
      AR_SOUND_MACHINE_BD_SILKY,
      AR_SOUND_MACHINE_BD_SHARP,
      AR_SOUND_MACHINE_BD_ACOUSTIC,

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,
      AR_SOUND_MACHINE_SD_ACOUSTIC,

      AR_SOUND_MACHINE_SY_DUAL_VCO,
      AR_SOUND_MACHINE_SY_CHIP,
      AR_SOUND_MACHINE_SY_RAW,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_02[] =
   // 02: SD  (bd_sd_dualvco_noise_impulse)
   {
      AR_SOUND_MACHINE_BD_HARD,
      AR_SOUND_MACHINE_BD_CLASSIC,
      AR_SOUND_MACHINE_BD_FM,
      AR_SOUND_MACHINE_BD_PLASTIC,
      AR_SOUND_MACHINE_BD_SILKY,
      AR_SOUND_MACHINE_BD_SHARP,
      AR_SOUND_MACHINE_BD_ACOUSTIC,

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,
      AR_SOUND_MACHINE_SD_ACOUSTIC,

      AR_SOUND_MACHINE_SY_DUAL_VCO,
      AR_SOUND_MACHINE_SY_CHIP,
      AR_SOUND_MACHINE_SY_RAW,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_03[] =
   // 03: RS  (bd_sd_rs_cp_dualvco_noise_impulse)
   {
      AR_SOUND_MACHINE_BD_HARD,
      AR_SOUND_MACHINE_BD_CLASSIC,
      AR_SOUND_MACHINE_BD_FM,
      AR_SOUND_MACHINE_BD_PLASTIC,
      AR_SOUND_MACHINE_BD_SILKY,
      AR_SOUND_MACHINE_BD_SHARP,
      AR_SOUND_MACHINE_BD_ACOUSTIC,

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,
      AR_SOUND_MACHINE_SD_ACOUSTIC,

      AR_SOUND_MACHINE_RS_HARD,
      AR_SOUND_MACHINE_RS_CLASSIC,

      AR_SOUND_MACHINE_CP_CLASSIC,

      AR_SOUND_MACHINE_SY_DUAL_VCO,
      AR_SOUND_MACHINE_SY_CHIP,
      AR_SOUND_MACHINE_SY_RAW,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_04[] =
   // 04: CP  (bd_sd_rs_cp_dualvco_noise_impulse)
   {
      AR_SOUND_MACHINE_BD_HARD,
      AR_SOUND_MACHINE_BD_CLASSIC,
      AR_SOUND_MACHINE_BD_FM,
      AR_SOUND_MACHINE_BD_PLASTIC,
      AR_SOUND_MACHINE_BD_SILKY,
      AR_SOUND_MACHINE_BD_SHARP,
      AR_SOUND_MACHINE_BD_ACOUSTIC,

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,
      AR_SOUND_MACHINE_SD_ACOUSTIC,

      AR_SOUND_MACHINE_RS_HARD,
      AR_SOUND_MACHINE_RS_CLASSIC,

      AR_SOUND_MACHINE_CP_CLASSIC,

      AR_SOUND_MACHINE_SY_DUAL_VCO,
      AR_SOUND_MACHINE_SY_CHIP,
      AR_SOUND_MACHINE_SY_RAW,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_05[] =
   // 05: BT  (bt_noise_impulse)
   {
      AR_SOUND_MACHINE_BT_CLASSIC,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_06[] =
   // 06: LT  (xt_noise_impulse)
   {
      AR_SOUND_MACHINE_XT_CLASSIC,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_07[] =
   // 07: MT  (xt_noise_impulse)
   {
      AR_SOUND_MACHINE_XT_CLASSIC,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_08[] =
   // 08: HT  (xt_noise_impulse)
   {
      AR_SOUND_MACHINE_XT_CLASSIC,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_09[] =
   // 09: CH  (ch_oh_noise_impulse)
   {
      AR_SOUND_MACHINE_CH_CLASSIC,
      AR_SOUND_MACHINE_CH_METALLIC,

      AR_SOUND_MACHINE_OH_CLASSIC,
      AR_SOUND_MACHINE_OH_METALLIC,

      AR_SOUND_MACHINE_HH_BASIC,
      AR_SOUND_MACHINE_HH_LAB,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_10[] =
   // 10: OH  (ch_oh_noise_impulse)
   {
      AR_SOUND_MACHINE_CH_CLASSIC,
      AR_SOUND_MACHINE_CH_METALLIC,

      AR_SOUND_MACHINE_OH_CLASSIC,
      AR_SOUND_MACHINE_OH_METALLIC,

      AR_SOUND_MACHINE_HH_BASIC,
      AR_SOUND_MACHINE_HH_LAB,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_11[] =
   // 11: CY  (cy_cb_noise_impulse)
   {
      AR_SOUND_MACHINE_CY_CLASSIC,
      AR_SOUND_MACHINE_CY_METALLIC,
      AR_SOUND_MACHINE_CY_RIDE,

      AR_SOUND_MACHINE_CB_CLASSIC,
      AR_SOUND_MACHINE_CB_METALLIC,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_12[] =
   // 12: CB  (cy_cb_noise_impulse)
   {
      AR_SOUND_MACHINE_CY_CLASSIC,
      AR_SOUND_MACHINE_CY_METALLIC,
      AR_SOUND_MACHINE_CY_RIDE,

      AR_SOUND_MACHINE_CB_CLASSIC,
      AR_SOUND_MACHINE_CB_METALLIC,

      AR_SOUND_MACHINE_UT_NOISE,
      AR_SOUND_MACHINE_UT_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

const sSI *ar_sound_compatible_machines[/*12 num_tracks*/] = {
   ar_sound_compatible_machines_01,
   ar_sound_compatible_machines_02,
   ar_sound_compatible_machines_03,
   ar_sound_compatible_machines_04,
   ar_sound_compatible_machines_05,
   ar_sound_compatible_machines_06,
   ar_sound_compatible_machines_07,
   ar_sound_compatible_machines_08,
   ar_sound_compatible_machines_09,
   ar_sound_compatible_machines_10,
   ar_sound_compatible_machines_11,
   ar_sound_compatible_machines_12
};

const char *const ar_sound_lfo_dest_names_ui[AR_NUM_SOUND_LFO_DEST_UI] = {
   "META:None",           // AR_SOUND_LFO_DEST_NONE
   "Synth Param 1",       // AR_SOUND_LFO_DEST_SYN_1
   "Synth Param 2",       // AR_SOUND_LFO_DEST_SYN_2
   "Synth Param 3",       // AR_SOUND_LFO_DEST_SYN_3
   "Synth Param 4",       // AR_SOUND_LFO_DEST_SYN_4
   "Synth Param 5",       // AR_SOUND_LFO_DEST_SYN_5
   "Synth Param 6",       // AR_SOUND_LFO_DEST_SYN_6
   "Synth Param 7",       // AR_SOUND_LFO_DEST_SYN_7
   "Synth Param 8",       // AR_SOUND_LFO_DEST_SYN_8
   "SAMP:Tune",           // AR_SOUND_LFO_DEST_SMP_TUN
   "SAMP:Fine Tune",      // AR_SOUND_LFO_DEST_SMP_FIN
   "SAMP:Sample Slot",    // AR_SOUND_LFO_DEST_SMP_SMP
   "SAMP:Bit Reduction",  // AR_SOUND_LFO_DEST_SMP_BR
   "SAMP:Start",          // AR_SOUND_LFO_DEST_SMP_STA
   "SAMP:End",            // AR_SOUND_LFO_DEST_SMP_END
   "SAMP:Loop",           // AR_SOUND_LFO_DEST_SMP_LOP
   "SAMP:Level",          // AR_SOUND_LFO_DEST_SMP_LEV
   "FILT:Env. Depth",     // AR_SOUND_LFO_DEST_FLT_ENV
   "FILT:Attack Time",    // AR_SOUND_LFO_DEST_FLT_ATK
   "FILT:Decay Time",     // AR_SOUND_LFO_DEST_FLT_DEC
   "FILT:Sustain Level",  // AR_SOUND_LFO_DEST_FLT_SUS
   "FILT:Release Time",   // AR_SOUND_LFO_DEST_FLT_REL
   "FILT:Frequency",      // AR_SOUND_LFO_DEST_FLT_FRQ
   "FILT:Resonance",      // AR_SOUND_LFO_DEST_FLT_RES
   "AMP:Attack Time",     // AR_SOUND_LFO_DEST_AMP_ATK
   "AMP:Hold Time",       // AR_SOUND_LFO_DEST_AMP_HLD
   "AMP:Decay Time",      // AR_SOUND_LFO_DEST_AMP_DEC
   "AMP:Overdrive",       // AR_SOUND_LFO_DEST_AMP_OVR
   "AMP:Volume",          // AR_SOUND_LFO_DEST_AMP_VOL
   "AMP:Pan",             // AR_SOUND_LFO_DEST_AMP_PAN
   "AMP:Accent Level",    // AR_SOUND_LFO_DEST_AMP_ACC
   "AMP:Delay Send",      // AR_SOUND_LFO_DEST_AMP_DLY
   "AMP:Reverb Send",     // AR_SOUND_LFO_DEST_AMP_REV
};

// UI list index to internal id
const sUI ar_sound_lfo_dest_ids_ui[AR_NUM_SOUND_LFO_DEST_UI] = {
   AR_SOUND_LFO_DEST_NONE,
   AR_SOUND_LFO_DEST_SYN_1,
   AR_SOUND_LFO_DEST_SYN_2,
   AR_SOUND_LFO_DEST_SYN_3,
   AR_SOUND_LFO_DEST_SYN_4,
   AR_SOUND_LFO_DEST_SYN_5,
   AR_SOUND_LFO_DEST_SYN_6,
   AR_SOUND_LFO_DEST_SYN_7,
   AR_SOUND_LFO_DEST_SYN_8,
   AR_SOUND_LFO_DEST_SMP_TUN,
   AR_SOUND_LFO_DEST_SMP_FIN,
   AR_SOUND_LFO_DEST_SMP_SMP,
   AR_SOUND_LFO_DEST_SMP_BR,
   AR_SOUND_LFO_DEST_SMP_STA,
   AR_SOUND_LFO_DEST_SMP_END,
   AR_SOUND_LFO_DEST_SMP_LOP,
   AR_SOUND_LFO_DEST_SMP_LEV,
   AR_SOUND_LFO_DEST_FLT_ENV,
   AR_SOUND_LFO_DEST_FLT_ATK,
   AR_SOUND_LFO_DEST_FLT_DEC,
   AR_SOUND_LFO_DEST_FLT_SUS,
   AR_SOUND_LFO_DEST_FLT_REL,
   AR_SOUND_LFO_DEST_FLT_FRQ,
   AR_SOUND_LFO_DEST_FLT_RES,
   AR_SOUND_LFO_DEST_AMP_ATK,
   AR_SOUND_LFO_DEST_AMP_HLD,
   AR_SOUND_LFO_DEST_AMP_DEC,
   AR_SOUND_LFO_DEST_AMP_OVR,
   AR_SOUND_LFO_DEST_AMP_VOL,
   AR_SOUND_LFO_DEST_AMP_PAN,
   AR_SOUND_LFO_DEST_AMP_ACC,
   AR_SOUND_LFO_DEST_AMP_DLY,
   AR_SOUND_LFO_DEST_AMP_REV
};

// internal id to UI list index
const sUI ar_sound_lfo_dest_ids_int[AR_NUM_SOUND_LFO_DEST_INT] = {
   1,   // AR_SOUND_LFO_DEST_SYN_1    ( 0)  // 0x00 (e.g. LEV) (machine-dependent)
   2,   // AR_SOUND_LFO_DEST_SYN_2    ( 1)  // 0x01 (e.g. TUN)
   3,   // AR_SOUND_LFO_DEST_SYN_3    ( 2)  // 0x02 (e.g. DEC)
   4,   // AR_SOUND_LFO_DEST_SYN_4    ( 3)  // 0x03 (e.g. TYP)
   5,   // AR_SOUND_LFO_DEST_SYN_5    ( 4)  // 0x04 (e.g. MOD)
   6,   // AR_SOUND_LFO_DEST_SYN_6    ( 5)  // 0x05 (e.g. SWT)
   7,   // AR_SOUND_LFO_DEST_SYN_7    ( 6)  // 0x06 (e.g. SWD)
   8,   // AR_SOUND_LFO_DEST_SYN_8    ( 7)  // 0x07 (e.g. TIC)
   9,   // AR_SOUND_LFO_DEST_SMP_TUN  ( 8)  // 0x08
   10,  // AR_SOUND_LFO_DEST_SMP_FIN  ( 9)  // 0x09
   11,  // AR_SOUND_LFO_DEST_SMP_SMP  (10)  // 0x0A
   12,  // AR_SOUND_LFO_DEST_SMP_BR   (11)  // 0x0B
   13,  // AR_SOUND_LFO_DEST_SMP_STA  (12)  // 0x0C
   14,  // AR_SOUND_LFO_DEST_SMP_END  (13)  // 0x0D
   15,  // AR_SOUND_LFO_DEST_SMP_LOP  (14)  // 0x0E
   16,  // AR_SOUND_LFO_DEST_SMP_LEV  (15)  // 0x0F
   18,  // AR_SOUND_LFO_DEST_FLT_ATK  (16)  // 0x10
   20,  // AR_SOUND_LFO_DEST_FLT_SUS  (17)  // 0x11
   19,  // AR_SOUND_LFO_DEST_FLT_DEC  (18)  // 0x12
   21,  // AR_SOUND_LFO_DEST_FLT_REL  (19)  // 0x13
   22,  // AR_SOUND_LFO_DEST_FLT_FRQ  (20)  // 0x14
   23,  // AR_SOUND_LFO_DEST_FLT_RES  (21)  // 0x15
   -1,  // (22)
   17,  // AR_SOUND_LFO_DEST_FLT_ENV  (23)  // 0x17
   24,  // AR_SOUND_LFO_DEST_AMP_ATK  (24)  // 0x18
   25,  // AR_SOUND_LFO_DEST_AMP_HLD  (25)  // 0x19
   26,  // AR_SOUND_LFO_DEST_AMP_DEC  (26)  // 0x1A
   27,  // AR_SOUND_LFO_DEST_AMP_OVR  (27)  // 0x1B
   31,  // AR_SOUND_LFO_DEST_AMP_DLY  (28)  // 0x1C
   32,  // AR_SOUND_LFO_DEST_AMP_REV  (29)  // 0x1D
   29,  // AR_SOUND_LFO_DEST_AMP_PAN  (30)  // 0x1E
   28,  // AR_SOUND_LFO_DEST_AMP_VOL  (31)  // 0x1F
   30,  // AR_SOUND_LFO_DEST_AMP_ACC  (32)  // 0x20  ("AMP:Accent Level", [FUNC]+[BANK B/F])
   -1,  // (33)
   -1,  // (34)
   -1,  // (35)
   -1,  // (36)
   -1,  // (37)
   -1,  // (38)
   -1,  // (39)
   -1,  // (40)
    0,  // AR_SOUND_LFO_DEST_NONE     (41)  // 0x29
};

// velocity+aftertouch mod destinations:
const char *const ar_sound_mod_dest_names_ui[AR_NUM_SOUND_MOD_DEST_UI] = {
   /*  0 */ "META:None",           // AR_SOUND_MOD_DEST_NONE            (41)
   /*  1 */ "LFO Multiplier",      // AR_SOUND_MOD_DEST_LFO_MULTIPLIER  (34)
   /*  2 */ "LFO:Waveform",        // AR_SOUND_MOD_DEST_LFO_WAVEFORM    (37)
   /*  3 */ "LFO:Trig Mode",       // AR_SOUND_MOD_DEST_LFO_TRIGMODE    (39)
   /*  4 */ "LFO:Speed",           // AR_SOUND_MOD_DEST_LFO_SPEED       (33)
   /*  5 */ "LFO:Fade In/Out",     // AR_SOUND_MOD_DEST_LFO_FADE        (35)
   /*  6 */ "LFO:Start Phase",     // AR_SOUND_MOD_DEST_LFO_PHASE       (38)
   /*  7 */ "LFO:Depth",           // AR_SOUND_MOD_DEST_LFO_DEPTH       (40)
   /*  8 */ "Synth Param 1",       // AR_SOUND_MOD_DEST_SYN_1           ( 0)
   /*  9 */ "Synth Param 2",       // AR_SOUND_MOD_DEST_SYN_2           ( 1)
   /* 10 */ "Synth Param 3",       // AR_SOUND_MOD_DEST_SYN_3           ( 2)
   /* 11 */ "Synth Param 4",       // AR_SOUND_MOD_DEST_SYN_4           ( 3)
   /* 12 */ "Synth Param 5",       // AR_SOUND_MOD_DEST_SYN_5           ( 4)
   /* 13 */ "Synth Param 6",       // AR_SOUND_MOD_DEST_SYN_6           ( 5)
   /* 14 */ "Synth Param 7",       // AR_SOUND_MOD_DEST_SYN_7           ( 6)
   /* 15 */ "Synth Param 8",       // AR_SOUND_MOD_DEST_SYN_8           ( 7)
   /* 16 */ "SAMP:Tune",           // AR_SOUND_MOD_DEST_SMP_TUN         ( 8)  // 0x08
   /* 17 */ "SAMP:Fine Tune",      // AR_SOUND_MOD_DEST_SMP_FIN         ( 9)  // 0x09
   /* 18 */ "SAMP:Sample Slot",    // AR_SOUND_MOD_DEST_SMP_SMP         (10)  // 0x0A
   /* 19 */ "SAMP:Bit Reduction",  // AR_SOUND_MOD_DEST_SMP_BR          (11)  // 0x0B
   /* 20 */ "SAMP:Start",          // AR_SOUND_MOD_DEST_SMP_STA         (12)  // 0x0C
   /* 21 */ "SAMP:End",            // AR_SOUND_MOD_DEST_SMP_END         (13)  // 0x0D
   /* 22 */ "SAMP:Loop",           // AR_SOUND_MOD_DEST_SMP_LOP         (14)  // 0x0E
   /* 23 */ "SAMP:Level",          // AR_SOUND_MOD_DEST_SMP_LEV         (15)  // 0x0F
   /* 24 */ "FILT:Env. Depth",     // AR_SOUND_MOD_DEST_FLT_ENV         (23)  // 0x17
   /* 25 */ "FILT:Attack Time",    // AR_SOUND_MOD_DEST_FLT_ATK         (16)  // 0x10
   /* 26 */ "FILT:Decay Time",     // AR_SOUND_MOD_DEST_FLT_DEC         (18)  // 0x12
   /* 27 */ "FILT:Sustain Level",  // AR_SOUND_MOD_DEST_FLT_SUS         (17)  // 0x11
   /* 28 */ "FILT:Release Time",   // AR_SOUND_MOD_DEST_FLT_REL         (19)  // 0x13
   /* 29 */ "FILT:Frequency",      // AR_SOUND_MOD_DEST_FLT_FRQ         (20)  // 0x14
   /* 30 */ "FILT:Resonance",      // AR_SOUND_MOD_DEST_FLT_RES         (21)  // 0x15
   /* 31 */ "AMP:Attack Time",     // AR_SOUND_MOD_DEST_AMP_ATK         (24)  // 0x18
   /* 32 */ "AMP:Hold Time",       // AR_SOUND_MOD_DEST_AMP_HLD         (25)  // 0x19
   /* 33 */ "AMP:Decay Time",      // AR_SOUND_MOD_DEST_AMP_DEC         (26)  // 0x1A
   /* 34 */ "AMP:Overdrive",       // AR_SOUND_MOD_DEST_AMP_OVR         (27)  // 0x1B
   /* 35 */ "AMP:Volume",          // AR_SOUND_MOD_DEST_AMP_VOL         (31)  // 0x1F
   /* 36 */ "AMP:Pan",             // AR_SOUND_MOD_DEST_AMP_PAN         (30)  // 0x1E
   /* 37 */ "AMP:Accent Level",    // AR_SOUND_MOD_DEST_AMP_ACC         (32)  // 0x20
   /* 38 */ "AMP:Delay Send",      // AR_SOUND_MOD_DEST_AMP_DLY         (28)  // 0x1C
   /* 39 */ "AMP:Reverb Send",     // AR_SOUND_MOD_DEST_AMP_REV         (29)  // 0x1D
};

// UI list index to internal id
const sUI ar_sound_mod_dest_ids_ui[AR_NUM_SOUND_MOD_DEST_UI] = {
   AR_SOUND_MOD_DEST_NONE,
   AR_SOUND_MOD_DEST_LFO_MULTIPLIER,
   AR_SOUND_MOD_DEST_LFO_WAVEFORM,
   AR_SOUND_MOD_DEST_LFO_TRIGMODE,
   AR_SOUND_MOD_DEST_LFO_SPEED,
   AR_SOUND_MOD_DEST_LFO_FADE,
   AR_SOUND_MOD_DEST_LFO_PHASE,
   AR_SOUND_MOD_DEST_LFO_DEPTH,
   AR_SOUND_MOD_DEST_SYN_1,
   AR_SOUND_MOD_DEST_SYN_2,
   AR_SOUND_MOD_DEST_SYN_3,
   AR_SOUND_MOD_DEST_SYN_4,
   AR_SOUND_MOD_DEST_SYN_5,
   AR_SOUND_MOD_DEST_SYN_6,
   AR_SOUND_MOD_DEST_SYN_7,
   AR_SOUND_MOD_DEST_SYN_8,
   AR_SOUND_MOD_DEST_SMP_TUN,
   AR_SOUND_MOD_DEST_SMP_FIN,
   AR_SOUND_MOD_DEST_SMP_SMP,
   AR_SOUND_MOD_DEST_SMP_BR,
   AR_SOUND_MOD_DEST_SMP_STA,
   AR_SOUND_MOD_DEST_SMP_END,
   AR_SOUND_MOD_DEST_SMP_LOP,
   AR_SOUND_MOD_DEST_SMP_LEV,
   AR_SOUND_MOD_DEST_FLT_ENV,
   AR_SOUND_MOD_DEST_FLT_ATK,
   AR_SOUND_MOD_DEST_FLT_DEC,
   AR_SOUND_MOD_DEST_FLT_SUS,
   AR_SOUND_MOD_DEST_FLT_REL,
   AR_SOUND_MOD_DEST_FLT_FRQ,
   AR_SOUND_MOD_DEST_FLT_RES,
   AR_SOUND_MOD_DEST_AMP_ATK,
   AR_SOUND_MOD_DEST_AMP_HLD,
   AR_SOUND_MOD_DEST_AMP_DEC,
   AR_SOUND_MOD_DEST_AMP_OVR,
   AR_SOUND_MOD_DEST_AMP_VOL,
   AR_SOUND_MOD_DEST_AMP_PAN,
   AR_SOUND_MOD_DEST_AMP_ACC,
   AR_SOUND_MOD_DEST_AMP_DLY,
   AR_SOUND_MOD_DEST_AMP_REV
};

// internal id to UI list index
const sUI ar_sound_mod_dest_ids_int[AR_NUM_SOUND_LFO_DEST_INT] = {
   /*  0 */   8,  // AR_SOUND_MOD_DEST_SYN_1    ( 0)  // 0x00 (e.g. LEV) (machine-dependent)
   /*  1 */   9,  // AR_SOUND_MOD_DEST_SYN_2    ( 1)  // 0x01 (e.g. TUN)
   /*  2 */  10,  // AR_SOUND_MOD_DEST_SYN_3    ( 2)  // 0x02 (e.g. DEC)
   /*  3 */  11,  // AR_SOUND_MOD_DEST_SYN_4    ( 3)  // 0x03 (e.g. TYP)
   /*  4 */  12,  // AR_SOUND_MOD_DEST_SYN_5    ( 4)  // 0x04 (e.g. MOD)
   /*  5 */  13,  // AR_SOUND_MOD_DEST_SYN_6    ( 5)  // 0x05 (e.g. SWT)
   /*  6 */  14,  // AR_SOUND_MOD_DEST_SYN_7    ( 6)  // 0x06 (e.g. SWD)
   /*  7 */  15,  // AR_SOUND_MOD_DEST_SYN_8    ( 7)  // 0x07 (e.g. TIC)
   /*  8 */  16,  // AR_SOUND_MOD_DEST_SMP_TUN  ( 8)  // 0x08
   /*  9 */  17,  // AR_SOUND_MOD_DEST_SMP_FIN  ( 9)  // 0x09
   /* 10 */  18,  // AR_SOUND_MOD_DEST_SMP_SMP  (10)  // 0x0A
   /* 11 */  19,  // AR_SOUND_MOD_DEST_SMP_BR   (11)  // 0x0B
   /* 12 */  20,  // AR_SOUND_MOD_DEST_SMP_STA  (12)  // 0x0C
   /* 13 */  21,  // AR_SOUND_MOD_DEST_SMP_END  (13)  // 0x0D
   /* 14 */  22,  // AR_SOUND_MOD_DEST_SMP_LOP  (14)  // 0x0E
   /* 15 */  23,  // AR_SOUND_MOD_DEST_SMP_LEV  (15)  // 0x0F
   /* 16 */  25,  // AR_SOUND_MOD_DEST_FLT_ATK  (16)  // 0x10
   /* 17 */  27,  // AR_SOUND_MOD_DEST_FLT_SUS  (17)  // 0x11
   /* 18 */  26,  // AR_SOUND_MOD_DEST_FLT_DEC  (18)  // 0x12
   /* 19 */  28,  // AR_SOUND_MOD_DEST_FLT_REL  (19)  // 0x13
   /* 20 */  29,  // AR_SOUND_MOD_DEST_FLT_FRQ  (20)  // 0x14
   /* 21 */  30,  // AR_SOUND_MOD_DEST_FLT_RES  (21)  // 0x15
   /* 22 */  -1,  // (22)
   /* 23 */  24,  // AR_SOUND_MOD_DEST_FLT_ENV  (23)  // 0x17
   /* 24 */  31,  // AR_SOUND_MOD_DEST_AMP_ATK  (24)  // 0x18
   /* 25 */  32,  // AR_SOUND_MOD_DEST_AMP_HLD  (25)  // 0x19
   /* 26 */  33,  // AR_SOUND_MOD_DEST_AMP_DEC  (26)  // 0x1A
   /* 27 */  34,  // AR_SOUND_MOD_DEST_AMP_OVR  (27)  // 0x1B
   /* 28 */  38,  // AR_SOUND_MOD_DEST_AMP_DLY  (28)  // 0x1C
   /* 29 */  39,  // AR_SOUND_MOD_DEST_AMP_REV  (29)  // 0x1D
   /* 30 */  36,  // AR_SOUND_MOD_DEST_AMP_PAN  (30)  // 0x1E
   /* 31 */  35,  // AR_SOUND_MOD_DEST_AMP_VOL  (31)  // 0x1F
   /* 32 */  37,  // AR_SOUND_MOD_DEST_AMP_ACC  (32)  // 0x20  ("AMP:Accent Level", [FUNC]+[BANK B/F])
   /* 33 */   4,  // AR_SOUND_MOD_DEST_LFO_SPEED       (33)
   /* 34 */   1,  // AR_SOUND_MOD_DEST_LFO_MULTIPLIER  (34)
   /* 35 */   5,  // AR_SOUND_MOD_DEST_LFO_FADE        (35)
   /* 36 */  -1,  // (36)
   /* 37 */   2,  // AR_SOUND_MOD_DEST_LFO_WAVEFORM    (37)
   /* 38 */   6,  // AR_SOUND_MOD_DEST_LFO_PHASE       (38)
   /* 39 */   3,  // AR_SOUND_MOD_DEST_LFO_TRIGMODE    (39)
   /* 40 */   7,  // AR_SOUND_MOD_DEST_LFO_DEPTH       (40)
   /* 41 */   0,  // AR_SOUND_MOD_DEST_NONE     (41)  // 0x29
};




// (note) in order of sysex fields (synth_param_1..8)
const char *const ar_sound_machine_param_short_names[8][AR_NUM_SOUND_MACHINES] = {
   // synth_param_1:
   {
      "LEV",  //  0:bd hard     : lev
      "LEV",  //  1:bd classic  : lev
      "LEV",  //  2:sd hard     : lev
      "LEV",  //  3:sd classic  : lev
      "LEV",  //  4:rs hard     : lev
      "LEV",  //  5:rs classic  : lev
      "LEV",  //  6:cp classic  : lev
      "LEV",  //  7:bt classic  : lev
      "LEV",  //  8:xt classic  : lev
      "LEV",  //  9:ch classic  : lev
      "LEV",  // 10:oh classic  : lev
      "LEV",  // 11:cy classic  : lev
      "LEV",  // 12:cb classic  : lev
      "LEV",  // 13:bd fm       : lev
      "LEV",  // 14:sd fm       : lev
      "LEV",  // 15:ut noise    : lev
      "LEV",  // 16:ut impulse  : lev
      "LEV",  // 17:ch metallic : lev
      "LEV",  // 18:oh metallic : lev
      "LEV",  // 19:cy metallic : lev
      "LEV",  // 20:cb metallic : lev
      "LEV",  // 21:bd plastic  : lev
      "LEV",  // 22:bd silky    : lev
      "LEV",  // 23:sd natural  : lev
      "LEV",  // 24:hh basic    : lev
      "LEV",  // 25:cy ride     : lev
      "LEV",  // 26:bd sharp    : lev
      "-",    // 27:DISABLE     : -
      "LEV",  // 28:sy dual vco : lev
      "LEV",  // 29:sy chip     : lev
      "LEV",  // 30:bd acoustic : lev
      "LEV",  // 31:sd acoustic : lev
      "LEV",  // 32:sy raw      : lev
      "LEV",  // 33:hh lab      : lev
   },

   // synth_param_2:
   {
      "TUN",  //  0:bd hard     : tun (64=+0)
      "TUN",  //  1:bd classic  : tun (64=+0)
      "TUN",  //  2:sd hard     : tun (64=+0)
      "TUN",  //  3:sd classic  : tun (64=+0)
      "TUN",  //  4:rs hard     : tun (64=+0)
      "T1",   //  5:rs classic  : t1  (64=+0)
      "TON",  //  6:cp classic  : ton (0..127)
      "TUN",  //  7:bt classic  : tun (64=+0)
      "TUN",  //  8:xt classic  : tun (64=+0)
      "TUN",  //  9:ch classic  : tun (64=+0)
      "TUN",  // 10:oh classic  : tun (64=+0)
      "TUN",  // 11:cy classic  : tun (64=+0)
      "TUN",  // 12:cb classic  : tun (64=+0)
      "TUN",  // 13:bd fm       : tun (64=+0)
      "TUN",  // 14:sd fm       : tun (64=+0)
      "LPF",  // 15:ut noise    : lpf
      "ATK",  // 16:ut impulse  : atk
      "TUN",  // 17:ch metallic : tun (64=+0)
      "TUN",  // 18:oh metallic : tun (64=+0)
      "TUN",  // 19:cy metallic : tun (64=+0)
      "TUN",  // 20:cb metallic : tun (64=+0)
      "TUN",  // 21:bd plastic  : tun (64=+0)
      "TUN",  // 22:bd silky    : tun (64=+0)
      "TUN",  // 23:sd natural  : tun (64=+0)
      "TUN",  // 24:hh basic    : tun (64=+0)
      "TUN",  // 25:cy ride     : tun (64=+0)
      "TUN",  // 26:bd sharp    : tun (64=+0)
      "-",    // 27:DISABLE     : -
      "TUN",  // 28:sy dual vco : tun (64=+0)
      "TUN",  // 29:sy chip     : tun (64=+0) (uses LSB)
      "TUN",  // 30:bd acoustic : tun (64=+0) (uses LSB)
      "TUN",  // 31:sd acoustic : tun (64=+0) (uses LSB)
      "TUN",  // 32:sy raw      : tun (64=+0) (uses LSB)
      "OSC1", // 33:hh lab      : osc1 (uses 8bit? LSB)
   },

   // synth_param_3:
   {
      "DEC",  //  0:bd hard     : dec
      "DEC",  //  1:bd classic  : dec
      "DEC",  //  2:sd hard     : dec
      "DEC",  //  3:sd classic  : dec
      "DEC",  //  4:rs hard     : dec
      "DEC",  //  5:rs classic  : dec
      "NOD",  //  6:cp classic  : nod
      "DEC",  //  7:bt classic  : dec
      "DEC",  //  8:xt classic  : dec
      "DEC",  //  9:ch classic  : dec
      "DEC",  // 10:oh classic  : dec
      "DEC",  // 11:cy classic  : dec
      "DEC",  // 12:cb classic  : dec
      "DEC",  // 13:bd fm       : dec
      "DEC",  // 14:sd fm       : dec
      "DEC",  // 15:ut noise    : dec
      "DEC",  // 16:ut impulse  : dec
      "DEC",  // 17:ch metallic : dec
      "DEC",  // 18:oh metallic : dec
      "DEC",  // 19:cy metallic : dec
      "DEC",  // 20:cb metallic : dec
      "DEC",  // 21:bd plastic  : dec
      "DEC",  // 22:bd silky    : dec
      "BDY",  // 23:sd natural  : bdy
      "DEC",  // 24:hh basic    : dec
      "DEC",  // 25:cy ride     : dec
      "DEC",  // 26:bd sharp    : dec
      "-",    // 27:DISABLE     : -
      "DEC1", // 28:sy dual vco : dec#1
      "DCY",  // 29:sy chip     : dcy
      "DEC",  // 30:bd acoustic : dec
      "BDY",  // 31:sd acoustic : bdy
      "DCY",  // 32:sy raw      : dcy (0..126,127=inf)
      "DEC",  // 33:hh lab      : dec
   },

   // synth_param_4:
   {
      "HLD",  //  0:bd hard     : hld
      "HLD",  //  1:bd classic  : hld
      "SWD",  //  2:sd hard     : swd
      "DET",  //  3:sd classic  : det
      "SWD",  //  4:rs hard     : swd
      "BAL",  //  5:rs classic  : bal (64=+0)
      "NUM",  //  6:cp classic  : num
      "-",    //  7:bt classic  : -
      "SWD",  //  8:xt classic  : swd
      "COL",  //  9:ch classic  : col (64=+0)
      "COL",  // 10:oh classic  : col (64=+0)
      "COL",  // 11:cy classic  : col (64=+0)
      "DET",  // 12:cb classic  : det
      "FMA",  // 13:bd fm       : fma
      "FMT",  // 14:sd fm       : fmt (64=+0)
      "HPF",  // 15:ut noise    : hpf
      "-",    // 16:ut impulse  : -
      "-",    // 17:ch metallic : -
      "-",    // 18:oh metallic : -
      "TON",  // 19:cy metallic : ton (64=+0)
      "DET",  // 20:cb metallic : det
      "TYP",  // 21:bd plastic  : typ
      "HLD",  // 22:bd silky    : hld
      "DEC",  // 23:sd natural  : dec
      "TON",  // 24:hh basic    : ton (64=+0)
      "TYP",  // 25:cy ride     : typ (0..3=A..D)
      "HLD",  // 26:bd sharp    : hld
      "-",    // 27:DISABLE     : -
      "DET",  // 28:sy dual vco : det
      "OF2",  // 29:sy chip     : of2 (40=-24..64=+0..88=+24)
      "HLD",  // 30:bd acoustic : hld
      "NOD",  // 31:sd acoustic : nod
      "DET",  // 32:sy raw      : det (64=+0) (uses LSB)
      "OSC2", // 33:hh lab      : osc2 (uses 8bit? LSB)
   },

   // synth_param_5:
   {
      "SWT",  //  0:bd hard     : swt
      "SWT",  //  1:bd classic  : swt
      "TIC",  //  2:sd hard     : tic
      "SNP",  //  3:sd classic  : snp
      "TIC",  //  4:rs hard     : tic
      "T2",   //  5:rs classic  : t2  (64=+0)
      "RAT",  //  6:cp classic  : rat
      "NOL",  //  7:bt classic  : nol
      "SWT",  //  8:xt classic  : swt
      "-",    //  9:ch classic  : -
      "-",    // 10:oh classic  : -
      "TON",  // 11:cy classic  : ton (64=+0)
      "PW1",  // 12:cb classic  : pw1 (64=+0)
      "SWT",  // 13:bd fm       : swt
      "FMD",  // 14:sd fm       : fmd
      "LPQ",  // 15:ut noise    : lpq
      "-",    // 16:ut impulse  : -
      "-",    // 17:ch metallic : -
      "-",    // 18:oh metallic : -
      "TRD",  // 19:cy metallic : trd
      "PW1",  // 20:cb metallic : pw1 (64=+0)
      "MOD",  // 21:bd plastic  : mod
      "SWT",  // 22:bd silky    : swt
      "BAL",  // 23:sd natural  : bal (0..127)
      "TRD",  // 24:hh basic    : trd
      "HIT",  // 25:cy ride     : hit
      "SWT",  // 26:bd sharp    : swt
      "-",    // 27:DISABLE     : -
      "DEC2", // 28:sy dual vco : dec#2
      "OF3",  // 29:sy chip     : of3 (40=-24..64=+0..88=+24)
      "SWT",  // 30:bd acoustic : swt
      "NOL",  // 31:sd acoustic : nol
      "NOL",  // 32:sy raw      : nol
      "OSC3", // 33:hh lab      : osc3 (uses 8bit? LSB)
   },

   // synth_param_6:
   {
      "SNP",  //  0:bd hard     : snp
      "SWP",  //  1:bd classic  : swd
      "NOD",  //  2:sd hard     : nod
      "NOD",  //  3:sd classic  : nod
      "NOL",  //  4:rs hard     : nol
      "SYM",  //  5:rs classic  : sym (64=+0)
      "NOL",  //  6:cp classic  : nol
      "SNP",  //  7:bt classic  : snp
      "NOD",  //  8:xt classic  : nod
      "-",    //  9:ch classic  : -
      "-",    // 10:oh classic  : -
      "-",    // 11:cy classic  : -
      "PW2",  // 12:cb classic  : pw2 (64=+0)
      "FMS",  // 13:bd fm       : fms
      "NOD",  // 14:sd fm       : nod
      "ATK",  // 15:ut noise    : atk
      "-",    // 16:ut impulse  : -
      "-",    // 17:ch metallic : -
      "-",    // 18:oh metallic : -
      "-",    // 19:cy metallic : -
      "PW2",  // 20:cb metallic : pw2 (64=+0)
      "SWT",  // 21:bd plastic  : swt
      "SWD",  // 22:bd silky    : swd
      "LPF",  // 23:sd natural  : lpf
      "RST",  // 24:hh basic    : rst (0 or 1)
      "C1",   // 25:cy ride     : c1
      "SWD",  // 26:bd sharp    : swd
      "-",    // 27:DISABLE     : -
      "BAL",  // 28:sy dual vco : bal (64=+0)
      "OF4",  // 29:sy chip     : of4 (40=-24..64=+0..88=+24)
      "SWD",  // 30:bd acoustic : swd
      "HLD",  // 31:sd acoustic : hld
      "WAV1", // 32:sy raw      : wav1 (0=sin,1=asin,2=tri,3=ssaw,4=asaw,5=saw,6=ring)
      "OSC4", // 33:hh lab      : osc4 (uses 8bit? LSB)
   },

   // synth_param_7:
   {
      "WAV",  //  0:bd hard     : wav
      "WAV",  //  1:bd classic  : wav
      "NOL",  //  2:sd hard     : nol
      "NOL",  //  3:sd classic  : nol
      "SYN",  //  4:rs hard     : syn
      "NOL",  //  5:rs classic  : nol
      "RND",  //  6:cp classic  : rnd
      "SWD",  //  7:bt classic  : swd (FW1.70+)
      "NOL",  //  8:xt classic  : nol
      "-",    //  9:ch classic  : -
      "-",    // 10:oh classic  : -
      "-",    // 11:cy classic  : -
      "-",    // 12:cb classic  : -
      "FMD",  // 13:bd fm       : fmd
      "NOL",  // 14:sd fm       : nol
      "SWT",  // 15:ut noise    : swt
      "-",    // 16:ut impulse  : -
      "-",    // 17:ch metallic : -
      "-",    // 18:oh metallic : -
      "-",    // 19:cy metallic : -
      "-",    // 20:cb metallic : -
      "SWD",  // 21:bd plastic  : swd
      "DUS",  // 22:bd silky    : dus
      "LPF",  // 23:sd natural  : hpf
      "-",    // 24:hh basic    : -
      "C2",   // 25:cy ride     : c2
      "WAV",  // 26:bd sharp    : wav
      "-",    // 27:DISABLE     : -
      "BND",  // 28:sy dual vco : bnd (64=+0)
      "WAV",  // 29:sy chip     : wav (0=sin..127=p99%)
      "WAV",  // 30:bd acoustic : wav (0=sinA,1=sinB,2=asinA,3=asinB,4=triA,5=triB,6=ssawA,7=ssawB,8=sawA,9=sawB,10=sqrA,11=sqrA)
      "SWD",  // 31:sd acoustic : swd
      "WAV2", // 32:sy raw      : wav2 (0=sineA,1=ssawA,2=sineB,3=ssawB)
      "OSC5", // 33:hh lab      : osc5 (uses 8bit? LSB)
   },

   // synth_param_8:
   {
      "TIC",  //  0:bd hard     : tic
      "TRA",  //  1:bd classic  : tra
      "SWT",  //  2:sd hard     : swt
      "BAL",  //  3:sd classic  : bal (64=+0)
      "SWT",  //  4:rs hard     : swt
      "TIC",  //  5:rs classic  : tic
      "CPD",  //  6:cp classic  : cpd
      "-",    //  7:bt classic  : -
      "TON",  //  8:xt classic  : ton (64=+0)
      "-",    //  9:ch classic  : -
      "-",    // 10:oh classic  : -
      "-",    // 11:cy classic  : -
      "-",    // 12:cb classic  : -
      "FMT",  // 13:bd fm       : fmt (64=+0)
      "FMA",  // 14:sd fm       : fma
      "SWD",  // 15:ut noise    : swd (64=+0)
      "POL",  // 16:ut impulse  : pol (0 or 1)
      "-",    // 17:ch metallic : -
      "-",    // 18:oh metallic : -
      "-",    // 19:cy metallic : -
      "-",    // 20:cb metallic : -
      "TIC",  // 21:bd plastic  : tic
      "CLK",  // 22:bd silky    : clk
      "RES",  // 23:sd natural  : res
      "-",    // 24:hh basic    : -
      "C3",   // 25:cy ride     : c3
      "TIC",  // 26:bd sharp    : tic
      "-",    // 27:DISABLE     : -
      "CFG",  // 28:sy dual vco : cfg (0..79)
      "SPD",  // 29:sy chip     : spd (0=128T..65=25 5Hz)
      "IMP",  // 30:bd acoustic : imp
      "IMP",  // 31:sd acoustic : imp
      "BAL",  // 32:sy raw      : bal (64=+0)
      "OSC6", // 33:hh lab      : osc6 (uses 8bit? LSB)
   },
};



/* ---------------------------------------------------------------------------- ar_sound_request */
ar_error_t ar_sound_request(sU8 *_dstBuf, sU8 _devId, sU8 _soundNr) {
   ar_sysex_meta_t meta;
   ar_error_t ret;

   AR_SYSEX_META_INIT(meta, _devId, AR_TYPE_SOUND, _soundNr);

   ret = ar_sysex_request(_dstBuf, &meta);

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_request_x */
ar_error_t ar_sound_request_x(sU8 *_dstBuf, sU8 _devId, sU8 _soundNr) {
   ar_sysex_meta_t meta;
   ar_error_t ret;

   AR_SYSEX_META_INIT(meta, _devId, AR_TYPE_SOUND, (128u + (_soundNr & 127u)));

   ret = ar_sysex_request(_dstBuf, &meta);

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_syx_to_raw */
ar_error_t ar_sound_syx_to_raw(sU8               *_rawBuf,
                               const sU8         *_syxBuf,
                               sU32               _syxBufSize,
                               sU32              *_retRawBufSize,
                               ar_sysex_meta_t   *_meta
                               ) {
   ar_error_t ret;
   sU32 datSz;
   ar_sysex_meta_t meta;

   ret = ar_sysex_to_raw(_rawBuf, &_syxBuf, &_syxBufSize, &datSz, &meta);

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

      if(AR_TYPE_SOUND == meta.obj_type)
      {
         /* Succeeded */
      }
      else
      {
         ret = AR_ERR_NOT_A_SOUND;
      }
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_raw_to_syx */
ar_error_t ar_sound_raw_to_syx(sU8                   *_syxBuf,
                               const sU8             *_rawBuf,
                               sU32                   _rawBufSize,
                               sU32                  *_retSyxBufSize,
                               const ar_sysex_meta_t *_meta
                               ) {
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

/* ---------------------------------------------------------------------------- ar_sound_get_machine_name */
const char *ar_sound_get_machine_name(const ar_sound_t *_sound) {
   const char *ret = NULL;
   if(NULL != _sound)
   {
      if(_sound->machine_type < AR_NUM_SOUND_MACHINES)
      {
         ret = ar_sound_machine_names[_sound->machine_type];
      }
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_machine_name_by_id */
const char *ar_sound_get_machine_name_by_id(sUI _machineId) {
   const char *ret;
   if(_machineId < AR_NUM_SOUND_MACHINES)
      ret = ar_sound_machine_names[_machineId];
   else
      ret = NULL;
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_machine_id_by_track_and_list_idx */
sSI ar_sound_get_machine_id_by_track_and_list_idx(sUI _trackIdx, sUI _listIdx) {
   sSI ret = -1;
   if(_trackIdx < 12u)
   {
      sUI listIdx = 0u;
      const sSI *id = ar_sound_compatible_machines[_trackIdx];
      while(-1 != *id)
      {
         if(listIdx == _listIdx)
         {
            ret = *id;
            break;
         }
         id++;
         listIdx++;
      }
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_list_index_by_track_idx_and_machine_id */
sSI ar_sound_get_list_index_by_track_idx_and_machine_id(sUI _trackIdx, sUI _machineId) {
   sSI ret = -1;
   if(_trackIdx < 12u)
   {
      sUI listIdx = 0u;
      const sSI *id = ar_sound_compatible_machines[_trackIdx];
      while(-1 != *id)
      {
         if(*id == (sSI)_machineId)
         {
            ret = listIdx;
            break;
         }
         listIdx++;
         id++;
      }
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_machine_param_short_name */
const char *ar_sound_get_machine_param_short_name(const ar_sound_t *_sound, sUI _synthParamIdx) {
   const char *ret = NULL;
   if(_synthParamIdx < 8u)
   {
      if(NULL != _sound)
      {
         if(_sound->machine_type < AR_NUM_SOUND_MACHINES)
         {
            ret = ar_sound_machine_param_short_names[_synthParamIdx][_sound->machine_type];
         }
      }
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_lfo_dest_name */
sBool ar_sound_get_lfo_dest_name(const ar_sound_t *_sound, char *_retBuf, sUI _retBufSz) {
   sBool ret = S_FALSE;
   if(NULL != _sound)
   {
      if(_sound->machine_type < AR_NUM_SOUND_MACHINES)
      {
         if(_retBufSz >= AR_SOUND_MAX_LFO_DEST_NAME)
         {
            if(_sound->lfo_dest < 8u)
            {
               // e.g. "Synth Param 5 [DEC2]"
               Dsnprintf(_retBuf,
                         _retBufSz,
                         "%s [%s]",
                         ar_sound_lfo_dest_names_ui[ar_sound_lfo_dest_ids_int[_sound->lfo_dest]],
                         ar_sound_machine_param_short_names[_sound->lfo_dest][_sound->machine_type]
                         );
               ret = S_TRUE;
            }
            else if(_sound->lfo_dest < AR_NUM_SOUND_LFO_DEST_INT)
            {
               sSI listIdx = ar_sound_lfo_dest_ids_int[_sound->lfo_dest];

               if(-1 != listIdx)
               {
                  // e.g. "SAMP:Bit Reduction"
                  Dsnprintf(_retBuf,
                            _retBufSz,
                            "%s",
                            ar_sound_lfo_dest_names_ui[listIdx]
                            );
                  ret = S_TRUE;
               }
            }
            else
            {
               Dprintf("[---] ar_sound_get_lfo_dest_name: invalid lfo_dest=%u (0x%02x)\n", _sound->lfo_dest, _sound->lfo_dest);
            }
         }
      }
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_lfo_dest_by_list_idx */
sSI ar_sound_get_lfo_dest_by_list_idx(sUI _listIdx) {
   sSI ret;
   if(_listIdx < AR_NUM_SOUND_LFO_DEST_UI)
   {
      ret = ar_sound_lfo_dest_ids_ui[_listIdx];
   }
   else
   {
      ret = -1;
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_list_idx_by_lfo_dest */
sSI ar_sound_get_list_idx_by_lfo_dest(sUI _lfoDest) {
   sSI ret;
   if(_lfoDest < AR_NUM_SOUND_LFO_DEST_INT)
   {
      ret = ar_sound_lfo_dest_ids_int[_lfoDest];
   }
   else
   {
      ret = -1;
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_lfo_dest_name */
sBool ar_sound_get_lfo_dest_name_by_list_idx(const ar_sound_t *_sound, sUI _listIdx, char *_retBuf, sUI _retBufSz) {
   sBool ret = S_FALSE;
   if(NULL != _sound)
   {
      if(_sound->machine_type < AR_NUM_SOUND_MACHINES)
      {
         if(_retBufSz >= AR_SOUND_MAX_LFO_DEST_NAME)
         {
            if( (_listIdx >= 1u) && (_listIdx <= 8u) )
            {
               // e.g. "Synth Param 5 [DEC2]"
               Dsnprintf(_retBuf,
                         _retBufSz,
                         "%s [%s]",
                         ar_sound_lfo_dest_names_ui[_listIdx],
                         ar_sound_machine_param_short_names[_listIdx - 1u][_sound->machine_type]
                         );
               ret = S_TRUE;
            }
            else if(_listIdx < AR_NUM_SOUND_LFO_DEST_UI)
            {
               // e.g. "SAMP:Bit Reduction"
               Dsnprintf(_retBuf,
                         _retBufSz,
                         "%s",
                         ar_sound_lfo_dest_names_ui[_listIdx]
                         );
               ret = S_TRUE;
            }
            else
            {
               Dprintf("[---] ar_sound_get_lfo_dest_name_by_list_idx: invalid lfo listIdx=%u\n", _listIdx);
            }
         }
      }
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_mod_dest_name */
sBool ar_sound_get_mod_dest_name(const ar_sound_t *_sound, sUI _modDestId, char *_retBuf, sUI _retBufSz) {
   sBool ret = S_FALSE;
   if(NULL != _sound)
   {
      if(_sound->machine_type < AR_NUM_SOUND_MACHINES)
      {
         if(_retBufSz >= AR_SOUND_MAX_LFO_DEST_NAME)
         {
            if(_modDestId < 8u)
            {
               // e.g. "Synth Param 5 [DEC2]"
               Dsnprintf(_retBuf,
                         _retBufSz,
                         "%s [%s]",
                         ar_sound_mod_dest_names_ui[ar_sound_mod_dest_ids_int[_modDestId]],
                         ar_sound_machine_param_short_names[_modDestId][_sound->machine_type]
                         );
               ret = S_TRUE;
            }
            else if(_modDestId < AR_NUM_SOUND_MOD_DEST_INT)
            {
               sSI listIdx = ar_sound_mod_dest_ids_int[_modDestId];

               if(-1 != listIdx)
               {
                  // e.g. "SAMP:Bit Reduction"
                  Dsnprintf(_retBuf,
                            _retBufSz,
                            "%s",
                            ar_sound_mod_dest_names_ui[listIdx]
                            );
                  ret = S_TRUE;
               }
            }
            else
            {
               Dprintf("[---] ar_sound_get_mod_dest_name: invalid modDestId=%u (0x%02x)\n", _modDestId, _modDestId);
            }
         }
      }
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_mod_dest_by_list_idx */
sSI ar_sound_get_mod_dest_by_list_idx(sUI _listIdx) {
   sSI ret;
   if(_listIdx < AR_NUM_SOUND_MOD_DEST_UI)
   {
      ret = ar_sound_mod_dest_ids_ui[_listIdx];
   }
   else
   {
      ret = -1;
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_list_idx_by_mod_dest */
sSI ar_sound_get_list_idx_by_mod_dest(sUI _modDest) {
   sSI ret;
   if(_modDest < AR_NUM_SOUND_MOD_DEST_INT)
   {
      ret = ar_sound_mod_dest_ids_int[_modDest];
   }
   else
   {
      ret = -1;
   }
   return ret;
}

/* ---------------------------------------------------------------------------- ar_sound_get_mod_dest_name */
sBool ar_sound_get_mod_dest_name_by_list_idx(const ar_sound_t *_sound, sUI _listIdx, char *_retBuf, sUI _retBufSz) {
   sBool ret = S_FALSE;
   if(NULL != _sound)
   {
      if(_sound->machine_type < AR_NUM_SOUND_MACHINES)
      {
         if(_retBufSz >= AR_SOUND_MAX_MOD_DEST_NAME)
         {
            if( (_listIdx >= 8u) && (_listIdx <= 15u) )
            {
               // e.g. "Synth Param 5 [DEC2]"
               Dsnprintf(_retBuf,
                         _retBufSz,
                         "%s [%s]",
                         ar_sound_mod_dest_names_ui[_listIdx],
                         ar_sound_machine_param_short_names[_listIdx - 8u][_sound->machine_type]
                         );
               ret = S_TRUE;
            }
            else if(_listIdx < AR_NUM_SOUND_MOD_DEST_UI)
            {
               // e.g. "SAMP:Bit Reduction"
               Dsnprintf(_retBuf,
                         _retBufSz,
                         "%s",
                         ar_sound_mod_dest_names_ui[_listIdx]
                         );
               ret = S_TRUE;
            }
            else
            {
               Dprintf("[---] ar_sound_get_mod_dest_name_by_list_idx: invalid mod listIdx=%u\n", _listIdx);
            }
         }
      }
   }
   return ret;
}
