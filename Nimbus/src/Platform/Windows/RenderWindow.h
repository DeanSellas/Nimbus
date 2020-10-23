#pragma once
namespace Nimbus
{
	class WindowContainer;

	class RenderWindow
	{

	public:
		~RenderWindow();
		HWND GetWindowHandle() const { return m_handle; }
		bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
		bool ProcessMessages();
	private:
		void RegisterWindow();
		HWND m_handle = NULL;
		HINSTANCE m_hInstance = NULL;
		std::string m_window_title = "";
		std::wstring m_window_title_wide = L"";
		std::string m_window_class = "";
		std::wstring m_window_class_wide = L"";
		int m_width = 0;
		int m_height = 0;
	};
}
