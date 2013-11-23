#include "IVMSDog.h"
CIVMSDog::CIVMSDog()
{
	InitAllParam();
};

CIVMSDog::~CIVMSDog()
{

}
/****************************************************************************************************
* @��������:	ReadData
* @��  �ܣ�		��Ƶ������¼�Ƕ�������Ϣ
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		�ȶ�������Ϣ--->������Ƶ������¼�ǵ���Ϣ
****************************************************************************************************/
HRESULT CIVMSDog::ReadData()
{
	HRESULT hr = CHikDog::ReadData();
	if( S_OK != hr )
	{
		return -1;
	}
	hr = GetCustomInfo( );
	if( S_OK != hr  )
	{
		return -2;
	}
	return S_OK;
}
/****************************************************************************************************
* @��������:	ReadData
* @��  �ܣ�		��Ƶ������¼�Ƕ�д������Ϣ
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		���д��������Ƶ������¼�ǵ���Ϣ-->д��������Ϣ---->д��
****************************************************************************************************/
HRESULT CIVMSDog::WriteData()
{
	HRESULT hr = S_OK;
	hr = SetCustomInfo( );
	if( S_OK != hr  )
	{
		return hr;
	}

	hr = CHikDog::WriteData();
	if( S_OK != hr )
	{
		return hr;
	}
	
	return S_OK;
}
/****************************************************************************************************
* @��������:	GetCustomInfo
* @��  �ܣ�		��ȡ������Ϣ--��Ƶ������¼�ǵĲ���
* @��  ����		��
* @����ֵ��		S_OK �����ɹ� 
* @˵  ����		�ӽ�����Ϣbuf�г�ȡ��������Ϣ(��Ƶ������¼�ǵĲ���)
****************************************************************************************************/
HRESULT CIVMSDog::GetCustomInfo( )
{
	HRESULT hr = S_OK;
	memcpy( &m_CustomInfo,m_pMemoryBuf+m_InfoHeader.m_CustomInfoAddr,sizeof( m_CustomInfo ) );
	return hr;
}
/****************************************************************************************************
* @��������:	SetCustomInfo
* @��  �ܣ�		���ö�����Ϣ
* @��  ����		��
* @����ֵ��		S_OK �����ɹ� 
* @˵  ����		���д��������������Ƶ������¼�ǵĲ���
****************************************************************************************************/
HRESULT CIVMSDog::SetCustomInfo( )
{
	HRESULT hr = S_OK;
	memcpy( m_pMemoryBuf+m_InfoHeader.m_CustomInfoAddr,&m_CustomInfo,sizeof( m_CustomInfo ) );
	return hr;
}
HRESULT CIVMSDog::InitAllParam( )
{
	HRESULT hr = S_OK;
	hr = CHikDog::InitAllParam();
	m_InfoHeader.m_CustomInfoLen = (BYTE)sizeof( m_CustomInfo );
	memset( &m_CustomInfo,0,sizeof( m_CustomInfo ) );
	//����ͷ+������Ϣ+��Ƶ�羯��Ϣ+У��λ
	m_BufLen = sizeof( m_InfoHeader )+sizeof( m_InfoBody ) +sizeof( m_CustomInfo ) + 1;//
	return hr;
}