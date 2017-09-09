
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc_ar.h"


#define BUF_SIZE  (1024 * 1024 * 4u)

#define SYX_PATH "f:/docs_synths/elektron_analog_rytm/sysex_test/"


/* ---------------------------------------------------------------------------- load_file */
static void load_file(sU8 *syx, const char *fname, sU32 *retSize) {
   FILE *fh;

   *retSize = 0;

   fh = fopen(fname, "rb");
   if(NULL != fh)
   {
      long sz;

      fseek(fh, 0, SEEK_END);
      sz = ftell(fh);
      fseek(fh, 0, SEEK_SET);

      if(sz <= BUF_SIZE)
      {
         *retSize = (sU32) fread(syx, 1, sz, fh);

         if(*retSize > BUF_SIZE)
         {
            *retSize = 0;
         }
      }

      fclose(fh);
   }
}

/* ---------------------------------------------------------------------------- save_file */
static void save_file(sU8 *data, sU32 dataSize, const char *fname) {
   FILE *fh;

   fh = fopen(fname, "wb");
   
   if(NULL != fh)
   {
      (void)fread(data, 1, dataSize, fh);

      fclose(fh);
   }
}

/* ---------------------------------------------------------------------------- loc_compare */
static sSI loc_compare(const sU8 *a, const sU8 *b, sUI numBytes) {
   sUI idx = 0;

   while(idx < numBytes)
   {
      if(a[idx] != b[idx])
      {
         break;
      }

      idx++;
   }

   if(idx == numBytes)
   {
      idx = ~0u;
   }

   return (sSI)idx;
}

/* ---------------------------------------------------------------------------- tc_pattern_request */
static void tc_pattern_request(sU8 *buf) {
   if(AR_ERR_OK == ar_pattern_request(buf, 0, (6 * 16) + 0))
   {
      printf("ok\n");
   }
}

/* ---------------------------------------------------------------------------- tc_kit_request */
static void tc_kit_request(sU8 *buf) {
   if(AR_ERR_OK == ar_kit_request(buf, 0, (0 * 16) + 0))
   {
      printf("ok\n");
   }
}

/* ---------------------------------------------------------------------------- tc_syx_to_raw */
static void tc_syx_to_raw(sU8 *raw, sU8 *syx, const char *fname) {
   sU32 syxSz;

   load_file(syx, fname, &syxSz);
   
   if(syxSz > 0)
   {
      ar_error_t err;
      ar_sysex_meta_t meta;
      sU32 datSz;
      const sU8 *sb = syx;  /* (note) simply passing &syx to ar_sysex_raw() is not allowed in C99/GCC/clang.
                             *        assigning to a tmpvar ("sb") first, then passing &sb is. madness!
                             *  Also see here: <http://c-faq.com/ansi/constmismatch.html>
                             */

      err = ar_sysex_to_raw(raw, &sb, &syxSz, &datSz, &meta);

      if(AR_ERR_OK == err)
      {
         printf("ok\n");
      }
      else
      {
         printf("NOK\n");
      }
   }
}

/* ---------------------------------------------------------------------------- tc_multi_syx_to_raw */
static void tc_multi_syx_to_raw(sU8 *raw, sU8 *syx, const char *fname) {
   sU32 syxSz;

   load_file(syx, fname, &syxSz);

   if(syxSz > 0)
   {
      ar_error_t err;
      ar_sysex_meta_t meta;
      sU32 datSz;
      const sU8 *sb = syx;
      sU32 sbsz = syxSz;
      sUI numMsg = 0;

      for(;;)
      {
         if(sbsz > 0)
         {
            err = ar_sysex_to_raw(raw, &sb, &sbsz, &datSz, &meta);

            printf("[%4u] meta obj_type = %02x\n", numMsg, meta.obj_type);

            if(meta.obj_type > AR_TYPE_GLOBAL)
            {
               printf("[%4u] oops: obj_type (0x%02x)\n", numMsg, meta.obj_type);
            }

            if(AR_TYPE_GLOBAL == meta.obj_type)
            {
               printf("[%4u] global\n", numMsg);
            }

            if(AR_TYPE_SETTINGS == meta.obj_type)
            {
               printf("[%4u] settings\n", numMsg);
            }

            if(AR_ERR_OK == err)
            {
               printf("[%4u] ok\n", numMsg);
               numMsg++;
            }
            else
            {
               printf("[%4u] NOK, err=%d\n", numMsg, err);
               break;
            }
         }
         else
         {
            /* all done */
            printf("ok, all done. parsed %u sysex messages.", numMsg);
            break;
         }
      }
   }
}

