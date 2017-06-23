#include "stdafx.h"
#include "Vertex.h"


CVertex::CVertex():m_vPosition(XMFLOAT3(0.0f, 0.0f, 0.0f))
{ }

CVertex::CVertex(XMFLOAT3 _pos)
{
	m_vPosition = _pos;
}

CVertex::CVertex(float _x, float _y, float _z)
{
	m_vPosition = XMFLOAT3(_x, _y, _z);
}


CVertex::~CVertex()
{
}
