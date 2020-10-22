#pragma once
#include <DirectXMath.h>
namespace Nimbus
{
	struct Vertex
	{
		Vertex();
		
		Vertex(float x, float y, float z, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 0.0f) : pos(x, y, z), color(r, g, b) {}
		Vertex(DirectX::XMFLOAT3 positionFloat,  float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 0.0f) : pos(positionFloat), color(r, g, b) {}
		
		Vertex(float x, float y, float z, DirectX::XMFLOAT3 colorFloat = { 1.0f, 1.0f, 1.0f }) : pos(x, y, z), color(colorFloat) {}
		Vertex(DirectX::XMFLOAT3 positionFloat, DirectX::XMFLOAT3 colorFloat = { 1.0f, 1.0f, 1.0f }) : pos(positionFloat), color(colorFloat) {}
		
		Vertex(float x, float y, float z = 0.0f, DirectX::XMFLOAT4 colorFloat = { 1.0f, 1.0f, 1.0f, 0.0f }) : pos(x, y, z), color(colorFloat.x, colorFloat.y, colorFloat.z) {}
		Vertex(DirectX::XMFLOAT3 positionFloat, DirectX::XMFLOAT4 colorFloat = { 1.0f, 1.0f, 1.0f, 0.0f }) : pos(positionFloat), color(colorFloat.x, colorFloat.y, colorFloat.z) {}
		
		Vertex(float x, float y, float z, DirectX::XMVECTORF32 dxColor = DirectX::Colors::White) : pos(x, y, z), color(dxColor) {}
		Vertex(DirectX::XMFLOAT3 positionFloat, DirectX::XMVECTORF32 dxColor = DirectX::Colors::White) : pos(positionFloat), color(dxColor) {}

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};
}