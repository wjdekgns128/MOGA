#ifndef _SWAGGA_H
#define _SWAGGA_H
//모듈은 상속받을필요 없당 ㅋ
#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif

using namespace KG;

#include"cKeyAsk.h"


class cDrumNote
{
public:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	KGRenderSingle*			m_pSingle[EFFECT];
	cKeyAsk					m_cKeyAsk;
	int						m_Node_Number;
	int						Judge_Bar_X;
	int						Judge_Bar_Y;
	int						m_Node_x;
	int						m_Node_y;
	int						m_numberBack;
	int						m_numberFront;
	int						m_EffectState;
	bool					m_AlphaCheck;
	int						m_NoteResult;
	KGRect					Judger_rNode;
	bool					m_Judger_Node_Dead;
	bool					m_Judger_Node_Cool;
	bool					m_Judger_Node_Miss;
	bool					m_Judger_Node_Perfect;
	int						Judge_Node_X_Check;
	bool					m_bSibal;
	bool					m_bObject;
	bool					m_bCollusionCheck;
	int						m_nKeyCheck;
	int						m_bNumberCheck;
	bool					m_bComboRenderCheck;
	bool					m_bComboOneCheck;
	bool					m_bComboBefore;
	bool					m_nMissBefore;




	bool					m_Disable;
public:
	cDrumNote(KGAnimate* pAnimate, KGSound* pSound, int m_Node_Counter, int x, int y, int number1, int number2, int NumberCheck, int KeyCheck);
	~cDrumNote();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void					SetDisable(bool bDisable);
	bool					GetDisable();
	void					Judge_Funtion(int result);
	void					GetNumber(int number1, int number2);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void					KeyCheckRender(int Key);
	//IMPLEMENT_GET_SET(bool, Disable);
};

#endif