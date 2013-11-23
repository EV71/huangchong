#ifndef  __CODEC_H__
#define  __CODEC_H__
#include "Encrypt.h"


class  CCodec
{

public:
#define KEY_STR "0123456789abcdefg"
#define MAX_CODE_KEY_LEN	18
#define MAX_CODE_LEN		1000

	CCodec();
		~CCodec();
		//װ����Կ
		HRESULT InitializeKey( const BYTE * pKey,int nLen );
		//������Դ����
		HRESULT SetCryptData( const BYTE * pString ,int nLen );
		//�õ���Դ����
		HRESULT GetCryptData( BYTE * const pString ,int &nLen );
		//���ܺ���
		HRESULT Encrypt( );
		//���ܺ���
		HRESULT Decrypt( );

	protected:
		//��Կ
		BYTE m_pKey[ MAX_CODE_KEY_LEN ];
		//������ݵĿռ�
		BYTE m_pStr[ MAX_CODE_LEN ] ;
		//���ݳ���
		int  m_nStrLen;
};



#endif//__CODEC_H__