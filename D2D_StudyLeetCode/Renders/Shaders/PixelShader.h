#pragma once

/// <summary>
/// Compiles Shader file and Create & Set PixelShader.
/// </summary>
class PixelShader : public IShader
{
public: // Override
	void Create(const wstring& path, const string& entryName = "PS") override;
	void Clear() override;
	void SetShader() override;

public: // Getter
	ID3D11PixelShader* GetResouece() const { return m_pixelShader.Get(); }
	ID3DBlob* GetBlob() const { return m_blob.Get(); }

private:
	ComPtr<ID3D11PixelShader> m_pixelShader = nullptr;
	ComPtr<ID3DBlob> m_blob = nullptr;
};