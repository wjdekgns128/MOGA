#include "cOpenning.h"

cOpenning::cOpenning()
{
	m_pSprite				= NULL;

}


cOpenning::~cOpenning()
{
	SAFE_DELETE(m_pSprite);

}


HRESULT cOpenning::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		//m_pSprite->Entry(L"res/te/Ani.Te");
	}

	return S_OK;
}


HRESULT cOpenning::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cOpenning::OnLostDevice(void* pUserContext)
{
}


void cOpenning::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
}


void cOpenning::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cOpenning::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 255), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		TextOut(GetDC(cMain()->GethWnd()), 0, 0, L"1=logo, 2=openning 3=menu 4=game 5=result", 41);
		TextOut(GetDC(cMain()->GethWnd()), 0, 20, L"OPENNING SCENE", 14);

		V(pd3dDevice->EndScene());
	}
}


void cOpenning::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
#if defined(DEBUE) || defined(_DEBUG)
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case '1':
		cMain()->Trans(L"logo");
		break;
	case '2':
		cMain()->Trans(L"openning");
		break;
	case '3':
		cMain()->Trans(L"menu");
		break;
	case '4':
		cMain()->Trans(L"game");
		break;
	case '5':
		cMain()->Trans(L"result");
		break;

	}
#endif
}


void cOpenning::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	if(bButtonDown)
	{
		if(bLeftButtonDown)
		{

		}
		if(bRightButtonDown)
		{

		}
	}


}


LRESULT cOpenning::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}
	