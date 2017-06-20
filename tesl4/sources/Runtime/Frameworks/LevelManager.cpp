#include "../../stdafx.h"
#pragma once

CLevelManagers* CLevelManagers::m_Instance = nullptr;


CLevelManagers* CLevelManagers::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new CLevelManagers();
	}

	if (m_Instance == nullptr)
	{
		return nullptr;
	}

	return m_Instance;
}

CLevelManagers::CLevelManagers()
{
}


CLevelManagers::~CLevelManagers()
{
}

CMeshProto* CLevelManagers::AddMeshObj_dev()
{
	CMeshProto* proto = new CMeshProto();
	proto->Init();

	return proto;
}

HRESULT CLevelManagers::Init()
{
	HRESULT res = S_OK; 

	AddMeshObj_dev();

	return res;
}
