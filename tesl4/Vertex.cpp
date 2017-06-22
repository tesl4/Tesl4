#include "stdafx.h"
#include "Vertex.h"


CVertex::CVertex():m_vPosition(XMFLOAT3(0.0f, 0.0f, 0.0f))
{ }

CVertex::CVertex(XMFLOAT3 _pos)
{
	m_vPosition = _pos;
}


CVertex::~CVertex()
{
}
