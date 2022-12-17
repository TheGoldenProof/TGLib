#pragma once

namespace TGLib {
	// prevents "treat warnings as errors" from acting up on *temporarily* unused variables.
	template <typename T> constexpr void UNUSED_VAR(T v) { (v); }

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
	nullostream nullout;
}