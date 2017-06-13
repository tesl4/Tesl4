#pragma once
class CWindowsclass
{
private:
	static CWindowsclass m_Instance;

	

public:
	
	CWindowsclass(HWND _hwnd, HINSTANCE _hinst);
	virtual ~CWindowsclass();

	HRESULT InitWindow();
};

