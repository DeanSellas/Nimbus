#include "pch.h"
#include "WindowContainer.h"

namespace Nimbus
{
	WindowContainer::WindowContainer() {
		static bool rawInput = false;
		if(!rawInput)
		{
			// mouse raw input setup
			RAWINPUTDEVICE rid;
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = NULL;

			// if register fails
			if(RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{
				std::stringstream msg;
				msg << GetLastError() << " Failed to register raw input devices";
				NIM_CORE_LOG->error(msg.str());
				exit(-1);
			}
			rawInput = true;
		}
	}
	
	LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		if(ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		{
			return true;
		}
		switch(uMsg)
		{
			// KEYBOARD MESSAGES
			case WM_KEYDOWN:
			{
				unsigned char keycode = static_cast<unsigned char>(wParam);
				if(keyboard.KeyAutoRepeat())
				{
					keyboard.OnKeyPressed(keycode);
				}
				const bool wasPressed = lParam & 0x40000000;
				if(!wasPressed)
				{
					keyboard.OnKeyPressed(keycode);
				}
				return 0;
			}
			case WM_KEYUP:
			{
				unsigned char keycode = static_cast<unsigned char>(wParam);
				keyboard.OnKeyReleased(keycode);
				return 0;
			}
			case WM_CHAR:
			{
				unsigned char ch = static_cast<unsigned char>(wParam);
				if(keyboard.CharAutoRepeat())
				{
					keyboard.OnChar(ch);
				}
				else
				{
					const bool wasPressed = lParam & 0x40000000;
					if(!wasPressed)
					{
						keyboard.OnChar(ch);
					}
				}
				return 0;
			}

			// MOUSE MESSAGES
			case WM_MOUSEMOVE:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				mouse.OnMouseMove(EventType::Move, x, y);
				return 0;
			}
			case WM_LBUTTONDOWN:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				mouse.OnButton(EventType::LPress, x, y);
				return 0;
			}
			case WM_LBUTTONUP:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				mouse.OnButton(EventType::LRelease, x, y);
				return 0;
			}
			case WM_RBUTTONDOWN:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				mouse.OnButton(EventType::RPress, x, y);
				return 0;
			}
			case WM_RBUTTONUP:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				mouse.OnButton(EventType::RRelease, x, y);
				return 0;
			}
			case WM_MBUTTONDOWN:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				mouse.OnButton(EventType::MPress, x, y);
				return 0;
			}
			case WM_MBUTTONUP:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				mouse.OnButton(EventType::MRelease, x, y);
				return 0;
			}
			case WM_MOUSEWHEEL:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				EventType wheel;
				if(GET_WHEEL_DELTA_WPARAM(wParam) > 0)
				{
					wheel = EventType::WheelUp;
				}
				else if(GET_WHEEL_DELTA_WPARAM(wParam) < 0)
				{
					wheel = EventType::WheelDown;
				}
				else
				{
					wheel = EventType::Invalid;
				}
				mouse.OnWheel(wheel, x, y);
				break;
			}

			case WM_INPUT:
			{
				UINT dataSize;
				GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

				if(dataSize > 0)
				{
					std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
					if(GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
					{
						RAWINPUT* rawinput = reinterpret_cast<RAWINPUT*>(rawdata.get());
						if(rawinput->header.dwType == RIM_TYPEMOUSE)
						{
							mouse.OnMouseMove(EventType::RAW_MOVE, rawinput->data.mouse.lLastX, rawinput->data.mouse.lLastY);
						}
					}
				}

				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}

			default:
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}