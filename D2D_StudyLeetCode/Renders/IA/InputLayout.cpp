#include "stdafx.h"
#include "InputLayout.h"

void InputLayout::Create(const D3D11_INPUT_ELEMENT_DESC* desc, const UINT& count, const ComPtr<ID3DBlob> blob)
{
	if (!desc || !count || !blob)
		assert(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		desc,
		count, 
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&m_inputLayout
	);
	CHECK(hr);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(m_inputLayout.Get());
}
