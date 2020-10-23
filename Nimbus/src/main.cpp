#include <pch.h>
#include "Nimbus/Core/Engine.h"

// TODO: move this to a seperate project in the future. and make the engine a DLL
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
