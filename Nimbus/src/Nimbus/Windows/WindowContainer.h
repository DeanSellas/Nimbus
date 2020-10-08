#pragma once
#include "RenderWindow.h"
#include "Nimbus/Inputs/KeyBoard.h"
#include "Nimbus/Inputs/Mouse.h"
#include "Nimbus/Renderer/Renderer.h"

namespace Nimbus
{
	class WindowContainer
	{
	public:
		// MOUSE CLASS
		// KEYBOARD CLASS
		// WINPROC
		WindowContainer();
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		RenderWindow render_window;
		KeyBoard keyboard;
		Mouse mouse;
		Renderer renderer;
	};
}