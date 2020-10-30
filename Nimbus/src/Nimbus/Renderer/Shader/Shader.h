#pragma once
namespace Nimbus
{
	template <typename T>
	class Shader
	{
	public:
		T* GetShader() { return m_shader.Get(); }
		ID3D10Blob* GetBuffer() { return m_buffer.Get(); }

		HRESULT ReadShaderFile(std::wstring shaderpath) { return D3DReadFileToBlob(shaderpath.c_str(), m_buffer.GetAddressOf()); }

	protected:
		Microsoft::WRL::ComPtr<T> m_shader;
		Microsoft::WRL::ComPtr<ID3D10Blob> m_buffer;
	};
}
