#include "pch.h"
#include "PixelShader.h"

namespace Nimbus
{
	bool PixelShader::Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath) {
		HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), m_buffer.GetAddressOf());

		if(FAILED(hr))
		{
			NIM_CORE_LOG->error(L"Failed to load shader at: {}", shaderpath);
			return false;
		}

		hr = device->CreatePixelShader(m_buffer->GetBufferPointer(), m_buffer->GetBufferSize(), NULL, m_shader.GetAddressOf());
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error(L"Failed To create Vertex Shader: {}", shaderpath);
			return false;
		}

		NIM_CORE_LOG->info("Loaded Pixel Shader!");

		return true;
	}
}

