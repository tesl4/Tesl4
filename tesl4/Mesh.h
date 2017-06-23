#include "../../stdafx.h"
#pragma once
#include "Vertex.h"
class CMesh
{
private:
	UINT m_RefCount;

protected:
	std::vector<CVertex>	m_Vertices;
	std::vector<DWORD>		m_Indexes;
	
	UINT m_strides;
	UINT m_offset;
	D3D11_PRIMITIVE_TOPOLOGY m_PrimeTopology;

	ID3D11Buffer*		m_VertextBuffer			= nullptr;
	ID3D11Buffer*		m_IndexBuffer			= nullptr;
	
public:

	CMesh();
	virtual ~CMesh();

	virtual void Init();

	virtual void Render();
	

	void AddRef();
	void Release();
};

