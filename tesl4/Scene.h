#include "stdafx.h"
#pragma once
class CScene
{
	std::vector<CShaderObj*>	*m_ShaderObjects;
	std::vector<CActor*>		*m_Actors;
	

public:
	CScene();
	virtual ~CScene();

	void BuildActor();
	
	void Release();

};

