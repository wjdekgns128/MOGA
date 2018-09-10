#include "cBase.h"


cBase::cBase()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pSingle				= NULL;
	m_pDialog				= NULL;
	m_pDialog2				= NULL;
	m_pSound				= NULL;
	m_pCursor				= NULL;
	for(int i=0; i<EFFECT; i++)
		m_pEffect[i]		= NULL;
	m_nXCheck				= 0;
	m_nYCheck				= 0;
	Judge_Bar_X				= 815;			//노드바의 X값
	Judge_Bar_Y				= 768;		//노드바의 Y값
	Judger_rBar = KGRect(Judge_Bar_X-209.f, Judge_Bar_Y-18.5f, Judge_Bar_X+209.f, Judge_Bar_Y+18.5f); //노드바 판정바에 렉트값. 초기화


}


cBase::~cBase()
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pCursor)
	for(int i=0; i<EFFECT; i++)
		SAFE_DELETE(m_pEffect[i]);


	for(int i=0; i<m_nLayers; i++)
	{
		if(m_pBaseLoad != NULL)
		{
			for(int j=0; j<m_pBaseLoad[i].m_Number;j++)
			{
				SAFE_DELETE(m_pBaseLoad[i].m_pBaseNote[j]);
			}
			SAFE_DELETE_ARRAY(m_pBaseLoad[i].m_pBaseNote);
		}
	}
	for(int i=0;i<m_nLayers;i++)
		SAFE_DELETE_ARRAY(m_pBaseLoad);



}
void cBase::OnDestroyDevice(void* pUserContext)
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	for(int i=0; i<EFFECT; i++)
		SAFE_DELETE(m_pEffect[i]);

	for(int i=0; i<m_nLayers; i++)
	{
		if(m_pBaseLoad != NULL)
		{
			for(int j=0; j<m_pBaseLoad[i].m_Number;j++)
			{
				SAFE_DELETE(m_pBaseLoad[i].m_pBaseNote[j]);
			}
			SAFE_DELETE_ARRAY(m_pBaseLoad[i].m_pBaseNote);
		}
	}
	for(int i=0;i<m_nLayers;i++)
		SAFE_DELETE_ARRAY(m_pBaseLoad);
	

}
HRESULT cBase::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Judge.Te");
		m_pSprite->Entry(L"res/te/Instrument.Te");
		m_pSprite->Entry(L"res/te/example.te");
		m_pSprite->Entry(L"res/te/perfect.te");
		m_pSprite->Entry(L"res/te/Base_Note.te");
		m_pSprite->Entry(L"res/te/Base_Background.te");
		m_pSprite->Entry(L"res/te/CGEffect.te");
		m_pSprite->Entry(L"res/te/MPEffect.te");

	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor02");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"res/ta/teamlogo.ta");
		m_pAnimate->Entry(L"res/ta/Effect.ta");
	}
	if(m_pSingle == NULL)
	{
		m_pSingle		= new KGRenderSingle(m_pAnimate);
	}
	if(m_pDialog == NULL)
	{
		m_pDialog		= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog->AddNumber(88, L"num_", D3DXVECTOR3(50, 50, 0));
	}
	if(m_pDialog2 == NULL)
	{
		m_pDialog2		= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog2->AddNumber(89, L"num_", D3DXVECTOR3(150, 50, 0));
	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"swagga",  L"/res/sound/Music/swagga.wav");
		m_pSound->Entry(L"just",  L"/res/sound/Music/just.wav");

	}
	if(MUSIC == JUST)
	{
		Base_Music_Load(L"BASEJUST.txt");
	}
	else if(MUSIC == SWAGGA)
	{
		Base_Music_Load(L"BASESWAGGA.txt");
	}
	//else if(MUSIC == PRACTIC) // 나중에 튜토리얼
	//{
	//}
	if(MUSIC == SWAGGA)				//뮤직상태가 스웨거라면
	{
		m_pSound->Play(L"swagga", false, 0, 0); //스웨거 재생
		m_pSound->Stop(L"just");
	}
	if(MUSIC == JUST){
		m_pSound->Play(L"just", false, 0, 0);
		m_pSound->Stop(L"swagga");
	}
	for(int i=0; i<EFFECT; i++)
		m_pEffect[i]		= new KGRenderSingle(m_pAnimate);

	//m_pEffect[EFFECT_PERFECT]->Entry(L"Perfect", D3DXVECTOR3(530.f, -45.f, 0), true, 2);
	//m_pEffect[EFFECT_COOL]->Entry(L"Cool", D3DXVECTOR3(730.f, -45.f, 0), true, 2);
	//m_pEffect[EFFECT_GOOD]->Entry(L"Good", D3DXVECTOR3(730.f, -45.f, 0), true, 2);
	//m_pEffect[EFFECT_MISS]->Entry(L"Miss", D3DXVECTOR3(730.f, -45.f, 0), true, 2);
	

	/*if(MUSCI == PRACTICE){ // 나중에
	}*/
	return S_OK;
}


HRESULT cBase::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog2);
	return S_OK;
}


void cBase::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pDialog2);
}




