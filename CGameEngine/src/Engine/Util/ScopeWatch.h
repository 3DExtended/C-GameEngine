#pragma once
#include <functional>

namespace ENGINE {
	namespace UTIL {
		/// <summary>
		/// An instance of this is destroyed at the end of a scope
		///		(in reversed order of instantiation).
		/// When it gets destroyed (by reaching the end of the scope)
		///		the memberfunction memFun is called on the passed object
		///		obj.
		/// 
		/// Example Usage:
		/// void main(){
		///		//do stuff here
		///		Display *display;	//Create some object
		///		{	//Create new scope 
		///			ScopeWatch<Display> watch(display, &Display::Foo);
		///			//Do stuff here
		///		}	//display->Foo() gets called
		/// 
		///		//do other stuff here 
		/// }
		/// 
		/// </summary>
		template <class T>
		class ScopeWatch {
		public:

			/// <summary>
			/// Creates a new scope watch for a given object and a given member function.
			/// </summary>
			/// <param name="obj">A pointer to an object of type T</param>
			/// <param name="memFun">The member function you wanna call after a scope</param>
			ScopeWatch(T* obj, void (T::*memFun)()) : obj(obj), memFun(memFun) {}
			~ScopeWatch() {
				std::invoke(memFun, obj);
			}

		private:
			T* obj;
			void(T::*memFun)();
		};
	}
}