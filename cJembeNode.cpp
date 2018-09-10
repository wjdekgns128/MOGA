#include "cJembeNode.h"
// 저스트 끝..
// 스웨거 작업..
cJembeNode::cJembeNode(KGAnimate*  pAnimate,KGSound*pSound,KGDialog* pDialog)
{
	Make_Time				= 0;
	Score_Time				= 0;
	m_pAnimate				= pAnimate;
	m_pSprite				= pAnimate->GetSprite();
	m_Mradius				= 15; // 마우스 지름 15
	radius					= 15;
	m_pSound				= pSound;
	m_pDialog				= pDialog;
	Combo					= 0; 
	Num						= 0;
	check					= 0;
	Effect_Time				= 0;
	jembe_back				= 0;
	back_Time				= 0;
	fAlp					= 1;
	m_IMax_Combo			= 0;
	switch(MUSIC)
	{
	case JUST:
		if(LEVEL == EASY)
			LoadNode(L"EASYJEMBEJUST.txt");
		if(LEVEL ==	NORMAL)
			LoadNode(L"JEMBEJUST.txt");
		if(LEVEL == HARD)
			LoadNode(L"HARDJEMBEJUST.txt");
		m_pSound->Play(L"just");
		break;
	case SWAGGA:
		LoadNode(L"JEMBESWAGGA.txt");
		m_pSound->Play(L"swagga");
		break;
	case PRACTICE:
		LoadNode(L"JEMBEPRACTICE.txt");
		m_pSound->Play(L"practice");
		break;
	}
	MAXNODE					= Node_Max;

}
cJembeNode::~cJembeNode()
{

	SAFE_DELETE_ARRAY(m_Node);
}
void cJembeNode::OnDestroyDevice(void* pUserContext)
{

	SAFE_DELETE_ARRAY(m_Node);

}
HRESULT cJembeNode::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	return S_OK;
}
HRESULT cJembeNode::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	return S_OK;
}

void cJembeNode::OnLostDevice(void* pUserContext)
{

}

