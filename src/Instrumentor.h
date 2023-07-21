#pragma once

#include "TGLib.h"

#include <chrono>
#include <fstream>

//#define PROFILING
#ifdef PROFILING
#define PROFILE_BEGIN_SESSION(name, filepath) ::TGLib::Instrumentor::Get().BeginSession(name, filepath)
#define PROFILE_END_SESSION() ::TGLib::Instrumentor::Get().EndSession()
#define PROFILE_SCOPE(name) ::TGLib::InstrumentationTimer timer## __LINE__ (name)
#else
#define PROFILE_BEGIN_SESSION(name, filepath)
#define PROFILE_END_SESSION()
#define PROFILE_SCOPE(name)
#endif // PROFILING
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)

namespace TGLib {

struct ProfileResult {
	const std::string name;
	u64 start, end;
	std::thread::id threadID;
};

class Instrumentor {
public:
	~Instrumentor();

	static Instrumentor& Get();

	void BeginSession(const std::string& name, const std::string& filepath = "instr.json");
	void EndSession();
	void WriteProfile(const ProfileResult& result);
	void WriteHeader();
	void WriteFooter();
private:
	Instrumentor();
private:
	std::string sessionName = "None";
	std::ofstream outStream;
	i32 profileCount = 0;
	std::mutex mtx;
	bool activeSession = false;
};

class InstrumentationTimer {
public:
	InstrumentationTimer(const std::string& name);
	~InstrumentationTimer();

	void Stop();
private:
	ProfileResult result;
	std::chrono::time_point<std::chrono::steady_clock> startTP;
	bool stopped;
};

}