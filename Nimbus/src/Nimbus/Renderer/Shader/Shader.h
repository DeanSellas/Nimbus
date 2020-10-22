#pragma once
// TODO: Create a shader class that will encompass both pixel and vertex shaderst

namespace Nimbus
{
	template <typename T>
	class Shader
	{
	public:
		T* GetShader() { return m_shader.Get(); }
		ID3D10Blob* GetBuffer() { return m_buffer.Get(); }

	protected:
		Microsoft::WRL::ComPtr<T> m_shader;
		Microsoft::WRL::ComPtr<ID3D10Blob> m_buffer;
	};
}