/* ---------------------------------------------------------------------------- tc_syx_to_raw_to_syx */
static void tc_syx_to_raw_to_syx(sU8 *raw, sU8 *syx, sU8 *resyx, const char *fname) {
   sU32 syxSz;

   load_file(syx, fname, &syxSz);

   if(syxSz > 0)
   {
      ar_error_t err;
      ar_sysex_meta_t meta;
      sU32 datSz;
      const sU8 *sb = syx;
      sU32 sbsz = syxSz;

      err = ar_sysex_to_raw(raw, &sb, &sbsz, &datSz, &meta);

      if(AR_ERR_OK == err)
      {
         /* Query required buffer size */
         err = ar_raw_to_sysex(NULL, raw, datSz, &sbsz, &meta);

         if(AR_ERR_OK == err)
         {
            if(sbsz == syxSz)
            {
               memset(resyx, 0xCD, sbsz);

               err = ar_raw_to_sysex(resyx, raw, datSz, NULL/*syxSz*/, &meta);

               if(AR_ERR_OK == err)
               {
                  sSI diffIdx = loc_compare(syx, resyx, syxSz);

                  if(-1 == diffIdx)
                  {
                     printf("ok (to syx)\n");
                  }
                  else
                  {
                     printf("NOK (compare, diffIdx=%d (0x%04x)\n", diffIdx, diffIdx);
                  }
               }
               else
               {
                  printf("NOK (to syx)\n");
               }
            }
            else
            {
               printf("NOK (query resyx size, have %u (0x%04x), expected %u (0x%04x)", sbsz, sbsz, syxSz, syxSz);
            }
         }
         else
         {
            printf("NOK (query syx size)\n");
         }
      }
      else
      {
         printf("NOK (to raw)\n");
      }
   }
}

/* ---------------------------------------------------------------------------- tc_multi_syx_to_raw_to_syx */
static void tc_multi_syx_to_raw_to_syx(sU8 *raw, sU8 *syx, sU8 *resyx, const char *fname) {
   sU32 syxSz;

   load_file(syx, fname, &syxSz);

   if(syxSz > 0)
   {
      ar_error_t err;
      ar_sysex_meta_t meta;
      sU32 datSz;
      const sU8 *sb = syx;
      sU32 sbsz = syxSz;
      sUI numMsg = 0;

      for(;;)
      {
         if(sbsz > 0)
         {
            const sU8 *curSyx = sb;
            sU32 curSyxSz = sbsz;

            err = ar_sysex_to_raw(raw, &sb, &sbsz, &datSz, &meta);

            printf("[%4u] meta obj_type = %u\n", numMsg, meta.obj_type);

            if(AR_TYPE_SETTINGS == meta.obj_type)
            {
               printf("[%4u] settings\n", numMsg);
            }

            if(AR_ERR_OK == err)
            {
               sU32 rbsz;

               curSyxSz = (curSyxSz - sbsz);  /* delta = num bytes read*/

               /* Query required buffer size */
               err = ar_raw_to_sysex(NULL, raw, datSz, &rbsz, &meta);

               if(AR_ERR_OK == err)
               {
                  if(curSyxSz == rbsz)
                  {
                     memset(resyx, 0xCD, rbsz);

                     err = ar_raw_to_sysex(resyx, raw, datSz, NULL/*syxSz*/, &meta);

                     if(AR_ERR_OK == err)
                     {
                        sSI diffIdx = loc_compare(curSyx, resyx, rbsz);

                        if(-1 == diffIdx)
                        {
                           printf("[%4u] ok (to syx)\n", numMsg);
                        }
                        else
                        {
                           printf("[%4u] NOK (compare, diffIdx=%d (0x%04x)\n", numMsg, diffIdx, diffIdx);
                           break;
                        }
                     }
                     else
                     {
                        printf("[%4u] NOK (to syx)\n", numMsg);
                        break;
                     }
                  }
                  else
                  {
                     printf("[%4u] NOK (query resyx size, have %d (0x%04x), expected %d (0x%04x)", numMsg, rbsz, rbsz, curSyxSz, curSyxSz);
                     break;
                  }
               }
               else
               {
                  printf("[%4u] NOK (query syx size)\n", numMsg);
                  break;
               }

               numMsg++;
            }
            else
            {
               printf("[%4u] NOK (to raw), err=%d\n", numMsg, err);
               break;
            }
         }
         else
         {
            /* all done */
            printf("ok, all done. parsed %u sysex messages.", numMsg);
            break;
         }
      }
   }
}

/* ---------------------------------------------------------------------------- tc_pattern_syx_to_raw */
static void tc_pattern_syx_to_raw_to_syx(sU8 *raw, sU8 *syx, sU8 *resyx, const char *fname) {
   ar_error_t err;
   ar_sysex_meta_t meta;
   sU32 syxSz;

   load_file(syx, fname, &syxSz);

   if(syxSz > 0)
   {
      sU32 rawSz;

      err = ar_pattern_syx_to_raw(raw, syx, syxSz, &rawSz, &meta);

      if(AR_ERR_OK == err)
      {
         sU32 resyxSz;

         memset(resyx, 0xCD, syxSz);

         err = ar_pattern_raw_to_syx(resyx, raw, rawSz, &resyxSz, &meta);

         if(AR_ERR_OK == err)
         {
            if(resyxSz == syxSz)
            {
               sSI diffIdx;

               diffIdx = loc_compare(syx, resyx, syxSz);

               if(-1 == diffIdx)
               {
                  printf("ok\n");
               }
               else
               {
                  printf("NOK (ar_pattern_raw_to_syx) (diffIdx=%d (0x%04x))\n", diffIdx, diffIdx);
               }
            }
            else
            {
               printf("NOK (ar_pattern_raw_to_syx) (expected resyxSz=%u, have=%u)\n", syxSz, resyxSz);
            }
         }
         else
         {
            printf("NOK (ar_pattern_raw_to_syx) err=%d\n", err);
         }
      }
      else
      {
         printf("NOK (ar_pattern_syx_to_raw) err=%d\n", err);
      }
   }
}

