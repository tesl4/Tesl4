#include "Renderer.h"

#pragma once
class CRenderDX11 : public CRender
{
public:
	CRenderDX11();
	~CRenderDX11();
	
	HRESULT Init(HWND) override;
	void Draw() override;
	HRESULT Cleanup() override;
private:
	ID3D11Device			*m_pDevice			  = nullptr;
	ID3D11DeviceContext		*m_pIContext		  = nullptr;
	IDXGISwapChain			*m_pSwapChain		  = nullptr;
	ID3D11RenderTargetView	*m_pRenderTargetView  = nullptr;
	ID3D11Texture2D			*m_pDepthStencilTex2d = nullptr;
	ID3D11DepthStencilView  *m_pDepthStencilView  = nullptr;

	D3D_DRIVER_TYPE				m_driverType;
	D3D_FEATURE_LEVEL			m_FeatureLv;
	

};