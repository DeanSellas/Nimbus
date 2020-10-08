#include "pch.h"
#include "RenderWindow.h"
#include  "WindowContainer.h"

#include "Nimbus/Log.h"
namespace Nimbus
{
	RenderWindow::~RenderWindow() {
		if(m_handle != NULL)
		{
			UnregisterClass(m_window_class_wide.c_str(), m_hInstance);
			DestroyWindow(m_handle);
		}
	}

	bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
		m_hInstance = hInstance;

		m_window_title = window_title;
		m_window_class = window_class;

		m_width = width;
		m_height = height;

		m_window_title_wide = StringConverter::StringToWide(window_title);
		m_window_class_wide = StringConverter::StringToWide(window_class);

		RegisterWindow();

		RECT windowRect = { 0, 0, width, height };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		// https://docs.microsoft.com/en-us/windows/win32/learnwin32/creating-a-window
		m_handle = CreateWindowEx(
			0,
			m_window_class_wide.c_str(),
			m_window_title_wide.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			0,
			0,
			width,
			height,
			NULL,
			NULL,
			hInstance,
			pWindowContainer);

		if(FAILED(m_handle))
		{
			NIM_CORE_LOG->error("Create Window Failed for window: " + window_title);
			return false;
		}


		ShowWindow(m_handle, SW_SHOW);
		UpdateWindow(m_handle);
		SetForegroundWindow(m_handle);
		SetFocus(m_handle);
		return true;
	}

	LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch(uMsg)
		{
			case WM_CLOSE:
				DestroyWindow(hwnd);
				return 0;
			default:
				WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
				return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		switch(uMsg)
		{
			case WM_CREATE:
			{
				const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
				WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
				if(pWindow == nullptr)
				{
					NIM_CORE_LOG->error("Pointer to window container is null!");
					exit(-1);
				}
				SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
				SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
				return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
			}

			default:
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	void RenderWindow::RegisterWindow() {
		WNDCLASSEX wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = HandleMessageSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hInstance;
		wc.hIcon = NULL;
		wc.hIconSm = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_window_class_wide.c_str();
		wc.cbSize = sizeof(WNDCLASSEX);

		RegisterClassEx(&wc);
	}


	bool RenderWindow::ProcessMessages() {
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));
		while(PeekMessage(&msg, m_handle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_NULL)
		{
			if(!IsWindow(m_handle))
			{
				m_handle = NULL;
				UnregisterClass(m_window_class_wide.c_str(), m_hInstance);
				return false;
			}
		}

		return true;
	}
}


