#pragma once
class CVertex
{
	XMFLOAT3 m_vPosition;

public:
	CVertex();
	CVertex(XMFLOAT3 _pos);
	virtual ~CVertex();
};

