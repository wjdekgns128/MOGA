#include "cKeyAsk.h"

cKeyAsk::cKeyAsk()
{
	m_KeyTimeChk			= false ;
	m_KeyTime				= GetTickCount() ;
	m_KeyDoubleTime			= GetTickCount() ;

	ZeroMemory(m_KeyDownChk, sizeof(m_KeyDownChk)) ;
	ZeroMemory(m_KeyDoubleTimeChk, sizeof(m_KeyDoubleTimeChk)) ;
}

cKeyAsk::~cKeyAsk()
{
}

bool cKeyAsk::KeyDown(int vk)
{
	if( KeyDownChk(vk) )
	{
		if( vk >= 37 && vk <= 40 )							// VK_LEFT ~ VK_RIGHT ����Ű 4���� �ƽ�Ű ��
		{
			m_KeyDownChk[vk-37] = true ;
			return true ;
		}

		else if( vk >= 48 && vk <= 90 )						// ����Ű 0~1�� ���ĺ� A~Z�� �ƽ�Ű ��
		{
			m_KeyDownChk[vk-45] = true ;
			return true ;
		}
	}

	return false ;
}

bool cKeyAsk::KeyUp(int vk)
{
	if( KeyUpChk(vk) )
	{
		if( vk >= 37 && vk <= 40 && m_KeyDownChk[vk-37] )			// VK_LEFT ~ VK_RIGHT ����Ű 4���� �ƽ�Ű ��
		{
			m_KeyDownChk[vk-37] = false ;
			return true ;
		}

		else if( vk >= 48 && vk <= 90 && m_KeyDownChk[vk-45] )		// ����Ű 0~1�� ���ĺ� A~Z�� �ƽ�Ű ��
		{
			m_KeyDownChk[vk-45] = false ;
			return true ;
		}
	}

	return false ;
}

bool cKeyAsk::LongTimeKeyDown( int vk, float time )
{
	time *= 1000 ;

	if( KeyDownChk(vk) )
	{
		if(!m_KeyTimeChk)
		{
			m_KeyTimeChk = true ;
			m_KeyTime = GetTickCount() ;
		}

		else if( GetTickCount() - m_KeyTime > (unsigned)time && m_KeyTimeChk  )
		{
			m_KeyTimeChk = false ;
			return true ;
		}
	}

	if( KeyUpChk(vk) )
		m_KeyTimeChk = false ;

	return false ;
}

bool cKeyAsk::DoubleKeyDown( int vk, float time )
{
	static DWORD			DelayTime = GetTickCount() ;						// �ι� �Է� �Ϸ�� �ٽ� �Է��Ҷ� �����̸� �ֱ� ���� �ð� ��Soo

	time *= 1000 ;

	if( KeyDownChk(vk) )
	{
		if( GetTickCount() - DelayTime > 100 && !m_KeyDoubleTimeChk[0] && !m_KeyDoubleTimeChk[1] )
			m_KeyDoubleTimeChk[0] = true ;

		else if( GetTickCount() - m_KeyDoubleTime < (unsigned)time && m_KeyDoubleTimeChk[1] )
		{
			m_KeyDoubleTimeChk[1] = false ;
			DelayTime = GetTickCount() ;
			return true ;
		}

		else if( GetTickCount() - m_KeyDoubleTime > (unsigned)time && m_KeyDoubleTimeChk[1] )
			m_KeyDoubleTimeChk[1] = false ;
	}

	if( KeyUpChk(vk) )
	{
		if( m_KeyDoubleTimeChk[0] )
		{
			m_KeyDoubleTimeChk[0] = false ;
			m_KeyDoubleTimeChk[1] = true ;
			m_KeyDoubleTime = GetTickCount() ;
		}
	}

	return false ;
}

