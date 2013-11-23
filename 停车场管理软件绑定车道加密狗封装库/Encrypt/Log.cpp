#include "Log.h"
CLog::CLog()
{
	m_nMsgLen = 0;
	m_pFile = NULL;
	memset( m_pMsgBuf,0,sizeof( m_pMsgBuf ) );
}
CLog::~CLog()
{
	if( m_pFile != NULL )
	{
		fclose ( m_pFile );
	}
}
/****************************************************************************************************
 * @��������:	WriteError
 * @��  �ܣ�	��������Ϣд���ļ�
 * @��  ����	��
 * @����ֵ��	S_OK  �ɹ�  S_FALSE ʧ��
 * @˵  ����	����ʹ�ú��� �����⿪��
 ****************************************************************************************************/
HRESULT  CLog::WriteError(  )
{
	HRESULT hr = S_FALSE;

	if( NULL != m_pFile )
	{
		fprintf_s( m_pFile,m_pMsgBuf );
		hr = S_OK;
	}

	return hr;
}
/****************************************************************************************************
* @��������:PostError
* @��  �ܣ�	���������Ϣ
* @��  ����	
* @nError	�������
* @����ֵ��	S_OK  �ɹ�  S_FALSE ʧ��
* @˵  ����	����ʹ�ú��� �����⿪��
****************************************************************************************************/
HRESULT  CLog::PostError( HRESULT nError )
{

	HRESULT hr = S_FALSE;
	//�ȷ�����Ϣ
	hr = TranslateError( nError  );
	if( S_OK == hr )
	{
		//�ٴ�����Ϣ	
		hr = WriteError( );
	}
	
	return hr;
}
/****************************************************************************************************
* @��������:TranslateError
* @��  �ܣ�	���������Ϣ
* @��  ����	
* @nError	�������
* @����ֵ��	S_OK  �ɹ�  S_FALSE ʧ��
* @˵  ����	����ʹ�ú��� �����⿪��
****************************************************************************************************/
HRESULT CLog::TranslateError( HRESULT nError )
{
	int nLen = 0,nIndex = 0;
	HRESULT hr = S_FALSE;
	static char * szMsg[3] = {
							"�����ɹ�",
							"�ڴ����",
							"��������"};
	//////////////////////////////////////////////////////////////////////////


	//TODO:������ʵ��

	//////////////////////////////////////////////////////////////////////////
	if( nIndex < 0 && nIndex > 3 )
	{
		return hr;
	}
	
	nLen = (int)strlen( szMsg[ nIndex ] );
	if( nLen >=  MAX_LOG_MSG_SIZE )
	{
		return  hr;
	}
	strcpy_s( m_pMsgBuf,nLen,szMsg[ nIndex ] );
	
	m_nMsgLen = nLen;
	
	hr = S_OK;
	
	return hr;  
}
/****************************************************************************************************
* @��������:PostError
* @��  �ܣ�	���������Ϣ
* @��  ����	
* @nError	�������
* @����ֵ��	S_OK  �ɹ�  S_FALSE ʧ��
* @˵  ����	����ʹ�ú��� �����⿪��
****************************************************************************************************/
HRESULT CLog::WriteLog( const char * pChError )
{
	DWORD dwFileSize = 0;
	struct tm  when; 
	time_t  now; 
	WORD  nYear = 0;
	HRESULT hr = S_OK;
	if( NULL == m_pFile )
	{
		fopen_s( &m_pFile, LOG_FILE_NAME,"a");
		if( NULL == m_pFile )
		{
			return -1;
		}
	}

	fseek( m_pFile,0,SEEK_END);
	dwFileSize = ftell( m_pFile );
	//����ļ���С�������������
	if( dwFileSize > MAX_LOG_SIZE )
	{
		fclose( m_pFile );
		fopen_s( &m_pFile,LOG_FILE_NAME,"w");
		if( NULL == m_pFile ) 
		{
			return -2;
		}
	}
	time(   &now   ); 
	localtime_s( &when,&now   );  
	nYear = when.tm_year+1900;
	fprintf_s( m_pFile,"%4.4d%2.2d%2.2d %2.2d:%2.2d:%2.2d %s\n",		
				when.tm_year,when.tm_mon,when.tm_yday,
				when.tm_hour,when.tm_min,when.tm_sec,
				pChError );
	fclose( m_pFile );	
	m_pFile = NULL;
	return hr;
}
