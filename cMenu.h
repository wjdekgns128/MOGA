#ifndef _cMenu_H
#define _cMenu_H

#include "MyInclude.h"

using namespace KG;

class cMenu : public KGScene  , public KGResponseDialog
{
private:
	enum
	{
		BT_GAME =1 ,
		BT_HELP,
		BT_CREATE,
		BT_QUIT,
		TM_FADE,
		
	};
private:

	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderSingle*			m_pSingle;
	int						menu_check;
	D3DXVECTOR3				m_vPos;
	cKey					m_Key;
	KGDialog*				m_pDialog;
	KGSound*				m_pSound;
	float					m_fAlpha;
	float					m_fFadeTime;
	KGCursor*				m_pCursor;
public:
	

public:
	cMenu();
	~cMenu();


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

protected:
	void					SetDisable(bool bDisable);
};

#endif