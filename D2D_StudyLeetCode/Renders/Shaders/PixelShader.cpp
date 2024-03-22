#include "stdafx.h"
#include "PixelShader.h"

void PixelShader::Create(const wstring& path, const string& entryName)
{
	m_path = path;
	m_entryName = entryName;

	CompileShader(path, entryName, "ps_5_0", &m_blob);

	HRESULT hr = DEVICE->CreatePixelShader
	(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		&m_pixelShader
	);
	CHECK(hr);
}

void PixelShader::Clear()
{
	m_pixelShader.ReleaseAndGetAddressOf();
	m_blob.ReleaseAndGetAddressOf();
}

void PixelShader::SetShader()
{
	DC->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}
