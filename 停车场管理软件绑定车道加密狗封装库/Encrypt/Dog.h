#ifndef __DOG_H__
#define __DOG_H__
#include "gsmh.h"
#include "Encrypt.h"
#include "Log.h"

class   CDog:public CLog
{
public:
	//�������ܹ�����ڴ�����
	#define MAX_DOG_MEMORY_LEN  300
	//�ɹ�д���˽���ֽ���
	#define MAX_PRIVATE_MEMORY_LEN 0x80
		CDog();	
		~CDog();
	protected:
		//��ȡ����
		virtual HRESULT ReadData( );
		//д����
		virtual HRESULT WriteData(  );
		//У���
		virtual HRESULT CheckSum( );
		//����У���
		virtual HRESULT SetSum( );

		BYTE  m_pMemoryBuf[ MAX_DOG_MEMORY_LEN ];
		int  m_BufLen;
};

#endif //__DOG_H__