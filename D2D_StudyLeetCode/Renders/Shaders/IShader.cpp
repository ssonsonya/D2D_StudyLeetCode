#include "stdafx.h"
#include "IShader.h"

void IShader::CompileShader(const wstring& path, const string& entryName, const string& profile, ID3DBlob** blob)
{
	ComPtr<ID3DBlob> error;
	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),
		nullptr,
		nullptr,
		entryName.c_str(),
		profile.c_str(),
		D3DCOMPILE_ENABLE_STRICTNESS,
		0,
		blob,
		&error
	);
	CheckShaderError(hr, error);
}

void IShader::CheckShaderError(const HRESULT& hr, const ComPtr<ID3DBlob>& error)
{
	if (FAILED(hr))
	{
		if (error.Get())
		{
			const string& str = (const char*)error->GetBufferPointer();
			MessageBoxA(nullptr, str.c_str(), "Shader Error!", MB_OK);
		}
		assert(false);
	}
}
