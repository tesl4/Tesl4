#pragma once
#include "Mesh.h"
class CTriangles : public CMesh
{
public:
	CTriangles();
	virtual ~CTriangles();

	void Render() override;
};

