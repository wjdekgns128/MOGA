#include "cMode.h" // 2초있으면 결과창이나옴 대충보면 다이어로그 로 버튼2개 생성, 한개누르면 게임 한개누르면 메뉴로 . 

cMode::cMode()
{
	m_pSprite				= NULL;
	m_pDialog				= NULL;
	m_pSound				= NULL;
	m_pAnimate				= NULL;
	m_pSingle				= NULL;
	m_pCursor				= NULL;

}


cMode::~cMode()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pCursor);

	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
}


HRESULT cMode::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

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
	if(m_pDialog == NULL)
	{

		m_pDialog			= new KGDialog(m_pSprite, 0, this);

		m_pDialog->AddButton(BT_DRUM, L"Dr", L"Dr_ok", L"Dr_check", L"Dr", D3DXVECTOR3(580, 250, 0),true);
		m_pDialog->AddButton(BT_JEMBE, L"Je", L"Je_ok", L"Je_check", L"Je", D3DXVECTOR3(540, 400, 0),true);
		m_pDialog->AddButton(BT_BASE, L"Ba", L"Ba_ok", L"Ba_check", L"Ba", D3DXVECTOR3(500, 550, 0),true);
		m_pDialog->AddTimeBar(TM_FADE, L"", D3DXVECTOR3(0, 0, 0), 0.4f);
		m_pDialog->AddTimeBar(TM_Next_FADE, L"", D3DXVECTOR3(0, 0, 0), 0.4f);

	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor01");
	}
	if(m_pSound == NULL)			
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"menu",  L"/res/sound/Music/MainMenuSound.wav");
	}
	mode_check				= 1;
	m_pDialog->GetTimeBar(TM_FADE)->SetDisable(false);
	m_pDialog->GetTimeBar(TM_Next_FADE)->SetDisable(true);

	m_fFadeTime = 0;
	m_fAlpha = 1;
	m_Next_fAlpha = 0;
	return S_OK;
}


HRESULT cMode::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	return S_OK;
}


void cMode::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
}


void cMode::OnDestroyDevice(void* pUserContext)
{

	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pDialog);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pCursor);

}


void cMode::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pSound->Play(L"menu", false, 0, DSBPLAY_LOOPING);
	if(!m_pDialog->GetTimeBar(TM_FADE)->GetDisable())
	{
		m_fFadeTime += fElapsedTime;
		if(m_fFadeTime > 0.01f)
		{
			m_fAlpha -= 0.05f;
			if(m_fAlpha < 0) m_fAlpha = 0;
			m_fFadeTime = 0;
		}

	}
	if(!m_pDialog->GetTimeBar(TM_Next_FADE)->GetDisable())
	{
		m_fFadeTime += fElapsedTime;
		if(m_fFadeTime > 0.01f)
		{
			m_Next_fAlpha += 0.05f;
			if(m_Next_fAlpha > 1) m_Next_fAlpha = 1;
			m_fFadeTime = 0;
		}

	}
	SAFE_ONFRAMEMOVE(m_pDialog);

}


void cMode::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;



	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"Moag",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		if(mode_check == 1)
			m_pSprite->Render(L"Dr_check",D3DXVECTOR3(620 - (mode_check * 40),100+(mode_check*150),0),D3DXCOLOR(1,1,1,1));
		else if(mode_check == 2)
			m_pSprite->Render(L"Je_check",D3DXVECTOR3(620 - (mode_check * 40),100+(mode_check*150),0),D3DXCOLOR(1,1,1,1));
		else if(mode_check == 3)
			m_pSprite->Render(L"Ba_check",D3DXVECTOR3(620 - (mode_check * 40),100+(mode_check*150),0),D3DXCOLOR(1,1,1,1));
		SAFE_ONFRAMERENDER(m_pDialog);
		SAFE_ONFRAMERENDER(m_pSingle);
		SAFE_ONFRAMERENDER(m_pCursor);

		m_pSprite->Render(L"black", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,m_fAlpha));
		m_pSprite->Render(L"black", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,m_Next_fAlpha));
		V(pd3dDevice->EndScene());
	}
}


void cMode::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pDialog);

	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_F1:
		{
			cMain()->Trans(L"menu");
			break;
		}
	case VK_UP:
		{
			mode_check -=1;
			if(mode_check < 1)
				mode_check = 3;
			break;
		}
	case VK_DOWN:
		{
			mode_check +=1;
			if(mode_check > 3)
				mode_check =1;
			break;
		}
	case VK_RETURN:
		{
			if(m_pDialog->GetTimeBar(TM_Next_FADE)->GetDisable())
			{
				m_pDialog->GetTimeBar(TM_Next_FADE)->Reset();
				SetDisable(true);
			}
			break;
		}
	}

}


void cMode::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pCursor);

	if(bButtonDown)
	{
		m_pSingle->Entry(L"mouse_effect", D3DXVECTOR3(xPos-100,yPos-60,0), true, 1); // 임펙트이다.
	}
}


LRESULT cMode::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	return uMsg;
}
void cMode::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	case BT_DRUM:
	case BT_JEMBE:
	case BT_BASE:
		m_pDialog->GetTimeBar(TM_Next_FADE)->Reset();
		mode_check = id;
		SetDisable(true);
		break;
	case TM_Next_FADE:
		switch(mode_check)
		{
		case DRUM:
			cMain()->Trans(L"choic");
			PLAYCHOICE = DRUM;
			break;
		case JEMBE:
			cMain()->Trans(L"choic");
			PLAYCHOICE = JEMBE;
			break;
		case  BASE:
			cMain()->Trans(L"choic");
			PLAYCHOICE = BASE;
			break;
		}
	}
}
void cMode::SetDisable(bool bDisable)
{
	m_pDialog->GetButton(BT_DRUM)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_JEMBE)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_BASE)->SetDisable(bDisable);
}