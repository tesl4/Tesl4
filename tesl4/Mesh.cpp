#include "stdafx.h"
#pragma once

CMesh::CMesh()
{
	m_strides = sizeof(CVertex);
	m_offset = 0;
	m_PrimeTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_RefCount = 1;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(CVertex) * m_Vertices.size();
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	
	D3D11_SUBRESOURCE_DATA bufferData;
	ZeroMemory(&bufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	bufferData.pSysMem = &m_Vertices[0];
	CRenderDX11::GetInstance()->GetDevice()->CreateBuffer(&bufferDesc, &bufferData, &m_VertextBuffer);

	m_strides = sizeof(CVertex);
}

CMesh::~CMesh()
{
	if (m_VertextBuffer != nullptr) m_VertextBuffer->Release();
}

void CMesh::Render()
{
	if (m_VertextBuffer != nullptr) CRenderDX11::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertextBuffer, &m_strides, &m_offset);
	CRenderDX11::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(m_PrimeTopology);
	CRenderDX11::GetInstance()->GetDeviceContext()->Draw(m_Vertices.size(), m_offset);
	
}

void CMesh::AddRef()
{
	m_RefCount++;
}

void CMesh::Release()
{
	m_RefCount--;
	if (m_RefCount < 1) delete this;
}
