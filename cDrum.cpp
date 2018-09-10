#include "cDrum.h"

cDrum::cDrum()
{
	m_pSprite				= NULL;
	m_pSound				= NULL;
	m_pAnimate				= NULL;
	m_pDialog				= NULL;
	m_pDialog2				= NULL;
	m_pCombo = NULL;
	m_nCombo				= 0;
	m_nDrumState			= -1;
	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		m_pSingle[i] = NULL;
	}
	
	m_Node_Number			= 0;
	m_nXCheck				= 0;
	m_ComboTime				= 0.f;
	m_nYCheck				= 0;
	Judge_Bar_X				= 212.f+601.f;		//노드바의 X값
	Judge_Bar_Y				= 100.f;			//노드바의 Y값
	Judger_rBar = KGRect(Judge_Bar_X-62.f, Judge_Bar_Y-62.f, Judge_Bar_X+62.f, Judge_Bar_Y+62.f); //노드바 판정바에 렉트값. 초기화
}


cDrum::~cDrum()
{

	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pCombo);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		SAFE_DELETE(m_pSingle[i]);
	}
	if(m_pDrumNote != NULL)
	{
		for(int i= 0;i<m_Node_Number;i++)
		{
			SAFE_DELETE(m_pDrumNote[i]);
		}
		for(int i=0;i<m_Node_Number;i++)
			SAFE_DELETE_ARRAY(m_pDrumNote);
	}
	//컨트롤 쉬프트 f9
}	

void cDrum::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pCombo);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		SAFE_DELETE(m_pSingle[i]);
	}
	
	if(m_pDrumNote != NULL)
	{
		for(int i= 0;i<m_Node_Number;i++)
		{
			SAFE_DELETE(m_pDrumNote[i]);
		}
		for(int i=0;i<m_Node_Number;i++)
			SAFE_DELETE_ARRAY(m_pDrumNote);
	}
}
HRESULT cDrum::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Judge.Te");				// 드럼 그림은 그림파일안에있으니 알아서하시길.
		m_pSprite->Entry(L"res/te/Instrument.Te");
		m_pSprite->Entry(L"res/te/example.te");
		m_pSprite->Entry(L"res/te/CGEffect.te");
		m_pSprite->Entry(L"res/te/MPEffect.te");
		m_pSprite->Entry(L"res/te/drum_click.te");
		m_pSprite->Entry(L"res/te/Drum_Click.te");
		m_pSprite->Entry(L"res/te/Combo.te");
		m_pSprite->Entry(L"res/te/ComboNumber.te");
		m_pSprite->Entry(L"res/te/Notes.te");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"res/ta/Effect.ta");
		m_pAnimate->Entry(L"res/ta/Drum_Click.ta");
		m_pAnimate->Entry(L"res/ta/Combo.ta");
		


	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"swagga",  L"/res/sound/Music/swagga.wav");
		m_pSound->Entry(L"just",  L"/res/sound/Music/just.wav");

		m_pSound->Entry(L"Kick",  L"/res/sound/Drum/Kick.wav");
		m_pSound->Entry(L"Hiat",  L"/res/sound/Drum/Hiat.wav");
		m_pSound->Entry(L"Snear",  L"/res/sound/Drum/Snear.wav");

	}
	if(m_pDialog == NULL)
	{
		m_pDialog			= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog->AddNumber(56, L"Combonum_", D3DXVECTOR3(380.f, 145.f, 0));
	}
	if(m_pDialog2 == NULL)
	{
		m_pDialog2			= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog2->AddNumber(57, L"Combonum_", D3DXVECTOR3(50, 200, 0));
	}
	m_pCombo						= new KGRenderSingle(m_pAnimate);
	if(MUSIC == SWAGGA)				//뮤직상태가 스웨거라면
	{
		Load_Node(L"DRUMSWAGGA.txt");
		m_pSound->Play(L"swagga", false, 0, 0); //스웨거 재생
		m_pSound->Stop(L"just");

	}
	if(MUSIC == JUST){
		Load_Node(L"DRUMJUST.txt");
		m_pSound->Play(L"just", false, 0, 0);
		m_pSound->Stop(L"swagga");

	}//351 316
	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		if(m_pSingle[i] == NULL)
		{
			m_pSingle[i]			= new KGRenderSingle(m_pAnimate);
		}
	}
	

	SCORE					= 0 ;
	NOWNODE					= 0 ;
	MAXNODE					= m_Node_Number;
	MAXPERFECT				= 0 ;
	MAXGOOD					= 0 ;
	MAXMISS					= 0 ;
	MAXCOMBO				= 0 ;
	m_dwChage_time			= 0;
	
	



	return S_OK;
}


HRESULT cDrum::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog2);
	return S_OK;
}


void cDrum::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pDialog2);
}




