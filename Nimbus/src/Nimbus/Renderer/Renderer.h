#pragma once
#include "Adapter.h"
#include "Vertex.h"

#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>

namespace Nimbus
{
	class Renderer
	{
	public:
		bool Init(HWND hwnd, int width, int height);
		void RenderFrame();

	private:
		bool InitDX11(HWND hwnd, int width, int height);
		bool InitShaders();
		bool InitScene();

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTarget;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer2;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterState;

		VertexShader m_vertexShader;
		PixelShader m_pixelShader;

		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	};
}


