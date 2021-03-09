// ISO C9x  compliant stdint.h for Microsoft Visual Studio
// Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124
//
//  Copyright (c) 2006-2008 Alexander Chemeris
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//   2. Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//   3. The name of the author may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////////

(*
// Define _W64 macros to mark types changing their size, like intptr_t.
#ifndef _W64
#  if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#     define _W64 __w64
#  else
#     define _W64
#  endif
#endif
*)
// 7.18.1 Integer types

// 7.18.1.1 Exact-width integer types

type
  int8_t = Shortint;
  int16_t = Smallint;
  int32_t = Integer;
  uint8_t = Byte;
  uint16_t = Word;
  uint32_t = Cardinal;
  int64_t = Int64;
  uint64_t = UInt64;


// 7.18.1.2 Minimum-width integer types
type
  int_least8_t = int8_t;
  int_least16_t = int16_t;
  int_least32_t = int32_t;
  int_least64_t = int64_t;
  uint_least8_t = uint8_t;
  uint_least16_t = uint16_t;
  uint_least32_t = uint32_t;
  uint_least64_t = uint64_t;

  // 7.18.1.3 Fastest minimum-width integer types
  int_fast8_t = int8_t;
  int_fast16_t = int16_t;
  int_fast32_t = int32_t;
  int_fast64_t = int64_t;
  uint_fast8_t = uint8_t;
  uint_fast16_t = uint16_t;
  uint_fast32_t = uint32_t;
  uint_fast64_t = uint64_t;

  // 7.18.1.4 Integer types capable of holding object pointers

{$IFDEF CPU64}
  intptr_t = Int64;
  uintptr_t = UInt64;
{$ELSE}
  intptr_t = Integer;
  uintptr_t = Cardinal;
{$ENDIF}

// 7.18.1.5 Greatest-width integer types

  intmax_t = int64_t;
  uintmax_t = uint64_t;


  // 7.18.2 Limits of specified-width integer types

  // 7.18.2.1 Limits of exact-width integer types
const
  INT8_MIN = int8_t(Low(int8_t));
  INT8_MAX = int8_t(High(int8_t));
  INT16_MIN = int16_t(Low(int16_t));
  INT16_MAX = int16_t(High(int16_t));
  INT32_MIN = int32_t(Low(int32_t));
  INT32_MAX = int32_t(High(int32_t));
  INT64_MIN = int64_t(Low(int64_t));
  INT64_MAX = int64_t(High(int64_t));
  UINT8_MAX = uint8_t(High(uint8_t));
  UINT16_MAX = uint16_t(High(uint16_t));
  UINT32_MAX = uint32_t(High(uint32_t));
  UINT64_MAX = uint64_t(High(uint64_t));
  // 7.18.2.2 Limits of minimum-width integer types
  INT_LEAST8_MIN = INT8_MIN;
  INT_LEAST8_MAX = INT8_MAX;
  INT_LEAST16_MIN = INT16_MIN;
  INT_LEAST16_MAX = INT16_MAX;
  INT_LEAST32_MIN = INT32_MIN;
  INT_LEAST32_MAX = INT32_MAX;
  INT_LEAST64_MIN = INT64_MIN;
  INT_LEAST64_MAX = INT64_MAX;
  UINT_LEAST8_MAX = UINT8_MAX;
  UINT_LEAST16_MAX = UINT16_MAX;
  UINT_LEAST32_MAX = UINT32_MAX;
  UINT_LEAST64_MAX = UINT64_MAX;
  // 7.18.2.3 Limits of fastest minimum-width integer types
  INT_FAST8_MIN = INT8_MIN;
  INT_FAST8_MAX = INT8_MAX;
  INT_FAST16_MIN = INT16_MIN;
  INT_FAST16_MAX = INT16_MAX;
  INT_FAST32_MIN = INT32_MIN;
  INT_FAST32_MAX = INT32_MAX;
  INT_FAST64_MIN = INT64_MIN;
  INT_FAST64_MAX = INT64_MAX;
  UINT_FAST8_MAX = UINT8_MAX;
  UINT_FAST16_MAX = UINT16_MAX;
  UINT_FAST32_MAX = UINT32_MAX;
  UINT_FAST64_MAX = UINT64_MAX;
  // 7.18.2.4 Limits of integer types capable of holding object pointers
{$IFDEF CPU64}
  INTPTR_MIN = INT64_MIN;
  INTPTR_MAX = INT64_MAX;
  UINTPTR_MAX = UINT64_MAX;
{$ELSE}
  INTPTR_MIN = INT32_MIN;
  INTPTR_MAX = INT32_MAX;
  UINTPTR_MAX = UINT32_MAX;
{$ENDIF}
  // 7.18.2.5 Limits of greatest-width integer types
  INTMAX_MIN = INT64_MIN;
  INTMAX_MAX = INT64_MAX;
  UINTMAX_MAX = UINT64_MAX;
  // 7.18.3 Limits of other integer types


{$IFDEF CPU64}
  PTRDIFF_MIN = INT64_MIN;
  PTRDIFF_MAX = INT64_MAX;
{$ELSE}
  PTRDIFF_MIN = INT32_MIN;
  PTRDIFF_MAX = INT32_MAX;
{$ENDIF}
{$IFDEF CPU64}
  SIG_ATOMIC_MIN = INT64_MIN;
  SIG_ATOMIC_MAX = INT64_MAX;
{$ELSE}
  SIG_ATOMIC_MIN = INT32_MIN;
  SIG_ATOMIC_MAX = INT32_MAX;
{$ENDIF}
{$IFDEF CPU64}
  SIZE_MAX = UINT64_MAX;
{$ELSE}
  SIZE_MAX = UINT32_MAX;
{$ENDIF}

// WCHAR_MIN and WCHAR_MAX are also defined in <wchar.h>
const
  WCHAR_MIN = 0;
  WCHAR_MAX = UINT16_MAX;
  WINT_MIN = 0;
  WINT_MAX = UINT16_MAX;


// 7.18.4 Limits of other integer types

// 7.18.4.1 Macros for minimum-width integer constants
(*
#define INT8_C(val)  val##i8
#define INT16_C(val) val##i16
#define INT32_C(val) val##i32
#define INT64_C(val) val##i64

#define UINT8_C(val)  val##ui8
#define UINT16_C(val) val##ui16
#define UINT32_C(val) val##ui32
#define UINT64_C(val) val##ui64

// 7.18.4.2 Macros for greatest-width integer constants
const
  INTMAX_C = INT64_C;
  UINTMAX_C = UINT64_C;
*)

