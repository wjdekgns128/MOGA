#include "cMusicChoice.h"
cMusicChoice::cMusicChoice()
{
	m_pSprite				= NULL;
	m_pSound				= NULL;
	m_vPos					= D3DXVECTOR3(300, 200, 0);
	m_pCursor				= NULL;

}

cMusicChoice::~cMusicChoice()
{
	SAFE_DELETE(m_pSprite);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pCursor);


}


HRESULT cMusicChoice::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	//////////////////////////////////////////////////////////////////////////
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/MusicChoice.Te");
		m_pSprite->Entry(L"res/te/level.Te");
		m_pSprite->Entry(L"res/te/example.te");


	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"swagga_sample",  L"/res/sound/Music/swagga_sample.wav");
		m_pSound->Entry(L"just_sample",  L"/res/sound/Music/just_sample.wav");
		m_pSound->Entry(L"practice_sample", L"/res/sound/Music/practice_sample.wav");

		//m_pSound->isPlay(L"swagga");
	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor01");
	}
	m_MusicState			= 0;
	m_Icheck				= 1; // 0 쉬움 1보통 2 어려움
	m_SelectCD				= 0;

	return S_OK;
}


HRESULT cMusicChoice::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	return S_OK;
}


void cMusicChoice::OnLostDevice(void* pUserContext)
{
}


void cMusicChoice::OnDestroyDevice(void* pUserContext)
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pCursor);

}


void cMusicChoice::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_Icheck == 0)
		LEVEL = EASY;
	if(m_Icheck == 1)
		LEVEL = NORMAL;
	if(m_Icheck == 2)
		LEVEL = HARD;
	if(m_SelectCD == 0)
	{
		m_pSound->Play(L"just_sample", false, 0, DSBPLAY_LOOPING);
		m_pSound->Stop(L"swagga_sample");
		m_pSound->Stop(L"practice_sample");

		//m_pSound->Stop(L"swagga"); // 튜토리얼때
	}
	if(m_SelectCD == 1)
	{
		m_pSound->Play(L"swagga_sample", false, 0, DSBPLAY_LOOPING);
		m_pSound->Stop(L"just_sample");
		m_pSound->Stop(L"practice_sample");

		//m_pSound->Stop(L"swagga"); // 튜토리얼때
	}
	if(m_SelectCD == 2) // 튜토리얼 
	{
		m_pSound->Play(L"practice_sample", false, 0, DSBPLAY_LOOPING);
		m_pSound->Stop(L"just_sample");
		m_pSound->Stop(L"swagga_sample");
		//m_pSound->Stop(L"swagga"); // 튜토리얼때
	}

}


void cMusicChoice::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{

		m_pSprite->Render(L"MusicChoice", m_vPos, D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"JustCD",D3DXVECTOR3(m_vPos.x+400-(m_SelectCD * 100 *2),m_vPos.y-400+(m_SelectCD*100*2), 0), D3DXCOLOR(1,1,1,1)); // 튜토리얼 그림
		//m_pSprite->Render(L"JustCD",D3DXVECTOR3(m_vPos.x+400-(m_SelectCD * 100 * 2),m_vPos.y-400+(m_SelectCD*100 *2), 0), D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"SwaggaCD",D3DXVECTOR3(m_vPos.x+200-(m_SelectCD * 100 *2),m_vPos.y-200+(m_SelectCD*100 * 2), 0), D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"JustCD",D3DXVECTOR3(m_vPos.x-(m_SelectCD * 100 *2),m_vPos.y+(m_SelectCD*100*2), 0), D3DXCOLOR(1,1,1,1));
		if(LEVEL == EASY)
			m_pSprite->Render(L"0",D3DXVECTOR3(500,500, 500), D3DXCOLOR(1,1,1,1));
		if(LEVEL == NORMAL)
			m_pSprite->Render(L"1",D3DXVECTOR3(500,500,500), D3DXCOLOR(1,1,1,1));
		if(LEVEL == HARD)
			m_pSprite->Render(L"2",D3DXVECTOR3(500,500,500), D3DXCOLOR(1,1,1,1));
		SAFE_ONFRAMERENDER(m_pCursor);

		V(pd3dDevice->EndScene());
	}
}


void cMusicChoice::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_UP:
		{
			m_SelectCD +=1;
			if(m_SelectCD > 2)
				m_SelectCD = 0;

			break;
		}
	case VK_DOWN:
		{
			m_SelectCD -=1;
			if(m_SelectCD < 0)
				m_SelectCD = 2;
			break;
		}
	case VK_RIGHT:
		{
			m_Icheck +=1;
			if(m_Icheck > 2)
				m_Icheck = 0;
			break;
		}
	case VK_LEFT:
		{
			m_Icheck -=1;
			if(m_Icheck < 0)
				m_Icheck = 2;
			break;
		}
	case VK_RETURN:
		Select(m_SelectCD);
		break;
	case VK_F1:
		cMain()->Trans(L"mode");
	}


}


void cMusicChoice::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
						   bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	m_vMPos.x = xPos;
	m_vMPos.y = yPos;
	SAFE_ONMOUSE(m_pCursor);
	if(nMouseWheelDelta > 0)
	{
		m_SelectCD +=1;
		if(m_SelectCD)
			m_SelectCD;
		if(m_SelectCD > 2)
			m_SelectCD = 0;


	}
	if(nMouseWheelDelta < 0)
	{
		m_SelectCD -=1;
		if(m_SelectCD)
			m_SelectCD;
		if(m_SelectCD < 0)
			m_SelectCD = 2;
	}
	if(bButtonDown)
	{
		if(bLeftButtonDown)
		{
			if(xPos > 300 && xPos < 610 &&  yPos > 200 && yPos < 480)
			{
				Select(m_SelectCD);
			}
		}
		if(bRightButtonDown)
		{

		}
	}


}


LRESULT cMusicChoice::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}

void cMusicChoice::OnEvent(UINT id, int xPos, int yPos)
{

}

void cMusicChoice::Select(int m_SelectCD)
{
	switch(m_SelectCD)
	{
	case 0:
		MUSIC = JUST;				
		if(PLAYCHOICE == DRUM)		
			cMain()->Trans(L"drum");
		if(PLAYCHOICE == JEMBE)
			cMain()->Trans(L"jembe");
		if(PLAYCHOICE == BASE)
			cMain()->Trans(L"base");
		break;
	case 1:
		MUSIC = SWAGGA;			
		if(PLAYCHOICE == DRUM)		
			cMain()->Trans(L"drum");
		if(PLAYCHOICE == JEMBE)
			cMain()->Trans(L"jembe");
		if(PLAYCHOICE == BASE)
			cMain()->Trans(L"base");
		break;
	case 2:	    // 연습노래
		MUSIC =PRACTICE;
		if(PLAYCHOICE == DRUM)		
			cMain()->Trans(L"drum"); 
		if(PLAYCHOICE == JEMBE)
			cMain()->Trans(L"jembe");
		if(PLAYCHOICE == BASE)
			cMain()->Trans(L"base"); 
		break;
	}	
}