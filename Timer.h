#pragma once
#include "TGLib.h"
#include <chrono>

namespace TGLib {

class Timer {
public:
	Timer();

	template <typename Rep = f32, typename Period = std::ratio<1>>
	std::chrono::duration<Rep, Period> Mark_dur() noexcept {
		using namespace std::chrono;
		const auto old = last;
		last = steady_clock::now();
		totalTime = last - old;
		const auto activeTime = totalTime - pauseTime;
		pauseLast = last;
		pauseTime = steady_clock::duration::zero();
		return duration_cast<duration<Rep, Period>>(activeTime);
	}
	template <typename Rep = f32, typename Period = std::ratio<1>>
	Rep Mark() noexcept {
		return Mark_dur<Rep, Period>().count();
	}

	template <typename Rep = f32, typename Period = std::ratio<1>>
	std::chrono::duration<Rep, Period> Peek_dur() const noexcept {
		using namespace std::chrono;
		const auto curr = steady_clock::now();
		const auto totalTime_ = curr - last;
		const auto pauseTime_ = pauseTime + (paused ? (curr - pauseLast) : steady_clock::duration::zero());
		const auto activeTime = totalTime_ - pauseTime_;
		return duration_cast<duration<Rep, Period>>(activeTime);
	}
	template <typename Rep = f32, typename Period = std::ratio<1>>
	Rep Peek() const noexcept {
		return Peek_dur<Rep, Period>().count();
	}

	void SetPaused(bool paused) noexcept;
	bool IsPaused() const noexcept;
private:
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::duration totalTime;
	std::chrono::steady_clock::time_point pauseLast;
	std::chrono::steady_clock::duration pauseTime;
	bool paused = false;
};

}