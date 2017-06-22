#pragma once
class CShader
{
protected:
	ID3D11VertexShader	*m_VertexShader;
	ID3D11InputLayout	*m_VertexLayout;

	ID3D11PixelShader	*m_PixelShader;

public:
	CShader();
	virtual ~CShader();

	void InitVertexShader(WCHAR* _fileName, LPCSTR _entryPoint, LPCSTR _shadermodel, 
							ID3D11VertexShader **_d3d1VertexShader, D3D11_INPUT_ELEMENT_DESC *_inputLayoutDesc, UINT _elements, ID3D11InputLayout **_inputLayout);
	void InitPixelShader(WCHAR* _fileName, LPCSTR _entryPoint, LPCSTR _shadermodel, 
							ID3D11PixelShader **_pixelShader);
	
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	
	virtual void CreateShader();
	virtual void Render();
};

