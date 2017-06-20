#include "../../stdafx.h"
#pragma once

class CRender
{
public:


	virtual HRESULT Init(HWND)	= 0;
	virtual void	Draw()		= 0;
	virtual HRESULT Cleanup()	= 0;
	
	CRender();
	virtual ~CRender();

private:
	CRender* m_instance;

	ID3D11Device*			g_pd3dDevice		= nullptr;
	ID3D11DeviceContext*    g_pImmediateContext = nullptr;
	IDXGISwapChain*         g_pSwapChain		= nullptr;

};