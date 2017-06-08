#pragma once
#include"stdafx.h"

typedef struct TVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

typedef struct CBNeverChanges
{
	XMMATRIX mView;
};

typedef struct CBChangeOnResize
{
	XMMATRIX mProjection;
};

typedef struct CBChangesEveryFrame
{
	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};

typedef struct TConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	XMFLOAT4 vLightDir[2];
	XMFLOAT4 vLightColor[2];
	XMFLOAT4 vOutputColor;
};