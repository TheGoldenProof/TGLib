#pragma once
#include "TGLib.h"
#include <chrono>

namespace TGLib {

class Timer {
public:
	Timer();
	f32 Mark() noexcept; // does not unpause
	f32 Peek() const noexcept;
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