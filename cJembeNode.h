#ifndef _cJembeNode_H
#define _cJembeNode_H

#include "MyInclude.h"
using namespace KG;
class cJembeNode : public KGScene,KGResponseDialog
{
public: 
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	D3DXVECTOR3				m_Mpos; // 마우스 좌표
	double					m_Mradius; // 마우스 원반지름
	float					Make_Time; // 만들어지는 총시간
	DWORD					Kill_Time;	// 콤보 시간 
	DWORD					Effect_Time;
	DWORD					back_Time;
	int						Combo;			//// 콤보 //  3개 연속으로 맞추는순간  콤보 1 그상태에서 한개더 2 -> 3 -> 4-> 5 스코어는 x콤보
	int						check;
	int						Num;
	DWORD					Score_Time;	// 스코어화면으로 넘어가는시간
	int						jembe_back;
	KGDialog*				m_pDialog;
	float					fAlp;
	double					radius; // 노트의 원반지름
	int						m_IMax_Combo;
	D3DXVECTOR3				m_vPatpos;	
	typedef struct Node // 노트 구조체 
	{
			int						m_state; // 0 : x 1: o 2:x
			D3DXVECTOR3				m_vPos; // 노트의 좌표
			float					save_Time; // 노트 간격
			DWORD					NodeCheck_Time; // 큰원은 체크시간
			DWORD					check_Time; // 스코어 시간
			int						Node_Check; // 큰원의 반지름 줄어드는 거리?
			int						check; // 1 : 퍼펙 2: 굿 3:미스
			int						color;// 나올색
			
			KGRenderSingle*			impact;
			KGRenderSingle*			m_pSingle;
			~Node()
			{
				SAFE_DELETE(m_pSingle);
				SAFE_DELETE(impact);
			}
	}_Node;
	_Node*				m_Node;

	int					Node_Max; //노드의 총숫자
public:
	

public:
	cJembeNode(KGAnimate*	pAnimate,	KGSound* pSound,KGDialog* pDialog);
	~cJembeNode();


public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);

	void LoadNode(WCHAR* pFileName);
	void DecodeNode(FILE* pFile);
	bool ColBetween(D3DXVECTOR3 m_vPos,double m_radius,int check);
	bool NoColBetween(D3DXVECTOR3 m_vPos,double m_radius);
	int	 Combo_OK(int check);
	void score_OK(int effect , int combo,int score);
	void OK(int color,int nocolor,int check);
	void PatDraw(int First,int Last);
};

#endif