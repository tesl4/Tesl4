#include "stdafx.h"
#include "ShaderObj.h"


CShaderObj::CShaderObj()
{
	//m_objects = new std::vector<CActor>();
}


CShaderObj::~CShaderObj()
{
	for (int i = 0; i < m_actors.size(); i++)
	{
		if (&m_actors[i] != nullptr) m_actors[i]->Release();
	}

	//if (m_objects != nullptr) delete m_objects;
}

void CShaderObj::AddActor(CActor* _actor)
{
	if (std::find(m_actors.begin(), m_actors.end(), _actor) == m_actors.end())
	{
		m_actors.push_back(_actor);
		_actor->Addref();
	}
}

void CShaderObj::RemoveActor(CActor* _actor)
{
	auto found = std::find(m_actors.begin(), m_actors.end(), _actor);
	if ( found != m_actors.end())
	{
		m_actors.erase(found);
		_actor->Addref();
	}
}

void CShaderObj::CreateShader()
{
	D3D11_INPUT_ELEMENT_DESC inputLayout[]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT elements = ARRAYSIZE(inputLayout);

	CShaderObj::InitVertexShader(L"tutorial.fx", "VS", "vs_4_0", &m_VertexShader, inputLayout, elements, &m_VertexLayout);
	CShaderObj::InitPixelShader(L"tutorial.fx", "PS", "ps_4_0", &m_PixelShader);


}

void CShaderObj::Render()
{
	CShader::Render();
	for (int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->Render();
	}
}


