#pragma once

#define Key_Default 0
#define Key_Down 1
#define Key_Up 2
#define Key_LongDown 3
#define Key_LongUp 4


enum
{
	DOWN = 5,
	UP,
	LEFT,
	RIGHT,
	ATTACK,
};

class cKey
{
private:
	int						keyList[256];
	int						keySetting[256];	//0 : default, 1 : 눌러져다 땟을때
	DWORD					Key_Time;
	bool					Key_Time_Check;
	bool					Key_Double_Check;
	bool					Key_Double_Check2;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	bool					Key_Double_Other_Check;
	DWORD					Key_Double_Time_Check;
	int						KeyTable[6][5]; //배열 행에 맨첫번째는 카운트
	int						KeyCheck[5];
	int						AniTable[4][5];
	int						count;
	
	

public:
	cKey();
	~cKey();
	bool					KeyLongDownPark(int vk, float time);
	bool					KeyDownPark(int vk);
	bool					KeyUpPark(int vk);
	bool					KeyDoubleDownPark(int vk);
	void					Load_Key(const WCHAR *pFileName);
	void					Decode_Key(FILE *stream);
	void					Load_Ani(const WCHAR *pFileName);
	void					Decode_Ani(FILE *stream);


};