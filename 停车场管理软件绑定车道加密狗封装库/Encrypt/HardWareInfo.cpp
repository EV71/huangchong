#include "HardWareInfo.h"

CHardWareInfo::CHardWareInfo()
{

}

CHardWareInfo::~CHardWareInfo()
{

}
/****************************************************************************************************
* @��������:	GetHardWareInfo
* @��  �ܣ�		��ȡӲ�����к�
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		Ӳ�����к���	MAX_INFO_LEN �ֽڵ����ݹ��� �ֱ���MAX_INFO_LEN/4���ȵ����ݴ洢
				cup���кš�Ӳ�����кš��������кš��������к�
****************************************************************************************************/
HRESULT CHardWareInfo::GetHardWareInfo()
{
	BYTE * pAddr = &m_HardWareInfo[0];
	UINT nLen = MAX_INFO_LEN/4;
	if( FALSE == GetCpuID() )
	{
		return -1;
	}
	if( FALSE == GetSerialNum() )
	{
		return -2;
	}
	if( FALSE == GetBios() )
	{
		return -3;
	}
	if( FALSE == GetMAcAddr() )
	{
		return -4;
	}
	memcpy( pAddr,m_CpuInfo,nLen );
	pAddr += nLen;
	memcpy( pAddr,m_SerialInfo,nLen );
	pAddr += nLen;
	memcpy( pAddr,m_BiosInfo,nLen );
	pAddr += nLen;
	memcpy( pAddr,m_MacInfo,nLen );
	pAddr += nLen;
	return S_OK;
}