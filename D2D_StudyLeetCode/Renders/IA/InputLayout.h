#pragma once

/// <summary>
/// Creates InputLayout and Sets IA. 
/// </summary>
class InputLayout
{
public:
	void Create(const D3D11_INPUT_ELEMENT_DESC* desc, const UINT& count, const ComPtr<ID3DBlob> blob);
	void SetIA();

public: // Getter
	ID3D11InputLayout* GetResource() const { return m_inputLayout.Get(); }

private:
	ComPtr<ID3D11InputLayout> m_inputLayout = nullptr;
};