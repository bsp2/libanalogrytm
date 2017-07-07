libanalogrytm
=============

Portable Sysex Library for the Elektron Analog Rytm Drum Computer


## Introduction

The aim of this project is to create an open-source library that can be used to
decode, modify, and encode system exclusive messages sent/received by the Analog Rytm MIDI synthesizer.

By design, the library itself does _NOT_ contain any actual MIDI I/O or user interface code.


## Legal

This is not an official Elektron development.

All file format information has been found out by analyzing/comparing hundreds of sysex messages sent by the AR.

This library may be used in both open and closed source software (see [LICENSE](../master/LICENSE)).


## Status

- The basic AR sysex object types (kit, sound, pattern, song, settings, global) have been identified.

- The basic sysex container structure and encoding has been identified. See [sysex.h](../master/sysex.h), [sysex.c](../master/sysex.c).

- Most of the pattern format has been analyzed. See [pattern.h](../master/pattern.h).

- Most of the kit format has been analyzed. See [kit.h](../master/kit.h).

- The library can convert a "whole project" .syx file (sent by the AR) to raw data, and back to .syx again.
  See [testcases/main.c](../master/testcases/main.c). Example output: [log.txt](../master/vs2013/libanalogrytm_test/Debug/log.txt).
