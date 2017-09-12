#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>	

namespace ENGINE {
	class Display
	{
	public:
		/// <summary>
		/// Creates a new window and a new OpenGL context 
		/// which we need to render to.
		/// </summary>
		/// <param name="width">The width of the new window</param>
		/// <param name="height">The height of the new window</param>
		/// <param name="title">The title of the window</param>
		Display(int width, int height, const std::string title);

		~Display();

		/// <summary>
		/// Redraws the GLClearColor on the buffer and resets the depth buffer
		/// </summary>
		void ClearBuffer();

		/// <summary>
		/// In order to show an image/buffer we need to 
		/// swap between two existing buffers
		/// </summary>
		void SwapBuffer();

		/// <summary>
		/// Returns the width of that window
		/// </summary>
		/// <returns>Width of the window</returns>
		int inline GetWidth() { return width; }

		/// <summary>
		/// Returns the height of that window
		/// </summary>
		/// <returns>Height of the window</returns>
		int inline GetHeight() { return height; }

		/// <summary>
		/// This call sets the clear color of the window to a certain color
		/// </summary>
		/// <param name="r">Red part of color (Range 0-1)</param>
		/// <param name="g">Green part of color (Range 0-1)</param>
		/// <param name="b">Blue part of color (Range 0-1)</param>
		void SetClearColor(float r, float g, float b);

		static Display* GetInstance();
	private:
		//width and height of window
		int width, height;

		//the OpenGL context needed to work with the GPU
		SDL_GLContext glContext;

		//The window handler by SDL2
		SDL_Window * window;

		static Display* instance;

	private:
		friend class Component;
		friend class Scene;
		void SetMousePosition(int x, int y);
	};
}
