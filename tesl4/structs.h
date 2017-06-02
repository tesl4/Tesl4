#pragma once
#include"stdafx.h"

typedef struct TVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

typedef struct TConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

};