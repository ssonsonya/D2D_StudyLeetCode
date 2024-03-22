#pragma once

/// <summary>
/// Compiles Shader file and Create & Set VertexShader.
/// </summary>
class VertexShader : public IShader
{
public: // Override
	void Create(const wstring& path, const string& entryName = "VS") override;
	void Clear() override;
	void SetShader() override;

public:
	ID3D11VertexShader* GetResources() const { return m_vertexShader.Get(); }
	ID3DBlob* GetBlob() const { return m_blob.Get(); }

private:
	ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
	ComPtr<ID3DBlob> m_blob = nullptr;
};