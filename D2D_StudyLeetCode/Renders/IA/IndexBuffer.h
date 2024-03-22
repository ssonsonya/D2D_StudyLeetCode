#pragma once

/// <summary>
/// Manages Buffer carrying Index info. 
/// Creates Buffer and Sets IA.
/// </summary>
class IndexBuffer
{
public:
	void Create(const vector<UINT>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

public: // Setter
	void SetIA();

public: // Getter
	ID3D11Buffer* GetResource() const { return m_indexBuffer.Get(); }
	UINT GetStride() const { return m_stride; }
	UINT GetOffset() const { return m_offset; }
	UINT GetCount() const { return m_count; }

private:
private:
	ComPtr<ID3D11Buffer> m_indexBuffer = nullptr;
	UINT m_stride = 0;
	UINT m_offset = 0;
	UINT m_count = 0;
};