void cJembeNode::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	Make_Time += fElapsedTime;
	m_pDialog->GetNumber(1)->SetNumber(SCORE);
	m_pDialog->GetNumber(2)->SetNumber(m_IMax_Combo);
	m_pDialog->GetNumber(3)->SetNumber(((((MAXPERFECT + MAXGOOD)) *100)/ MAXNODE));
	for(int i=0;i<Node_Max;i++)   //////////////////////////////// 노트 생성
	{
		if(Num == i)
		{
			if(Make_Time  >= m_Node[i].save_Time) 
			{
				//KGOutputDebugString(L"%f\n",Make_Time);
				if(m_Node[i].m_state == 0)
				{
					Make_Time = 0;
					m_Node[i].m_state = 1;
					Num +=1;
					break;
				}
			}		
		}
	}
	/////////////////////////////////////////////////////////////
	for(int i=0;i<Node_Max;i++)///////////////////////노트의 큰원 줄어드는 시간
	{
		if(m_Node[i].m_state == 1)
		{
			if(m_Node[i].NodeCheck_Time == 0)
				m_Node[i].NodeCheck_Time = GetTickCount();
			else if(GetTickCount() - m_Node[i].NodeCheck_Time > 16 - LEVEL )
			{
				m_Node[i].NodeCheck_Time =0;
				if(m_Node[i].Node_Check > 5)
					m_Node[i].Node_Check -=1;
			}
		}

	}
	//////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	for(int i=0;i<Node_Max;i++)       /////////////////// 줄어드면 없어짐
	{
		if(m_Node[i].Node_Check == 5)
		{
			check = Combo_OK(i);
			m_Node[i].check = 3; // 없어졌을때 미스나오게하거나 안하거나
			m_Node[i].m_state = 2;
			m_Node[i].Node_Check= -1;
			Combo = 0;
			m_IMax_Combo = 0;
			MAXMISS	 +=1;
			break;
		}
	}
	////   시간 
	for(int i=0;i<Node_Max;i++)
	{
		if(m_Node[i].check != 0)
		{
			if(m_Node[i].check_Time == 0)
				m_Node[i].check_Time = GetTickCount();
			else if(GetTickCount() - m_Node[i].check_Time > 50)
			{
				m_Node[i].check_Time = 0;
				m_Node[i].check = 0;
				NOWNODE+=1;				// 없어지는 노트 
				break;
			}
		}
	}
	if(jembe_back != 0)
	{
		if(back_Time == 0)
			back_Time = GetTickCount();
		else if(GetTickCount() - back_Time > 500)
		{
			back_Time = 0;
			jembe_back = 0;
		}
	}
	if(NOWNODE == MAXNODE  )		// 스코어로 넘어가는 시간
	{
		if(Score_Time == 0)
			Score_Time =GetTickCount();
		else if(GetTickCount() - Score_Time > 2000)
		{
			Score_Time	= 0;
			cMain()->Trans(L"score");
		}
	}
}
void cJembeNode::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pSprite->Render(L"jembe_back",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	if(jembe_back == 0)
		m_pSprite->Render(L"jembe_en",D3DXVECTOR3(243,462,0),D3DXCOLOR(1,1,1,fAlp));
	else if(jembe_back == 1)
		m_pSprite->Render(L"jembe_back_red",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,fAlp));
	else if(jembe_back == 2)
		m_pSprite->Render(L"jembe_back_blue",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,fAlp));
	m_pSprite->Render(L"Persent",D3DXVECTOR3(640,697,0),D3DXCOLOR(1,1,1,1));
	m_pSprite->Render(L"combo",D3DXVECTOR3(310,627,0),D3DXCOLOR(1,1,1,1));
	m_pSprite->Render(L"score",D3DXVECTOR3(750,740,0),D3DXCOLOR(1,1,1,1));

	for(int i=0;i<Node_Max;i++)
	{
		SAFE_ONFRAMERENDER(m_Node[i].impact);
		SAFE_ONFRAMERENDER(m_Node[i].m_pSingle);
	}
	for(int i=Node_Max-1;i>=0;i--)
	{
		if(m_Node[i].m_state == 1)
		{
			////// 첫번째는 큰노트일듯
			//// 두번째는 작은
			switch(m_Node[i].color) 
			{
			case 0:
				m_pSprite->Render(L"node",D3DXVECTOR3(m_Node[i].m_vPos.x-20,m_Node[i].m_vPos.y-20,0),D3DXCOLOR(1,1,1,1));
				break;
			case 1:
				m_pSprite->Render(L"node1",D3DXVECTOR3(m_Node[i].m_vPos.x-20,m_Node[i].m_vPos.y-20,0),D3DXCOLOR(1,1,1,1));
				break;
			}
			m_pSprite->Render(L"node2",KGRect(m_Node[i].m_vPos.x-m_Node[i].Node_Check,m_Node[i].m_vPos.y-m_Node[i].Node_Check,m_Node[i].m_vPos.x+m_Node[i].Node_Check,m_Node[i].m_vPos.y+m_Node[i].Node_Check),D3DXCOLOR(1,1,1,1),-1);
		} 
		if(MUSIC == PRACTICE)
		{
			if(m_Node[i].Node_Check <= 25 && m_Node[i].Node_Check > 17 && m_Node[i].m_state == 1)
			{
				m_pSprite->Render(L"ok",D3DXVECTOR3(m_Node[i].m_vPos.x-150,m_Node[i].m_vPos.y-30,0),D3DXCOLOR(1,1,1,1));
				break;
			}
		}
	}
	if(Combo < 3)
	{
		if(m_Node[check].check == 1)
		{
			m_Node[check].m_pSingle->Entry(L"perfect", D3DXVECTOR3(m_Node[check].m_vPos.x-110,m_Node[check].m_vPos.y-150,0), true, 1);
		}
		else if(m_Node[check].check == 2)
		{
			m_Node[check].m_pSingle->Entry(L"Good", D3DXVECTOR3(m_Node[check].m_vPos.x-110,m_Node[check].m_vPos.y-150,0), true, 1);
		}
		else if(m_Node[check].check == 3)
		{
			m_Node[check].m_pSingle->Entry(L"Miss", D3DXVECTOR3(m_Node[check].m_vPos.x-110,m_Node[check].m_vPos.y-150,0), true, 1);
		}

	}

	if(m_Node[check].check != 0)
	{
		if(Combo >= 3)
		{
			m_Node[check].m_pSingle->Entry(L"Combo", D3DXVECTOR3(m_Node[check].m_vPos.x-130,m_Node[check].m_vPos.y,0), true, 1);		
		}
	}
	// 임펙트
	if(m_Node[check].check == 1)  
	{
		if(m_Node[check].color == 0)
		{
			m_Node[check].impact->Entry(L"jembe_effect_red", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}
		if(m_Node[check].color == 1)
		{
			m_Node[check].impact->Entry(L"jembe_effect_blue", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}	
	}
	else if(m_Node[check].check == 2)
	{
		if(m_Node[check].color == 0)
		{
			m_Node[check].impact->Entry(L"jembe_effect_red", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}
		if(m_Node[check].color == 1)
		{
			m_Node[check].impact->Entry(L"jembe_effect_blue", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}	
	}
	else if(m_Node[check].check == 3)
	{
		m_Node[check].impact->Entry(L"jembe_miss_effect", D3DXVECTOR3(m_Node[check].m_vPos.x-60,m_Node[check].m_vPos.y-45,0), true, 1); // 임펙트이다.
	}
}
void cJembeNode::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
						 bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	m_Mpos.x = xPos;  // 미우스좌표
	m_Mpos.y = yPos;
	if(bButtonDown)
	{
		if(bLeftButtonDown)
		{
			for(int i=0;i<Node_Max;i++)
			{
				if(ColBetween(m_Mpos,m_Mradius,i)) // 충돌처리
				{
					if(m_Node[i].m_state == 1)
					{
						jembe_back = 1;
						OK(0,1,i);
						check = Combo_OK(i);
						break;
					}
				}

			}
		}
		if(bRightButtonDown) 
		{
			for(int i=0;i<Node_Max;i++)
			{
				if(ColBetween(m_Mpos,m_Mradius,i)) // 충돌처리
				{
					if(m_Node[i].m_state == 1)
					{
						jembe_back = 2;
						OK(1,0,i);
						check = Combo_OK(i);
						break;
					}
				}
			}

		}
		if(NoColBetween(m_Mpos,m_Mradius)) // 통빈화면 눌렀을때 
		{
			m_Node[check].impact->Entry(L"mouse_effect", D3DXVECTOR3(m_Mpos.x-100,m_Mpos.y-60,0), true, 1); // 임펙트이다.
		}

	}
}
void cJembeNode::LoadNode(WCHAR* pFileName)
{
	FILE* pFile;

	pFile = _wfopen(pFileName, L"r");
	if(pFile == NULL)
		return;
	DecodeNode(pFile);
	fclose(pFile);
}

void cJembeNode::DecodeNode(FILE* pFile)
{   ///// 전체적인 노트의 크기 시간 지름 좌표 등등 
	SRANDOM();
	WCHAR pSave[256];
	fgetws(pSave, 256, pFile);
	swscanf(pSave, L"%d", &Node_Max);
	m_Node = new _Node[Node_Max];
	memset(m_Node, 0, sizeof(m_Node));
	for(int i =0; i < Node_Max; i++)
	{
		fgetws(pSave, sizeof(pSave), pFile);
		swscanf(pSave, L"%f",&m_Node[i].save_Time);
		m_Node[i].m_vPos		= D3DXVECTOR3(RANDOM(100,900),RANDOM(30,500),0);
		m_Node[i].m_state      = 0;
		m_Node[i].Node_Check	= 60;
		m_Node[i].NodeCheck_Time = 0;
		m_Node[i].check        = 0;
		m_Node[i].check_Time   = 0;
		m_Node[i].color = RANDOM(0,1);
		m_Node[i].m_pSingle = new KGRenderSingle(m_pAnimate);
		m_Node[i].impact	= new KGRenderSingle(m_pAnimate);
	}
	if(MUSIC == JUST)  // 기획에서 넘어오면 패턴 임 
	{
		if(LEVEL == EASY)
		{
			PatDraw(10,12);
			PatDraw(14,16);
			PatDraw(18,21);
			PatDraw(23,25);
			PatDraw(34,37);
			PatDraw(40,43);
			PatDraw(48,50);
			PatDraw(52,55);
			PatDraw(57,59);
			PatDraw(61,63);
			PatDraw(65,67);
			PatDraw(17,19);
			PatDraw(21,23);
			PatDraw(30,38);
			PatDraw(41,44);
			PatDraw(51,52);
		}
		if(LEVEL ==	NORMAL)
		{
			PatDraw(1,2);
			PatDraw(4,5);
			PatDraw(7,8);
			PatDraw(13,14);
			PatDraw(16,20);
			PatDraw(22,26);
			PatDraw(29,32);
			PatDraw(34,36);
			PatDraw(37,40);
			PatDraw(42,43);
			PatDraw(45,46);
			PatDraw(50,54);
			PatDraw(56,60);
			PatDraw(63,64);
			PatDraw(66,69);
			PatDraw(74,79);
			PatDraw(81,83);
			PatDraw(86,91);
			PatDraw(94,96);
			PatDraw(97,98);
			PatDraw(100,104);
			PatDraw(106,108);
			PatDraw(109,110);
			PatDraw(112,116);
			PatDraw(123,125);
			PatDraw(127,129);
		}
		if(LEVEL == HARD)
		{
			PatDraw(4, 6);
			PatDraw(7, 8);
			PatDraw(9, 11);
			PatDraw(13, 17);
			PatDraw(19, 22);
			PatDraw(24, 29);
			PatDraw(32, 37);
			PatDraw(38, 42);
			PatDraw(45, 49);
			PatDraw(51, 56);
			PatDraw(58, 63);
			PatDraw(64, 68);
			PatDraw(70, 74);
			PatDraw(76, 81);
			PatDraw(83, 86);
			PatDraw(88, 92);
			PatDraw(95, 100);
			PatDraw(102, 106);
			PatDraw(109, 114);
			PatDraw(116, 122);
			PatDraw(124, 130);
			PatDraw(132, 140);
			PatDraw(143, 148);
			PatDraw(154, 156);
			PatDraw(158, 163);
			PatDraw(164, 166);
			PatDraw(167, 172);
			PatDraw(175, 179);
			PatDraw(182, 187);
			PatDraw(188, 191);
			PatDraw(192, 197);
			PatDraw(200, 204);
			PatDraw(207, 211);
		}					   
	}						   
	/*if(MUSIC == SWAGGA)
	{				 
	if(LEVEL == EASY )
	{

	}
	if(LEVEL ==	NORMAL)
	{

	}
	if(LEVEL == HARD)
	{

	}
	}*/
}
void cJembeNode::PatDraw(int First,int Last)
{
	m_vPatpos = D3DXVECTOR3(RANDOM(30,700),RANDOM(30,500),0);
	for(int i=First;i<=Last;i++)
		m_Node[i].m_vPos = D3DXVECTOR3(m_vPatpos.x+((i-(First-1))*35),m_vPatpos.y,0);

}
bool cJembeNode::ColBetween(D3DXVECTOR3 m_vPos,double m_radius,int check)
{  /// 충돌처리
	return (pow(m_vPos.x - m_Node[check].m_vPos.x,2)+
		pow(m_vPos.y - m_Node[check].m_vPos.y,2)
		< pow(radius + m_radius,2));
}
bool cJembeNode::NoColBetween(D3DXVECTOR3 m_vPos,double m_radius)
{  /// 충돌처리
	for(int i=0;i<Node_Max;i++)
	{
		return (pow(m_vPos.x - m_Node[i].m_vPos.x,2)+
			pow(m_vPos.y - m_Node[i].m_vPos.y,2)
	> pow(radius + m_radius,2));
	}
}
int	 cJembeNode::Combo_OK(int check)
{
	return check;
}
void cJembeNode::score_OK(int effect , int combo,int score)
{		/// 스코어점수관련 굿과 퍼펙트로나눔
	if(effect == 0)
	{
		if(combo < 3)
			SCORE+= score;
		else if(combo == 3)
			SCORE += score*2;
		else if(combo == 4)
			SCORE += score*3;
		else if(combo == 5)
			SCORE += score*4;
		else if(combo >= 6)
			SCORE += score*5;
	}
	else if(effect == 1)
	{
		if(combo < 3)
			SCORE+=score;
		else if(combo == 3)
			SCORE +=score*2;
		else if(combo == 4)
			SCORE +=score*4;
		else if(combo == 5)
			SCORE +=score*6;
		else if(combo >= 6)
			SCORE +=score*8;
	}
}
void cJembeNode::OK(int color,int nocolor,int check)
{
	if(m_Node[check].color  == color)
	{
		if((m_Node[check].Node_Check > 25 && m_Node[check].Node_Check < 34) || (m_Node[check].Node_Check <= 17 && m_Node[check].Node_Check > 12))
		{  // 굿일때
			m_Node[check].m_state = 2;
			m_Node[check].check   = 2;
			Combo+=1;
			MAXGOOD +=1;
			if(Combo >= 3)
			{
				m_IMax_Combo+=1;
				MAXCOMBO+=1;
			}
			score_OK(0, Combo,1);
		}
		else if(m_Node[check].Node_Check <= 25 && m_Node[check].Node_Check > 17)
		{ // 퍼펙
			m_Node[check].m_state = 2;
			m_Node[check].check  = 1;
			Combo+=1;
			MAXPERFECT +=1;
			if(Combo >= 3)
			{
				MAXCOMBO+=1;
				m_IMax_Combo +=1;

			}
			score_OK(1, Combo,2);
		}
		else // 미스
		{
			m_Node[check].m_state =2;
			m_Node[check].check  = 3;
			MAXMISS		+=1;
			Combo = 0;
			m_IMax_Combo =0;
		}
	}
	if(MUSIC != PRACTICE)
	{
		if(m_Node[check].color  ==	nocolor)  
		{
			m_Node[check].check = 3;
			m_Node[check].m_state =2;
			MAXMISS		+=1;
			Combo = 0;
			m_IMax_Combo = 0;
		}
	}
}