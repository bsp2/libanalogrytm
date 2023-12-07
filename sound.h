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
 * ---- changed: 21Oct2019, 24Oct2019, 25Oct2019, 26Oct2019, 15Jul2021, 25Nov2023, 28Nov2023
 * ----          07Dec2023
 * ----
 * ----
 */

#ifndef __AR_SOUND_H__
#define __AR_SOUND_H__

#include "cplusplus_begin.h"

#pragma pack(push)
#pragma pack(1)


#define AR_SOUND_SYX_V4_SZ  207u   /* SysEx size, including F0 / F7 (FW1.50..1.61B) */
#define AR_SOUND_SYX_V5_SZ  201u   /* SysEx size, including F0 / F7 (FW1.70) */
#define AR_SOUND_SYX_SZ  AR_SOUND_SYX_V5_SZ

#define AR_SOUND_V4_SZ      168u   /* Raw, decoded size (FW1.50/1.61b) */
#define AR_SOUND_V5_SZ      162u   /* Raw, decoded size (FW1.70) */
#define AR_SOUND_SZ AR_SOUND_V5_SZ  // == sizeof(ar_sound_t)

#define AR_SOUND_MACHINE_BD_HARD       0u
#define AR_SOUND_MACHINE_BD_CLASSIC    1u
#define AR_SOUND_MACHINE_SD_HARD       2u
#define AR_SOUND_MACHINE_SD_CLASSIC    3u
#define AR_SOUND_MACHINE_RS_HARD       4u
#define AR_SOUND_MACHINE_RS_CLASSIC    5u
#define AR_SOUND_MACHINE_CP_CLASSIC    6u
#define AR_SOUND_MACHINE_BT_CLASSIC    7u
#define AR_SOUND_MACHINE_XT_CLASSIC    8u
#define AR_SOUND_MACHINE_CH_CLASSIC    9u
#define AR_SOUND_MACHINE_OH_CLASSIC   10u
#define AR_SOUND_MACHINE_CY_CLASSIC   11u
#define AR_SOUND_MACHINE_CB_CLASSIC   12u
#define AR_SOUND_MACHINE_BD_FM        13u
#define AR_SOUND_MACHINE_SD_FM        14u
#define AR_SOUND_MACHINE_UT_NOISE     15u
#define AR_SOUND_MACHINE_UT_IMPULSE   16u
#define AR_SOUND_MACHINE_CH_METALLIC  17u
#define AR_SOUND_MACHINE_OH_METALLIC  18u
#define AR_SOUND_MACHINE_CY_METALLIC  19u
#define AR_SOUND_MACHINE_CB_METALLIC  20u
#define AR_SOUND_MACHINE_BD_PLASTIC   21u
#define AR_SOUND_MACHINE_BD_SILKY     22u
#define AR_SOUND_MACHINE_SD_NATURAL   23u
#define AR_SOUND_MACHINE_HH_BASIC     24u
#define AR_SOUND_MACHINE_CY_RIDE      25u
#define AR_SOUND_MACHINE_BD_SHARP     26u
#define AR_SOUND_MACHINE_DISABLE      27u
#define AR_SOUND_MACHINE_SY_DUAL_VCO  28u
#define AR_SOUND_MACHINE_SY_CHIP      29u
#define AR_SOUND_MACHINE_BD_ACOUSTIC  30u
#define AR_SOUND_MACHINE_SD_ACOUSTIC  31u
#define AR_SOUND_MACHINE_SY_RAW       32u
#define AR_SOUND_MACHINE_HH_LAB       33u
#define AR_NUM_SOUND_MACHINES         34u

extern const char *const ar_sound_machine_names [AR_NUM_SOUND_MACHINES];

// each list is terminated by id=-1
extern const sSI *ar_sound_compatible_machines [12/*num_tracks*/];

