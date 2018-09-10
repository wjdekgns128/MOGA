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
	D3DXVECTOR3				m_Mpos; // ���콺 ��ǥ
	double					m_Mradius; // ���콺 ��������
	float					Make_Time; // ��������� �ѽð�
	DWORD					Kill_Time;	// �޺� �ð� 
	DWORD					Effect_Time;
	DWORD					back_Time;
	int						Combo;			//// �޺� //  3�� �������� ���ߴ¼���  �޺� 1 �׻��¿��� �Ѱ��� 2 -> 3 -> 4-> 5 ���ھ�� x�޺�
	int						check;
	int						Num;
	DWORD					Score_Time;	// ���ھ�ȭ������ �Ѿ�½ð�
	int						jembe_back;
	KGDialog*				m_pDialog;
	float					fAlp;
	double					radius; // ��Ʈ�� ��������
	int						m_IMax_Combo;
	D3DXVECTOR3				m_vPatpos;	
	typedef struct Node // ��Ʈ ����ü 
	{
			int						m_state; // 0 : x 1: o 2:x
			D3DXVECTOR3				m_vPos; // ��Ʈ�� ��ǥ
			float					save_Time; // ��Ʈ ����
			DWORD					NodeCheck_Time; // ū���� üũ�ð�
			DWORD					check_Time; // ���ھ� �ð�
			int						Node_Check; // ū���� ������ �پ��� �Ÿ�?
			int						check; // 1 : ���� 2: �� 3:�̽�
			int						color;// ���û�
			
			KGRenderSingle*			impact;
			KGRenderSingle*			m_pSingle;
			~Node()
			{
				SAFE_DELETE(m_pSingle);
				SAFE_DELETE(impact);
			}
	}_Node;
	_Node*				m_Node;

	int					Node_Max; //����� �Ѽ���
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