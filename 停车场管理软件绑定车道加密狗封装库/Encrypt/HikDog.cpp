#include "HikDog.h"
#include "HikDate.h"
CHikDog::CHikDog()
{
	//InitAllParam();
}
CHikDog::~CHikDog()
{

}
/****************************************************************************************************
* @��������:	ReadData
* @��  �ܣ�		��ȡ���ܹ���Ϣ�������ɺ������ܹ���ʽ
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		����--->���ܹ�--->��ȡ������Ϣ
****************************************************************************************************/
HRESULT CHikDog::ReadData()
{	

	if( S_OK != CDog::ReadData() )							//˳��3
	{
		//WriteLog("������-��ȡ����ʧ��");
		return -1;
	}

	if( S_OK != Decrypt() )									//˳��2
	{
		//WriteLog("������-��ȡ���ݺ����ʧ��");
		return -2;
	}

	if( S_OK != GetHikInfo() )								//˳��1
	{
		//WriteLog("������-��ȡ���ݺ��ȡ������Ϣʧ��");
		return -3;
	}
	
	return S_OK;
}
/****************************************************************************************************
* @��������:	WriteData
* @��  �ܣ�		������д����ܹ�
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		��ȡ������Ϣ--->��������--->д��
****************************************************************************************************/
HRESULT CHikDog::WriteData()
{
	if( S_OK != SetHikInfo() )								//˳��1
	{		
		//WriteLog("������-���û�����Ϣʧ��");
		return S_FALSE;
	}

	if( S_OK != Encrypt() )									//˳��2
	{
		//WriteLog("������-��������ʧ��");
		return S_FALSE;
	}

	if( S_OK != CDog::WriteData() )						//˳��3
	{
		//WriteLog("������-д����ʧ��");
		return  S_FALSE;
	}
	return  S_OK;
}
/****************************************************************************************************
* @��������:	WriteData
* @��  �ܣ�		����������Ϣ
* @��  ����		��
* @����ֵ��		S_OK �ɹ�
* @˵  ����		���Ѷ�ȡ��Ϣ�Ļ������н���������Ϣ
****************************************************************************************************/

HRESULT CHikDog::GetHikInfo( )
{
	memcpy( &m_InfoHeader,m_pMemoryBuf,sizeof( m_InfoHeader ) );
	memcpy( &m_InfoBody,m_pMemoryBuf+m_InfoHeader.m_BaseInfoAddr ,sizeof( m_InfoBody ) );
	return S_OK;
}
/****************************************************************************************************
* @��������:	SetHikInfo
* @��  �ܣ�		����������Ϣ
* @��  ����		��
* @����ֵ��		S_OK �ɹ�
* @˵  ����		��������Ϣд���д������
****************************************************************************************************/

HRESULT CHikDog::SetHikInfo( )
{
	HRESULT hr = S_OK;
	memcpy( m_pMemoryBuf,&m_InfoHeader,sizeof( m_InfoHeader ) );
	memcpy( m_pMemoryBuf+m_InfoHeader.m_BaseInfoAddr,&m_InfoBody,sizeof( m_InfoBody ) );
	return  hr;
}

