#pragma once
#include "Shader.h"

namespace Nimbus
{
	class PixelShader : public Shader<ID3D11PixelShader>
	{
	public:
		bool Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath);
	};
}

