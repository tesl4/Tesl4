#include "stdafx.h"
#include "Triangles.h"


CTriangles::CTriangles() : CMesh::CMesh()
{
	m_Vertices = {
		CVertex(0.0f, 0.5f, 0.5f),
		CVertex(0.5f, -0.5f, 0.5f),
		CVertex(-0.5f, -0.5f, 0.5f),
	};


}


CTriangles::~CTriangles()
{
}

void CTriangles::Init()
{
	CMesh::Init();
}

void CTriangles::Render()
{
	CMesh::Render();
}
