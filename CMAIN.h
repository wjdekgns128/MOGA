#ifndef _CMAIN_H
#define _CMAIN_H

#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif

#include "MyInclude.h"

using namespace KG;

class CMAIN : public KGEmotion
{
public:
	int				g_MusicState;
	int				g_InstrumentState;
	float			g_AlphaBar;
	int				g_DrumCombo;
	int				g_test;

	// 스코어에 필요한거
	int				g_score;				
	int				g_nownode;			
	int				g_maxnode;
	int				g_perfect;
	int				g_good;
	int				g_miss;
	int				g_maxcombo;
	int				g_Ilevel;
	CMAIN();
	~CMAIN();


public:
	static CMAIN*			m_pMain;


public:
	void					Create();
	void					Init();
};

static CMAIN* cMain()
{
	return CMAIN::m_pMain;
}

#endif