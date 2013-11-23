#ifndef  __LOG_H__
#define  __LOG_H__
#include "Encrypt.h"

class  CLog
{
	#define  MAX_LOG_MSG_SIZE 1024
	#define  MAX_LOG_SIZE 5*1024*1024
	#define  LOG_FILE_NAME ""//"CryptLog.txt"
	#define  LOG_FILE_LEN  ( strlen( LOG_FILE_NAME ) )
	public:
		CLog();
		~CLog();
		//ֱ��д��־
		virtual HRESULT WriteLog( const char * pChError );
	public:
		//���������Ϣ����
		virtual HRESULT PostError( HRESULT nError );
	private:
		//���������Ϣ
		virtual HRESULT TranslateError( HRESULT nError );
		//����־��Ϣд���ļ�
		virtual HRESULT  WriteError( void );
	
	protected:
		//������Ϣ�洢�ռ�
		char m_pMsgBuf[ MAX_LOG_MSG_SIZE ];
		//��־�ļ�ָ��
		FILE *m_pFile;
		//��Ϣ����
		int  m_nMsgLen;
};






#endif	 __LOG_H__