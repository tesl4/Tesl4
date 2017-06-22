#include "stdafx.h"
#include "ShaderObj.h"


CShaderObj::CShaderObj()
{
	//m_objects = new std::vector<CActor>();
}


CShaderObj::~CShaderObj()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (&m_objects[i] != nullptr) m_objects[i]->Release();
	}

	//if (m_objects != nullptr) delete m_objects;
}

void CShaderObj::AddActor(CActor* _actor)
{
	if (std::find(m_objects.begin(), m_objects.end(), _actor) == m_objects.end())
	{
		m_objects.push_back(_actor);
		_actor->Addref();
	}
}

void CShaderObj::RemoveActor(CActor* _actor)
{
	auto found = std::find(m_objects.begin(), m_objects.end(), _actor);
	if ( found != m_objects.end())
	{
		m_objects.erase(found);
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
	CShaderObj::InitPixelShader(L"tutorial.fx", "PS", "vs_4_0", &m_PixelShader);


}

void CShaderObj::Render()
{
	CShader::Render();
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->Render();
	}
}


