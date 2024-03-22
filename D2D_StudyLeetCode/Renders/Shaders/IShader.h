#pragma once

/// <summary>
/// Base Class of Vertex, PixelShader. 
/// Compiles Shader and Checks error if occur.
/// </summary>
class IShader
{
public:
	virtual ~IShader() = default;

public:
	virtual void Create(const wstring& path, const string& entryName) = 0;
	virtual void Clear() = 0;
	virtual void SetShader() = 0;

protected:
	void CompileShader(const wstring& path, const string& entryName, const string& profile, ID3DBlob** blob);

private:
	void CheckShaderError(const HRESULT& hr, const ComPtr<ID3DBlob>& error);

protected:
	wstring m_path = L"";
	string m_entryName = "";
};