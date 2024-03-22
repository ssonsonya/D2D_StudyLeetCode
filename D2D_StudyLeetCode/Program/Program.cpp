#include "stdafx.h"
#include "Program.h"

Program::Program()
{
	m_vertexBuffer = make_unique<VertexBuffer>();
	m_indexBuffer = make_unique<IndexBuffer>();
	m_vertexShader = make_unique<VertexShader>();
	m_inputLayout = make_unique<InputLayout>();
	m_pixelShader = make_unique<PixelShader>();

	//vertexData
	m_vertices.assign(4, VertexColor());
	m_vertices[0].position = { -0.5f,-0.5f };
	m_vertices[0].color = { 1.0f,0.0f,0.0f,1.0f };
	m_vertices[1].position = { -0.5f,0.5f };
	m_vertices[1].color = { 1.0f,0.0f,0.0f,1.0f };
	m_vertices[2].position = { 0.5f,-0.5f };
	m_vertices[2].color = { 1.0f,0.0f,0.0f,1.0f };
	m_vertices[3].position = { 0.5f,0.5f };
	m_vertices[3].color = { 0.0f,1.0f,0.0f,1.0f };

	m_vertexBuffer->Create(m_vertices, D3D11_USAGE_IMMUTABLE);
	m_vertexShader->Create(L"_ShaderFiles/VertexColor.hlsl");

	//indexData
	m_indeces = { 0,1,2,2,1,3 };

	m_indexBuffer->Create(m_indeces, D3D11_USAGE_IMMUTABLE);

	//InputLayout
	m_inputLayout->Create(VertexColor::descs, VertexColor::count, m_vertexShader->GetBlob());

	//pixelShader
	m_pixelShader->Create(L"_ShaderFiles/VertexColor.hlsl");

	//CreateWorldViewPorjection
	Matrix S, R, T;
	/*
	S._11 = 100;
	S._22 = 100;
	*/
	S = XMMatrixScaling(100, 100, 1);
	/*
	R._11 = cosf(XMConvertToRadians(-30.0f));
	R._12 = sinf(XMConvertToRadians(-30.0f));
	R._21 = -sinf(XMConvertToRadians(-30.0f));
	R._22 = cosf(XMConvertToRadians(-30.0f));
	*/
	R = XMMatrixRotationZ(XMConvertToRadians(0.0f));
	/*
	T._41 = 100;
	T._42 = 100;
	*/
	T = XMMatrixTranslation(100, 100, 0);

	m_world = S * R * T;

	m_view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));

	m_projection = XMMatrixOrthographicLH(g_winWidth, g_winHeight, 0, 1);

	//constantBuffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &m_gpuBuffer);
	CHECK(hr);
}

void Program::Update()
{
	m_cpuBuffer.world = XMMatrixTranspose(m_world);
	m_cpuBuffer.view = XMMatrixTranspose(m_view);
	m_cpuBuffer.projection = XMMatrixTranspose(m_projection);

	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	DC->Map
	(
		m_gpuBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedSubResource
	);
	memcpy(mappedSubResource.pData, &m_cpuBuffer, sizeof(TransformData));
	DC->Unmap(m_gpuBuffer.Get(), 0);
}

void Program::Render()
{
	//IA
	m_vertexBuffer->SetIA();
	m_indexBuffer->SetIA();
	m_inputLayout->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//VSCBuffer
	DC->VSSetConstantBuffers(0, 1, m_gpuBuffer.GetAddressOf());

	//VS
	m_vertexShader->SetShader();

	//PS
	m_pixelShader->SetShader();

	//Draw
	DC->DrawIndexed(m_indexBuffer->GetCount(), 0, 0);
}