/****************************************************************************************************
* @��������:	Encrypt
* @��  �ܣ�		�Դ�д���������м���
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		
****************************************************************************************************/
HRESULT CHikDog::Encrypt()
{
	HRESULT hr = S_OK;

	//���ü��ܶ���
	hr = SetCryptData( m_pMemoryBuf,m_BufLen );
	if( S_OK != hr )
	{
		//WriteLog("������--���ü������ݴ���");
		return hr;
	}
	//��ʼ����
	hr = CCodec::Encrypt();
	if( S_OK != hr )
	{
		//WriteLog("������--�������ݴ���");
		return hr;
	}
	//��ȡ���ܺ����Ϣ
	hr = GetCryptData( m_pMemoryBuf ,m_BufLen );
	if( hr != S_OK )
	{
		//WriteLog("������--��ȡ���ܺ�����ݴ���");
		return hr;
	}

	return  hr;
}
/****************************************************************************************************
* @��������:	Decrypt
* @��  �ܣ�		�Զ�ȡ�������ݻ��������н���
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		
****************************************************************************************************/
HRESULT CHikDog::Decrypt()
{
	HRESULT hr = S_OK;
	//���ý��ܶ���
	hr = SetCryptData( m_pMemoryBuf,m_BufLen );
	if( S_OK != hr )
	{
		//WriteLog("������--���ý�������ʧ��");
		return hr;
	}
	//���ݽ���
	hr = CCodec::Decrypt();
	if( S_OK != hr )
	{
		//WriteLog("������--��������ʧ��");
		return hr;
		
	}
	//��ȡ���ܺ����Ϣ
	hr = GetCryptData( m_pMemoryBuf,m_BufLen );
	if( S_OK != hr )
	{
		//WriteLog("������--��ȡ���ܺ������ʧ��");
		return hr;
	}

	return  hr;
}
HRESULT CHikDog::InitAllParam( )
{
	memset( &m_InfoBody,0,sizeof(  m_InfoBody ) );
	memset( &m_InfoHeader,0,sizeof( m_InfoHeader ) );
	m_InfoHeader.m_BaseInfoAddr = 0x00 +sizeof( INFO_HEADER );
	m_InfoHeader.m_BaseInfoLen = sizeof( BASEINFO_BODY );
	m_InfoHeader.m_CustomInfoAddr = m_InfoHeader.m_BaseInfoAddr + m_InfoHeader.m_BaseInfoLen;
	m_InfoHeader.m_CustomInfoLen = 0;
	memset( m_InfoHeader.m_Resver1,0,sizeof( m_InfoHeader.m_Resver1 ) );
	//������Ϣ
	memcpy( m_InfoBody.m_CompanyName,HIK_COMPANY_NAME,4 );
	memset( m_pStr,0,sizeof( m_pStr ) );
	//����ͷ+������Ϣ+��Ƶ�羯��Ϣ+У��λ
	m_BufLen = sizeof( m_InfoHeader )+sizeof( m_InfoBody )  + 1;//

	return S_OK;
}
/****************************************************************************************************
* @��������:	CheckDogBind
* @��  �ܣ�		����Ӳ���Ƿ񱻰�
* @��  ����		��				
* @����ֵ��		S_OK �Ѿ���������  -1 ��ȡ���ܹ�ʧ�� -2 δ�� 
				-3 ��ȡӲ����Ϣʧ�� -4 �������ĵ��԰�			
* @˵  ����		
****************************************************************************************************/
HRESULT CHikDog::CheckDogBind( )
{
	//��������  �ж��Ƿ��
	if( S_OK != ReadData() )
	{
		//WriteLog("������-�����ʱ��ȡ��ʧ��");
		return -1;
	}
	/*if(  m_InfoBody.m_bBind != TRUE )
	{
		WriteLog("��δ��");
		return -2;
	}*/
	//�����ȡ����Ӳ��IDʧ��
	/*if( S_OK != GetHardWareInfo( ) )
	{
		WriteLog("������-�����ʱ��ȡӲ����Ϣʧ��");
		return -3;
	}
	//����������ĵ��԰�
	/*if( 0 != memcmp( m_HardWareInfo,m_InfoBody.m_HareWareID,MAX_INFO_LEN ) )
	{
		WriteLog("������-�󶨵�Ӳ���뱾��Ӳ��ID��ƥ��");
		return -4;
	}*/
	/*if( TRUE == ISDateOff( m_InfoBody.m_BindDate,m_InfoBody.m_UseDays ) )
	{
		WriteLog("������-ʹ�����ڵ���");
		return -5;
	}*/
	return  S_OK;
	
}
/****************************************************************************************************
* @��������:	BindDog
* @��  �ܣ�		�����ܹ��뱾�����Խ��а�
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		д ����-�󶨱��-Ӳ��ID-������Ϣ-����-д��
****************************************************************************************************/
HRESULT CHikDog::BindDog( )
{
	HRESULT hr = S_OK;
	
	hr = CHikDog::CheckDogBind( );
	//����Ѿ��� -- ����S_OK
	if( S_OK == hr  )
	{
		return hr;
	}
	///�������δ��
	if( -2 != hr )
	{
		return hr;
	}
	//���δ��
	 
	struct tm  when; 
	time_t  now; 
	WORD  nYear = 0;
	//�����Ҫ��
	m_InfoBody.m_bBind = TRUE;
	
	//��¼������
	time(   &now   ); 
	localtime_s( &when,&now   );  
	//2011  08  20 [2011(2�ֽ�)][08(1�ֽ�)][20(1�ֽ�)] ��4���ֽ�
	nYear = when.tm_year+1900;
	m_InfoBody.m_BindDate[0] = nYear/100;
	m_InfoBody.m_BindDate[1] = nYear%100;
	m_InfoBody.m_BindDate[2] = when.tm_mon+1;
	m_InfoBody.m_BindDate[3] = when.tm_mday;
	
	//���Ӳ��ID
	/*hr = GetHardWareInfo();
	if( S_OK != hr )
	{
		return hr;
	}
	memcpy( m_InfoBody.m_HareWareID,m_HardWareInfo,MAX_INFO_LEN );*/
	//����
	hr = SetHikInfo();
	if( S_OK != hr )
	{
		return  hr;
	}
	//д��
	hr = WriteData();
	if( S_OK != hr )
	{
		return  hr;
	}

	return  hr;
}
/****************************************************************************************************
* @��������:	ISDateOff
* @��  �ܣ�		�ж���Ȩ�޷����
* @��  ����		TRUE
* @����ֵ��		TRUE ����  FALSE δ����
* @˵  ����		
****************************************************************************************************/
BOOL CHikDog::ISDateOff( BYTE nDate[4] ,WORD nDays )
{
	struct tm  tmNow; 
	time_t  nNow; 
	time( &nNow ); 
	localtime_s( &tmNow,&nNow);  
	tmNow.tm_year += 1900;

	date dNow,dBegin;
	dNow.year = tmNow.tm_year;
	dNow.month = tmNow.tm_mon+1;
	dNow.day = tmNow.tm_mday;
	
	dBegin.year = 100*nDate[0]+nDate[1];
	dBegin.month = nDate[2];
	dBegin.day = nDate[3];
	int nDayElaps = DaysBetweenDate( dBegin,dNow );
	if(!( dNow.year == dBegin.year &&
		dNow.month == dBegin.month && 
		dNow.day == dBegin.day ) )
	{
		if( nDayElaps >= nDays || 0 == nDayElaps )
		{
			return TRUE;
		}	
	}
	
	return FALSE;
}