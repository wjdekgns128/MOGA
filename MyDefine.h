#ifndef _MYDEFINE_H
#define _MYDEFINE_H



#define	SCORE cMain()->g_score					// ����  �������� ++ ���ָ�ǰ���	
#define	NOWNODE	cMain()->g_nownode				// ������ ��Ʈ�Ǽ� ���� ���ֹ�����  �̰� �Ѱ��� ++;
#define	MAXNODE	cMain()->g_maxnode				// �̰� �Ѱ���      �����ڿ��ٰ� MAXNODE = �ѳ�Ʈ����  // �߸𸣰����� ������Ʈ .CPP ����
#define	MAXPERFECT		cMain()->g_perfect
#define	MAXGOOD			cMain()->g_good	
#define	MAXMISS			cMain()->g_miss
#define	MAXCOMBO		cMain()->g_maxcombo
//////���� 3���� ���� ������ �����ϴٰ� �ٽ� ���Ǽ���â���� ���������׵� �װ��Ҷ� *�ʱ�ȭ�ؾ���* 
#define MUSIC cMain()->g_MusicState
#define JUST  1
#define SWAGGA 2
#define PRACTICE 3 // Ʃ�丮�� �� 
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


///��ũ
#define F		7
#define E		6
#define	D		5
#define	C		4
#define	B		3
#define	A		2
#define	S		1
///// �̸��ٲٸ��
#define GAME	1
#define HELP	2
#define	CREATE		3
#define	QUIT		4

// �巳�޺�
#define DRUMCOMBO cMain()->g_DrumCombo

#define LAYER1 0
#define LAYER2 1
#define LAYER3 2
#define LAYER4 3
#define LAYER5 4 



// ��ũ �
#define NUMBE_MAX 10



enum
{
	EFFECT_PERFECT = 0,
	EFFECT_COOL,
	EFFECT_GOOD,
	EFFECT_MISS,

};
#endif