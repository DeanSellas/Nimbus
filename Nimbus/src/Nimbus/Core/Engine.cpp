#include "pch.h"
#include "Engine.h"

namespace Nimbus
{
	bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
		if(!render_window.Initialize(this, hInstance, window_title, window_class, width, height))
			return false;

		if(!renderer.Init(render_window.GetWindowHandle(), width, height))
			return false;

		return true;
	}

	bool Engine::ProcessMessages() {
		return render_window.ProcessMessages();
	}

	void Engine::Update() {
		while(!keyboard.CharBufferEmpty())
		{
			unsigned char ch = keyboard.ReadChar();
			std::string msg = "Char: ";
			msg += ch;
			NIM_CORE_LOG->info(msg);
		}
		while(!keyboard.KeyBufferEmpty())
		{
			KeyBoardEvent e = keyboard.ReadKey();
			std::string msg = "KeyEvent: ";
			if(e.isPressed())
			{
				msg += "[KEY PRESSED] ";
			}

			if(e.isReleased())
			{
				msg += "[KEY RELEASED] ";
			}

			msg += e.GetKeyCode();
			NIM_CORE_LOG->info(msg);
		}

		while(!mouse.MouseBufferEmpty())
		{
			MouseEvent e = mouse.ReadEvent();
			if(e.GetEventType() == EventType::WheelUp)
			{
				NIM_CORE_LOG->info("WHEEL UP!");
			}if(e.GetEventType() == EventType::WheelDown)
			{
				NIM_CORE_LOG->info("WHEEL DOWN!");
			}
			if(e.GetEventType() == EventType::RAW_MOVE)
			{
			}
		}
	}

	void Engine::Render() {
		renderer.RenderFrame();
	}
}