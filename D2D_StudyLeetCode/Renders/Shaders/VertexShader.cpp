#include "stdafx.h"

void VertexShader::Create(const wstring& path, const string& entryName)
{
	m_path = path;
	m_entryName = entryName;

	CompileShader(path, entryName, "vs_5_0", &m_blob);

	HRESULT hr = DEVICE->CreateVertexShader
	(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		&m_vertexShader
	);
	CHECK(hr);
}

void VertexShader::Clear()
{
	m_vertexShader.ReleaseAndGetAddressOf();
	m_blob.ReleaseAndGetAddressOf();
}

void VertexShader::SetShader()
{
	DC->VSSetShader(m_vertexShader.Get(), nullptr, 0);
}
