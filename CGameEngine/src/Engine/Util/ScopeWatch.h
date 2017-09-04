#pragma once
#include <functional>
namespace ENGINE {
	namespace UTIL {
		template <class T>
		class ScopeWatch {
		public:
			/// <summary>
			/// An instance of this is destroyed at the end of a scope
			///		(in reversed order of instantiation).
			/// When it is destroyed (by reaching end of scope), 
			///		the member funtion (memFun) of the passed object (obj) 
			///		is called.
			/// 
			/// Example Usage: 
			/// void main(){
			/// 
			///		//do stuff here
			///		Display* display;
			///		{
			///			ScopeWatch<Display> watch(display,&Display::Foo);
			///			//do stuff here
			///		} //display->Foo() gets called automatically
			/// 
			///		// do stuff here
			/// }
			///	
			/// </summary>
			/// <param name="obj">The object the member function is called on</param>
			/// <param name="memFun">The member function</param>
			ScopeWatch(T* obj, void (T::*memFun)() ):obj(obj), memFun(memFun) {
				
			}
			~ScopeWatch() {
				std::invoke(memFun, obj);
			}
		private:
			T * obj;
			void(T::*memFun)() ;

		};
	}
}