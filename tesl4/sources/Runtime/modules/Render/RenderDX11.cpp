#include "../../stdafx.h"
#pragma once

CRenderDX11* CRenderDX11::m_instance = nullptr;

CRenderDX11::CRenderDX11()
{
}

CRenderDX11::~CRenderDX11()
{
}

CRenderDX11* CRenderDX11::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CRenderDX11();
	}

	if(m_instance != nullptr) return m_instance;

	return nullptr;
}

HRESULT CRenderDX11::Init(HWND _hWnd)
{
	HRESULT res = S_OK;
	RECT rect;
	
	//WinPlatform
	GetClientRect(_hWnd, &rect);
	UINT width  = rect.right - rect.left;
	UINT height = rect.bottom - rect.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;


	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		res = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, 
			featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &sd, &m_pSwapChain, 
			&m_pDevice, &m_FeatureLv, &m_pIContext);
		if (SUCCEEDED(res))
			break;
	}
	
	if (FAILED(res) == false)
	{
		//create render target

		ID3D11Texture2D* pBackbuffer = nullptr;
		res = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackbuffer);
		if (FAILED(res) == false)
		{
			res = m_pDevice->CreateRenderTargetView(pBackbuffer, nullptr, &m_pRenderTargetView);
			pBackbuffer->Release();
			if (FAILED(res) == false)
			{
				//create render target
				D3D11_TEXTURE2D_DESC descDepth;
				ZeroMemory(&descDepth, sizeof(descDepth));
				descDepth.Width = width;
				descDepth.Height = height;
				descDepth.MipLevels = 1;
				descDepth.ArraySize = 1;
				descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				descDepth.SampleDesc.Count = 1;
				descDepth.SampleDesc.Quality = 0;
				descDepth.Usage = D3D11_USAGE_DEFAULT;
				descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				descDepth.CPUAccessFlags = 0;
				descDepth.CPUAccessFlags = 0;
				descDepth.MiscFlags = 0;
				res = m_pDevice->CreateTexture2D(&descDepth, nullptr, &m_pDepthStencilTex2d);
				if (FAILED(res) == false)
				{
					D3D11_DEPTH_STENCIL_VIEW_DESC descStencilView;
					ZeroMemory(&descStencilView, sizeof(descStencilView));
					descStencilView.Format = descDepth.Format;
					descStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
					descStencilView.Texture2D.MipSlice = 0;
					res = m_pDevice->CreateDepthStencilView(m_pDepthStencilTex2d, &descStencilView, &m_pDepthStencilView);
					if (FAILED(res) == false)
					{
						m_pIContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

						D3D11_VIEWPORT viewport;
						viewport.Width = (FLOAT)width;
						viewport.Height = (FLOAT)height;
						viewport.MinDepth = 0.0f;
						viewport.MaxDepth = 1.0f;
						viewport.TopLeftX = 0;
						viewport.TopLeftY = 0;
						m_pIContext->RSSetViewports(1, &viewport);

						m_Worldmat_dev = XMMatrixIdentity();

						XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
						XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
						XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
						m_Viewmat_dev = XMMatrixLookAtLH(Eye, At, Up);

						m_Projmat_dev = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (FLOAT)height, 0.01F, 100.0F);
					}
				}
			}
		}
	}


	return res;
}

void CRenderDX11::DrawStart()
{
	float ClearColor[4] = { 0.67f, 0.39f, 0.48f, 1.0f }; //red,green,blue,alpha
	m_pIContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

}

void CRenderDX11::DrawEnd()
{
	m_pSwapChain->Present(0, 0);

}

HRESULT CRenderDX11::Cleanup()
{
	if (m_pIContext)		 m_pIContext->ClearState();
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain)		 m_pSwapChain->Release();
	if (m_pIContext)		 m_pIContext->Release();
	if (m_pDevice)			 m_pDevice->Release();
	return false;
}

ID3D11Device * CRenderDX11::GetDevice()
{
	return m_pDevice;
}

ID3D11DeviceContext* CRenderDX11::GetDeviceContext()
{
	return m_pIContext;
}

bool CRenderDX11::IsInitialized()
{
	return m_pDevice != nullptr;
}


