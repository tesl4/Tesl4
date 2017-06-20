#include "../../../stdafx.h"
#pragma once
class CLevelManagers
{
	static CLevelManagers* m_Instance;

	std::list<CMesh*> m_Actors;

public:
	static CLevelManagers* GetInstance();

	CLevelManagers();
	~CLevelManagers();

	CMeshProto* AddMeshObj_dev();


	HRESULT Init();
	
	void Tick(float deltaTime)
	{
		for each(auto m_Actors in m_Actors)
		{
			m_Actors->RenderTick(deltaTime);
		}
	}
};