void cBase::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	
	SAFE_ONFRAMEMOVE(m_pDialog);
	SAFE_ONFRAMEMOVE(m_pDialog2);
	m_pDialog->GetNumber(88)->SetNumber(m_nXCheck);
	m_pDialog2->GetNumber(89)->SetNumber(m_nYCheck);
	for(int i=0; i<m_nLayers; i++)
	{
		for(int j=0; j<m_pBaseLoad[i].m_Number; j++)
		{
			if(m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Perfect)
			{
				if(m_pEffect[EFFECT_PERFECT]->empty())
				{
					m_pEffect[EFFECT_PERFECT]->Entry(L"Perfect", D3DXVECTOR3(530.f, -45.f, 0), true, 1);
					m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Perfect = false;
					break;
				}
			}
			else if(m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Cool)
			{
				if(m_pEffect[EFFECT_GOOD]->empty())
				{
					m_pEffect[EFFECT_GOOD]->Entry(L"Good", D3DXVECTOR3(730.f, -45.f, 0), true, 1);
					m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Cool = false;
					break;
				}
			}
			else if(m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Miss)
			{
				if(m_pEffect[EFFECT_MISS]->empty())
				{
					m_pEffect[EFFECT_MISS]->Entry(L"Miss", D3DXVECTOR3(730.f, -45.f, 0), true, 1);
					m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Miss = false;
					break;
				}
			}
		}
	}

	for(int i=0; i<m_nLayers; i++)
		m_pBaseLoad[i].OnFrameMove(pd3dDevice, fTime, fElapsedTime, pUserContext);
	//SAFE_ONFRAMEMOVE(m_pSingle);
}


void cBase::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;
	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{

		m_pSprite->Render(L"Base_Back", D3DXVECTOR3(0, 0, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
		for(int i=0; i<m_nLayers; i++)
			m_pBaseLoad[i].OnFrameRender(pd3dDevice, fTime, fElapsedTime, pUserContext);
		//SAFE_ONFRAMERENDER(m_pBaseLoad);
		SAFE_ONFRAMERENDER(m_pDialog);
		SAFE_ONFRAMERENDER(m_pDialog2);
		SAFE_ONFRAMERENDER(m_pCursor);

		for(int i=0; i<EFFECT; i++)
			SAFE_ONFRAMERENDER(m_pEffect[i]);
		V(pd3dDevice->EndScene());
	}




}


void cBase::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pDialog);
	SAFE_ONKEYBOARD(m_pDialog2);
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case 'D':
		KeySettingCheckPark(0);
		break;
	case 'F':
		KeySettingCheckPark(1);
		break;
	case 'J':
		KeySettingCheckPark(2);
		break;
	case 'K':
		KeySettingCheckPark(3);
		break;
	case VK_SPACE:
		KeySettingCheckPark(4);
		break;
	case VK_UP:
		cMain()->Trans(L"menu");
		break;

	}
}


void cBase::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{

	m_nXCheck = xPos;
	m_nYCheck = yPos;
	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pDialog2);
	SAFE_ONMOUSE(m_pCursor);

}


LRESULT cBase::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}

void cBase::Base_Music_Load(const WCHAR *pFileName)
{
	WCHAR					FileNameBuffer[256];
	WCHAR					m_cLine[100];
	WCHAR					m_cString[100];

	KGFindDXSDKMediaFileCch(FileNameBuffer, 256, pFileName);

	FILE*	fp = NULL;

#pragma warning ( disable : 4996)

	fp	= _wfopen(FileNameBuffer, L"rt");

	if(fp == NULL)
	{
		KGOutputDebugString(L"맵 로딩 실패\n");
		return;
	}

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[NOTEINFO]") == 0)
			DecodeBase(fp);
	}
	fclose(fp);

}
void cBase::DecodeBase(FILE* fp)
{
	WCHAR cLine[255];
	WCHAR ctemp[255];
	WCHAR strData[255];

	int nLayers = 0;

	memset(cLine, 0, sizeof(cLine));
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d",  &nLayers);

	m_pBaseLoad = new cBaseLoad[nLayers];

	if(!m_pBaseLoad)
		return;

	m_nLayers = nLayers;

	for(int i=0; i<nLayers; i++)
	{
		int NoteNumber;


		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf(cLine, L"%s", m_pBaseLoad[i].m_LoadName);

		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf(cLine, L"%d", &NoteNumber);

		cMain()->g_test = NoteNumber;
		m_pBaseLoad[i].m_Number = NoteNumber;

		m_pBaseLoad[i].m_pBaseNote = new cBaseNote*[NoteNumber];

		for(int j=0; j<NoteNumber; j++)
		{
			int	x;
			int y;
			fgetws(strData, 100, fp) ;
			swscanf(strData, L"%d %d", &x, &y) ;
			m_pBaseLoad[i].m_pBaseNote[j] = NULL;
			m_pBaseLoad[i].m_pBaseNote[j] = new cBaseNote( m_pAnimate, i, x, y );
		}
	}
}

void cBase::KeySettingCheckPark(int Key)
{
	int m_nKey				= Key;

	for(int i=0; i<m_nLayers; i++)
	{
		for(int j=0; j<m_pBaseLoad[i].m_Number; j++)
		{
			if(Judger_rBar.isOverlap(m_pBaseLoad[i].m_pBaseNote[j]->Judger_rNode))		//노드가 판정부분에 충돌이 되어있다면
			{
				m_pBaseLoad[i].m_pBaseNote[j]->m_bCollusionCheck = true;
			}
			if(m_pBaseLoad[i].m_pBaseNote[j]->m_bCollusionCheck)
			{
				if(!m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Dead)	
				{
					if(m_pBaseLoad[i].m_pBaseNote[j]->m_nNoteKind == m_nKey)
						m_pBaseLoad[i].m_pBaseNote[j]->KeyCheck();
				}
			}
		}
	}
}
