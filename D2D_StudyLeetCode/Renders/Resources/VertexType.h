#pragma once

///////////////////////////////
//  Vertex Type Struct List  //
///////////////////////////////

struct VertexColor
{
	VertexColor() = default;
	VertexColor(const Vector2& position, const Color& color) : position(position), color(color){}

	Vector2 position;
	Color color;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 2;
};