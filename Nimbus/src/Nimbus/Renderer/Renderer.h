#pragma once
#include "Adapter.h"
#include "Vertex.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>

#include <imgui.h>
#include <Nimbus/Renderer/ImGui/imgui_impl_win32.h>
#include <Nimbus/Renderer/ImGui/imgui_impl_dx11.h>

namespace Nimbus
{
	struct VertexBufferGroup
	{
		VertexBufferGroup(Microsoft::WRL::ComPtr<ID3D11Buffer> buffer, int c) : vertexBuffer(buffer), count(c) {}; 

		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
		int count;
	};
	
	class Renderer
	{
	public:
		bool Init(HWND hwnd, int width, int height);
		void RenderFrame(Timestep deltaTime);
		~Renderer() { m_vertexVector.clear(); }
	private:
		bool InitDX11(HWND hwnd, int width, int height);
		bool InitShaders();
		bool InitScene();

		

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTarget;

		std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> m_vertexVector;
		std::vector<int> m_vertexVectorCount;
		
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterState;

		Scope<DirectX::SpriteBatch> m_spriteBatch;
		Scope<DirectX::SpriteFont> m_spriteFont;
		
		VertexShader m_vertexShader;
		PixelShader m_pixelShader;
	};
}


