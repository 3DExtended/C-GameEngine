#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "../AutoUnbind.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#define NUMBEROFSTOREDTIMESTAMPS 50000;

namespace ENGINE {
	namespace UTIL {
		namespace DEBUG {
			class DebugAction:public AutoUnbind {
			private:
				struct TimeRepresentation {
					int32_t secs = 0;
					int32_t nsecs = 0;

					TimeRepresentation operator-(TimeRepresentation other)
					{
						TimeRepresentation tmp(*this); // copy

						tmp.nsecs -= other.nsecs;
						tmp.secs -= other.secs;

						while (tmp.nsecs < 0) {
							tmp.secs--;
							tmp.nsecs += 1000000000LL;
						}

						return tmp;
					}
				};

			public:
				void _bind();
				void _unbind();
				static DebugAction* GetAction(std::string name);
				~DebugAction();
			private:
				friend class EngineClass;
				static void DestroyAllActions();
				DebugAction(std::string name);

				static std::map<std::string,DebugAction*> actions;

				uint16_t numberOfEvents = 0;
				TimeRepresentation summedTimes;

				std::vector<TimeRepresentation> eachTime;

				TimeRepresentation* boundTime = new TimeRepresentation();
				TimeRepresentation* tempTimeStamp = new TimeRepresentation();

				void writeTimeStamp(TimeRepresentation* timeStamp);
			};
		}
	}
}

#define Action(name)\
	auto obj = ENGINE::UTIL::DEBUG::DebugAction::GetAction(name);\
	AutoBind(obj)
