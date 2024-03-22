#include "stdafx.h"
#include "VertexBuffer.h"

void VertexBuffer::SetIA()
{
	DC->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &m_stride, &m_offset);
}
