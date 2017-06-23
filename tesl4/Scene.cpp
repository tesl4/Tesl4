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
	
	CTriangles *triangleMesh = new CTriangles();
	triangleMesh->Init();
	CActor *newActor = new CActor();
	
	newActor->SetMesh(triangleMesh);
	
	newShaderObj->AddActor(newActor);
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

void CScene::Render()
{
	for (auto it : *m_ShaderObjects)
	{
		it->Render();
	}
}
