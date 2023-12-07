/* ----
 * ---- file   : pattern.c
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
 * ---- created: 01Aug2014
 * ---- changed: 04Aug2014, 24Oct2019, 27Nov2023, 07Dec2023
 * ----
 * ----
 */

// #define AR_DEBUG defined

#include "types.h"
#include "debug.h"
#include "error.h"
#include "sysex.h"
#include "pattern.h"


/* ---------------------------------------------------------------------------- ar_pattern_request */
ar_error_t ar_pattern_request(sU8 *_dstBuf, sU8 _devId, sU8 _patternNr) {
   ar_sysex_meta_t meta;
   ar_error_t ret;

   AR_SYSEX_META_INIT(meta, _devId, AR_TYPE_PATTERN, _patternNr);

   ret = ar_sysex_request(_dstBuf, &meta);

   return ret;
}

/* ---------------------------------------------------------------------------- ar_pattern_request_x */
ar_error_t ar_pattern_request_x(sU8 *_dstBuf, sU8 _devId, sU8 _patternNr) {
   ar_sysex_meta_t meta;
   ar_error_t ret;

   AR_SYSEX_META_INIT(meta, _devId, AR_TYPE_PATTERN, (128u + (_patternNr & 127u)));

   ret = ar_sysex_request(_dstBuf, &meta);

   return ret;
}

/* ---------------------------------------------------------------------------- ar_pattern_syx_to_raw */
ar_error_t ar_pattern_syx_to_raw(sU8               *_rawBuf,
                                 const sU8         *_syxBuf,
                                 sU32               _syxBufSize,
                                 sU32              *_retRawBufSize,
                                 ar_sysex_meta_t   *_meta
                                 ) {
   ar_error_t ret;
   sU32 datSz;
   ar_sysex_meta_t meta;

   ret = ar_sysex_to_raw(_rawBuf, &_syxBuf, &_syxBufSize, &datSz, &meta);

   Dprintf("xxx ar_pattern_syx_to_raw: syxSz=%u rawSz=%u  sizeof(pat)=%lu  sizeof(pat_track)=%lu\n", _syxBufSize, datSz, sizeof(ar_pattern_t), sizeof(ar_pattern_track_t));

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

      if(AR_TYPE_PATTERN == meta.obj_type)
      {
         /* Succeeded */
      }
      else
      {
         ret = AR_ERR_NOT_A_PATTERN;
      }
   }

   return ret;
}

