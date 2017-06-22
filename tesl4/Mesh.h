#include "../../stdafx.h"
#pragma once
class CMesh
{
private:
	UINT m_RefCount;

protected:
	std::vector<TVertex> m_Vertices;
	std::vector<DWORD> m_Indexes;
	
	UINT m_strides;
	UINT m_offset;
	D3D11_PRIMITIVE_TOPOLOGY m_PrimeTopology;

	ID3D11Buffer*		m_VertextBuffer			= nullptr;
	ID3D11Buffer*		m_IndexBuffer			= nullptr;
	
public:

	CMesh();
	virtual ~CMesh();


	virtual void Render();
	

	void AddRef();
	void Release();
};

