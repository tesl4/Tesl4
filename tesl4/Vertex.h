#pragma once
class CVertex
{
	XMFLOAT3 m_vPosition;

public:
	CVertex();
	CVertex(XMFLOAT3 _pos);
	CVertex(float _x, float _y, float _z);
	
	virtual ~CVertex();
};

