#include "CMAIN.h"

IMPLEMENT_MAIN(CMAIN);

CMAIN::CMAIN() : KGEmotion(L"Animate Example", 1024, 768)
{
	g_MusicState = 0;
	g_InstrumentState= 1;
	g_AlphaBar				= 1;
	g_DrumCombo				= 0;
	g_score					= 0;
	g_nownode				= 0;
	g_maxnode				= 0;
	g_test					= 0;
	g_perfect				= 0;
	g_good					= 0;
	g_miss					= 0;
	g_maxcombo				= 0;
	g_Ilevel				= 1;
	m_pMain					= this;

#if defined(NDEBUG)
	SetFullScreenBackBufferWidthAtModeChange(1024);
	SetFullScreenBackBufferHeightAtModeChange(768);
	SetOverrideWidth(1024);
	SetOverrideHeight(768);
	SetOverrideFullScreen(true);
	SetHandleAltEnter(false);
	SetHandleDefaultHotkeys(false);
	SetShowMsgBoxOnError(true);
	SetShowCursorWhenFullScreen(false);
#endif
}


CMAIN::~CMAIN()
{

}

void CMAIN::Create()
{
	Entry(L"logo", new cLogo);
	Entry(L"menu", new cMenu);
	Entry(L"mode", new cMode);
	Entry(L"result", new cResult);
	Entry(L"jembe",new cJembe);
	Entry(L"choic",new cMusicChoice);
	Entry(L"drum", new cDrum);
	Entry(L"base", new cBase);
	Entry(L"help",new cHelp);
	Entry(L"score",new cScore);
}


void CMAIN::Init()
{
	Trans(L"logo");
}