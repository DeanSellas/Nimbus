#pragma once
#include <DirectXMath.h>
namespace Nimbus
{
	struct Vertex
	{
		Vertex();
		Vertex(float x, float y, float z = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f) : pos(x, y, z), color(r, g, b) {}

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};
}