#pragma once

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
	unique_ptr<VertexBuffer> m_vertexBuffer = nullptr;

	vector<UINT> m_indeces;
	unique_ptr<IndexBuffer> m_indexBuffer = nullptr;

	unique_ptr<VertexShader> m_vertexShader = nullptr;

	unique_ptr<InputLayout> m_inputLayout = nullptr;

	unique_ptr<PixelShader> m_pixelShader = nullptr;

	Matrix m_world, m_view, m_projection;

	TransformData m_cpuBuffer;
	ComPtr<ID3D11Buffer> m_gpuBuffer;
};