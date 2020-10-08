#include <pch.h>
#include "Nimbus.h"

int WINAPI WinMain(HINSTANCE hInsatnce, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Nimbus::Log::Init();
	Nimbus::Engine engine;
	engine.Initialize(hInsatnce, "My Window", "MyWindowClass", 1280, 720);
	
	while(engine.ProcessMessages())
	{
		engine.Update();
		engine.Render();
	}
	
	return 0;
}
