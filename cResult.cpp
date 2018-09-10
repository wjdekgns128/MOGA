#include "cResult.h"

cResult::cResult()
{
	m_pSprite				= NULL;

}


cResult::~cResult()
{
	SAFE_DELETE(m_pSprite);

}


HRESULT cResult::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		//m_pSprite->Entry(L"res/te/Ani.Te");
	}

	return S_OK;
}


HRESULT cResult::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cResult::OnLostDevice(void* pUserContext)
{
}


void cResult::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
}


void cResult::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cResult::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
	
		V(pd3dDevice->EndScene());
	}
}


void cResult::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	

	}

}


void cResult::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
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


LRESULT cResult::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}
	