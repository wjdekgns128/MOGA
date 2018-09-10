#include "cBaseNote.h"


cBaseNote::cBaseNote(KGAnimate* pAnimate, int Node_Index, int x, int y)
{
	m_pAnimate				= pAnimate;
	m_pSprite				= m_pAnimate->GetSprite();
	m_nNoteKind = Node_Index;
	m_nNoteX = 0;
	m_nNoteX = 0;
	m_nNoteX = x;
	m_nNoteY = y;
	Judge_Node_X_Check		= 0; //400 50
	m_Judger_Node_Dead		= false;
	m_bCollusionCheck		= false;
	m_Judger_Node_Cool		= false;
	m_Judger_Node_Perfect	= false;
	m_Judger_Node_Miss		= false;
	Judger_rNode = KGRect(m_nNoteX-47.f, m_nNoteY-25.f, m_nNoteX+47.f, m_nNoteY+25.f); //노드에 렉트값	 초기화
}


cBaseNote::~cBaseNote()
{

}


void cBaseNote::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	cBase* pBase = (cBase*)cMain()->GetCurrent();

	if(!m_Judger_Node_Dead)
	{
		m_nNoteY += 5.f;					//노드가 움직이는 부분

		if(m_nNoteY >= 780)
		{
			m_Judger_Node_Miss = true;
			m_Judger_Node_Dead = true;
		}
	}


	Judger_rNode = KGRect(m_nNoteX-47.f, m_nNoteY-25.f, m_nNoteX+47.f, m_nNoteY+25.f); //노드에 렉트값	 초기화

}


void cBaseNote::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(!m_Judger_Node_Dead)
		m_pSprite->Render(L"Note_Base", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
	
}
void cBaseNote::KeyCheck()
{
	Judge_Node_X_Check = m_nNoteX;		// 스페이스바를 누른 그순간의 X값을 저장
	m_Judger_Node_Dead = true;				//노드를 없애고

	if(m_Judger_Node_Dead)
		m_nNoteX += 0;

	if(Judge_Node_X_Check >= 715 && Judge_Node_X_Check <= 732)			//저장한 X값이 758보다 크면 쿨
	{
		m_Judger_Node_Cool = true;										//쿨 트루
		m_Judger_Node_Perfect = false;
		m_Judger_Node_Miss = false;
	}
	if(Judge_Node_X_Check > 733 && Judge_Node_X_Check <= 766) //저장한 X값이 758보다 크고 858보다 작으면 퍼펙
	{
		m_Judger_Node_Cool = false;										//쿨 트루
		m_Judger_Node_Perfect = true;
		m_Judger_Node_Miss = false;
	}


}

