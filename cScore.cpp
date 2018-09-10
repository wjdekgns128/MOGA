#include "cScore.h"

cScore::cScore()
{
	m_pSprite					= NULL;
	m_pDialog					= NULL;
}


cScore::~cScore()
{
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pSprite); 

}


HRESULT cScore::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	m_rank						= 0;
	Next_Time					= 0;
	m_score						= 0;
	m_miss						= 0;
	m_good						= 0;
	m_perfect					= 0;
	m_combo						= 0;
	m_accuracy					= 0;
	m_check						= 3000;
	m_vPos						= D3DXVECTOR3(230,550,0);
	fMake_Time					= 0;
	m_fLevelscore				= 0;
	if(LEVEL == EASY)
		m_fLevelscore	= 0.5;
	else if(LEVEL == NORMAL)
		m_fLevelscore	= 1;
	else if(LEVEL == HARD)
		m_fLevelscore = 2;
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Dialog_number.Te");
		m_pSprite->Entry(L"res/te/CGEffect.te");
		m_pSprite->Entry(L"res/te/MPEffect.te");
		m_pSprite->Entry(L"res/te/RankABCD.te");
		m_pSprite->Entry(L"res/te/RankEFS.te");
		m_pSprite->Entry(L"res/te/RankInterface.te");
	}
	if(m_pDialog == NULL)
	{
		m_pDialog		= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog->AddNumber(1, L"Dnum_", D3DXVECTOR3(450, 250, 0),-25);
		//m_pDialog->AddNumber(2, L"Ranknum_", D3DXVECTOR3(0, 310, 0)); /////랭크 1부터 S ~~ E까지 그리저장할때 S == num_01 , A num_02 이런식으로
		m_pDialog->AddNumber(2, L"Dnum_", D3DXVECTOR3(850, 410, 0),-25); // 굿 부터 미스 콤보 
		m_pDialog->AddNumber(3, L"Dnum_", D3DXVECTOR3(850, 460, 0),-25);
		m_pDialog->AddNumber(4, L"Dnum_", D3DXVECTOR3(850, 510, 0),-25);
		m_pDialog->AddNumber(5, L"Dnum_", D3DXVECTOR3(850, 565, 0),-25);
		m_pDialog->AddNumber(6, L"Dnum_", D3DXVECTOR3(850, 620, 0),-25);
		//m_pDialog->AddNumber(7, L"Dnum_", D3DXVECTOR3(600, 300, 0));
	}
	return S_OK;
}
void cScore::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	SAFE_ONFRAMEMOVE(m_pDialog);
	fMake_Time += fElapsedTime;
	if(fMake_Time  >= 0.0001) 
	{
		fMake_Time = 0;
		m_check -=120;
	}
	if(m_check < 240)
		m_check = 240;
	if(m_score != SCORE)
	{
		m_score++;
	}
	if(m_perfect != MAXPERFECT)
	{
		m_perfect++;
	}
	if(m_miss != MAXMISS)
	{
		m_miss++;
	}
	if(m_good != MAXGOOD)
	{
		m_good++;
	}
	if(m_combo != MAXCOMBO)
	{
		m_combo++;
	}
	if(m_accuracy != ((((MAXPERFECT + MAXGOOD)) *100)/ MAXNODE))
	{
		m_accuracy++;
	}
	m_pDialog->GetNumber(1)->SetNumber(m_score);
	// 튜토리얼은 노트개수 7개정도 , 랭킹에 저장안되게 
	//m_pDialog->GetNumber(2)->SetNumber(m_rank);
	m_pDialog->GetNumber(2)->SetNumber(m_perfect);
	m_pDialog->GetNumber(3)->SetNumber(m_good);
	m_pDialog->GetNumber(4)->SetNumber(m_miss);
	m_pDialog->GetNumber(5)->SetNumber(m_combo);
	m_pDialog->GetNumber(6)->SetNumber(m_accuracy);
	if(m_score == SCORE)
	{
		if(Next_Time == 0)
			Next_Time =  GetTickCount();
		else if(GetTickCount() - Next_Time > 7000)
		{
			Next_Time					= 0;
			cMain()->Trans(L"choic");
		}
	}

	if(PLAYCHOICE == JEMBE) // 점수가 다르니 ;; 젬베;
	{
		if(MUSIC == JUST)
		{
			rank_check(12*m_fLevelscore,10*m_fLevelscore,8*m_fLevelscore,6*m_fLevelscore,4*m_fLevelscore,2*m_fLevelscore); // 음악마다 A,B,C,D,E 점수가 다르니깐 
		}			
		if(MUSIC == SWAGGA)
		{
			rank_check(13*m_fLevelscore,11*m_fLevelscore,9*m_fLevelscore,7*m_fLevelscore,5*m_fLevelscore,3*m_fLevelscore);
		}
		if(MUSIC == PRACTICE)
		{
			rank_check(0,0,0,0,0,0);
		}
	}
	
	if(PLAYCHOICE == DRUM) // 점수가 다르니 ;;
	{

		if(MUSIC == JUST)
		{
			rank_check(12*m_fLevelscore,10*m_fLevelscore,8*m_fLevelscore,6*m_fLevelscore,4*m_fLevelscore,2*m_fLevelscore); // 음악마다 A,B,C,D,E 점수가 다르니깐 
		}			
		if(MUSIC == SWAGGA)
		{
			rank_check(13*m_fLevelscore,11*m_fLevelscore,9*m_fLevelscore,7*m_fLevelscore,5*m_fLevelscore,3*m_fLevelscore);
		}
		if(MUSIC == PRACTICE)
		{
			rank_check(0,0,0,0,0,0);
		}
	}


}
void cScore::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"Rank_Perfect",D3DXVECTOR3(460,400,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_Good",D3DXVECTOR3(455,450,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_Miss",D3DXVECTOR3(455,500,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_MaxCombo",D3DXVECTOR3(420,550,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_JudgeAverage",D3DXVECTOR3(425,600,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Persent",D3DXVECTOR3(960,620,0),D3DXCOLOR(1,1,1,1));
		SAFE_ONFRAMERENDER(m_pDialog);
		V(pd3dDevice->EndScene());
		switch(m_rank)
		{
		case F:
			m_pSprite->Render(L"Ranknum_07",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case E:
			m_pSprite->Render(L"Ranknum_06",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case D:
			m_pSprite->Render(L"Ranknum_05",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case C:
			m_pSprite->Render(L"Ranknum_04",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case B:
			m_pSprite->Render(L"Ranknum_03",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case A:
			m_pSprite->Render(L"Ranknum_02",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case S:
			m_pSprite->Render(L"Ranknum_01",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		}

	}
}
void cScore::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					 bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	if(bButtonDown)
	{
		m_score = SCORE;
		m_perfect = MAXPERFECT;
		m_miss = MAXMISS;
		m_good = MAXGOOD;
		m_combo = MAXCOMBO;
		m_accuracy = ((((MAXPERFECT + MAXGOOD)) *100)/ MAXNODE);
	}
}
void cScore::rank_check(int SA,int AB,int BC,int CD ,int DE,int EF)
{	
	if(SCORE < EF)
	{
		m_rank = F;

	}
	else if(EF <= SCORE	 &&  SCORE	< DE)
	{
		m_rank = E;
	}
	else if(DE<= SCORE	 && SCORE	 < CD)
	{
		m_rank = D;
	}
	else if(CD<= SCORE	 && SCORE < BC)
	{
		m_rank = C;
	}
	else if(BC<= SCORE && SCORE < AB)
	{
		m_rank = B;
	}
	else if(AB<= SCORE && SCORE < SA)
	{
		m_rank = A;
	}
	else if(SA<= SCORE)
	{
		m_rank = S;
	}
}