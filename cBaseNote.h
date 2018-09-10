#ifndef _cBaseNote_H
#define _cBaseNote_H

#include "MyInclude.h"
#include "cKeyAsk.h"
#include "cKey.h"

using namespace KG;

class cKey;

class cBaseNote
{
public:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	int						m_nNoteKind;
	int						m_nNoteX;
	int						m_nNoteY;
	cKeyAsk					m_cKeyAsk;
	cKey					m_cKey;
	KGRect					Judger_rNode;
	int						Judge_Node_X_Check;
	bool					m_Judger_Node_Dead;
	bool					m_bCollusionCheck;
	bool					m_Judger_Node_Cool;
	bool					m_Judger_Node_Perfect;
	bool					m_Judger_Node_Miss;
	bool					m_bObject;


public:
	

public:
	cBaseNote();
	cBaseNote(KGAnimate* pAnimate, int Node_Index, int x, int y);
	~cBaseNote();


public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void					KeyCheck();
	
};

#endif