#include "../../stdafx.h"
#pragma once

HRESULT CMesh::Init()
{
	HRESULT res = false;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TVertex) * m_Vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &m_Vertices[0];
	res = CRenderDX11::GetInstance()->GetDevice()->CreateBuffer(&bd, &InitData, &m_VertextBuffer);
	if (SUCCEEDED(res))
	{
		UINT offset = 0;
		UINT strides = sizeof(TVertex);
		CRenderDX11::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertextBuffer, &strides, &offset);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * m_Indexes.size();
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = &m_Indexes[0];
		res = CRenderDX11::GetInstance()->GetDevice()->CreateBuffer(&bd, &InitData, &m_IndexBuffer);
		if (SUCCEEDED(res))
		{
			CRenderDX11::GetInstance()->GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
			CRenderDX11::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			InitVertexShader();
			InitPixelShader();

			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(TConstantBuffer);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = 0;
			res = CRenderDX11::GetInstance()->GetDevice()->CreateBuffer(&bd, nullptr, &m_ConstantBuffer);
		}
	}

	return res;
}

void CMesh::RenderTick(float deltaTime)
{
	CRenderDX11::GetInstance()->m_Worldmat_dev = XMMatrixRotationY(deltaTime);

	TConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(CRenderDX11::GetInstance()->m_Worldmat_dev);
	cb.mView = XMMatrixTranspose(CRenderDX11::GetInstance()->m_Viewmat_dev);
	cb.mProjection = XMMatrixTranspose(CRenderDX11::GetInstance()->m_Projmat_dev);
	CRenderDX11::GetInstance()->GetDeviceContext()->UpdateSubresource(m_ConstantBuffer, 0, NULL, &cb, 0, 0);

	//trouble
	if (m_VertexShader != nullptr)
	{
		CRenderDX11::GetInstance()->GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
		//std::cout << "m_VertexShader 스틸얼라이브" << std::endl;
	}
	else
	{
		//std::cout << "m_VertexShader 뒈짖" << std::endl;
	}

	if (m_ConstantBuffer != nullptr)
	{
		CRenderDX11::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
		std::cout << "m_ConstantBuffer 스틸얼라이브" << std::endl;
	}
	else
	{
		std::cout << "m_ConstantBuffer 뒈짖" << std::endl;
	}

	if (m_PixelShader != nullptr)
	{
		CRenderDX11::GetInstance()->GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);
		//std::cout << "m_PixelShader 스틸얼라이브" << std::endl;
	}

	CRenderDX11::GetInstance()->GetDeviceContext()->DrawIndexed(m_Indexes.size(), 0, 0);
}

void CMesh::Release()
{
}

HRESULT CMesh::InitPixelShader()
{
	HRESULT res = E_FAIL;
	ID3DBlob* pPSBlob = nullptr;
	res = CompileShaderFromFile(L"tutorial.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(res))
	{
		MessageBox(nullptr, L"CMesh::InitPixelShader tutorial.fx 을 찾지 못했습니다.", L"Error", MB_OK);
	}
	else
	{
		res = CRenderDX11::GetInstance()->GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_PixelShader);
		pPSBlob->Release();
	}
	return res;

}

HRESULT CMesh::InitVertexShader()
{
	HRESULT res = E_FAIL;

	ID3DBlob* pVSBlob = nullptr;
	res = CompileShaderFromFile(L"tutorial.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(res))
	{
		MessageBox(nullptr, L"CMesh::InitvertexShader tutorial.fx 을 찾지 못했습니다.", L"Error", MB_OK);
	}
	else
	{
		res = CRenderDX11::GetInstance()->GetDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_VertexShader);
		if (SUCCEEDED(res))
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			UINT numElem = ARRAYSIZE(layout);
			res = CRenderDX11::GetInstance()->GetDevice()->CreateInputLayout(layout, numElem, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_VertextInputLayout);
			pVSBlob->Release();
			if (SUCCEEDED(res))
				CRenderDX11::GetInstance()->GetDeviceContext()->IASetInputLayout(m_VertextInputLayout);
		}
	}
	return res;
}

HRESULT CMesh::InitConstantbufer()
{
	return E_NOTIMPL;
}

HRESULT CMesh::CompileShaderFromFile(WCHAR * szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob ** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}