#include "DebugAction.h"
using namespace ENGINE;
using namespace ENGINE::UTIL;
using namespace ENGINE::UTIL::DEBUG;

std::map<std::string, DebugAction*> DebugAction::actions = std::map<std::string, DebugAction*>();

#if _WIN32
LARGE_INTEGER sFrequency; //is initialized with 0
#endif

void ENGINE::UTIL::DEBUG::DebugAction::_bind()
{
	writeTimeStamp(boundTime);
}

void ENGINE::UTIL::DEBUG::DebugAction::_unbind()
{
	writeTimeStamp(tempTimeStamp);
	//difference between boundTime and tempTimeStamp is the time used
	//TODO
	TimeRepresentation temp;
	temp = *tempTimeStamp - *boundTime;

	std::cout << "Secs: " << temp.secs << ", NanoSecs: " << temp.nsecs << std::endl;

	numberOfEvents++;
}

DebugAction * ENGINE::UTIL::DEBUG::DebugAction::GetAction(std::string name)
{
#if _WIN32
	if (sFrequency.QuadPart == 0)
		QueryPerformanceFrequency(&sFrequency);
#endif
	DebugAction* action = nullptr;

	std::map<std::string, DebugAction*>::iterator it = actions.find(name);

	if (it == actions.end()) {
		action = new DebugAction(name);
		actions.insert(std::pair<std::string, DebugAction*>(name, action));
	}
	else {
		action = it->second;
	}

	return action;
}

ENGINE::UTIL::DEBUG::DebugAction::DebugAction(std::string name)
{
	NUMBEROFSTOREDTIMESTAMPS
}

ENGINE::UTIL::DEBUG::DebugAction::~DebugAction()
{
	delete boundTime;
}

void ENGINE::UTIL::DEBUG::DebugAction::DestroyAllActions()
{
}

void ENGINE::UTIL::DEBUG::DebugAction::writeTimeStamp(TimeRepresentation * timeStamp)
{
#ifdef _WIN32
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	timeStamp->secs = int32_t(time.QuadPart / sFrequency.QuadPart);
	timeStamp->nsecs = int32_t((time.QuadPart % sFrequency.QuadPart) * 1000000000LL / sFrequency.QuadPart);
#else
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	timeStamp->secs = t.tv_sec;
	timeStamp->nsecs = t.tv_nsec;
#endif
}