/* ---------------------------------------------------------------------------- main */
int main(int argc, char**argv) {
   sU8 *buf   = malloc(BUF_SIZE * 3);
   sU8 *syx   = buf + BUF_SIZE;
   sU8 *resyx = buf + (BUF_SIZE * 2);

   (void)argc;
   (void)argv;

   memset(buf, 0xCC, BUF_SIZE * 3);

#if 1
   printf("sizeof(ar_kit_t)=%d (0x%08x)\n", sizeof(ar_kit_t), sizeof(ar_kit_t));
   printf("sizeof(ar_kit_track_t)=%d (0x%08x)\n", sizeof(ar_kit_track_t), sizeof(ar_kit_track_t));
   {
      ar_kit_t kit;
#define Dprintoff(n) printf("offset of " #n " = %d (0x%08x)\n", (((sU8*)&(n)) - ((sU8*)&kit)), (((sU8*)&(n)) - ((sU8*)&kit)))
      Dprintoff(kit.tracks[0].sample_tune);
      Dprintoff(kit.tracks[1].sample_tune);
      Dprintoff(kit.fx_delay_time);
      Dprintoff(kit.fx_reverb_decay);
      Dprintoff(kit.fx_dist_amount);
      Dprintoff(kit.fx_comp_threshold);
      Dprintoff(kit.fx_comp_release);
      Dprintoff(kit.fx_lfo_depth_msb);
      Dprintoff(kit.perf_ctl[0]);
      Dprintoff(kit.scene_ctl[0]);
      Dprintoff(kit.current_scene_id);
#undef Dprintoff
      printf("\n\n");
   }
#endif

#if 1
   printf("sizeof(ar_pattern_t)=%d (0x%08x)\n", sizeof(ar_pattern_t), sizeof(ar_pattern_t));
   printf("sizeof(ar_pattern_track_t)=%d (0x%08x)\n", sizeof(ar_pattern_track_t), sizeof(ar_pattern_track_t));
   {
      ar_pattern_t pat;
#define Dprintoff(n) printf("offset of " #n " = %d (0x%08x)\n", (((sU8*)&(n)) - ((sU8*)&pat)), (((sU8*)&(n)) - ((sU8*)&pat)))
      Dprintoff(pat.tracks[0].num_steps);
      Dprintoff(pat.tracks[1].num_steps);
      Dprintoff(pat.plock_seqs[0].data[0]);
      Dprintoff(pat.plock_seqs[1].data[0]);
      Dprintoff(pat.pattern_len);
      Dprintoff(pat.pattern_speed);
#undef Dprintoff
   }
#endif


#if 1
   printf("sizeof(ar_sound_t)=%d (0x%08x)\n", sizeof(ar_sound_t), sizeof(ar_sound_t));
   {
      ar_sound_t sound;
      tc_syx_to_raw(buf, syx, SYX_PATH "sound/sound_0.syx");
   }
#endif

   // tc_pattern_request(buf);

   //tc_syx_to_raw(buf, syx, SYX_PATH "pat/d01_empty.syx");
   //tc_syx_to_raw(buf, syx, SYX_PATH "kit_funkydrummer.syx");
   //tc_syx_to_raw(buf, syx, SYX_PATH "kit_07_dmx.syx");
   //tc_syx_to_raw(buf, syx, SYX_PATH "soundx_00_dmx.syx");
   //tc_syx_to_raw(buf, syx, SYX_PATH "song.syx");
   
   //tc_multi_syx_to_raw(buf, syx, SYX_PATH "whole_project_dmx.syx");
   
   //tc_syx_to_raw_to_syx(buf, syx, resyx, SYX_PATH "pat/d01_empty.syx");
   //tc_syx_to_raw_to_syx(buf, syx, resyx, SYX_PATH "kit_07_dmx.syx");
   //tc_syx_to_raw_to_syx(buf, syx, resyx, SYX_PATH "song.syx");
   //tc_syx_to_raw_to_syx(buf, syx, resyx, SYX_PATH "sound.syx");

   // tc_multi_syx_to_raw_to_syx(buf, syx, resyx, SYX_PATH "whole_project_dmx.syx");

   //tc_pattern_syx_to_raw_to_syx(buf, syx, resyx, SYX_PATH "pat/a01_64steps_t1all.syx");
   
   // tc_kit_request(buf);

   // tc_syx_to_raw(buf, syx, SYX_PATH "kit/kit_01.syx");
   // tc_syx_to_raw_to_syx(buf, syx, resyx, SYX_PATH "kit/kit_01.syx");

   free(buf);

   return 0;
}
