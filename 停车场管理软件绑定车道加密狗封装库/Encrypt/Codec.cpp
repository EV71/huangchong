#include "Codec.h"
CCodec::CCodec()
{
	m_nStrLen = 0;
	memset( m_pStr,0,sizeof( m_pStr ) );
	memset( m_pKey,0,sizeof( m_pKey ) );
	memcpy( m_pKey,KEY_STR,MAX_CODE_KEY_LEN);
}

CCodec::~CCodec()
{
	
}
/****************************************************************************************************
* @��������:	SetData
* @��  �ܣ�		���ü��ܽ��ܹ����е���Կ
* @��  ����		
* @pKey			��Կָ��
* @nLen			��Կ����					
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		
****************************************************************************************************/
HRESULT CCodec::InitializeKey( const BYTE * pKey,int nLen )
{
	if( NULL == pKey )
	{
		return CODEC_INITKEY_ERROR_BUF_OUT;
	}
	if(	 nLen <=0 || nLen >=MAX_CODE_KEY_LEN )
	{
		return CODEC_INITKEY_ERROR_BUF_OUT;
	}
	memcpy( m_pKey,pKey,nLen );
	return S_OK;
}
/****************************************************************************************************
* @��������:	SetEncryptData
* @��  �ܣ�		������Ҫ���ܵ�����Դ
* @��  ����		
* @pString		����Դָ��
* @nLen         ����Դ����
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		��Ҫ���ܵĶ���������buf��
****************************************************************************************************/

HRESULT CCodec::SetCryptData( const BYTE * pString ,int nLen )
{
	if( NULL == pString )
	{
		return CODEC_CRYPT_EROR_BUF_NULL;
	}
	if( nLen <=0 || nLen >=MAX_CODE_LEN )
	{
		return CODEC_CRYPT_ERROR_BUF_OUT;
	}
	m_nStrLen = nLen;
	memcpy( m_pStr,pString,nLen );
	return S_OK;
}
/****************************************************************************************************
* @��������:	GetCryptData
* @��  �ܣ�		��ȡ����
* @��  ����		
* @pString		�������������ָ��
* @nLen         ������������ݳ���
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		�Ӽ���BUF�л�ȡ����
****************************************************************************************************/
HRESULT CCodec::GetCryptData( BYTE * const pString ,int &nLen )
{
	if( NULL == pString )
	{
		return -1;
	}
	memcpy( pString,m_pStr,m_nStrLen );
	nLen = m_nStrLen;
	return S_OK;
}
/****************************************************************************************************
* @��������:	Encrypt
* @��  �ܣ�		��������
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		������Դ�е����ݽ��м��� 
****************************************************************************************************/
HRESULT  CCodec::Encrypt( )
{
	BYTE nData = 0;
	for( int i=0;i<MAX_CODE_LEN;i++ )
	{
		nData = m_pKey[ i%MAX_CODE_KEY_LEN ];
		m_pStr[i] += nData;
	}

	return S_OK;
}
/****************************************************************************************************
* @��������:	Decrypt
* @��  �ܣ�		��������
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		������Դ�е����ݽ��н��� 
				��������˳��    InitializeKey->SetData->Encrypt ->Decrypt  	
****************************************************************************************************/
HRESULT CCodec:: Decrypt( )
{
	BYTE nData = 0;
	for( int i=0;i<MAX_CODE_LEN;i++ )
	{
		nData = m_pKey[ i%MAX_CODE_KEY_LEN ];
		m_pStr[i] -= nData;
	}
	return  S_OK;
}