// (note) in UI list order
#define AR_SOUND_LFO_DEST_NONE     41u  // 0x29
#define AR_SOUND_LFO_DEST_SYN_1     0u  // 0x00 (e.g. LEV) (machine-dependent)
#define AR_SOUND_LFO_DEST_SYN_2     1u  // 0x01 (e.g. TUN)
#define AR_SOUND_LFO_DEST_SYN_3     2u  // 0x02 (e.g. DEC)
#define AR_SOUND_LFO_DEST_SYN_4     3u  // 0x03 (e.g. TYP)
#define AR_SOUND_LFO_DEST_SYN_5     4u  // 0x04 (e.g. MOD)
#define AR_SOUND_LFO_DEST_SYN_6     5u  // 0x05 (e.g. SWT)
#define AR_SOUND_LFO_DEST_SYN_7     6u  // 0x06 (e.g. SWD)
#define AR_SOUND_LFO_DEST_SYN_8     7u  // 0x07 (e.g. TIC)
#define AR_SOUND_LFO_DEST_SMP_TUN   8u  // 0x08
#define AR_SOUND_LFO_DEST_SMP_FIN   9u  // 0x09
#define AR_SOUND_LFO_DEST_SMP_SMP  10u  // 0x0A
#define AR_SOUND_LFO_DEST_SMP_BR   11u  // 0x0B
#define AR_SOUND_LFO_DEST_SMP_STA  12u  // 0x0C
#define AR_SOUND_LFO_DEST_SMP_END  13u  // 0x0D
#define AR_SOUND_LFO_DEST_SMP_LOP  14u  // 0x0E
#define AR_SOUND_LFO_DEST_SMP_LEV  15u  // 0x0F
#define AR_SOUND_LFO_DEST_FLT_ENV  23u  // 0x17
#define AR_SOUND_LFO_DEST_FLT_ATK  16u  // 0x10
#define AR_SOUND_LFO_DEST_FLT_DEC  18u  // 0x12
#define AR_SOUND_LFO_DEST_FLT_SUS  17u  // 0x11
#define AR_SOUND_LFO_DEST_FLT_REL  19u  // 0x13
#define AR_SOUND_LFO_DEST_FLT_FRQ  20u  // 0x14
#define AR_SOUND_LFO_DEST_FLT_RES  21u  // 0x15
#define AR_SOUND_LFO_DEST_AMP_ATK  24u  // 0x18
#define AR_SOUND_LFO_DEST_AMP_HLD  25u  // 0x19
#define AR_SOUND_LFO_DEST_AMP_DEC  26u  // 0x1A
#define AR_SOUND_LFO_DEST_AMP_OVR  27u  // 0x1B
#define AR_SOUND_LFO_DEST_AMP_VOL  31u  // 0x1F
#define AR_SOUND_LFO_DEST_AMP_PAN  30u  // 0x1E
#define AR_SOUND_LFO_DEST_AMP_ACC  32u  // 0x20  ("AMP:Accent Level", [FUNC]+[BANK B/F])
#define AR_SOUND_LFO_DEST_AMP_DLY  28u  // 0x1C
#define AR_SOUND_LFO_DEST_AMP_REV  29u  // 0x1D

#define AR_NUM_SOUND_LFO_DEST_UI    33u
#define AR_NUM_SOUND_LFO_DEST_INT   42u
#define AR_SOUND_MAX_LFO_DEST_NAME  24u

extern const char *const ar_sound_lfo_dest_names_ui [AR_NUM_SOUND_LFO_DEST_UI];
extern const sUI         ar_sound_lfo_dest_ids_ui   [AR_NUM_SOUND_LFO_DEST_UI];  // maps UI list index to dest index
extern const sUI         ar_sound_lfo_dest_ids_int  [AR_NUM_SOUND_LFO_DEST_INT]; // maps dest index to UI list index

