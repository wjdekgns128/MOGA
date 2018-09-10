#ifndef _CSCORE_H_
#define _CSCORE_H_

#include "MyInclude.h"

using namespace KG;

class cScore : public KGScene
{
private:

	KGSprite*				m_pSprite;
	int						m_rank;
	int						Next_Time;
	KGDialog*				m_pDialog;
	FILE*					fp;
	int						save;
	int						m_score;
	int						m_miss;
	int						m_good;
	int						m_perfect;
	int						m_combo;
	int						m_accuracy;
	int						m_check;
	D3DXVECTOR3				m_vPos;
	float					fMake_Time;
	float						m_fLevelscore;
	
public:
	

public:
	cScore();
	~cScore();

public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	void rank_check(int SA,int AB, int BC ,int CD ,int DE,int EF); //// 더추가가능
};

#endif