void cDrum::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	Judger_rBar = KGRect(Judge_Bar_X-62.f, Judge_Bar_Y-62.f, Judge_Bar_X+62.f, Judge_Bar_Y+62.f); //노드바 판정바에 렉트값.

	//m_pDialog->GetNumber(56)->SetNumber(DRUMCOMBO);
	m_ComboTime += fElapsedTime;

	//--------------------------------------------------------------
	m_nCCheck = F_NoteNearCheck();//제일 가까운거를 체크하는 함수
	//---------------------------------------------------------------


	SAFE_ONFRAMEMOVE(m_pDialog);
	SAFE_ONFRAMEMOVE(m_pDialog2);
	

	m_pDialog->GetNumber(56)->SetNumber(m_nXCheck);
	m_pDialog2->GetNumber(57)->SetNumber(m_nYCheck);
	for(int i=0; i<m_Node_Number; i++)
	{
	if(m_pDrumNote[i]->m_bComboRenderCheck == true)
	{
		
			m_pDrumNote[i]->m_bComboRenderCheck = true;

		m_pDialog->SetVisible(true);
		if(m_ComboTime >= 2.f)
		{
			m_pDialog->SetVisible(false);
			m_ComboTime = 0;
		}
	}
	}
	for(int i=0; i<m_Node_Number; i++)
	{
		if(m_pDrumNote[i]->m_Node_x > 0)
		{
			m_pDrumNote[i]->m_bObject = true;
		}
		SAFE_ONFRAMEMOVE(m_pDrumNote[i]);

		if(m_pDrumNote[i]->m_bComboBefore == true)
		{
			m_pCombo->Entry(L"Combo", D3DXVECTOR3(0,0,0), true, 2);
		}

	}


	
	if(NOWNODE == MAXNODE)
	{
		if(m_dwChage_time == 0)
			m_dwChage_time = GetTickCount();
		else if(GetTickCount() - m_dwChage_time > 3000)
		{
			m_dwChage_time	= 0;
			cMain()->Trans(L"score");
		}
	}
}


void cDrum::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 111, 111, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"Drum", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 1, 1, 1));//788
		m_pSprite->Render(L"Drum_Bar", D3DXVECTOR3((float)0, (float)100, (float)0), D3DXCOLOR(1, 1, 1, AIPHABAR));//판정줄은 이곳에 출력
		
		SAFE_ONFRAMERENDER(m_pDialog);
		SAFE_ONFRAMERENDER(m_pDialog2);

	

		for(int i=0; i<m_Node_Number; i++)
		{
			if(m_pDrumNote[i]->m_Node_x > -1 && m_pDrumNote[i]->m_Node_x < 1400)
				SAFE_ONFRAMERENDER(m_pDrumNote[i]);
			if(m_pDrumNote[i]->m_bComboRenderCheck == true)
				SAFE_ONFRAMERENDER(m_pCombo);
			if(m_pDrumNote[i]->m_bComboBefore)
			{
				SAFE_ONFRAMERENDER(m_pCombo);
				m_pDrumNote[i]->m_bComboBefore = false;
			}
		}
		if(m_nDrumState != -1)
		{
			SAFE_ONFRAMERENDER(m_pSingle[m_nDrumState]);
		}

		
		V(pd3dDevice->EndScene());
	}
}


void cDrum::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pDialog);
	SAFE_ONKEYBOARD(m_pDialog2);

	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_SPACE:
		cMain()->Trans(L"menu");
		break;
	case '0':
		NumberSettingCheckPark(0);
		break;
	case '1':
		NumberSettingCheckPark(1);
		break;
	case '2':
		NumberSettingCheckPark(2);
		break;
	case '3':
		NumberSettingCheckPark(3);
		break;
	case '4':
		NumberSettingCheckPark(4);
		break;
	case '5':
		NumberSettingCheckPark(5);
		break;
	case '6':
		NumberSettingCheckPark(6);
		break;
	case '7':
		NumberSettingCheckPark(7);
		break;
	case '8':
		NumberSettingCheckPark(8);
		break;
	case '9':
		NumberSettingCheckPark(9);
		break;
	case 'S':
		m_nDrumState = 1;
		m_pSingle[1]->Entry(L"Drum_S", D3DXVECTOR3(327, 500, 0), true, 1);
		m_pSound->Play(L"Kick");
		KeySettingCheckPark(22, 1);
		break;
	case 'D':
		m_nDrumState = 0;
		m_pSingle[0]->Entry(L"Drum_D", D3DXVECTOR3(423, 484, 0), true, 1);
		m_pSound->Play(L"Hiat");
		KeySettingCheckPark(22, 2);
		break;
	case 'F':
		m_nDrumState = 2;
		m_pSingle[2]->Entry(L"Drum_F", D3DXVECTOR3(484, 370, 0), true, 1);
		m_pSound->Play(L"Snear");
		KeySettingCheckPark(22, 3);
		break;
	case 'J':
		m_nDrumState = 3;
		m_pSingle[3]->Entry(L"Drum_J", D3DXVECTOR3(534, 511, 0), true, 1);
		m_pSound->Play(L"Kick");
		KeySettingCheckPark(22, 4);
		break;
	case 'K':
		m_nDrumState = 4;
		m_pSingle[4]->Entry(L"Drum_K", D3DXVECTOR3(601, 371, 0), true, 1);
		m_pSound->Play(L"Hiat");
		KeySettingCheckPark(22, 5);
		break;
	case 'L':
		m_nDrumState = 1;
		m_pSingle[1]->Entry(L"Drum_L", D3DXVECTOR3(740, 540, 0), true, 1);
		m_pSound->Play(L"Snear");
		KeySettingCheckPark(22, 6);
		break;
	default:
		break;


	}

}


