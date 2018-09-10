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
	Judger_rNode = KGRect(m_nNoteX-47.f, m_nNoteY-25.f, m_nNoteX+47.f, m_nNoteY+25.f); //��忡 ��Ʈ��	 �ʱ�ȭ
}


cBaseNote::~cBaseNote()
{

}


void cBaseNote::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	cBase* pBase = (cBase*)cMain()->GetCurrent();

	if(!m_Judger_Node_Dead)
	{
		m_nNoteY += 5.f;					//��尡 �����̴� �κ�

		if(m_nNoteY >= 780)
		{
			m_Judger_Node_Miss = true;
			m_Judger_Node_Dead = true;
		}
	}


	Judger_rNode = KGRect(m_nNoteX-47.f, m_nNoteY-25.f, m_nNoteX+47.f, m_nNoteY+25.f); //��忡 ��Ʈ��	 �ʱ�ȭ

}


void cBaseNote::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(!m_Judger_Node_Dead)
		m_pSprite->Render(L"Note_Base", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
	
}
void cBaseNote::KeyCheck()
{
	Judge_Node_X_Check = m_nNoteX;		// �����̽��ٸ� ���� �׼����� X���� ����
	m_Judger_Node_Dead = true;				//��带 ���ְ�

	if(m_Judger_Node_Dead)
		m_nNoteX += 0;

	if(Judge_Node_X_Check >= 715 && Judge_Node_X_Check <= 732)			//������ X���� 758���� ũ�� ��
	{
		m_Judger_Node_Cool = true;										//�� Ʈ��
		m_Judger_Node_Perfect = false;
		m_Judger_Node_Miss = false;
	}
	if(Judge_Node_X_Check > 733 && Judge_Node_X_Check <= 766) //������ X���� 758���� ũ�� 858���� ������ ����
	{
		m_Judger_Node_Cool = false;										//�� Ʈ��
		m_Judger_Node_Perfect = true;
		m_Judger_Node_Miss = false;
	}


}

