#include "cLogo.h"

cLogo::cLogo()
{
		m_pAnimate	= NULL;
		m_pSprite	= NULL;
		m_pSingle	= NULL;
		m_vPos		= D3DXVECTOR3(0,0,0);
		Menu_Time = 0.0;
}


cLogo::~cLogo()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	
}


HRESULT cLogo::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	if(m_pSprite == NULL) 
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/logo1.Te");
		m_pSprite->Entry(L"res/te/logo2.Te");
		m_pSprite->Entry(L"res/te/logo3.Te");
		m_pSprite->Entry(L"res/te/logo.Te");

		//m_pSprite->Entry(L"res/te/gamelogo1.Te");
		//m_pSprite->Entry(L"res/te/gamelogo2.Te");
		//m_pSprite->Entry(L"res/te/gamelogo3.Te");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate   = new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"res/ta/teamlogo.Ta");
	}
	if(m_pSingle == NULL)
	{
		m_pSingle = new KGRenderSingle(m_pAnimate);
		m_pSingle->Entry(L"teamlogo",m_vPos,true,1);
	}
	return S_OK;
}


HRESULT cLogo::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cLogo::OnLostDevice(void* pUserContext)
{

}
void cLogo::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);

}
void cLogo::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	if(Menu_Time == 0.0)
		Menu_Time = GetTickCount();
	else if(GetTickCount() - Menu_Time  >= 1000) 
	{
		cMain()->Trans(L"menu");
		Menu_Time = 0;
	}

}
void cLogo::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))	
	{
		m_pSprite->Render(L"Logo",D3DXVECTOR3(230,100,0),D3DXCOLOR(1,1,1,1));
		//SAFE_ONFRAMERENDER(m_pSingle);
		V(pd3dDevice->EndScene());
	}
}
void cLogo::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	
	}

}
void cLogo::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
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

LRESULT cLogo::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}