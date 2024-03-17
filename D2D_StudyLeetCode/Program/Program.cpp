#include "stdafx.h"
#include "Program.h"

Program::Program()
{
	//vertexData
	{
		m_vertices.assign(4, VertexColor());
		m_vertices[0].position = { -0.5f,-0.5f };
		m_vertices[0].color = { 1.0f,0.0f,0.0f,1.0f };
		m_vertices[1].position = { -0.5f,0.5f };
		m_vertices[1].color = { 1.0f,0.0f,0.0f,1.0f };
		m_vertices[2].position = { 0.5f,-0.5f };
		m_vertices[2].color = { 1.0f,0.0f,0.0f,1.0f };
		m_vertices[3].position = { 0.5f,0.5f };
		m_vertices[3].color = { 0.0f,1.0f,0.0f,1.0f };
	}

	//vertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.ByteWidth = sizeof(VertexColor) * (UINT)m_vertices.size();
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = m_vertices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &m_vertexBuffer);
		CHECK(hr);
	}

	//vertexShader
	{
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
		ID3DBlob* OutError = NULL;
		HRESULT hr = D3DCompileFromFile
		(
			L"_ShaderFiles/VertexColor.hlsl",
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"VS",
			"vs_5_0",
			flags,
			0,
			&m_vsBlob,
			&OutError
		);

		if (OutError)
		{
			string str = (char*)OutError->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "HLSL Error", MB_OK);
		}
		CHECK(hr);

		hr = DEVICE->CreateVertexShader
		(
			m_vsBlob->GetBufferPointer(),
			m_vsBlob->GetBufferSize(),
			nullptr,
			&m_vertexShader
		);
		CHECK(hr);
	}

	//indexData
	{
		m_indeces = { 0,1,2,2,1,3 };
	}

	//indexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * (UINT)m_indeces.size();

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = m_indeces.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &m_indexBuffer);
		CHECK(hr);
	}

	//InputLayout
	{
		//InputLayoutDESC
		D3D11_INPUT_ELEMENT_DESC layoutDesc[]
		{
			{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		};

		HRESULT hr = DEVICE->CreateInputLayout
		(
			layoutDesc,
			2,
			m_vsBlob->GetBufferPointer(),
			m_vsBlob->GetBufferSize(),
			&m_inputLayout
		);
		CHECK(hr);
	}

	//pixelShader
	{
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
		ID3DBlob* OutError = NULL;
		HRESULT hr = D3DCompileFromFile
		(
			L"_ShaderFiles/VertexColor.hlsl",
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"PS",
			"ps_5_0",
			flags,
			0,
			&m_psBlob,
			&OutError
		);

		if (OutError)
		{
			string str = (char*)OutError->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "HLSL Error", MB_OK);
		}
		CHECK(hr);

		hr = DEVICE->CreatePixelShader
		(
			m_psBlob->GetBufferPointer(),
			m_psBlob->GetBufferSize(),
			nullptr,
			&m_pixelShader
		);
		CHECK(hr);
	}

	//CreateWorldViewPorjection
	{
		Matrix S, R, T;
		/*
		S._11 = 100;
		S._22 = 100;
		*/
		S = XMMatrixScaling(50, 100, 1);
		/*
		R._11 = cosf(XMConvertToRadians(-30.0f));
		R._12 = sinf(XMConvertToRadians(-30.0f));
		R._21 = -sinf(XMConvertToRadians(-30.0f));
		R._22 = cosf(XMConvertToRadians(-30.0f));
		*/
		R = XMMatrixRotationZ(XMConvertToRadians(-30.0f));
		/*
		T._41 = 100;
		T._42 = 100;
		*/
		T = XMMatrixTranslation(100, 100, 0);

		m_world = S * R * T;

		m_view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));

		m_projection = XMMatrixOrthographicLH(g_winWidth, g_winHeight, 0, 1);
	}

	//constanctBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TransformData);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &m_gpuBuffer);
		CHECK(hr);
	}
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
	UINT stride = sizeof(VertexColor);
	UINT offset = 0;
	//IA
	DC->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	DC->IASetInputLayout(m_inputLayout.Get());
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//VSCBuffer
	DC->VSSetConstantBuffers(0, 1, m_gpuBuffer.GetAddressOf());

	//VS
	DC->VSSetShader(m_vertexShader.Get(), nullptr, 0);

	//PS
	DC->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//±×·Á¶ó
	DC->DrawIndexed((UINT)m_indeces.size(), 0, 0);
}
