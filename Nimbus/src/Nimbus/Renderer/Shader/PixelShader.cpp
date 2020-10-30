#include "pch.h"
#include "PixelShader.h"

namespace Nimbus
{
	bool PixelShader::Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath) {
		HRESULT hr = ReadShaderFile(shaderpath);

		ERROR_CHECK(FAILED(hr), L"Failed to load shader at: " + shaderpath);

		
		hr = device->CreatePixelShader(m_buffer->GetBufferPointer(), m_buffer->GetBufferSize(), NULL, m_shader.GetAddressOf());

		ERROR_CHECK(FAILED(hr), L"Failed To Create Pixel Shader: " + shaderpath);

		NIM_CORE_LOG->info("Loaded Pixel Shader!");

		return true;
	}
}

