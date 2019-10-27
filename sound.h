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
 * ---- created: 21Aug2017
 * ---- changed: 21Oct2019, 24Oct2019, 25Oct2019, 26Oct2019
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

#define AR_SOUND_MACHINE_BD_HARD      ( 0)
#define AR_SOUND_MACHINE_BD_CLASSIC   ( 1)
#define AR_SOUND_MACHINE_SD_HARD      ( 2)
#define AR_SOUND_MACHINE_SD_CLASSIC   ( 3)
#define AR_SOUND_MACHINE_RS_HARD      ( 4)
#define AR_SOUND_MACHINE_RS_CLASSIC   ( 5)
#define AR_SOUND_MACHINE_CP_CLASSIC   ( 6)
#define AR_SOUND_MACHINE_BT_CLASSIC   ( 7)
#define AR_SOUND_MACHINE_XT_CLASSIC   ( 8)
#define AR_SOUND_MACHINE_CH_CLASSIC   ( 9)
#define AR_SOUND_MACHINE_OH_CLASSIC   (10)
#define AR_SOUND_MACHINE_CY_CLASSIC   (11)
#define AR_SOUND_MACHINE_CB_CLASSIC   (12)
#define AR_SOUND_MACHINE_BD_FM        (13)
#define AR_SOUND_MACHINE_SD_FM        (14)
#define AR_SOUND_MACHINE_NOISE_GEN    (15)
#define AR_SOUND_MACHINE_IMPULSE      (16)
#define AR_SOUND_MACHINE_CH_METALLIC  (17)
#define AR_SOUND_MACHINE_OH_METALLIC  (18)
#define AR_SOUND_MACHINE_CY_METALLIC  (19)
#define AR_SOUND_MACHINE_CB_METALLIC  (20)
#define AR_SOUND_MACHINE_BD_PLASTIC   (21)
#define AR_SOUND_MACHINE_BD_SILKY     (22)
#define AR_SOUND_MACHINE_SD_NATURAL   (23)
#define AR_SOUND_MACHINE_HH_BASIC     (24)
#define AR_SOUND_MACHINE_CY_RIDE      (25)
#define AR_SOUND_MACHINE_BD_SHARP     (26)
#define AR_SOUND_MACHINE_DISABLE      (27)
#define AR_SOUND_MACHINE_DUAL_VCO     (28)
#define AR_NUM_SOUND_MACHINES         (29)

extern const char *const ar_sound_machine_names [AR_NUM_SOUND_MACHINES];

// each list is terminated by id=-1
extern const sSI *ar_sound_compatible_machines [12/*num_tracks*/];

