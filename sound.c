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
 * ---- changed: 25Oct2019, 26Oct2019
 * ----
 * ----
 */

#define AR_DEBUG  defined

#include <stdio.h>  // for *snprintf()

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
   "noise gen",    // 15
   "impulse",      // 16
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
   "dual vco",     // 28
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

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,

      AR_SOUND_MACHINE_DUAL_VCO,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,

      AR_SOUND_MACHINE_DUAL_VCO,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,

      AR_SOUND_MACHINE_RS_HARD,
      AR_SOUND_MACHINE_RS_CLASSIC,

      AR_SOUND_MACHINE_CP_CLASSIC,

      AR_SOUND_MACHINE_DUAL_VCO,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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

      AR_SOUND_MACHINE_SD_HARD,
      AR_SOUND_MACHINE_SD_CLASSIC,
      AR_SOUND_MACHINE_SD_FM,
      AR_SOUND_MACHINE_SD_NATURAL,

      AR_SOUND_MACHINE_RS_HARD,
      AR_SOUND_MACHINE_RS_CLASSIC,

      AR_SOUND_MACHINE_CP_CLASSIC,

      AR_SOUND_MACHINE_DUAL_VCO,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_05[] =
   // 05: BT  (bt_noise_impulse)
   {
      AR_SOUND_MACHINE_BT_CLASSIC,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_06[] =
   // 06: LT  (xt_noise_impulse)
   {
      AR_SOUND_MACHINE_XT_CLASSIC,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_07[] =
   // 07: MT  (xt_noise_impulse)
   {
      AR_SOUND_MACHINE_XT_CLASSIC,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

      AR_SOUND_MACHINE_DISABLE,
      -1
   }
   ;

static const sSI ar_sound_compatible_machines_08[] =
   // 08: HT  (xt_noise_impulse)
   {
      AR_SOUND_MACHINE_XT_CLASSIC,

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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

      AR_SOUND_MACHINE_NOISE_GEN,
      AR_SOUND_MACHINE_IMPULSE,

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
      "LEV",  // 15:noise gen   : lev
      "LEV",  // 16:impulse     : lev
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
      "LEV",  // 28:dual vco    : lev
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
      "LPF",  // 15:noise gen   : lpf
      "ATK",  // 16:impulse     : atk
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
      "TUN",  // 28:dual vco    : tun (64=+0)
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
      "DEC",  // 15:noise gen   : dec
      "DEC",  // 16:impulse     : dec
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
      "DEC1", // 28:dual vco    : dec#1
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
      "HPF",  // 15:noise gen   : hpf
      "-",    // 16:impulse     : -
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
      "DET",  // 28:dual vco    : det
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
      "-",    // 12:cb classic  : -
      "SWT",  // 13:bd fm       : swt
      "FMD",  // 14:sd fm       : fmd
      "LPQ",  // 15:noise gen   : lpq
      "-",    // 16:impulse     : -
      "-",    // 17:ch metallic : -
      "-",    // 18:oh metallic : -
      "TRD",  // 19:cy metallic : trd
      "-",    // 20:cb metallic : -
      "MOD",  // 21:bd plastic  : mod
      "SWT",  // 22:bd silky    : swt
      "BAL",  // 23:sd natural  : bal (0..127)
      "TRD",  // 24:hh basic    : trd
      "HIT",  // 25:cy ride     : hit
      "SWT",  // 26:bd sharp    : swt
      "-",    // 27:DISABLE     : -
      "DEC2", // 28:dual vco    : dec#2
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
      "-",    // 12:cb classic  : -
      "FMS",  // 13:bd fm       : fms
      "NOD",  // 14:sd fm       : nod
      "ATK",  // 15:noise gen   : atk
      "-",    // 16:impulse     : -
      "-",    // 17:ch metallic : -
      "-",    // 18:oh metallic : -
      "-",    // 19:cy metallic : -
      "-",    // 20:cb metallic : -
      "SWT",  // 21:bd plastic  : swt
      "SWD",  // 22:bd silky    : swd
      "LPF",  // 23:sd natural  : lpf
      "RST",  // 24:hh basic    : rst (0 or 1)
      "C1",   // 25:cy ride     : c1
      "SWD",  // 26:bd sharp    : swd
      "-",    // 27:DISABLE     : -
      "BAL",  // 28:dual vco    : bal (64=+0)
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
      "-",    //  7:bt classic  : -
      "NOL",  //  8:xt classic  : nol
      "-",    //  9:ch classic  : -
      "-",    // 10:oh classic  : -
      "-",    // 11:cy classic  : -
      "-",    // 12:cb classic  : -
      "FMD",  // 13:bd fm       : fmd
      "NOL",  // 14:sd fm       : nol
      "SWT",  // 15:noise gen   : swt
      "-",    // 16:impulse     : -
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
      "BND",  // 28:dual vco    : bnd (64=+0)
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
      "SWD",  // 15:noise gen   : swd (64=+0)
      "POL",  // 16:impulse     : pol (0 or 1)
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
      "CFG",  // 28:dual vco    : cfg (0..79)
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
