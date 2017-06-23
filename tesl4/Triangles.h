#pragma once
#include "Mesh.h"
class CTriangles : public CMesh
{
public:
	CTriangles();
	virtual ~CTriangles();

	void Init() override;

	void Render() override;
};

