#include "stdafx.h"
#include "IndexBuffer.h"

void IndexBuffer::Create(const vector<UINT>& indices, const D3D11_USAGE& usage)
{
	m_stride = sizeof(UINT);
	m_count = (UINT)indices.size();

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
	subData.pSysMem = indices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &m_indexBuffer);
	CHECK(hr);
}

void IndexBuffer::SetIA()
{
	DC->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
