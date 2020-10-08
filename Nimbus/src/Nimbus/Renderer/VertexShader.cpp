#include "pch.h"
#include "VertexShader.h"

namespace Nimbus
{
	bool VertexShader::Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements) {
		HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), m_buffer.GetAddressOf());

		if(FAILED(hr))
		{
			NIM_CORE_LOG->error(L"Failed to load shader at: {}", shaderpath);
			return false;
		}

		hr = device->CreateVertexShader(m_buffer->GetBufferPointer(), m_buffer->GetBufferSize(), NULL, m_shader.GetAddressOf());
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error(L"Failed To create Vertex Shader: {}", shaderpath);
			return false;
		}

		hr = device->CreateInputLayout(
			layoutDesc,
			numElements,
			m_buffer->GetBufferPointer(),
			m_buffer->GetBufferSize(),
			m_inputLayout.GetAddressOf()
		);

		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed To Create Input Layout");
			return false;
		}

		NIM_CORE_LOG->info("Loaded Vertex Shader!");

		return true;
	}

}