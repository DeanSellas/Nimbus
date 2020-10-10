#include "pch.h"
#include "Renderer.h"


namespace Nimbus
{
	bool Renderer::Init(HWND hwnd, int width, int height) {
		if(!InitDX11(hwnd, width, height))
			return false;
		if(!InitShaders())
			return false;
		if(!InitScene())
			return false;

		return true;
	}

	void Renderer::RenderFrame() {
		float bgcolor[] = { 0.0f, 0.0f, 0.0f };
		m_deviceContext->ClearRenderTargetView(m_renderTarget.Get(), bgcolor);
		m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		m_deviceContext->IASetInputLayout(m_vertexShader.GetInputLayout());
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_deviceContext->RSSetState(m_rasterState.Get());

		m_deviceContext->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

		m_deviceContext->VSSetShader(m_vertexShader.GetShader(), NULL, 0);
		m_deviceContext->PSSetShader(m_pixelShader.GetShader(), NULL, 0);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		// Red Tri
		m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
		m_deviceContext->Draw(3, 0);

		// Green Tri
		m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer2.GetAddressOf(), &stride, &offset);
		m_deviceContext->Draw(3, 0);

		m_swapChain->Present(1, NULL);
	}

	bool Renderer::InitDX11(HWND hwnd, int width, int height) {
		std::vector<AdapterData> adapters = Adapter::GetAdapterData();

		// if an adapter is found
		if(adapters.size() < 1)
		{
			NIM_CORE_LOG->error("No Graphics Adapters Found!");
			return false;
		}

		// Finds primary Adapter. Uses vram size for calculation
		AdapterData* adapter = nullptr;
		for(unsigned int i = 0; i < adapters.size(); i++)
		{
			if(adapter == nullptr || adapter->description.DedicatedVideoMemory < adapters[i].description.DedicatedVideoMemory)
			{
				adapter = &adapters[i];
			}
		}

		NIM_CORE_LOG->info(L"Using GFX Adapter: {}", adapter->description.Description);

		// Swap Chain Description
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferDesc.Width = width;
		scd.BufferDesc.Height = height;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;

		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = hwnd;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr;
		hr = D3D11CreateDeviceAndSwapChain(
			adapter->pAdapter, // Pointer To Adapter
			D3D_DRIVER_TYPE_UNKNOWN, // Drive to use
			NULL, // For Software Driver
			NULL, // Flags
			NULL, 0, // Array of Feature Levels
			D3D11_SDK_VERSION, // SDK Version
			&scd, // Swap Chain Description
			m_swapChain.GetAddressOf(), // Pointer To Swap Chain
			m_device.GetAddressOf(), // Pointer To Device
			NULL, // Supported Feature Levels
			m_deviceContext.GetAddressOf() // Address of Device Context
		);
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed To Create Swap Chain");
			return false;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Get Buffer Failed!");
			return false;
		}

		hr = m_device->CreateRenderTargetView(backBuffer.Get(), NULL, m_renderTarget.GetAddressOf());
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to create Render View!");
			return false;
		}

		// Describe Depth Stencil
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		hr = m_device->CreateTexture2D(&depthStencilDesc, NULL, m_depthStencilBuffer.GetAddressOf());
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to create Depth Stencil Buffer");
			return false;
		}

		hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), NULL, m_depthStencilView.GetAddressOf());
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to create Depth Stencil View");
			return false;
		}

		m_deviceContext->OMSetRenderTargets(1, m_renderTarget.GetAddressOf(), m_depthStencilView.Get());

		// Create Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
		ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

		depthStencilStateDesc.DepthEnable = true;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		hr = m_device->CreateDepthStencilState(&depthStencilStateDesc, m_depthStencilState.GetAddressOf());
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to create Depth Stencil State");
			return false;
		}

		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = width;
		viewport.Height = height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		m_deviceContext->RSSetViewports(1, &viewport);

		// Create Rasterizer State
		D3D11_RASTERIZER_DESC rasterDesc;
		ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));

		// Sets Render Mode - Solid or Wireframe
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.CullMode = D3D11_CULL_BACK;

		hr = m_device->CreateRasterizerState(&rasterDesc, m_rasterState.GetAddressOf());
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to create Rasterizer state");
			return false;
		}

		return true;
	}

	bool Renderer::InitShaders() {
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA},
			{"Color", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA},
		};

		if(!m_vertexShader.Init(m_device, L"VertexShader_v.cso", layout, ARRAYSIZE(layout)))
		{
			return false;
		}

		if(!m_pixelShader.Init(m_device, L"PixelShader_p.cso"))
		{
			return false;
		}

		return true;
	}

	bool Renderer::InitScene() {
		Vertex v[] = {
			Vertex(-0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f),
			Vertex(0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f),
			Vertex(0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f)
		};

		D3D11_BUFFER_DESC vertexBufferDescription;
		ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDescription.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v);
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = 0;
		vertexBufferDescription.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = v;

		HRESULT hr = m_device->CreateBuffer(&vertexBufferDescription, &vertexBufferData, m_vertexBuffer.GetAddressOf());

		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to create vertex buffer");
			return false;
		}

		// Init Green Tri

		Vertex v2[] = {
			Vertex(-0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f),
			Vertex(0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f),
			Vertex(0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f)
		};

		ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDescription.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v2);
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = 0;
		vertexBufferDescription.MiscFlags = 0;

		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = v2;

		hr = m_device->CreateBuffer(&vertexBufferDescription, &vertexBufferData, m_vertexBuffer2.GetAddressOf());

		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to create vertex buffer");
			return false;
		}

		return true;
	}

}