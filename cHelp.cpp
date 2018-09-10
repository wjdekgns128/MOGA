#include "cResult.h"

cHelp::cHelp()
{
	m_pSprite				= NULL;
	m_vPos					= D3DXVECTOR3(200,200,0);
	Help_Check				= 0;
}


cHelp::~cHelp()
{
	SAFE_DELETE(m_pSprite);

}


HRESULT cHelp::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Menu_Check.Te");
	}

	return S_OK;
}


HRESULT cHelp::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cHelp::OnLostDevice(void* pUserContext)
{
}


void cHelp::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
}


void cHelp::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cHelp::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		if(Help_Check == 0)
		m_pSprite->Render(L"St_check",m_vPos,D3DXCOLOR(1,1,1,1));
		else if(Help_Check ==1)
		m_pSprite->Render(L"Qu_check",m_vPos,D3DXCOLOR(1,1,1,1));
		else if(Help_Check == 2)
		m_pSprite->Render(L"Cr_check",m_vPos,D3DXCOLOR(1,1,1,1));
		V(pd3dDevice->EndScene());
	}
}


void cHelp::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_RIGHT:
		{
			Help_Check++;
			if(Help_Check > 2)
				Help_Check = 0;
			break;
		}
	case VK_LEFT:
		{
			Help_Check--;
			if(Help_Check < 0)
				Help_Check = 2;
			break;
		}
	}

}


void cHelp::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
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


LRESULT cHelp::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}
	