void cDrum::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{

	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pDialog2);
	m_nXCheck = xPos;
	m_nYCheck = yPos;
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


LRESULT cDrum::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}

void cDrum::Load_Node(const WCHAR *pFileName)
{
	FILE*				stream;
	WCHAR				strData[100];
	WCHAR				temp[100];

	stream				= _wfopen(pFileName, L"rt");

	if(stream == NULL)
		return;

	if(stream)
	{
		while( !feof(stream) )						//파일이 끝날때까지
		{
			fgetws(strData, 100, stream);			//stream을 읽어 strData에 집어넣음.
			swscanf(strData, L"%s", temp);			//strData를 temp에 집어넣음.

			if(wcscmp(L"[MUSIC]", temp) == 0)		//temp와 문자의 수를 비교 
			{
				Decode_Node(stream);
				break;
			}

		}
	}

}
void cDrum::Decode_Node(FILE *stream)
{
	SRANDOM();
	WCHAR					strData[100];

	int x					= 0;
	int y					= 0;
	int NumberCheck			= 0;
	int KeyCheck			= 0;
	if(fgetws(strData, 100, stream))
	{
		swscanf(strData, L"%d", &m_Node_Counter) ;
		m_Node_Number = m_Node_Counter;

		m_pDrumNote = new cDrumNote*[m_Node_Number];

		for(int i = 0 ; i < m_Node_Number ; i++ )
		{

			m_pDrumNote[i] = NULL;
			fgetws(strData, 100, stream) ;

			swscanf(strData, L"%d %d %d %d", &x, &y, &NumberCheck, &KeyCheck) ;
			m_pDrumNote[i] = new cDrumNote( m_pAnimate, m_pSound, i, x, 144, RANDOM(0, 9), RANDOM(0, 9), NumberCheck, KeyCheck);
			//	m_pDrumNote[i]->SetDisable(true);
		}
		fclose(stream);
	}

}
int cDrum::F_NoteNearCheck()
{
	int temp = -9999;
	int	check = -1;
	for(int i=0; i<m_Node_Number; i++)
	{	
		if(!m_pDrumNote[i]->m_Judger_Node_Dead)
		{
			if(m_pDrumNote[i]->Judge_Bar_X > temp)//910 940 855 1012
			{
				if(Judger_rBar.isOverlap(m_pDrumNote[i]->Judger_rNode))
				{
					if(m_pDrumNote[i]->Judge_Bar_X > 910 || m_pDrumNote[i]->Judge_Bar_X < 915)
					{
						temp = m_pDrumNote[i]->Judge_Bar_X;
						check = i;
					}
				}
			}

		}

	}
	if(check != -1)
	{
		m_pDrumNote[check]->m_bCollusionCheck = true;
	}
	return check;
}

void cDrum::KeySettingCheckPark(int Number = 0, int Key = 0)
{
	int m_nNumber			= Number;
	int m_nKey				= Key;

	for(int i=0; i<m_Node_Number; i++)
	{
		m_pDrumNote[i]->m_bComboRenderCheck = true;
		if(m_pDrumNote[i]->m_bNumberCheck == 0)
		{
			if(m_pDrumNote[i]->m_bCollusionCheck)
			{
				if(!m_pDrumNote[i]->m_Judger_Node_Dead)	
				{
					if(m_pDrumNote[i]->m_nKeyCheck == m_nKey)
						m_pDrumNote[i]->Judge_Funtion(m_nNumber);
				}
			}
		}
	}
}


void cDrum::NumberSettingCheckPark(int Number = 0)
{
	int m_nNumber			= Number;

	for(int i=0; i<m_Node_Number; i++)
	{
		m_pDrumNote[i]->m_bComboRenderCheck = true;
		if(m_pDrumNote[i]->m_bNumberCheck == 1)	
		{
			if(m_pDrumNote[i]->m_nKeyCheck == 0)
			{
				if(!m_pDrumNote[i]->m_Judger_Node_Dead)
				{
					m_pDrumNote[i]->Judge_Funtion(m_nNumber);
				}
			}
		}
	}
}