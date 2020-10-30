#pragma once
#include <windows.h>
#include "Platform/Windows/WindowContainer.h"
#include "Nimbus/Renderer/Renderer.h"

namespace Nimbus
{
	class Engine : WindowContainer
	{
	public:
		Engine() {}
		~Engine() {}
		bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
		bool ProcessMessages();
		void Update();
		void Render();

	private:
		std::chrono::system_clock::time_point m_startTime, m_lastTime;
	};
}

