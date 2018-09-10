#include "cBaseLoad.h"

cBaseLoad::cBaseLoad()
{
	m_pBaseNote = NULL;
}


cBaseLoad::~cBaseLoad ()
{

}


void cBaseLoad::OnLostDevice(void* pUserContext)
{
}


void cBaseLoad::OnDestroyDevice(void* pUserContext)
{	
}


void cBaseLoad::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	for(int i=0; i<m_Number; i++)
		SAFE_ONFRAMEMOVE(m_pBaseNote[i]);
}


void cBaseLoad::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	for(int i=0; i<m_Number; i++)
		SAFE_ONFRAMERENDER(m_pBaseNote[i]);
}
