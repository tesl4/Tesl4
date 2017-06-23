#pragma once
#include "Actor.h"
#include "Shader.h"
class CShaderObj :
	public CShader
{

	std::vector<CActor*> m_actors;


public:
	CShaderObj();
	virtual ~CShaderObj();

	void AddActor(CActor *_actor);
	void RemoveActor(CActor *_actor);

	void CreateShader() override;
	void Render() override;
};

