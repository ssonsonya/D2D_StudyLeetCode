#pragma once

struct VertexColor
{
	Vector2 position = Vector2(0.0f, 0.0f);
	Color color = Color(0.0f, 0.0f, 0.0f);
};

struct TransformData
{
	Matrix world;
	Matrix view;
	Matrix projection;
};

class Program
{
public:
	Program();

public:
	void Update();
	void Render();

private:
	vector<VertexColor> m_vertices;
	ComPtr<ID3D11Buffer> m_vertexBuffer;

	vector<UINT> m_indeces;
	ComPtr<ID3D11Buffer> m_indexBuffer;

	ComPtr<ID3DBlob> m_vsBlob;
	ComPtr<ID3D11VertexShader> m_vertexShader;

	ComPtr<ID3D11InputLayout> m_inputLayout;

	ComPtr<ID3DBlob> m_psBlob;
	ComPtr<ID3D11PixelShader> m_pixelShader;

	Matrix m_world, m_view, m_projection;

	TransformData m_cpuBuffer;
	ComPtr<ID3D11Buffer> m_gpuBuffer;
};