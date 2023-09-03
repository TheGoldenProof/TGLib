#include "Instrumentor.h"

#include <algorithm>

namespace TGLib {

Instrumentor::Instrumentor() {}

Instrumentor::~Instrumentor() {
	EndSession();
}

Instrumentor& Instrumentor::Get() {
	static Instrumentor instance;
	return instance;
}

void Instrumentor::BeginSession(const std::string& name, const std::string& filepath) {
	if (activeSession) EndSession();

	activeSession = true;
	outStream.open(filepath);
	WriteHeader();
	sessionName = name;
}

void Instrumentor::EndSession() {
	if (!activeSession) return;

	activeSession = false;
	WriteFooter();
	outStream.close();
	profileCount = 0;
}

void Instrumentor::WriteProfile(const ProfileResult& result) {
	std::lock_guard<std::mutex> lock(mtx);

	if (profileCount++ > 0) outStream << ',';

	std::string name = result.name;
	std::replace(name.begin(), name.end(), '"', '\'');

	outStream
		<< "{"
		<< "\"cat\":\"function\","
		<< "\"dur\":" << (result.end - result.start) << ','
		<< "\"name\":\"" << name << "\","
		<< "\"ph\":\"X\","
		<< "\"pid\":0,"
		<< "\"tid\":" << result.threadID << ','
		<< "\"ts\":" << result.start
		<< "}";
}

void Instrumentor::WriteHeader() {
	outStream << "{\"otherData\":{},\"traceEvents\":[";
}

void Instrumentor::WriteFooter() {
	outStream << "]}";
}


InstrumentationTimer::InstrumentationTimer(const std::string& name)
	: result({ name, 0, 0, std::this_thread::get_id() }), stopped(false) {
	startTP = std::chrono::steady_clock::now();
}

InstrumentationTimer::~InstrumentationTimer() {
	if (!stopped) Stop();
}

void InstrumentationTimer::Stop() {
	using namespace std::chrono;
	auto endTP = steady_clock::now();

	result.start = time_point_cast<microseconds>(startTP).time_since_epoch().count();
	result.end = time_point_cast<microseconds>(endTP).time_since_epoch().count();
	result.threadID = std::this_thread::get_id();
	Instrumentor::Get().WriteProfile(result);

	stopped = true;
}

}