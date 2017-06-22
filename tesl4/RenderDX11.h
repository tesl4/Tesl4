#include "../../stdafx.h"

#pragma once
class CRenderDX11
{
public:
	static CRenderDX11* GetInstance();
	
	HRESULT Init(HWND)/* override*/;
	void DrawStart()/* override*/;
	void DrawEnd();
	HRESULT Cleanup()/* override*/;

	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetDeviceContext();
	
	bool		IsInitialized();

	~CRenderDX11();

	/*XMMATRIX m_Worldmat_dev;
	XMMATRIX m_Viewmat_dev;
	XMMATRIX m_Projmat_dev;*/

private:
	CRenderDX11();
	static CRenderDX11 *CRenderDX11::m_instance;
	
	ID3D11Device			*m_pDevice			  = nullptr;
	ID3D11DeviceContext		*m_pIContext		  = nullptr;
	IDXGISwapChain			*m_pSwapChain		  = nullptr;
	ID3D11RenderTargetView	*m_pRenderTargetView  = nullptr;
	ID3D11Texture2D			*m_pDepthStencilTex2d = nullptr;
	ID3D11DepthStencilView  *m_pDepthStencilView  = nullptr;

	D3D_DRIVER_TYPE				m_driverType;
	D3D_FEATURE_LEVEL			m_FeatureLv;

	
};