// (note) in UI list order
#define AR_SOUND_LFO_DEST_NONE     (41)  // 0x29
#define AR_SOUND_LFO_DEST_SYN_1    ( 0)  // 0x00 (e.g. LEV) (machine-dependent)
#define AR_SOUND_LFO_DEST_SYN_2    ( 1)  // 0x01 (e.g. TUN)
#define AR_SOUND_LFO_DEST_SYN_3    ( 2)  // 0x02 (e.g. DEC)
#define AR_SOUND_LFO_DEST_SYN_4    ( 3)  // 0x03 (e.g. TYP)
#define AR_SOUND_LFO_DEST_SYN_5    ( 4)  // 0x04 (e.g. MOD)
#define AR_SOUND_LFO_DEST_SYN_6    ( 5)  // 0x05 (e.g. SWT)
#define AR_SOUND_LFO_DEST_SYN_7    ( 6)  // 0x06 (e.g. SWD)
#define AR_SOUND_LFO_DEST_SYN_8    ( 7)  // 0x07 (e.g. TIC)
#define AR_SOUND_LFO_DEST_SMP_TUN  ( 8)  // 0x08
#define AR_SOUND_LFO_DEST_SMP_FIN  ( 9)  // 0x09
#define AR_SOUND_LFO_DEST_SMP_SMP  (10)  // 0x0A
#define AR_SOUND_LFO_DEST_SMP_BR   (11)  // 0x0B
#define AR_SOUND_LFO_DEST_SMP_STA  (12)  // 0x0C
#define AR_SOUND_LFO_DEST_SMP_END  (13)  // 0x0D
#define AR_SOUND_LFO_DEST_SMP_LOP  (14)  // 0x0E
#define AR_SOUND_LFO_DEST_SMP_LEV  (15)  // 0x0F
#define AR_SOUND_LFO_DEST_FLT_ENV  (23)  // 0x17
#define AR_SOUND_LFO_DEST_FLT_ATK  (16)  // 0x10
#define AR_SOUND_LFO_DEST_FLT_DEC  (18)  // 0x12
#define AR_SOUND_LFO_DEST_FLT_SUS  (17)  // 0x11
#define AR_SOUND_LFO_DEST_FLT_REL  (19)  // 0x13
#define AR_SOUND_LFO_DEST_FLT_FRQ  (20)  // 0x14
#define AR_SOUND_LFO_DEST_FLT_RES  (21)  // 0x15
#define AR_SOUND_LFO_DEST_AMP_ATK  (24)  // 0x18
#define AR_SOUND_LFO_DEST_AMP_HLD  (25)  // 0x19
#define AR_SOUND_LFO_DEST_AMP_DEC  (26)  // 0x1A
#define AR_SOUND_LFO_DEST_AMP_OVR  (27)  // 0x1B
#define AR_SOUND_LFO_DEST_AMP_VOL  (31)  // 0x1F
#define AR_SOUND_LFO_DEST_AMP_PAN  (30)  // 0x1E
#define AR_SOUND_LFO_DEST_AMP_ACC  (32)  // 0x20  ("AMP:Accent Level", [FUNC]+[BANK B/F])
#define AR_SOUND_LFO_DEST_AMP_DLY  (28)  // 0x1C
#define AR_SOUND_LFO_DEST_AMP_REV  (29)  // 0x1D

#define AR_NUM_SOUND_LFO_DEST_UI   (33)
#define AR_NUM_SOUND_LFO_DEST_INT  (42)

#define AR_SOUND_MAX_LFO_DEST_NAME  (24)

extern const char *const ar_sound_lfo_dest_names_ui [AR_NUM_SOUND_LFO_DEST_UI];
extern const sUI         ar_sound_lfo_dest_ids_ui   [AR_NUM_SOUND_LFO_DEST_UI];  // maps UI list index to dest index
extern const sUI         ar_sound_lfo_dest_ids_int  [AR_NUM_SOUND_LFO_DEST_INT]; // maps dest index to UI list index



/* (note) request sound workbuffers 0..11 ("SOUNDX") to retrieve track sounds 1..12 */

