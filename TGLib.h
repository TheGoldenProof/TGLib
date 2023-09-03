#pragma once

#include <stdint.h>

#include <string>
#include <iostream>
#include <optional>

#ifndef IS_DEBUG
#ifdef NDEBUG
#define IS_DEBUG false
#else
#define IS_DEBUG true
#endif // NDEBUG
#endif // !IS_DEBUG

#define dbgexcept noexcept(!IS_DEBUG)

#ifdef NDEBUG
#define DEBUG_LOG(str)
#else
#define DEBUG_LOG(str) OutputDebugStringA(str)
#endif // NDEBUG

namespace TGLib {
// prevents "treat warnings as errors" from acting up on *temporarily* unused variables.
// template <typename T> constexpr void UNUSED_VAR(T v) { (v); }
// Just use UNREFERENCED_PARAMETER()

#ifdef TGLIB_NOGLOBALNUMBERTYPES
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using usize = size_t;

using f32 = float;
using f64 = double;

using wchar = wchar_t;
#endif // !TGLIB_NOGLOBALNUMBERTYPES


namespace {
template <class cT, class traits = std::char_traits<cT> >
class basic_nullbuf : public std::basic_streambuf<cT, traits> {
	typename traits::int_type overflow(typename traits::int_type c) {
		return traits::not_eof(c);
	}
};

template <class cT, class traits = std::char_traits<cT> >
class basic_nullostream : public std::basic_ostream<cT, traits> {
public:
	basic_nullostream() :
		std::basic_ios<cT, traits>(&m_sbuf),
		std::basic_ostream<cT, traits>(&m_sbuf) {}

private:
	basic_nullbuf<cT, traits> m_sbuf;
};

using nullostream = basic_nullostream<char>;
}

// A stream that outputs to nowhere.
inline nullostream nullout;
}

#ifndef TGLIB_NOGLOBALNUMBERTYPES
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using usize = size_t;

using f32 = float;
using f64 = double;

using wchar = wchar_t;
#endif // TGLIB_NOGLOBALNUMBERTYPES

#ifdef TGLIB_INC_INSTRUMENTOR
#include "Instrumentor.h"
#endif // TGLIB_INC_INSTRUMENTOR
#ifdef TGLIB_INC_TIMER
#include "Timer.h"
#endif // TGLIB_INC_TIMER
#ifdef TGLIB_INC_UTIL
#include "Util.h"
#endif // TGLIB_INC_UTIL

