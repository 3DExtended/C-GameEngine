#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "../AutoUnbind.h"

#define NUMBEROFSTOREDTIMESTAMPS 50000 //TODO config file

namespace ENGINE {
	namespace UTIL {
		namespace DEBUG {

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

				TimeRepresentation operator+(TimeRepresentation other)
				{
					TimeRepresentation tmp(*this); // copy

					tmp.nsecs += other.nsecs;
					tmp.secs += other.secs;

					while (tmp.nsecs > 1000000000LL) {
						tmp.secs++;
						tmp.nsecs -= 1000000000LL;
					}

					return tmp;
				}

				TimeRepresentation operator/(uint16_t val)
				{
					TimeRepresentation tmp(*this); // copy

					tmp.secs /= val;

					tmp.nsecs += (tmp.secs - (tmp.secs*val)) * 1000000000LL;

					tmp.nsecs /= val;

					return tmp;
				}
				
				friend std::ostream &operator<< (std::ostream &out, TimeRepresentation time) {
					int32_t millisecs = time.nsecs / 1000000LL;
					int32_t microsecs = (time.nsecs - millisecs* 1000000LL) / 1000LL;
					int32_t nanosecs = (time.nsecs- microsecs* 1000LL - millisecs* 1000000LL);

					bool printFromHere = false;
					if (time.secs != 0) {
						out << "Seconds: " << time.secs;
						printFromHere = true;
					}
					
					if (millisecs != 0 || printFromHere) {
						out << " Milliseconds: " << millisecs;
						printFromHere = true;

					}
					
					if (microsecs != 0 || printFromHere) {
						out << " Microseconds: " << microsecs;
						printFromHere = true;

					}
					
					out << " Nanoseconds: " << nanosecs;
					printFromHere = true;
					

					return out;
				}
			};

			class DebugAction:public AutoUnbind {
			public:
				void _bind();
				void _unbind();
				static DebugAction* GetAction(std::string name);
				~DebugAction();

				TimeRepresentation GetAverage();

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
				std::string name;
			};
		}
	}
}

#define Action(name)\
	auto obj = ENGINE::UTIL::DEBUG::DebugAction::GetAction(name);\
	AutoBind(obj)
