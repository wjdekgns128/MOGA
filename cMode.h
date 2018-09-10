#ifndef _cMode_H
#define _cMode_H

#include "MyInclude.h"

using namespace KG;

class cMode : public KGScene,KGResponseDialog
{

private:
	enum
	{
		BT_DRUM =1 ,
		BT_JEMBE,
		BT_BASE,
		TM_FADE,
		TM_Next_FADE,
	};

	KGSprite*				m_pSprite;
	KGRenderSingle*			m_pSingle;
	KGAnimate*				m_pAnimate;
	int						mode_check;
	D3DXVECTOR3				m_vPos;
	KGDialog*				m_pDialog;
	KGSound*				m_pSound;
	float					m_fAlpha;
	float					m_fFadeTime;
	float					m_Next_fAlpha;
	KGCursor*				m_pCursor;

public:
	

public:
	cMode();
	~cMode();


public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);

	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
	void CALLBACK			OnEvent(UINT id, int xPos, int yPox);
	void					SetDisable(bool bDisable);

};

#endif