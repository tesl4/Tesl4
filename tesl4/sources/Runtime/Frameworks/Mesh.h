#include "../../stdafx.h"
#pragma once
class CMesh
{

protected:
	std::vector<TVertex> m_Vertices;
	std::vector<DWORD> m_Indexes;
	
	ID3D11Buffer*		m_VertextBuffer			= nullptr;
	ID3D11Buffer*		m_IndexBuffer			= nullptr;
	ID3D11VertexShader* m_VertexShader			= nullptr;
	ID3D11InputLayout*	m_VertextInputLayout	= nullptr;
	ID3D11PixelShader*	m_PixelShader			= nullptr;
	ID3D11Buffer*		m_ConstantBuffer		= nullptr;
	

public:

	CMesh()
	{

	}

	virtual ~CMesh()
	{

	}


	HRESULT Init();

	virtual void RenderTick(float deltaTime);
	virtual void Release();
	HRESULT InitPixelShader();
	HRESULT InitVertexShader();
	HRESULT InitConstantbufer();


	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);



};

