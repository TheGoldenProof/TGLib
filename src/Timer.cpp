#include "Timer.h"
//#include <ratio>

using namespace std::chrono;

namespace TGLib {

Timer::Timer() {
	last = steady_clock::now();
	totalTime = nanoseconds::zero();
	pauseTime = nanoseconds::zero();
}

f32 Timer::Mark() noexcept {
	const auto old = last;
	last = steady_clock::now();
	totalTime = last - old;
	const auto activeTime = totalTime - pauseTime;
	pauseLast = last;
	pauseTime = nanoseconds::zero();
	return duration<f32>(activeTime).count();
}

f32 Timer::Peek() const noexcept {
	const auto curr = steady_clock::now();
	const auto totalTime_ = curr - last;
	const auto pauseTime_ = pauseTime + (paused? (curr - pauseLast) : nanoseconds::zero());
	const auto activeTime = totalTime_ - pauseTime_;
	return duration<f32>(activeTime).count();
}

void Timer::SetPaused(bool paused_) noexcept {
	if (paused_ == paused) return;
	paused = paused_;
	if (paused) {
		pauseLast = steady_clock::now();
	} else {
		const auto old = pauseLast;
		pauseLast = steady_clock::now();
		pauseTime += pauseLast - old;
	}
}

bool Timer::IsPaused() const noexcept {
	return paused;
}

}