#pragma once
#include "Shader.h"

namespace Nimbus
{
	class VertexShader : public Shader<ID3D11VertexShader>
	{
	public:
		bool Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);

		ID3D11InputLayout* GetInputLayout() { return m_inputLayout.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	};
}