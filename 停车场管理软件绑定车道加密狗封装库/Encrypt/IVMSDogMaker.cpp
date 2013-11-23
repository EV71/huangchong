#include "IVMSDogMaker.h"

CIVMSDogMaker::CIVMSDogMaker()
{
	
}
CIVMSDogMaker::~CIVMSDogMaker()
{
}
/****************************************************************************************************
* @��������:	MakePRDog
* @��  �ܣ�		������Ƶ������¼�Ǽ��ܹ�
* @��  ����		
* @wDays		ʹ������
* @nChannels	ͨ����
* @nLanes		������
* @nPlatForm	ƽ̨����
* @nChannelType	ͨ������
* @����ֵ��		S_OK �����ɹ� 
* @˵  ����		
****************************************************************************************************/
HRESULT CIVMSDogMaker::MakePRDog( 
					   WORD wDays,
					   BYTE nChannels,
					   BYTE nLanes,
					   BYTE nPlatForm,
					   BYTE nChannelType  )
{
	HRESULT hr = S_OK;
	memset( m_pMemoryBuf,0,sizeof(m_pMemoryBuf) );
	hr = CIVMSDog::ReadData();
	InitAllParam( );
	if( S_OK != hr  )
	{
		return hr;
	}
	m_InfoBody.m_bBind = FALSE;
	m_InfoBody.m_UseDays = wDays;
	m_CustomInfo.m_nChannels = nChannels;
	m_CustomInfo.m_nLanes = nLanes;
	m_CustomInfo.m_bConnPlatForm = nPlatForm;
	m_CustomInfo.m_nChannelType = nChannelType;
	m_CustomInfo.m_nResverd3[0] = 0xf0;
	hr = WriteData();
	return hr;
}

/****************************************************************************************************
* @��������:	MakeFRDog
* @��  �ܣ�		������Ƶ������¼�Ǽ��ܹ�
* @��  ����		
* @wDays		ʹ������
* @nChannels	ͨ����
* @nLanes		������
* @nPlatForm	ƽ̨����
* @nChannelType	ͨ������
* @����ֵ��		S_OK �����ɹ� 
* @˵  ����		
****************************************************************************************************/
HRESULT CIVMSDogMaker::MakeFRDog( 
					   WORD wDays,
					   BYTE nChannelsFace,
					   BYTE nLanesFace,
					   BYTE nPlatFormFace,
					   BYTE nChannelTypeFace  )
{
	HRESULT hr = S_OK;
	memset( m_pMemoryBuf,0,sizeof(m_pMemoryBuf) );
	hr = CIVMSDog::ReadData();
	InitAllParam( );
	if( S_OK != hr  )
	{
		return hr;
	}
	m_InfoBody.m_bBind = FALSE;
	m_InfoBody.m_UseDays = wDays;
	m_CustomInfo.m_nChannelsFace= nChannelsFace;
	m_CustomInfo.m_nLanesFace= nLanesFace;
	m_CustomInfo.m_bConnPlatFormFace= nPlatFormFace;
	m_CustomInfo.m_nChannelTypeFace= nChannelTypeFace;
	m_CustomInfo.m_nResverd3[0] = 0xf0;
	hr = WriteData();
	return hr;
}

/****************************************************************************************************
* @��������:	MakeDog
* @��  �ܣ�		������Ƶ������¼�Ǽ��ܹ�
* @��  ����		
* @nChannelsPlate	��ʶͨ����
* @nChannelsFace ����ʶ��ͨ����
* @nPlatForm			�豸����
* @����ֵ��		S_OK �����ɹ� 
* @˵  ����		
****************************************************************************************************/
HRESULT CIVMSDogMaker::MakeDog( 
								 BYTE nChannelsPlate,
								 BYTE nChannelsFace,
								 BYTE nPlatForm)
{
	HRESULT hr = S_OK;
	memset( m_pMemoryBuf,0,sizeof(m_pMemoryBuf) );
	hr = CIVMSDog::ReadData();
	InitAllParam( );
	if( S_OK != hr  )
	{
		return hr;
	}
	m_InfoBody.m_bBind = FALSE;
	m_CustomInfo.m_nChannels = nChannelsPlate;
	m_CustomInfo.m_nChannelsFace= nChannelsFace;
	m_CustomInfo.m_bConnPlatForm= nPlatForm;
	m_CustomInfo.m_nResverd3[0] = 0xf0;
	hr = WriteData();
	return hr;
}

					