/* ---------------------------------------------------------------------------- ar_pattern_raw_to_syx */
ar_error_t ar_pattern_raw_to_syx(sU8                   *_syxBuf,
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

/* ---------------------------------------------------------------------------- ar_pattern_track_get_trig_flags */
sU16 ar_pattern_track_get_trig_flags(const ar_pattern_track_t *_patternTrack,
                                     const sUI                 _stepIdx
                                     ) {
   const sU8 *buffer   = _patternTrack->trig_bits;
   const sUI _startBit = 14u * _stepIdx;
   const sUI _numBits  = 14u;
   const sUI endBit    = _startBit + _numBits;
   const sUI size      = 14u * 64u;
   sU32 r = 0u;
   if( ((endBit + 7u) >> 3) <= size )
   {
      const sUI startByte = _startBit >> 3;
            sUI bitOff    = (_startBit - (startByte << 3));
            sUI outShift  = _numBits;
            sUI bitsLeft  = _numBits;
            sUI byteOff   = startByte;
      while(bitsLeft > 0u)
      {
         sUI bitsAvail = (8u - bitOff);
         if(bitsLeft < bitsAvail)
         {
            outShift -= bitsLeft;
            r |= ( (buffer[byteOff] >> (bitsAvail - bitsLeft)) & ((1u << bitsLeft) - 1u) ) << outShift;
            bitsLeft = 0u;
         }
         else
         {
            outShift -= bitsAvail;
            r |= (buffer[byteOff] & ((1u << bitsAvail) - 1u)) << outShift;
            bitsLeft -= bitsAvail;
            bitOff = 0u;
            byteOff++;
         }
      }
   }
   return (sU16)r;
}

/* ---------------------------------------------------------------------------- ar_pattern_track_set_trig_flags */
void ar_pattern_track_set_trig_flags(      ar_pattern_track_t *_patternTrack,
                                     const sUI                 _stepIdx,
                                     const sU16                _val
                                     ) {
   const sUI _startBit = 14u * _stepIdx;
   const sUI _numBits  = 14u;
   const sUI endBit    = _startBit + _numBits;
   sU8 *buffer = _patternTrack->trig_bits;
   const sUI size      = 14u * 64u;
   if( ((endBit + 7u) >> 3) <= size )
   {
      const sUI startByte = _startBit >> 3;
            sUI bitOff    = (_startBit - (startByte << 3));  // 0..7
            sUI outShift  = _numBits;
            sUI byteOff   = startByte;
            sUI bitsLeft  = _numBits;
      while(bitsLeft > 0u)
      {
         const sUI bitsAvail = (8u - bitOff);
         if(bitsLeft < bitsAvail)
         {
            outShift -= bitsLeft;
            buffer[byteOff] = (buffer[byteOff] & ((1u << (8u - bitsLeft)) - 1u)) | ((_val & ((1u << bitsLeft) - 1u)) << (8u - bitsLeft));
            bitsLeft = 0u;
         }
         else
         {
            outShift -= bitsAvail;
            buffer[byteOff] = (buffer[byteOff] & ~((1u << bitsAvail) - 1u)) | (_val >> outShift);
            bitsLeft -= bitsAvail;
            bitOff = 0u;
            byteOff++;
         }
      }
   }
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_note */
sU8 ar_pattern_track_get_step_note(const ar_pattern_track_t *_patternTrack,
                                   const sUI                 _stepIdx
                                   ) {
   return _patternTrack->notes[_stepIdx] & 127u;
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_note */
void ar_pattern_track_set_step_note(ar_pattern_track_t *_patternTrack,
                                    const sUI           _stepIdx,
                                    const sU8           _val
                                    ) {
   sU8 v = _patternTrack->notes[_stepIdx] & 0x80u;
   _patternTrack->notes[_stepIdx] = v | (_val & 127u);
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_velocity */
sU8 ar_pattern_track_get_step_velocity(const ar_pattern_track_t *_patternTrack,
                                       const sUI                 _stepIdx
                                       ) {
   return _patternTrack->velocities[_stepIdx];
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_velocity */
void ar_pattern_track_set_step_velocity(ar_pattern_track_t *_patternTrack,
                                        const sUI           _stepIdx,
                                        const sU8           _val
                                        ) {
   // 'val' 0xFF = use default velocity, 0..127 otherwise
   _patternTrack->velocities[_stepIdx] = _val;
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_note_length */
sU8 ar_pattern_track_get_step_note_length(const ar_pattern_track_t *_patternTrack,
                                          const sUI                 _stepIdx
                                          ) {
   return _patternTrack->note_lengths[_stepIdx];
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_note_length */
void ar_pattern_track_set_step_note_length(ar_pattern_track_t *_patternTrack,
                                           const sUI           _stepIdx,
                                           const sU8           _val
                                           ) {
   _patternTrack->note_lengths[_stepIdx] = _val;
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_micro_timing */
sS8 ar_pattern_track_get_step_micro_timing(const ar_pattern_track_t *_patternTrack,
                                           const sUI                 _stepIdx
                                           ) {
   sS8 r = (sS8) (_patternTrack->micro_timings[_stepIdx] & 0x3Fu);
   if(r & 0x20)
      r |= 0xC0;
   return r;
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_micro_timing */
void ar_pattern_track_set_step_micro_timing(ar_pattern_track_t *_patternTrack,
                                            const sUI           _stepIdx,
                                            const sS8           _val
                                            ) {
   sU8 v = _patternTrack->micro_timings[_stepIdx] & 0xC0u;
   _patternTrack->micro_timings[_stepIdx] = v | ((sU8)(_val & 0x3F));
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_retrig_length */
sU8 ar_pattern_track_get_step_retrig_length(const ar_pattern_track_t *_patternTrack,
                                            const sUI                 _stepIdx
                                            ) {
   return _patternTrack->retrig_lengths[_stepIdx] & 0x7Fu;
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_retrig_length */
void ar_pattern_track_set_step_retrig_length(ar_pattern_track_t *_patternTrack,
                                             const sUI           _stepIdx,
                                             const sU8           _val
                                             ) {
   sU8 v = _patternTrack->retrig_lengths[_stepIdx] & 0x80u;
   _patternTrack->retrig_lengths[_stepIdx] = v | (_val & 0x7Fu);
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_retrig_rate */
sU8 ar_pattern_track_get_step_retrig_rate(const ar_pattern_track_t *_patternTrack,
                                          const sUI                 _stepIdx
                                          ) {
   return _patternTrack->retrig_rates[_stepIdx] & 0x1Fu;
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_retrig_rate */
void ar_pattern_track_set_step_retrig_rate(ar_pattern_track_t *_patternTrack,
                                           const sUI           _stepIdx,
                                           const sU8           _val
                                           ) {
   sU8 v = _patternTrack->retrig_rates[_stepIdx] & 0xE0u;
   _patternTrack->retrig_rates[_stepIdx] = v | (_val & 0x1Fu);
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_retrig_velocity_offset */
sS8 ar_pattern_track_get_step_retrig_velocity_offset(const ar_pattern_track_t *_patternTrack,
                                                const sUI                 _stepIdx
                                                ) {
   return _patternTrack->retrig_velocity_offsets[_stepIdx];
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_retrig_velocity_offset */
void ar_pattern_track_set_step_retrig_velocity_offset(ar_pattern_track_t *_patternTrack,
                                                      const sUI           _stepIdx,
                                                      const sS8           _val
                                                      ) {
   _patternTrack->retrig_velocity_offsets[_stepIdx] = _val;
}


/* ---------------------------------------------------------------------------- ar_pattern_track_get_step_trig_condition */
sU8 ar_pattern_track_get_step_trig_condition(const ar_pattern_track_t *_patternTrack,
                                             const sUI                 _stepIdx
                                             ) {
   sU8 r;
   r  = (( _patternTrack->notes         [_stepIdx] & 0x80u/*2#10000000*/) >> (7-6));  // bit  6
   r |= (( _patternTrack->micro_timings [_stepIdx] & 0xC0u/*2#11000000*/) >> (6-4));  // bits 5..4
   r |= (( _patternTrack->retrig_lengths[_stepIdx] & 0x80u/*2#10000000*/) >> (7-3));  // bit  3
   r |= (( _patternTrack->retrig_rates  [_stepIdx] & 0xE0u/*2#11100000*/) >> (5-0));  // bits 2..0
   return r;   
}


/* ---------------------------------------------------------------------------- ar_pattern_track_set_step_trig_condition */
void ar_pattern_track_set_step_trig_condition(ar_pattern_track_t *_patternTrack,
                                              const sUI           _stepIdx,
                                              const sU8           _val
                                              ) {
   sU8 v;

   v = _patternTrack->notes         [_stepIdx] & ~0x80u;
   _patternTrack->notes         [_stepIdx] = v | ((_val & 0x40u/*2#01000000*/) << 1);

   v = _patternTrack->micro_timings [_stepIdx] & ~0xC0u;
   _patternTrack->micro_timings [_stepIdx] = v | ((_val & 0x30u/*2#00110000*/) << 2);

   v = _patternTrack->retrig_lengths[_stepIdx] & ~0x80u;
   _patternTrack->retrig_lengths[_stepIdx] = v | ((_val & 0x08u/*2#00001000*/) << 4);

   v = _patternTrack->retrig_rates  [_stepIdx] & ~0xE0u;
   _patternTrack->retrig_rates  [_stepIdx] = v | ((_val & 0x07u/*2#00000111*/) << 5);
}