typedef struct { /* 0xA8 (168) bytes */

   /* track01 kit offset:   46 (0x002E)
      track02 kit offset:  214 (0x00D6)
      track03 kit offset:  382 (0x017E)
      track04 kit offset:  550 (0x0226)
      track05 kit offset:  718 (0x02CE)
      track06 kit offset:  886 (0x0376)
      track07 kit offset: 1054 (0x041E)
      track08 kit offset: 1222 (0x04C6)
      track09 kit offset: 1390 (0x056E)
      track10 kit offset: 1558 (0x0616)
      track11 kit offset: 1726 (0x06BE)
      track12 kit offset: 1894 (0x0766)
   */

   sU8 __unknown_arr1[0xc];   /* @0x0000 */

   sU8 name[0xf];
   sU8 __pad_name;            /* @0x001B  (ASCIIZ?) */

   sU8 synth_param_1;         /* @0x001C
                                          0:bd hard     : lev
                                          1:bd classic  : lev
                                          2:sd hard     : lev
                                          3:sd classic  : lev
                                          4:rs hard     : lev
                                          5:rs classic  : lev
                                          6:cp classic  : lev
                                          7:bt classic  : lev
                                          8:xt classic  : lev
                                          9:ch classic  : lev
                                         10:oh classic  : lev
                                         11:cy classic  : lev
                                         12:cb classic  : lev
                                         13:bd fm       : lev
                                         14:sd fm       : lev
                                         15:noise gen   : lev
                                         16:impulse     : lev
                                         17:ch metallic : lev
                                         18:oh metallic : lev
                                         19:cy metallic : lev
                                         20:cb metallic : lev
                                         21:bd plastic  : lev
                                         22:bd silky    : lev
                                         23:sd natural  : lev
                                         24:hh basic    : lev
                                         25:cy ride     : lev
                                         26:bd sharp    : lev
                                         27:DISABLE     : -
                                         28:dual vco    : lev
                               */
   sU8 __unused_pad1;  /* synth_param_1_lsb. unused, always 0 */

   sU8 synth_param_2;         /* @0x001E
                                          0:bd hard     : tun (64=+0)
                                          1:bd classic  : tun (64=+0)
                                          2:sd hard     : tun (64=+0)
                                          3:sd classic  : tun (64=+0)
                                          4:rs hard     : tun (64=+0)
                                          5:rs classic  : t1  (64=+0)
                                          6:cp classic  : ton (0..127)
                                          7:bt classic  : tun (64=+0)
                                          8:xt classic  : tun (64=+0)
                                          9:ch classic  : tun (64=+0)
                                         10:oh classic  : tun (64=+0)
                                         11:cy classic  : tun (64=+0)
                                         12:cb classic  : tun (64=+0)
                                         13:bd fm       : tun (64=+0)
                                         14:sd fm       : tun (64=+0)
                                         15:noise gen   : lpf
                                         16:impulse     : atk
                                         17:ch metallic : tun (64=+0)
                                         18:oh metallic : tun (64=+0)
                                         19:cy metallic : tun (64=+0)
                                         20:cb metallic : tun (64=+0)
                                         21:bd plastic  : tun (64=+0)
                                         22:bd silky    : tun (64=+0)
                                         23:sd natural  : tun (64=+0)
                                         24:hh basic    : tun (64=+0)
                                         25:cy ride     : tun (64=+0)
                                         26:bd sharp    : tun (64=+0)
                                         27:DISABLE     : -
                                         28:dual vco    : tun (64=+0)
                              */
   sU8 __unused_pad2;  /* synth_param_2_lsb. unused, always 0 */

   sU8 synth_param_3;         /* @0x0020
                                          0:bd hard     : dec
                                          1:bd classic  : dec
                                          2:sd hard     : dec
                                          3:sd classic  : dec
                                          4:rs hard     : dec
                                          5:rs classic  : dec
                                          6:cp classic  : nod
                                          7:bt classic  : dec
                                          8:xt classic  : dec
                                          9:ch classic  : dec
                                         10:oh classic  : dec
                                         11:cy classic  : dec
                                         12:cb classic  : dec
                                         13:bd fm       : dec
                                         14:sd fm       : dec
                                         15:noise gen   : dec
                                         16:impulse     : dec
                                         17:ch metallic : dec
                                         18:oh metallic : dec
                                         19:cy metallic : dec
                                         20:cb metallic : dec
                                         21:bd plastic  : dec
                                         22:bd silky    : dec
                                         23:sd natural  : bdy
                                         24:hh basic    : dec
                                         25:cy ride     : dec
                                         26:bd sharp    : dec
                                         27:DISABLE     : -
                                         28:dual vco    : dec#1
                              */
   sU8 __unused_pad3;  /* synth_param_3_lsb. unused, always 0 */

   sU8 synth_param_4;         /* @0x0022
                                          0:bd hard     : hld
                                          1:bd classic  : hld
                                          2:sd hard     : swd
                                          3:sd classic  : det
                                          4:rs hard     : swd
                                          5:rs classic  : bal (64=+0)
                                          6:cp classic  : num
                                          7:bt classic  : -
                                          8:xt classic  : swd
                                          9:ch classic  : col (64=+0)
                                         10:oh classic  : col (64=+0)
                                         11:cy classic  : col (64=+0)
                                         12:cb classic  : det
                                         13:bd fm       : fma
                                         14:sd fm       : fmt (64=+0)
                                         15:noise gen   : hpf
                                         16:impulse     : -
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : ton (64=+0)
                                         20:cb metallic : det
                                         21:bd plastic  : typ
                                         22:bd silky    : hld
                                         23:sd natural  : dec
                                         24:hh basic    : ton (64=+0)
                                         25:cy ride     : typ (0..3=A..D)
                                         26:bd sharp    : hld
                                         27:DISABLE     : -
                                         28:dual vco    : det
                              */
   sU8 __unused_pad4;  /* synth_param_4_lsb. unused, always 0 */

   sU8 synth_param_5;         /* @0x0024
                                          0:bd hard     : swt
                                          1:bd classic  : swt
                                          2:sd hard     : tic
                                          3:sd classic  : snp
                                          4:rs hard     : tic
                                          5:rs classic  : t2  (64=+0)
                                          6:cp classic  : rat
                                          7:bt classic  : nol
                                          8:xt classic  : swt
                                          9:ch classic  : -
                                         10:oh classic  : -
                                         11:cy classic  : ton (64=+0)
                                         12:cb classic  :
                                         13:bd fm       : swt
                                         14:sd fm       : fmd
                                         15:noise gen   : lpq
                                         16:impulse     : -
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : trd
                                         20:cb metallic : -
                                         21:bd plastic  : mod
                                         22:bd silky    : swt
                                         23:sd natural  : bal (0..127)
                                         24:hh basic    : trd
                                         25:cy ride     : hit
                                         26:bd sharp    : swt
                                         27:DISABLE     : -
                                         28:dual vco    : dec#2
                              */
   sU8 __unused_pad5;  /* synth_param_5_lsb. unused, always 0 */

   sU8 synth_param_6;         /* @0x0026
                                          0:bd hard     : snp
                                          1:bd classic  : swd
                                          2:sd hard     : nod
                                          3:sd classic  : nod
                                          4:rs hard     : nol
                                          5:rs classic  : sym (64=+0)
                                          6:cp classic  : nol
                                          7:bt classic  : snp
                                          8:xt classic  : nod
                                          9:ch classic  : -
                                         10:oh classic  : -
                                         11:cy classic  : -
                                         12:cb classic  : -
                                         13:bd fm       : fms
                                         14:sd fm       : nod
                                         15:noise gen   : atk
                                         16:impulse     : -
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : -
                                         20:cb metallic : -
                                         21:bd plastic  : swt
                                         22:bd silky    : swd
                                         23:sd natural  : lpf
                                         24:hh basic    : rst (0 or 1)
                                         25:cy ride     : c1
                                         26:bd sharp    : swd
                                         27:DISABLE     : -
                                         28:dual vco    : bal (64=+0)
                              */
   sU8 __unused_pad6;  /* synth_param_6_lsb. unused, always 0 */

   sU8 synth_param_7;         /* @0x0028
                                          0:bd hard     : wav
                                          1:bd classic  : wav
                                          2:sd hard     : nol
                                          3:sd classic  : nol
                                          4:rs hard     : syn
                                          5:rs classic  : nol
                                          6:cp classic  : rnd
                                          7:bt classic  : -
                                          8:xt classic  : nol
                                          9:ch classic  : -
                                         10:oh classic  : -
                                         11:cy classic  : -
                                         12:cb classic  : -
                                         13:bd fm       : fmd
                                         14:sd fm       : nol
                                         15:noise gen   : swt
                                         16:impulse     : -
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : -
                                         20:cb metallic : -
                                         21:bd plastic  : swd
                                         22:bd silky    : dus
                                         23:sd natural  : hpf
                                         24:hh basic    : -
                                         25:cy ride     : c2
                                         26:bd sharp    : wav
                                         27:DISABLE     : -
                                         28:dual vco    : bnd (64=+0)
                              */
   sU8 __unused_pad7;  /* synth_param_7_lsb. unused, always 0 */

   sU8 synth_param_8;         /* @0x002A
                                          0:bd hard     : tic
                                          1:bd classic  : tra
                                          2:sd hard     : swt
                                          3:sd classic  : bal (64=+0)
                                          4:rs hard     : swt
                                          5:rs classic  : tic
                                          6:cp classic  : cpd
                                          7:bt classic  : -
                                          8:xt classic  : ton (64=+0)
                                          9:ch classic  : -
                                         10:oh classic  : -
                                         11:cy classic  : -
                                         12:cb classic  : -
                                         13:bd fm       : fmt (64=+0)
                                         14:sd fm       : fma
                                         15:noise gen   : swd (64=+0)
                                         16:impulse     : pol (0 or 1)
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : -
                                         20:cb metallic : -
                                         21:bd plastic  : tic
                                         22:bd silky    : clk
                                         23:sd natural  : res
                                         24:hh basic    : -
                                         25:cy ride     : c3
                                         26:bd sharp    : tic
                                         27:DISABLE     : -
                                         28:dual vco    : cfg (0..79)
                              */
   sU8 __unused_pad8;  /* synth_param_8_lsb. unused, always 0 */

   sU8 sample_tune;           /* @0x002c  0x40=0, 0x41=+1, .. */
   sU8 __unused_pad9;         /* @0x002d (lsb, always 0) */

   sU8 sample_fine_tune;      /* @0x002e  0x40=0, 0x41=+1, .. */
   sU8 __unused_pad10;        /* @0x002f (lsb, always 0) */

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
   sU8 __unused_pad11;        /* @0x0031 (lsb, always 0) */

   sU8 sample_br;             /* @0x0032  */
   sU8 __unused_pad12;        /* @0x0033 (lsb, always 0) */

   sU8 sample_start_offset;   /* @0x0034 */
   sU8 __unused_pad13;        /* @0x0035 (lsb, always 0) */

   sU8 sample_end_offset;     /* @0x0036 */
   sU8 __unused_pad14;        /* @0x0037 (lsb, always 0) */

   sU8 sample_loop_flag;      /* @0x0038  0x00=off, 0x01=on */
   sU8 __unused_pad15;        /* @0x0039 */

   sU8 sample_volume;         /* @0x003a */
   sU8 __unused_pad16;        /* @0x003b (lsb, always 0) */

   sU8 flt_attack;            /* @0x003c */
   sU8 __unused_pad17;        /* @0x003d (lsb, always 0) */

   sU8 flt_sustain;           /* @0x003e */
   sU8 __unused_pad18;        /* @0x003f (lsb, always 0) */

   sU8 flt_decay;             /* @0x0040 */
   sU8 __unused_pad19;        /* @0x0041 (lsb, always 0) */

   sU8 flt_release;           /* @0x0042 */
   sU8 __unused_pad20;        /* @0x0043 (lsb, always 0) */

   sU8 flt_cutoff;            /* @0x0044 */
   sU8 __unused_pad21;        /* @0x0045 (lsb, always 0) */

   sU8 flt_res;               /* @0x0046 */
   sU8 __unused_pad22;        /* @0x0047 (lsb, always 0) */

   sU8 flt_type;              /* @0x0048 */
   sU8 __unused_pad23;        /* @0x0049 (lsb, always 0) */

   sU8 flt_env;               /* @0x004a    64=0, 127=+63, 0=-64*/
   sU8 __unused_pad24;        /* @0x004b (lsb, always 0) */

   sU8 amp_attack;            /* @0x004c */
   sU8 __unused_pad25;        /* @0x004d (lsb, always 0) */

   sU8 amp_hold;              /* @0x004e */
   sU8 __unused_pad26;        /* @0x004f (lsb, always 0) */

   sU8 amp_decay;             /* @0x0050 */
   sU8 __unused_pad27;        /* @0x0051 (lsb, always 0) */

   sU8 amp_overdrive;         /* @0x0052 */
   sU8 __unused_pad28;        /* @0x0053 (lsb, always 0) */

   sU8 amp_delay_send;        /* @0x0054 */
   sU8 __unused_pad29;        /* @0x0055 (lsb, always 0) */

   sU8 amp_reverb_send;       /* @0x0056 */
   sU8 __unused_pad30;        /* @0x0057 (lsb, always 0) */

   sU8 amp_pan;               /* @0x0058 */
   sU8 __unused_pad31;        /* @0x0059 (lsb, always 0) */

   sU8 amp_volume;            /* @0x005a */
   sU8 __unused_pad32;        /* @0x005b (lsb, always 0) */

   sU8 __unknown2;            /* @0x005c */
   sU8 __unknown3;            /* @0x005d */

   sU8 lfo_speed;             /* @0x005e */
   sU8 __unused_pad33;        /* @0x005f (lsb, always 0) */

   sU8 lfo_multiplier;        /* @0x0060 */
   sU8 __unused_pad34;        /* @0x0061 (lsb, always 0) */

   sU8 lfo_fade;              /* @0x0062  0x40=0 */
   sU8 __unused_pad35;        /* @0x0063 (lsb, always 0) */

   sU8 lfo_dest;              /* @0x0064  see LFO_DEST_xxx */
   sU8 __unused_pad36;        /* @0x0065 (lsb, always 0) */

   sU8 lfo_wav;               /* @0x0066  0x0=tri, 0x1=sin, .. */
   sU8 __unused_pad37;        /* @0x0067 (lsb, always 0) */

   sU8 lfo_start_phase;       /* @0x0068 */
   sU8 __unused_pad38;        /* @0x0069 (lsb, always 0) */

   sU8 lfo_mode;              /* @0x006a  0x0=free, 0x1=trg, .. */
   sU8 __unused_pad39;        /* @0x006b (lsb, always 0) */

   sU8 lfo_depth_msb;         /* @0x006c  */
   sU8 lfo_depth_lsb;         /* @0x006d  */

   sU8 def_note;              /* @0x006e  0x3c=0, 0x3d=+1, 0x3b=-1 (initially 0x00 == +0 ?!)
                                   (note) not used in sound dump ? (only in kit?!!)
                               */
   sU8 __unknown_arr2[0xd];   /* @0x006f..0x007B  (correct location of trig/vel/def_len/.. ?) */

   sU8 machine_type;          /* @0x007C   0:bd hard       1:bd classic    2:sd hard       3:sd classic
                                           4:rs hard       5:rs classic    6:cp classic    7:bt classic
                                           8:xt classic    9:ch classic   10:oh classic   11:cy classic
                                          12:cb classic   13:bd fm        14:sd fm        15:noise gen
                                          16:impulse      17:ch metallic  18:oh metallic  19:cy metallic
                                          20:cb metallic  21:bd plastic   22:bd silky     23:sd natural
                                          24:hh basic     25:cy ride      26:bd sharp     27:DISABLE
                                          28:dual vco     29:             30:             31:

                                          track01: kit off=170
                                          track02: kit off=338
                                          track03: kit off=506
                                          track04: kit off=674
                                          track05: kit off=842
                                          track06: kit off=1010
                                          track07: kit off=1178
                                          track08: kit off=1346
                                          track09: kit off=1514
                                          track10: kit off=1682
                                          track11: kit off=1850
                                          track12: kit off=2018
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


/*
 * Query machine name
 *
 *  Arguments:
 *   _sound - Pointer to ar_sound_t (e.g. &kit.tracks[4])
 *
 *  Returns:
 *   Machine name or NULL if the machine type is invalid or _sound is NULL.
 *
 */
const char *ar_sound_get_machine_name (const ar_sound_t *_sound);


/*
 * Query machine name by idx
 *
 *  Arguments:
 *   _machineIdx - Machine id (0..AR_NUM_SOUND_MACHINES)
 *
 *  Returns:
 *   Machine name or NULL if machine index is invalid.
 *
 */
const char *ar_sound_get_machine_name_by_id (sUI _machineId);


/*
 * Query machine id by track and UI list idx
 *
 *  (note) to query all compatible machines, call this fxn until it returns -1.
 *
 *  Arguments:
 *     _trackIdx - Track index (0..11)
 *      _listIdx - Machine UI list index (0..n)
 *
 *  Returns:
 *   Machine id or -1 if the track or machine index is invalid.
 *
 */
sSI ar_sound_get_machine_id_by_track_and_list_idx (sUI _trackIdx, sUI _listIdx);


/*
 * Query UI list index by track index and machine id.
 *
 *  Arguments:
 *     _trackIdx - Track index (0..11)
 *    _machineId - Machine id (0..AR_NUM_SOUND_MACHINES)
 *
 *  Returns:
 *   Machine id or -1 if the track or machine index is invalid.
 *
 */
sSI ar_sound_get_list_index_by_track_idx_and_machine_id(sUI _trackIdx, sUI _machineId);


/*
 * Query machine parameter short name (synth param 1..8)
 *
 *  Arguments:
 *           _sound - Pointer to ar_sound_t (e.g. &kit.tracks[4])
 *   _synthParamIdx - Synth parameter index (0..7)
 *
 *  Returns:
 *   Parameter name (TUN, LEV, ..) or NULL if the machine type or _synthParamIdx is invalid, or _sound is NULL.
 *
 */
const char *ar_sound_get_machine_param_short_name (const ar_sound_t *_sound, sUI _synthParamIdx);


/*
 * Query LFO destination name
 *
 *  Arguments:
 *      _sound - Pointer to ar_sound_t (e.g. &kit.tracks[4])
 *     _retBuf - Returns the null-terminated LFO destination name
 *   _retBufSz - Size of the char buffer (at least AR_SOUND_MAX_LFO_DEST_NAME (24) chars)
 *
 *  Returns:
 *   S_TRUE when the query succeeded or S_FALSE if the machine type is invalid or _sound is NULL.
 *
 */
sBool ar_sound_get_lfo_dest_name (const ar_sound_t *_sound, char *_retBuf, sUI _retBufSz);


/*
 * Map LFO destination UI list idx to synth-internal index.
 *
 *  Arguments:
 *    _listIdx - UI list index  (0..AR_NUM_SOUND_LFO_DEST_UI)
 *
 *  Returns:
 *   Synth internal LFO destination index. -1 if an error occured (invalid listIdx).
 *
 */
sSI ar_sound_get_lfo_dest_by_list_idx (sUI _listIdx);


/*
 * Map LFO destination synth-internal index to list idx.
 *
 *  Arguments:
 *    _lfoDest - Synth-internal LFO destination index  (0..AR_NUM_SOUND_LFO_DEST_INT)
 *
 *  Returns:
 *   UI list index. -1 if an error occured (invalid internal index).
 *
 */
sSI ar_sound_get_list_idx_by_lfo_dest (sUI _lfoDest);


/*
 * Query LFO destination name by UI list index
 *
 *  Arguments:
 *      _sound - Pointer to ar_sound_t (e.g. &kit.tracks[4])
 *    _listIdx - UI list index  (0..AR_NUM_SOUND_LFO_DEST_UI)
 *     _retBuf - Returns the null-terminated LFO destination name
 *   _retBufSz - Size of the char buffer (at least AR_SOUND_MAX_LFO_DEST_NAME (24) chars)
 *
 *  Returns:
 *   S_TRUE when the query succeeded or S_FALSE if the machine type is invalid or _sound is NULL.
 *
 */
sBool ar_sound_get_lfo_dest_name_by_list_idx (const ar_sound_t *_sound, sUI _listIdx, char *_retBuf, sUI _retBufSz);


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_SOUND_H__ */
