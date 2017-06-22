#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
	m_ShaderObjects = new std::vector<CShaderObj *>();
	m_Actors		= new std::vector<CActor *>();
}


CScene::~CScene()
{
}

void CScene::BuildActor()
{
	CShaderObj *newShaderObj = new CShaderObj();
	newShaderObj->CreateShader();
	m_ShaderObjects->push_back(newShaderObj);
	
	CTriangles *triangleMesh = new CTriangles();
	CActor *newActor = new CActor();
	
	newActor->SetMesh(triangleMesh);
	
	
	m_ShaderObjects->push_back(newShaderObj);
	m_Actors->push_back(newActor);
	
	triangleMesh->Release();

	
}

void CScene::Release()
{
	for (auto it : *m_Actors)
	{
		it->Release();
	}

}