// (note) same ids as AR_SOUND_LFO_DEST_xxx but different selection
#define AR_SOUND_MOD_DEST_NONE            41u
#define AR_SOUND_MOD_DEST_LFO_MULTIPLIER  34u
#define AR_SOUND_MOD_DEST_LFO_WAVEFORM    37u
#define AR_SOUND_MOD_DEST_LFO_TRIGMODE    39u
#define AR_SOUND_MOD_DEST_LFO_SPEED       33u
#define AR_SOUND_MOD_DEST_LFO_FADE        35u
#define AR_SOUND_MOD_DEST_LFO_PHASE       38u
#define AR_SOUND_MOD_DEST_LFO_DEPTH       40u
#define AR_SOUND_MOD_DEST_SYN_1            0u
#define AR_SOUND_MOD_DEST_SYN_2            1u
#define AR_SOUND_MOD_DEST_SYN_3            2u
#define AR_SOUND_MOD_DEST_SYN_4            3u
#define AR_SOUND_MOD_DEST_SYN_5            4u
#define AR_SOUND_MOD_DEST_SYN_6            5u
#define AR_SOUND_MOD_DEST_SYN_7            6u
#define AR_SOUND_MOD_DEST_SYN_8            7u
#define AR_SOUND_MOD_DEST_SMP_TUN          8u  // 0x08
#define AR_SOUND_MOD_DEST_SMP_FIN          9u  // 0x09
#define AR_SOUND_MOD_DEST_SMP_SMP         10u  // 0x0A
#define AR_SOUND_MOD_DEST_SMP_BR          11u  // 0x0B
#define AR_SOUND_MOD_DEST_SMP_STA         12u  // 0x0C
#define AR_SOUND_MOD_DEST_SMP_END         13u  // 0x0D
#define AR_SOUND_MOD_DEST_SMP_LOP         14u  // 0x0E
#define AR_SOUND_MOD_DEST_SMP_LEV         15u  // 0x0F
#define AR_SOUND_MOD_DEST_FLT_ENV         23u  // 0x17
#define AR_SOUND_MOD_DEST_FLT_ATK         16u  // 0x10
#define AR_SOUND_MOD_DEST_FLT_DEC         18u  // 0x12
#define AR_SOUND_MOD_DEST_FLT_SUS         17u  // 0x11
#define AR_SOUND_MOD_DEST_FLT_REL         19u  // 0x13
#define AR_SOUND_MOD_DEST_FLT_FRQ         20u  // 0x14
#define AR_SOUND_MOD_DEST_FLT_RES         21u  // 0x15
#define AR_SOUND_MOD_DEST_AMP_ATK         24u  // 0x18
#define AR_SOUND_MOD_DEST_AMP_HLD         25u  // 0x19
#define AR_SOUND_MOD_DEST_AMP_DEC         26u  // 0x1A
#define AR_SOUND_MOD_DEST_AMP_OVR         27u  // 0x1B
#define AR_SOUND_MOD_DEST_AMP_VOL         31u  // 0x1F
#define AR_SOUND_MOD_DEST_AMP_PAN         30u  // 0x1E
#define AR_SOUND_MOD_DEST_AMP_ACC         32u  // 0x20  ("AMP:Accent Level", [FUNC]+[BANK B/F])
#define AR_SOUND_MOD_DEST_AMP_DLY         28u  // 0x1C
#define AR_SOUND_MOD_DEST_AMP_REV         29u  // 0x1D
#define AR_NUM_SOUND_MOD_DEST_UI    40u
#define AR_NUM_SOUND_MOD_DEST_INT   42u
#define AR_SOUND_MAX_MOD_DEST_NAME  24u
extern const char *const ar_sound_mod_dest_names_ui [AR_NUM_SOUND_MOD_DEST_UI];
extern const sUI         ar_sound_mod_dest_ids_ui   [AR_NUM_SOUND_MOD_DEST_UI];  // maps UI list index to dest index
extern const sUI         ar_sound_mod_dest_ids_int  [AR_NUM_SOUND_MOD_DEST_INT]; // maps dest index to UI list index



/* (note) request sound workbuffers 0..11 ("SOUNDX") to retrieve track sounds 1..12 */

/*
 *
 *
 ** track sound
 *
 *    0xA2 (162) bytes (v5/FW1.70)
 *    0xA8 (168) bytes (v4/FW1.50/1.61)
 *
 *    FW1.70: starts @offset 0x002E in ar_kit_t
 */
