#pragma once

/// <summary>
/// Manage Buffer that will carry Resources(VertexType). 
/// Creates Buffer and Sets IA.
/// </summary>
class VertexBuffer
{
public:
	template <typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

public: // Setter
	void SetIA();

public: // Getter
	ID3D11Buffer* GetResource() const { return m_vertexBuffer.Get(); }
	UINT GetStride() const { return m_stride; }
	UINT GetOffset() const { return m_offset; }
	UINT GetCount() const { return m_count; }

private:
	ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
	UINT m_stride = 0;
	UINT m_offset = 0;
	UINT m_count = 0;
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	m_stride = sizeof(T);
	m_count = (UINT)vertices.size();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = m_stride * m_count;

	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
		break;
	case D3D11_USAGE_IMMUTABLE:
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
		break;
	}

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &m_vertexBuffer);
	CHECK(hr);
}
