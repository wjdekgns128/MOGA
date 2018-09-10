#include "MyInclude.h"


////////////////////x, y, 넘버가 나올건지 안나올것지 true(1) = 나옴, KeyCheck

cDrumNote::cDrumNote(KGAnimate* pAnimate, KGSound* pSound, int m_Node_Counter, int x, int y, int number1, int number2, int NumberCheck, int KeyCheck)
{
	m_pAnimate				= pAnimate;
	m_pSprite				= m_pAnimate->GetSprite();
	m_pSound				= pSound;
	for(int i=0; i<EFFECT; i++)
	{
		m_pSingle[i]		= new KGRenderSingle(m_pAnimate);
	}

	m_Node_Number			= m_Node_Counter;
	m_numberBack			= number1;
	m_numberFront			= number2;
	m_nKeyCheck				= KeyCheck;
	m_bNumberCheck			= NumberCheck;
	m_Node_x				= x*2;
	m_Node_y				= y;
	AIPHABAR				= 1;
	m_NoteResult			= m_numberFront + m_numberBack;
	Judge_Bar_X				= 212+601;		//노드바의 X값
	Judge_Bar_Y				= 312;		//노드바의 Y값
	m_Judger_Node_Dead		= false;	//노드바가 false이면 살아있다. true이면 죽어있다.
	m_Judger_Node_Cool		= false;	//노드의 체크 (cool!)
	m_Judger_Node_Miss		= false;    //MissA!!
	m_Judger_Node_Perfect	= false;	//퍼펙트!
	m_AlphaCheck			= false;
	m_bSibal				= false;
	m_bCollusionCheck		= false;
	m_bComboRenderCheck		= false;
	m_bComboOneCheck		= false;
	m_bComboBefore			= false;
	m_bObject				= false;
	m_nMissBefore			= true;
	Judge_Node_X_Check		= 0;
	m_EffectState			= -1;		//이펙트 상태
	Judger_rNode = KGRect(m_Node_x-52.f, m_Node_y-52.f, m_Node_x+52.f, m_Node_y+52.f); //노드에 렉트값	 초기화

	m_pSingle[EFFECT_PERFECT]->Entry(L"Perfect", D3DXVECTOR3(530.f, -45.f, 0), true, 2);
	m_pSingle[EFFECT_COOL]->Entry(L"Cool", D3DXVECTOR3(730.f, -45.f, 0), true, 2);
	m_pSingle[EFFECT_GOOD]->Entry(L"Good", D3DXVECTOR3(730.f, -45.f, 0), true, 2);
	m_pSingle[EFFECT_MISS]->Entry(L"Miss", D3DXVECTOR3(730.f, -45.f, 0), true, 2);

}
cDrumNote::~cDrumNote()
{
	for(int i=0; i<EFFECT; i++)
		SAFE_DELETE(m_pSingle[i]);
}
void cDrumNote::SetDisable(bool bDisable)
{
	m_Disable = bDisable;
}
bool cDrumNote::GetDisable()
{
	return m_Disable;
}