typedef struct {

   /* v4/FW1.50:
      track01 kit offset:   46 (0x002E)
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

   /* v5/FW1.70:
      track01 kit offset:   46 (0x002E)
      track02 kit offset:  208 (0x00D0)
      ..
    */

   sU8 __unknown_arr1[0xc];   /* @0x0000 reads BE EF BA CE 00 00 00 04 00 00 00 00 */

   sU8 name[15];              /* @0x000C */
   sU8 __pad_name;            /* @0x001B  (ASCIIZ?) */

   s_u16_t synth_param_1;     /* @0x001C  (LSB is always 0)
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
                                         15:ut noise    : lev
                                         16:ut impulse  : lev
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
                                         28:sy dual vco : lev
                                         29:sy chip     : lev
                                         30:bd acoustic : lev
                                         31:sd acoustic : lev
                                         32:sy raw      : lev
                                         33:hh lab      : lev
                               */

   s_u16_t synth_param_2;     /* @0x001E  (some machines use LSB since FW1.70
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
                                         15:ut noise    : lpf
                                         16:ut impulse  : atk
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
                                         28:sy dual vco : tun (64=+0)
                                         29:sy chip     : tun (64=+0) (uses LSB)
                                         30:bd acoustic : tun (64=+0) (uses LSB)
                                         31:sd acoustic : tun (64=+0) (uses LSB)
                                         32:sy raw      : tun (64=+0) (uses LSB)
                                         33:hh lab      : osc1 (uses 8bit? LSB)
                              */

   s_u16_t synth_param_3;     /* @0x0020  (LSB is always 0)
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
                                         15:ut noise    : dec
                                         16:ut impulse  : dec
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
                                         28:sy dual vco : dec#1
                                         29:sy chip     : dcy
                                         30:bd acoustic : dec
                                         31:sd acoustic : bdy
                                         32:sy raw      : dcy (0..126,127=inf)
                                         33:hh lab      : dec
                              */

   s_u16_t synth_param_4;     /* @0x0022  (some machines use LSB since FW1.70)
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
                                         15:ut noise    : hpf
                                         16:ut impulse  : -
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
                                         28:sy dual vco : det
                                         29:sy chip     : of2 (40=-24..64=+0..88=+24)
                                         30:bd acoustic : hld
                                         31:sd acoustic : nod
                                         32:sy raw      : det (64=+0) (uses LSB)
                                         33:hh lab      : osc2 (uses 8bit? LSB)
                              */

   s_u16_t synth_param_5;     /* @0x0024  ("hh lab" uses LSB since FW1.70)
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
                                         12:cb classic  : pw1 (64=+0)
                                         13:bd fm       : swt
                                         14:sd fm       : fmd
                                         15:ut noise    : lpq
                                         16:ut impulse  : -
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : trd
                                         20:cb metallic : pw1 (64=+0)
                                         21:bd plastic  : mod
                                         22:bd silky    : swt
                                         23:sd natural  : bal (0..127)
                                         24:hh basic    : trd
                                         25:cy ride     : hit
                                         26:bd sharp    : swt
                                         27:DISABLE     : -
                                         28:sy dual vco : dec#2
                                         29:sy chip     : of3 (40=-24..64=+0..88=+24)
                                         30:bd acoustic : swt
                                         31:sd acoustic : nol
                                         32:sy raw      : nol
                                         33:hh lab      : osc3 (uses 8bit? LSB)
                              */

   s_u16_t synth_param_6;     /* @0x0026  ("hh lab" uses LSB since FW1.70)
                                          0:bd hard     : snp
                                          1:bd classic  : swd
                                          2:sd hard     : nod
                                          3:sd classic  : nod
                                          4:rs hard     : nol
                                          5:rs classic  : sym (64=+0)
                                          6:cp classic  : nol
                                          7:bt classic  : snp (0..3)
                                          8:xt classic  : nod
                                          9:ch classic  : -
                                         10:oh classic  : -
                                         11:cy classic  : -
                                         12:cb classic  : pw2 (64=+0)
                                         13:bd fm       : fms
                                         14:sd fm       : nod
                                         15:ut noise    : atk
                                         16:ut impulse  : -
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : -
                                         20:cb metallic : pw2 (64=+0)
                                         21:bd plastic  : swt
                                         22:bd silky    : swd
                                         23:sd natural  : lpf
                                         24:hh basic    : rst (0 or 1)
                                         25:cy ride     : c1
                                         26:bd sharp    : swd
                                         27:DISABLE     : -
                                         28:sy dual vco : bal (64=+0)
                                         29:sy chip     : of4 (40=-24..64=+0..88=+24)
                                         30:bd acoustic : swd
                                         31:sd acoustic : hld
                                         32:sy raw      : wav1 (0=sin,1=asin,2=tri,3=ssaw,4=asaw,5=saw,6=ring)
                                         33:hh lab      : osc4 (uses 8bit? LSB)
                              */

   s_u16_t synth_param_7;     /* @0x0028  ("hh lab" uses LSB since FW1.70)
                                          0:bd hard     : wav
                                          1:bd classic  : wav
                                          2:sd hard     : nol
                                          3:sd classic  : nol
                                          4:rs hard     : syn
                                          5:rs classic  : nol
                                          6:cp classic  : rnd
                                          7:bt classic  : swd (FW1.70)
                                          8:xt classic  : nol
                                          9:ch classic  : -
                                         10:oh classic  : -
                                         11:cy classic  : -
                                         12:cb classic  : -
                                         13:bd fm       : fmd
                                         14:sd fm       : nol
                                         15:ut noise    : swt
                                         16:ut impulse  : -
                                         17:ch metallic : -
                                         18:oh metallic : -
                                         19:cy metallic : -
                                         20:cb metallic : -
                                         21:bd plastic  : swd
                                         22:bd silky    : dus
                                         23:sd natural  : hpf
                                         24:hh basic    : -
                                         25:cy ride     : c2
                                         26:bd sharp    : wav (0=sinA,1=sinB,2=asinA,3=asinB,4=triA,5=triB,6=ssawA,7=ssawB,8=sawA,9=sawB,10=sqrA,11=sqrB)
                                         27:DISABLE     : -
                                         28:sy dual vco : bnd (64=+0)
                                         29:sy chip     : wav (0=sin,1=asin,2=tri,3=ssaw,4=saw,5=sqr,6=noise,
                                                               7=anm1,8=anm2,9=anm3,10=anm4,11=anm5,
                                                               12=pwm+,13=pwm-,
                                                               14=triB,15=+tri,16=tri+,17=triX,
                                                               18=sawB,19=+saw,20=saw+,21=sawX,
                                                               22=sqrB,23=+sqr,24=sqr+,25=sqrX
                                                               26=tbl1,27=tbl2,28=tbl3,
                                                               29=p1%..127=p99%)
                                         30:bd acoustic : wav (0=sinA,1=sinB,2=asinA,3=asinB,4=triA,5=triB,6=ssawA,7=ssawB,8=sawA,9=sawB,10=sqrA,11=sqrB)
                                         31:sd acoustic : swd
                                         32:sy raw      : wav2 (0=sineA,1=ssawA,2=sineB,3=ssawB)
                                         33:hh lab      : osc5 (uses 8bit? LSB)
                              */

   s_u16_t synth_param_8;     /* @0x002A  ("hh lab" uses LSB since FW1.70)
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
                                         15:ut noise    : swd (64=+0)
                                         16:ut impulse  : pol (0 or 1)
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
                                         28:sy dual vco : cfg (0..79)
                                         29:sy chip     : spd (0=128T,1=128,2=64T,3=128d,4=64,5=32T,6=64d,7=32,8=16T,9=32d,10=16,11=8T,
                                                               12=16d,13=8,14=4T,15=8d,16=4,17=2T,18=4d,19=2,20=1T,21=2d,22=1,23=1d,24=1.0Hz,
                                                               25=1.56Hz,26=1.88Hz,27=2Hz,28=3.13Hz,29=3.75Hz,30=4Hz,31=5Hz,32=6.25Hz,33=7.5Hz,34=10Hz,
                                                               35=12.5Hz,36=15Hz,37=20Hz,38=25Hz,39=30Hz,40=40Hz,41=50Hz,42=60Hz,43=75Hz,
                                                               44=100Hz,45=120Hz,46=150Hz,47=180Hz,48=200Hz,49=240Hz,50=250Hz,
                                                               51=300Hz,52=350Hz,53=360Hz,54=400Hz,55=420Hz,56=480Hz,57=240 5Hz,
                                                               58=200 5Hz,59=150 5Hz,60=120 5Hz,61=100 5Hz,62=60 5Hz,63=50 5Hz,64=30 5Hz,65=25 5Hz
                                                               )
                                         30:bd acoustic : imp
                                         31:sd acoustic : imp
                                         32:sy raw      : bal (64=+0)
                                         33:hh lab      : osc6 (uses 8bit? LSB)
                              */

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

   sU8 sample_br;             /* @0x0032  sample bit reduction */
   sU8 __unused_pad12;        /* @0x0033 (lsb, always 0) */

   s_u16_t sample_start;      /* @0x0034  STA (LSB used since v5/FW1.70) */
   s_u16_t sample_end;        /* @0x0036  END (LSB used since v5/FW1.70) */

   sU8 sample_loop_flag;      /* @0x0038  0=off, 1=on */
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

   sU8 accent_level;          /* @0x005c accent level [FUNC+B/F] */
   sU8 __unused005D;          /* @0x005d (lsb, always 0)         */

   sU8 lfo_speed;             /* @0x005e */
   sU8 __unused_pad33;        /* @0x005f (lsb, always 0) */

   sU8 lfo_multiplier;        /* @0x0060 */
   sU8 __unused_pad34;        /* @0x0061 (lsb, always 0) */

   sU8 lfo_fade;              /* @0x0062  0x40=0 */
   sU8 __unused_pad35;        /* @0x0063 (lsb, always 0) */

   sU8 lfo_dest;              /* @0x0064  see LFO_DEST_xxx */
   sU8 __unused_pad36;        /* @0x0065 (lsb, always 0) */

   sU8 lfo_wav;               /* @0x0066 (0=tri,1=sin,2=sqr,3=saw,4=exp,5=rmp,6=rnd) */
   sU8 __unused_pad37;        /* @0x0067 (lsb, always 0) */

   sU8 lfo_start_phase;       /* @0x0068 (note) FW1.70: used as slew when wav is set to 6=rnd */
   sU8 __unused_pad38;        /* @0x0069 (lsb, always 0) */

   sU8 lfo_mode;              /* @0x006a (0=free,1=trg,2=hld,3=one,4=hlf) */
   sU8 __unused_pad39;        /* @0x006b (lsb, always 0) */

   s_u16_t lfo_depth;         /* @0x006c  */

   sU8 def_note;              /* @0x006e  0x3c=0, 0x3d=+1, 0x3b=-1 (initially 0x00 == +0 ?!)
                                   (note) not used in sound dump ? (only in kit?!!)
                               */
   sU8 __unknown_006F[0xd];   /* @0x006f..0x007B   */

   sU8 machine_type;          /* @0x007C   0:bd hard       1:bd classic    2:sd hard       3:sd classic
                                           4:rs hard       5:rs classic    6:cp classic    7:bt classic
                                           8:xt classic    9:ch classic   10:oh classic   11:cy classic
                                          12:cb classic   13:bd fm        14:sd fm        15:ut noise
                                          16:ut impulse   17:ch metallic  18:oh metallic  19:cy metallic
                                          20:cb metallic  21:bd plastic   22:bd silky     23:sd natural
                                          24:hh basic     25:cy ride      26:bd sharp     27:DISABLE
                                          28:sy dual vco  29:sy chip      30:bd acoustic  31:sd acoustic
                                          32:sy raw       33:hh lab

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
   sU8 mode_flags;            /* @0x007D bit 0  : ?
                                         bit 1  : env reset filter switch
                                         bit 2  : legacy fx send switch
                                         bit 3  : ?
                                         bit 4+5: chromatic mode  0=OFF, 1=SYNTH, 2=SAMPLE, 3=SYN+SMP
                                         bit 6  : velocity to vol switch
                                         bit 7  : ?
                                         (note) FW1.70: moved extra veltovol,legacyfx,envreset bytes to bit fields
                               */
#define AR_SOUND_MODE_SHIFT_ENVRESET_FILTER (1)
#define AR_SOUND_MODE_MASK_ENVRESET_FILTER  (1u << AR_SOUND_MODE_SHIFT_ENVRESET_FILTER)
#define AR_SOUND_MODE_SHIFT_LEGACY_FX       (2)
#define AR_SOUND_MODE_MASK_LEGACY_FX        (1u << AR_SOUND_MODE_SHIFT_LEGACY_FX)
#define AR_SOUND_MODE_SHIFT_CHROMATIC       (4)
#define AR_SOUND_MODE_MASK_CHROMATIC        ( (1u << AR_SOUND_MODE_SHIFT_CHROMATIC) | (1u << (AR_SOUND_MODE_SHIFT_CHROMATIC+1)) )
#define AR_SOUND_MODE_SHIFT_VELTOVOL        (6)
#define AR_SOUND_MODE_MASK_VELTOVOL         (1u << AR_SOUND_MODE_SHIFT_VELTOVOL)

   sU8 __unknown_007E[16];    /* @0x007E..0x008D */

   sU8 vel_amt_1;             /* @0x008E VELOCITY MOD */
   sU8 vel_target_1;          /* @0x008F */
   sU8 vel_amt_2;             /* @0x0090 */
   sU8 vel_target_2;          /* @0x0091 */
   sU8 vel_amt_3;             /* @0x0092 */
   sU8 vel_target_3;          /* @0x0093 */
   sU8 vel_amt_4;             /* @0x0094 */
   sU8 vel_target_4;          /* @0x0095 */
   sU8 at_amt_1;              /* @0x0096 AFTERTOUCH */
   sU8 at_target_1;           /* @0x0097 */
   sU8 at_amt_2;              /* @0x0098 */
   sU8 at_target_2;           /* @0x0099 */
   sU8 at_amt_3;              /* @0x009A */
   sU8 at_target_3;           /* @0x009B */
   sU8 at_amt_4;              /* @0x009C */
   sU8 at_target_4;           /* @0x009D */

   sU8 __unknown_009E[4];     /* @0x009E..0x00A1 */

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
S_EXTERN ar_error_t ar_sound_request (sU8 *_dstBuf, sU8 _devId, sU8 _patternNr);


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
S_EXTERN ar_error_t ar_sound_request_x (sU8 *_dstBuf, sU8 _devId, sU8 _patternNr);


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
S_EXTERN ar_error_t ar_sound_syx_to_raw (sU8             *_rawBuf,
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
S_EXTERN ar_error_t ar_sound_raw_to_syx (sU8                   *_syxBuf,
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
sSI ar_sound_get_list_index_by_track_idx_and_machine_id (sUI _trackIdx, sUI _machineId);


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
const char *ar_sound_get_machine_param_short_name (const ar_sound_t *_sound,
                                                   sUI               _synthParamIdx
                                                   );


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
sBool ar_sound_get_lfo_dest_name (const ar_sound_t *_sound,
                                  char             *_retBuf,
                                  sUI               _retBufSz
                                  );


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
sBool ar_sound_get_lfo_dest_name_by_list_idx (const ar_sound_t *_sound,
                                              sUI               _listIdx,
                                              char             *_retBuf,
                                              sUI               _retBufSz
                                              );


/*
 * Query velocity/aftertouch modulation destination name
 *
 *  Arguments:
 *      _sound - Pointer to ar_sound_t (e.g. &kit.tracks[4])
 *  _modDestId - Modulation destination synth-internal index (velocity or aftertouch mod target[1..4])
 *     _retBuf - Returns the null-terminated LFO destination name
 *   _retBufSz - Size of the char buffer (at least AR_SOUND_MAX_MOD_DEST_NAME (24) chars)
 *
 *  Returns:
 *   S_TRUE when the query succeeded or S_FALSE if the machine type is invalid or _sound is NULL.
 *
 */
sBool ar_sound_get_mod_dest_name (const ar_sound_t *_sound,
                                  sUI               _modDestId,
                                  char             *_retBuf,
                                  sUI               _retBufSz
                                  );


/*
 * Map mod destination UI list idx to synth-internal index.
 *
 *  Arguments:
 *    _listIdx - UI list index  (0..AR_NUM_SOUND_MOD_DEST_UI)
 *
 *  Returns:
 *   Synth internal mod destination index. -1 if an error occured (invalid listIdx).
 *
 */
sSI ar_sound_get_mod_dest_by_list_idx (sUI _listIdx);


/*
 * Map mod destination synth-internal index to list idx.
 *
 *  Arguments:
 *    _modDest - Synth-internal mod destination index  (0..AR_NUM_SOUND_MOD_DEST_INT)
 *
 *  Returns:
 *   UI list index. -1 if an error occured (invalid internal index).
 *
 */
sSI ar_sound_get_list_idx_by_mod_dest (sUI _modDest);


/*
 * Query mod destination name by UI list index
 *
 *  Arguments:
 *      _sound - Pointer to ar_sound_t (e.g. &kit.tracks[4])
 *    _listIdx - UI list index  (0..AR_NUM_SOUND_MOD_DEST_UI)
 *     _retBuf - Returns the null-terminated LFO destination name
 *   _retBufSz - Size of the char buffer (at least AR_SOUND_MAX_MOD_DEST_NAME (24) chars)
 *
 *  Returns:
 *   S_TRUE when the query succeeded or S_FALSE if the machine type is invalid or _sound is NULL.
 *
 */
sBool ar_sound_get_mod_dest_name_by_list_idx (const ar_sound_t *_sound,
                                              sUI               _listIdx,
                                              char             *_retBuf,
                                              sUI               _retBufSz
                                              );


#pragma pack(pop)

#include "cplusplus_end.h"

#endif /* __AR_SOUND_H__ */
