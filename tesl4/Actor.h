#pragma once
#include "Mesh.h"
#include "Actor.h"

class CActor
{
	int m_refCount;


public:
	CActor();
	virtual ~CActor();

	void Addref();
	void Release();
	
	XMMATRIX m_Worldmat;
	CMesh *m_Mesh;

	virtual void SetMesh(CMesh *_mesh);
	virtual void Tick(float delta);
	virtual void Render();


};

