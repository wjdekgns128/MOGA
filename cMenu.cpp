#include "cMenu.h"

cMenu::cMenu()
{
	m_pSprite				= NULL;
	m_pDialog				= NULL;
	m_pSound				= NULL;
	m_pCursor				= NULL;
	m_pAnimate				= NULL;
	m_pSingle				= NULL;
}
cMenu::~cMenu()
{
	SAFE_DELETE(m_pSprite);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);

}
HRESULT cMenu::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"menu", L"/res/sound/Music/MainMenuSound.wav");
	}
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Menu.Te");
		m_pSprite->Entry(L"res/te/Menu_Check.Te");
		m_pSprite->Entry(L"res/te/fade.Te");
		m_pSprite->Entry(L"res/te/mouse_effect.te"); 
		m_pSprite->Entry(L"res/te/mouse_effect2.te");
		m_pSprite->Entry(L"res/te/example.te");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate = new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"res/ta/mouse_effect.ta");
	}
	if(m_pSingle == NULL)
	{
		m_pSingle = new KGRenderSingle(m_pAnimate);
	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor01");
	}
	if(m_pDialog == NULL)
	{
		m_pDialog			= new KGDialog(m_pSprite, 0, this);
		m_pDialog->AddButton(BT_GAME, L"St", L"St_ok", L"St_check", L"St", D3DXVECTOR3(580, 240, 0),true);
		m_pDialog->AddButton(BT_HELP, L"He", L"He_ok", L"He_check", L"He", D3DXVECTOR3(540, 350, 0),true);
		m_pDialog->AddButton(BT_CREATE, L"Cr", L"Cr_ok", L"Cr_check",L"Cr", D3DXVECTOR3(500, 460, 0),true);
		m_pDialog->AddButton(BT_QUIT, L"Qu", L"Qu_ok", L"Qu_check", L"Qu", D3DXVECTOR3(460, 570, 0),true);
		m_pDialog->AddTimeBar(TM_FADE, L"", D3DXVECTOR3(0, 0, 0), 0.4f);

	}

	m_pDialog->GetTimeBar(TM_FADE)->SetDisable(true);
	m_fFadeTime = 0;
	m_fAlpha = 0;
	menu_check	= 1;
	/*m_pDialog->GetButton(0)->SetSound(L"bt1", L"bt2");
	m_pDialog->GetButton(1)->SetSound(L"bt3", L"bt4");*/
	return S_OK;
}


HRESULT cMenu::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	return S_OK;
}


void cMenu::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
}
void cMenu::OnDestroyDevice(void* pUserContext)
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
}


void cMenu::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pSound->Play(L"menu", false, 0, DSBPLAY_LOOPING);
	SAFE_ONFRAMEMOVE(m_pDialog);
	m_vPos			= D3DXVECTOR3(620-(menu_check*40),130+(menu_check*110),0);

	if(!m_pDialog->GetTimeBar(TM_FADE)->GetDisable())
	{
		m_fFadeTime += fElapsedTime;
		if(m_fFadeTime > 0.01f)
		{
			m_fAlpha += 0.05f;
			if(m_fAlpha > 1) m_fAlpha = 1;
			m_fFadeTime = 0;
		}

	}
}


void cMenu::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255,255), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"Moag",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		if(menu_check == 1)
			m_pSprite->Render(L"St_check",m_vPos,D3DXCOLOR(1,1,1,1));
		else if(menu_check == 2)
			m_pSprite->Render(L"He_check",m_vPos,D3DXCOLOR(1,1,1,1));
		else if(menu_check ==3)
			m_pSprite->Render(L"Cr_check",m_vPos,D3DXCOLOR(1,1,1,1));
		else if(menu_check == 4)
			m_pSprite->Render(L"Qu_check",m_vPos,D3DXCOLOR(1,1,1,1));
		SAFE_ONFRAMERENDER(m_pDialog);
		SAFE_ONFRAMERENDER(m_pCursor);
		SAFE_ONFRAMERENDER(m_pSingle);
		m_pSprite->Render(L"black", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,m_fAlpha));
		V(pd3dDevice->EndScene());
	}
}


void cMenu::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pDialog);

	if(!bKeyDown) return;

	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_UP:
		{
			if(!m_pDialog->GetTimeBar(TM_FADE)->GetDisable()) return;
			menu_check -=1;
			if(menu_check < 1)
				menu_check = 4;
			break;
		}
	case VK_DOWN:
		{
			if(!m_pDialog->GetTimeBar(TM_FADE)->GetDisable()) return;
			menu_check +=1;
			if(menu_check > 4)
				menu_check = 1;
			break;
		}
	case VK_RETURN:
		{
			if(m_pDialog->GetTimeBar(TM_FADE)->GetDisable())
			{
				m_pDialog->GetTimeBar(TM_FADE)->Reset();
				SetDisable(true);
			}
			break;
		}
	}

}	


void cMenu::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{


	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pCursor);
	if(bButtonDown)
	{
		m_pSingle->Entry(L"mouse_effect", D3DXVECTOR3(xPos-100,yPos-60,0), true, 1); // 임펙트이다.
	}
}


LRESULT cMenu::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	return uMsg;
}

void cMenu::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	case BT_GAME:
	case BT_HELP:
	case BT_CREATE:
	case BT_QUIT:
		m_pDialog->GetTimeBar(TM_FADE)->Reset();
		menu_check = id;
		SetDisable(true);
		break;
	case TM_FADE:
		switch(menu_check)
		{
		case GAME:		
			cMain()->Trans(L"mode");
			break;
		case HELP:
			cMain()->Trans(L"help");
			break;
		case CREATE:
			cMain()->Trans(L"mode");
			break;
		case QUIT:
			cMain()->CloseWindow();
			break;
		}
	}
}

void cMenu::SetDisable(bool bDisable)
{
	m_pDialog->GetButton(BT_GAME)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_HELP)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_CREATE)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_QUIT)->SetDisable(bDisable);
}
