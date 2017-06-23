#include "stdafx.h"
#include "Shader.h"

extern HWND g_hWnd;

CShader::CShader()
{
	
}


CShader::~CShader()
{
	if (m_VertexLayout != nullptr)m_VertexLayout->Release();
	if (m_PixelShader  != nullptr)m_PixelShader->Release();
	if (m_VertexShader  != nullptr)m_VertexShader->Release();


}

void CShader::InitVertexShader(WCHAR * _fileName, LPCSTR _entryPoint, LPCSTR _shadermodel, ID3D11VertexShader ** _d3d1VertexShader, D3D11_INPUT_ELEMENT_DESC * _inputLayoutDesc, UINT _elements, ID3D11InputLayout ** _inputLayout)
{
	ID3DBlob *vsBlob = nullptr;
	if (SUCCEEDED(CompileShaderFromFile(_fileName, _entryPoint, _shadermodel, &vsBlob)))
	{
		if(SUCCEEDED(CRenderDX11::GetInstance()->GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_VertexShader)))
		{
			if (SUCCEEDED(CRenderDX11::GetInstance()->GetDevice()->CreateInputLayout(_inputLayoutDesc, _elements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_VertexLayout)))
			{
				
			}
			vsBlob->Release();
		}
	}
	else
	{
		MessageBox(g_hWnd, L"VertexShader File 없음", L"Error", MB_OK);
	}

}

void CShader::InitPixelShader(WCHAR * _fileName, LPCSTR _entryPoint, LPCSTR _shadermodel, ID3D11PixelShader **_pixelShader)
{
	ID3DBlob *psBlob = nullptr;
	if (SUCCEEDED(CompileShaderFromFile(_fileName, _entryPoint, _shadermodel, &psBlob)))
	{
		if (SUCCEEDED(CRenderDX11::GetInstance()->GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_PixelShader)))
		{
			
		}
		psBlob->Release();
	}
	else
	{

		MessageBox(g_hWnd, L"PixelShader File 없음", L"Error", MB_OK);
	}
}

HRESULT CShader::CompileShaderFromFile(WCHAR * szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob ** ppBlobOut)
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

void CShader::CreateShader()
{
}

void CShader::Render()
{
	if (m_VertexLayout != null) CRenderDX11::GetInstance()->GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	if (m_VertexShader != null) CRenderDX11::GetInstance()->GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
	if (m_VertexLayout != null) CRenderDX11::GetInstance()->GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);
}
