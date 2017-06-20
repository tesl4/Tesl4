#pragma once
#include"stdafx.h"

typedef struct TVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
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
};


//typedef overrides
#define  TRect RECT;
