#pragma once
#include "Shader.h"
class CShaderObj :
	public CShader
{

	std::vector<CActor*> m_objects;


public:
	CShaderObj();
	virtual ~CShaderObj();

	void AddActor(CActor *_actor);
	void RemoveActor(CActor *_actor);

	void CreateShader() override;
	void Render() override;
};

