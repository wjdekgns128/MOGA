#include "MyInclude.h"


#define				Key_Default			0
#define				Key_Down			1
#define				Key_Up				2
#define				Key_LongDown		3
#define				Key_LongUp			4


inline int KeyDown	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 1:0 ); 
}


inline int KeyUp	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 0:1 ); 
}


cKey::cKey()
{
	for(int i=0; i<256; i++)
	{
		keyList[i]			= Key_Default;
		keySetting[i]		= Key_Default;
	}
	for( int i = 0 ; i < 5 ; i++ )
	{
		for( int j = 0 ; j < 6 ; j++ )
		{
		KeyTable[i][j]		= 0;
		}
		KeyCheck[i]			= 0;
	}
	for( int i = 0 ; i < 4 ; i++ )
	{
		for( int j = 0 ; j < 5 ; j++ )
		{
		AniTable[i][j]		= 0;
		}
	}
	Key_Time				= 0;
	Key_Time_Check			= 0;

	Key_Double_Check		= false;
	Key_Double_Check2		= false;
	Key_Double_Other_Check	= false;

	Key_Double_Time_Check	= 0;
	////////////////////////////////////////
	//Load_Key(L"key.txt");
	//Load_Ani(L"Animation.txt");
}


cKey::~cKey()
{
}


bool cKey::KeyDownPark(int vk)
{
	if(KeyDown(vk))
	{
		Key_Double_Other_Check = true;
		return keySetting[vk] = 1;
	}
	else
	{
		return keySetting[vk] = 0;
	}

	return keySetting[vk];

}

bool cKey::KeyUpPark(int vk)
{

	if(KeyUp(vk))
		return keySetting[vk] = 1;
	else
		return keySetting[vk] = 0;

	return keySetting[vk];

}


bool cKey::KeyLongDownPark(int vk, float time)
{
	
	if(KeyDown(vk))
	{
		if(Key_Time_Check == false)
		{
			Key_Time_Check = true;
			Key_Time = GetTickCount();
		}
		else if(GetTickCount() - Key_Time > time && Key_Time_Check)
		{
			Key_Time_Check = false;
			return keySetting[vk] = 1;
		}
	}
	else
		Key_Time_Check = false ;

	return keySetting[vk] = 0;
}


bool cKey::KeyDoubleDownPark(int vk)
{
	static DWORD			Key_Time = 0;
	
	if(KeyDown(vk))
	{
		if( !Key_Double_Check && !Key_Double_Check2 )
		{
			Key_Time = GetTickCount();
			Key_Double_Check = true;
		}
		else if( GetTickCount() - Key_Time < 200 && Key_Double_Check && Key_Double_Check2 && !Key_Double_Other_Check)
		{
			Key_Double_Other_Check = false;
			Key_Double_Check = false;
			Key_Time = 0;
			return keySetting[vk] = 1;
		}
	}

	if(KeyUp(vk))
	{
		if( Key_Double_Check && GetTickCount() - Key_Time < 200)
		{
			Key_Double_Check2 = true ;
		}
		else if( GetTickCount() - Key_Time > 200)
		{
			Key_Double_Other_Check = false;
			Key_Double_Check = false;
			Key_Double_Check2 = false ;
		}

	}
	return keySetting[vk] = 0;
}


void cKey::Load_Key(const WCHAR *pFileName)
{	
	FILE*				stream;
	WCHAR				strData[100];
	WCHAR				temp[100];

	stream				= _wfopen(pFileName, L"rt");

	if(stream == NULL)
		return;

	if(stream)
	{
		while( !feof(stream) )						//파일이 끝날때까지
		{
			fgetws(strData, 100, stream);			//stream을 읽어 strData에 집어넣음.
			swscanf(strData, L"%s", temp);			//strData를 temp에 집어넣음.


			if(wcscmp(L"[KEY]", temp) == 0)		//temp와 문자의 수를 비교 
			{
				Decode_Key(stream);
				break;
			}
		}
	}

}
void cKey::Decode_Key(FILE *stream)
{
	WCHAR					strData[100];

	if(fgetws(strData, 100, stream))
	{

		for( int i = 0 ; i < 5 ; i++ )
		{
				fgetws(strData, 100, stream) ;

				swscanf(strData, L"%d %d %d %d %d %d", &KeyTable[i][0], &KeyTable[i][1], 
					&KeyTable[i][2], &KeyTable[i][3], &KeyTable[i][4], &KeyTable[i][5]) ;
		}
		fclose(stream);
	}

}

void cKey::Load_Ani(const WCHAR *pFileName)
{	
	FILE*				stream;
	WCHAR				strData[100];
	WCHAR				temp[100];

	stream				= _wfopen(pFileName, L"rt");

	if(stream == NULL)
		return;

	if(stream)
	{
		while( !feof(stream) )						//파일이 끝날때까지
		{
			fgetws(strData, 100, stream);			//stream을 읽어 strData에 집어넣음.
			swscanf(strData, L"%s", temp);			//strData를 temp에 집어넣음.


			if(wcscmp(L"[ANIMATION]", temp) == 0)		//temp와 문자의 수를 비교 
			{
				Decode_Key(stream);
				break;
			}
		}
	}

}
void cKey::Decode_Ani(FILE *stream)
{
	WCHAR					strData[100];

	if(fgetws(strData, 100, stream))
	{

		for( int i = 0 ; i < 5 ; i++ )
		{
				fgetws(strData, 100, stream) ;

				swscanf(strData, L"%d %d %d %d", &AniTable[i][0], &AniTable[i][1], 
					&AniTable[i][2], &AniTable[i][3]) ;
		}
		fclose(stream);
	}

}
