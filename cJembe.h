#ifndef _cJembe_H
#define _cJembe_H

#include "MyInclude.h"
#include "cJembeNode.h"
using namespace KG;
class cJembeNode;

class cJembe : public KGScene,KGResponseDialog
{
public:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	cJembeNode*				m_Node;
	D3DXVECTOR3				m_vPos;
	DWORD					Make_Time; //메뉴로 넘어가는시간
	int						m_state;
	KGDialog*				m_pDialog;
	KGCursor*				m_pCursor;
	
public:
	

public:
	cJembe();
	~cJembe();


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
};

#endif