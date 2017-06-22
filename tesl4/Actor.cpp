#include "stdafx.h"
#include "Actor.h"


CActor::CActor()
{
	m_Worldmat = XMMatrixIdentity();
	m_Mesh = nullptr;
	m_refCount = 1;
}


CActor::~CActor()
{
	if (m_Mesh != nullptr) m_Mesh->Release();
}

void CActor::Addref()
{
	m_refCount++;
}

void CActor::Release()
{
	m_refCount--;
	if (m_refCount < 1) delete this;
}

void CActor::SetMesh(CMesh * _mesh)
{
	m_Mesh->Release();
	m_Mesh = _mesh;
	m_Mesh->AddRef();
}

void CActor::Tick(float delta)
{
}

void CActor::Render()
{
	if(m_Mesh != nullptr) m_Mesh->Render();
}