void cDrumNote::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	if(!m_Disable) return;

	cDrum* pDrum = (cDrum*)cMain()->GetCurrent();

	SRANDOM();
	if(m_bNumberCheck == 1)	
	{
		if(m_numberBack+m_numberFront >= 10)		//만약 뒤숫자와 앞숫자를 더했을경우 10보다 큰경우 다시 랜덤값을 조정
		{
			m_numberBack = RANDOM(0, 9);
			m_numberFront = RANDOM(0, 9);
			m_NoteResult = m_numberBack+m_numberFront;
		}
	}

	if(!m_Judger_Node_Dead /*&& (!m_Judger_Node_Cool || !m_Judger_Node_Perfect)*/)
		m_Node_x += 5.f*2;					//노드가 움직이는 부분
	else
		m_Node_x += 0;


	Judger_rNode = KGRect(m_Node_x-32.f, m_Node_y-32.f, m_Node_x+32.f, m_Node_y+32.f); //노드에 렉트값

	if(m_Node_x >= 1100.f )							//저장한 X값이 1024보다 작으면 미스
	{
		if(m_AlphaCheck == false)
		{
			m_AlphaCheck = true;
			AIPHABAR -= 0.1;
		}
		m_Judger_Node_Miss = true;
		m_Judger_Node_Dead = true;
		m_bObject = false;
		if(m_nMissBefore == true)
		{
			m_nMissBefore = false;
			pDrum->m_nCombo = 0;
			NOWNODE++;
			MAXMISS++;
			printf("Miss : %d %d\n", NOWNODE, MAXMISS);
		}
	}

	if(m_bComboOneCheck == true)
	{
		pDrum->m_nCombo++;
		SCORE++;
		NOWNODE++;
		printf("Clcik : %d\n", NOWNODE);
		if(m_Judger_Node_Cool)
		{
			MAXGOOD++;
		}
		else if(m_Judger_Node_Perfect)
		{
			MAXPERFECT++;
		}
		m_bComboBefore	= true;
		m_bComboOneCheck = false;

	}
	if(m_Judger_Node_Cool)
	{
		m_EffectState = EFFECT_GOOD;
	}
	else if(m_Judger_Node_Miss)
	{
		m_EffectState = EFFECT_MISS;
	}
	else if(m_Judger_Node_Perfect)
	{
		m_EffectState = EFFECT_PERFECT;
	}



}
void cDrumNote::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{



	
	if(m_EffectState > -1)
		SAFE_ONFRAMERENDER(m_pSingle[m_EffectState]);


	if(!m_Judger_Node_Dead && m_Node_x)
	{
		if(m_bObject)
		{
			KeyCheckRender(m_nKeyCheck);
			GetNumber(m_numberBack, m_numberFront);
		}
	}


}
void cDrumNote::Judge_Funtion(int result)
{
	cDrum* pDrum = (cDrum*)cMain()->GetCurrent();
	AIPHABAR += 0.1;
	Judge_Node_X_Check = m_Node_x;		// 스페이스바를 누른 그순간의 X값을 저장
	if(m_bComboOneCheck == false)
		m_bComboOneCheck = true;
	if(m_NoteResult == result)
	{
		m_Judger_Node_Dead = true;				//노드를 없애고

		if(m_Judger_Node_Dead)
			m_Node_x += 0;

		if(Judge_Node_X_Check >= 815 && Judge_Node_X_Check <= 855)			//저장한 X값이 758보다 크면 쿨
		{
			m_Judger_Node_Cool = true;										//쿨 트루
			m_Judger_Node_Perfect = false;
			m_Judger_Node_Miss = false;										//쿨 트루
		}
		if(Judge_Node_X_Check > 855 && Judge_Node_X_Check <= 1012) //저장한 X값이 758보다 크고 858보다 작으면 퍼펙
		{
			m_Judger_Node_Cool = false;										//쿨 트루
			m_Judger_Node_Perfect = true;
			m_Judger_Node_Miss = false;
		}							//퍼펙 트루
	}
	if(result > 10)
	{
		m_Judger_Node_Dead = true;				//노드를 없애고

		if(m_Judger_Node_Dead)
			m_Node_x += 0;

		if(Judge_Node_X_Check >= 815 && Judge_Node_X_Check <= 855)			//저장한 X값이 758보다 크면 쿨
		{
			m_Judger_Node_Cool = true;										//쿨 트루
			m_Judger_Node_Perfect = false;
			m_Judger_Node_Miss = false;
		}
		if(Judge_Node_X_Check > 855 && Judge_Node_X_Check <= 1012) //저장한 X값이 758보다 크고 858보다 작으면 퍼펙
		{
			m_Judger_Node_Cool = false;										//쿨 트루
			m_Judger_Node_Perfect = true;
			m_Judger_Node_Miss = false;
			AIPHABAR += 0.05;
		}
	}
}

void cDrumNote::GetNumber(int number1, int number2)
{
	if(m_bNumberCheck == 1)
	{
		switch(m_numberBack)
		{
		case 0:
			m_pSprite->Render(L"num_00", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 1:
			m_pSprite->Render(L"num_01", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 2:
			m_pSprite->Render(L"num_02", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 3:
			m_pSprite->Render(L"num_03", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 4:
			m_pSprite->Render(L"num_04", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 5:
			m_pSprite->Render(L"num_05", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 6:
			m_pSprite->Render(L"num_06", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 7:
			m_pSprite->Render(L"num_07", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 8:
			m_pSprite->Render(L"num_08", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 9:
			m_pSprite->Render(L"num_09", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		}
		switch(m_numberFront)
		{
		case 0:
			m_pSprite->Render(L"num_00", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 1:
			m_pSprite->Render(L"num_01", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 2:
			m_pSprite->Render(L"num_02", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 3:
			m_pSprite->Render(L"num_03", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 4:
			m_pSprite->Render(L"num_04", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 5:
			m_pSprite->Render(L"num_05", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 6:
			m_pSprite->Render(L"num_06", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 7:
			m_pSprite->Render(L"num_07", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 8:
			m_pSprite->Render(L"num_08", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 9:
			m_pSprite->Render(L"num_09", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		}
	}
}
void cDrumNote::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
#if defined(DEBUE) || defined(_DEBUG)
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	}
#endif
}
void cDrumNote::KeyCheckRender(int Key)
{
	switch(Key)
	{
	case KEY_S:
		m_pSprite->Render(L"Note_S", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 0, 1));
		break;
	case KEY_D:
		m_pSprite->Render(L"Note_D", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 0, 1, 1));
		break;
	case KEY_F:
		m_pSprite->Render(L"Note_F", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 0, 0));
		break;
	case KEY_J:
		m_pSprite->Render(L"Note_J", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 0, 0, 1));
		break;
	case KEY_K:
		m_pSprite->Render(L"Note_K", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 0, 0, 0));
		break;
	case KEY_L:
		m_pSprite->Render(L"Note_L", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 0, 1, 0));
		break;
	}
	//m_pSprite->Render(L"Master", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));
}