#ifndef _MYDEFINE_H
#define _MYDEFINE_H



#define	SCORE cMain()->g_score					// 점수  없어질때 ++ 해주면되겠지	
#define	NOWNODE	cMain()->g_nownode				// 없어진 노트의수 만약 없애버릴떄  이거 한개씩 ++;
#define	MAXNODE	cMain()->g_maxnode				// 이거 총개수      생성자에다가 MAXNODE = 총노트개수  // 잘모르겠으면 젬베노트 .CPP 봐봐
#define	MAXPERFECT		cMain()->g_perfect
#define	MAXGOOD			cMain()->g_good	
#define	MAXMISS			cMain()->g_miss
#define	MAXCOMBO		cMain()->g_maxcombo
//////위에 3개는 음악 선택후 게임하다가 다시 음악선택창으로 나오게할테데 그거할때 *초기화해야함* 
#define MUSIC cMain()->g_MusicState
#define JUST  1
#define SWAGGA 2
#define PRACTICE 3 // 튜토리얼 임 
#define PLAYCHOICE cMain()->g_InstrumentState
#define DRUM 1
#define JEMBE 2
#define BASE 3

#define EASY 0
#define NORMAL 1
#define HARD 2
#define LEVEL   cMain()->g_Ilevel

#define DRUMCLICK_MAX 5
#define AIPHABAR cMain()->g_AlphaBar
#define SRANDOM() srand(( unsigned int) time (NULL))
#define RANDOM(min,max) ((rand() % ((max) -(min)+1)) +(min))
#define EFFECT 4

#define KEY_S 1
#define KEY_D 2
#define KEY_F 3
#define KEY_J 4
#define KEY_K 5
#define KEY_L 6


///랭크
#define F		7
#define E		6
#define	D		5
#define	C		4
#define	B		3
#define	A		2
#define	S		1
///// 이름바꾸면됨
#define GAME	1
#define HELP	2
#define	CREATE		3
#define	QUIT		4

// 드럼콤보
#define DRUMCOMBO cMain()->g_DrumCombo

#define LAYER1 0
#define LAYER2 1
#define LAYER3 2
#define LAYER4 3
#define LAYER5 4 



// 랭크 몇개
#define NUMBE_MAX 10



enum
{
	EFFECT_PERFECT = 0,
	EFFECT_COOL,
	EFFECT_GOOD,
	EFFECT_MISS,

};
#endif