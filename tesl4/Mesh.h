#include "stdafx.h"
#pragma once
class CMesh
{
private:
	TVertex *vertices;
	WORD	*indices;

public:

	CMesh()
	{

	}

	virtual ~CMesh()
	{
	}
};

