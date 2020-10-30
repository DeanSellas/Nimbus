#include "pch.h"
#include "VertexShader.h"

namespace Nimbus
{
	bool VertexShader::Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements) {
		HRESULT hr = ReadShaderFile(shaderpath);
		
		ERROR_CHECK(FAILED(hr), L"Failed to load shader at: " + shaderpath);

		hr = device->CreateVertexShader(m_buffer->GetBufferPointer(), m_buffer->GetBufferSize(), NULL, m_shader.GetAddressOf());

		ERROR_CHECK(FAILED(hr), L"Failed to create Vertex Shader: "+shaderpath)

		hr = device->CreateInputLayout(
			layoutDesc,
			numElements,
			m_buffer->GetBufferPointer(),
			m_buffer->GetBufferSize(),
			m_inputLayout.GetAddressOf()
		);

		ERROR_CHECK(FAILED(hr), "Failed to Create Input Layout");
		
		NIM_CORE_LOG->info("Loaded Vertex Shader!");

		return true;
	}

}