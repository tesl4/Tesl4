#include "stdafx.h"
#pragma once
#include "ShaderObj.h"
#include "Actor.h"

class CScene
{
	std::vector<CShaderObj*>	*m_ShaderObjects;
	std::vector<CActor*>		*m_Actors;
	

public:
	CScene();
	virtual ~CScene();

	void BuildActor();
	
	void Release();

	void Render();


};

