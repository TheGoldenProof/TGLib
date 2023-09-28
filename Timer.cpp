#include "Timer.h"
//#include <ratio>

using namespace std::chrono;

namespace TGLib {

Timer::Timer() {
	last = steady_clock::now();
	totalTime = nanoseconds::zero();
	pauseTime = nanoseconds::zero();
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