#include "StdAfx.h"
#include "BufferManager.h"

CBufferManager::CBufferManager(void):
	m_nPicIndex(0)
	,m_nPlateIndex(0)
	,m_hMutexPlate(NULL)
	,m_bEmpty(TRUE)
{
	m_vPlateInfo.clear();
	m_vPicBuf.clear();
	m_vFlag.clear();
}

CBufferManager::~CBufferManager(void)
{
	ClearBufferManage();	
}

/** @fn		void CBufferManager::InitBufferManage()
 *	@brief	��ʼBuffer
 *	@return	bool	true��ʾ�ɹ�������ʧ��
 */
bool CBufferManager::InitBufferManage()
{
	if (m_vPlateInfo.empty() == TRUE)
	{
		//�����б�Ϊ�յ�ʱ�򴴽�
		for (int i = 0; i < SCCP_MAX_PLATEINFO_NUM; i ++)
		{
			LPNET_DVR_PLATE_RESULT pPlateInfo = NULL;
			try
			{
				pPlateInfo = new NET_DVR_PLATE_RESULT;
			}
			catch (...)
			{
				return false;
			}
			if (pPlateInfo != NULL)
			{
				m_vPlateInfo.push_back(pPlateInfo);
				m_vFlag.push_back(true);
			}
		}
		m_nPlateIndex = 0;
		m_bEmpty = TRUE;
	}
	if (m_vPicBuf.empty() == TRUE)
	{
		// ͼƬ�б�Ϊ��ʱ����
		for (int i = 0; i < SCCP_MAX_PIC_NUM; i ++)
		{
			char	*pBuf = NULL;
			try
			{
				pBuf = new char[SCCP_MAX_PIC_SIZE];
			}
			catch (...)
			{
				return false;
			}
			if (pBuf != NULL)
			{
				m_vPicBuf.push_back(pBuf);
			}
		}
		m_nPicIndex = 0;
	}

	if (m_hMutexPlate == NULL)
	{
		m_hMutexPlate = CreateMutex(NULL, FALSE, NULL);
		if (m_hMutexPlate == NULL)
		{
			return false;
		}
	}
	return true;
}

/** @fn		bool CBufferManager::InsertPlateInfo(LPNET_DVR_PLATE_RESULT pPlateInfo)
 *	@brief	���복����Ϣ
 *	@param	[IN]	pPlateInfo	������Ϣ
 *	@return	true��ʾ�ɹ�������ʧ��
 */
bool CBufferManager::InsertPlateInfo(LPNET_DVR_PLATE_RESULT pPlateInfo)
{
	if (pPlateInfo == NULL)
	{
		return false;
	}
	if (WaitForSingleObject(m_hMutexPlate, INFINITE) != WAIT_OBJECT_0)
	{
		return false;
	}
	int nIndex = m_nPlateIndex;
	if (m_vPlateInfo[m_nPlateIndex] != NULL)
	{
		// ���복����Ϣ
		ZeroMemory(m_vPlateInfo[m_nPlateIndex],sizeof(NET_DVR_PLATE_RESULT));
		memcpy(m_vPlateInfo[m_nPlateIndex], pPlateInfo, sizeof(NET_DVR_PLATE_RESULT));
		m_vFlag[m_nPlateIndex] = false;
		m_nPlateIndex = (m_nPlateIndex + 1) % SCCP_MAX_PLATEINFO_NUM;
		m_bEmpty = FALSE;
	}
	m_nPicIndex = 0;
	if (pPlateInfo->pBuffer1 != NULL && pPlateInfo->dwPicLen != 0)
	{
		// ���ý���ͼ
		if (m_vPicBuf[m_nPicIndex] != NULL)
		{
			memset(m_vPicBuf[m_nPicIndex],0,SCCP_MAX_PIC_SIZE);
			memcpy(m_vPicBuf[m_nPicIndex], pPlateInfo->pBuffer1, pPlateInfo->dwPicLen);
			m_vPlateInfo[nIndex]->pBuffer1 = (BYTE*)m_vPicBuf[m_nPicIndex];
		}
	}
	m_nPicIndex = (m_nPicIndex + 1) % SCCP_MAX_PIC_NUM;
	if (pPlateInfo->pBuffer2 != NULL && pPlateInfo->dwPicPlateLen != 0)
	{
		//���ó��Ʋ�ͼ
		if (m_vPicBuf[m_nPicIndex] != NULL)
		{
			memset(m_vPicBuf[m_nPicIndex],0,SCCP_MAX_PIC_SIZE);
			memcpy(m_vPicBuf[m_nPicIndex], pPlateInfo->pBuffer2, pPlateInfo->dwPicPlateLen);
			m_vPlateInfo[nIndex]->pBuffer2 = (BYTE*)m_vPicBuf[m_nPicIndex];
		}
	}
	m_nPicIndex = (m_nPicIndex + 1) % SCCP_MAX_PIC_NUM;
	if (pPlateInfo->pBuffer3 != NULL && pPlateInfo->dwBinPicLen != 0)
	{
		//���ó��ƶ�ֵͼ
		if (m_vPicBuf[m_nPicIndex] != NULL)
		{
			memset(m_vPicBuf[m_nPicIndex],0,SCCP_MAX_PIC_SIZE);
			memcpy(m_vPicBuf[m_nPicIndex], pPlateInfo->pBuffer3, pPlateInfo->dwBinPicLen);
			m_vPlateInfo[nIndex]->pBuffer3 = (BYTE*)m_vPicBuf[m_nPicIndex];
		}
	}
	m_nPicIndex = (m_nPicIndex + 1) % SCCP_MAX_PIC_NUM;
	if (pPlateInfo->pBuffer4 != NULL && pPlateInfo->dwCarPicLen != 0)
	{
		//���ó���ԭͼ
		if (m_vPicBuf[m_nPicIndex] != NULL)
		{
			memset(m_vPicBuf[m_nPicIndex],0,SCCP_MAX_PIC_SIZE);
			memcpy(m_vPicBuf[m_nPicIndex], pPlateInfo->pBuffer4, pPlateInfo->dwCarPicLen);
			m_vPlateInfo[nIndex]->pBuffer4 = (BYTE*)m_vPicBuf[m_nPicIndex];
		}
	}
	m_nPicIndex = (m_nPicIndex + 1) % SCCP_MAX_PIC_NUM;
	if (pPlateInfo->pBuffer5 != NULL && pPlateInfo->dwFarCarPicLen != 0)
	{
		//����Զ��ͼ
		if (m_vPicBuf[m_nPicIndex] != NULL)
		{
			memset(m_vPicBuf[m_nPicIndex],0,SCCP_MAX_PIC_SIZE);
			memcpy(m_vPicBuf[m_nPicIndex], pPlateInfo->pBuffer5, pPlateInfo->dwFarCarPicLen);
			m_vPlateInfo[nIndex]->pBuffer5 = (BYTE*)m_vPicBuf[m_nPicIndex];
		}
	}
	m_nPicIndex = (m_nPicIndex + 1) % SCCP_MAX_PIC_NUM;
	ReleaseMutex(m_hMutexPlate);
	return true;
}

/** @fn		bool CBufferManager::GetPlateInfo(LPNET_DVR_PLATE_RESULT pPlateInfo)
 *	@biref	��ȡ������Ϣ
 *	@param	[OUT]	pPlateInfo	������Ϣ
 *	@return	bool	true��ʾ�ɹ�������ʧ��
 */
bool CBufferManager::GetPlateInfo(LPNET_DVR_PLATE_RESULT pPlateInfo)
{
	if (pPlateInfo == NULL)
	{
		return false;
	}

	if (WaitForSingleObject(m_hMutexPlate, INFINITE) != WAIT_OBJECT_0)
	{
		return false;
	}

	if (m_bEmpty == TRUE)
	{
		ReleaseMutex(m_hMutexPlate);
		return false;
	}
	int			iIndex = m_nPlateIndex -1;
	if (iIndex == -1)
	{
		iIndex = SCCP_MAX_PLATEINFO_NUM - 1;
	}

	if (m_vPlateInfo[iIndex] != NULL)
	{
		memcpy(pPlateInfo, m_vPlateInfo[iIndex], sizeof(NET_DVR_PLATE_RESULT));
		m_vFlag[iIndex] = true;
	}
	ReleaseMutex(m_hMutexPlate);
	return true;
}

/** @fn		void CBufferManager::ClearBufferManage()
 *	@brief	��ջ���
 *	@return	void
 */
void CBufferManager::ClearBufferManage()
{
	std::vector<LPNET_DVR_PLATE_RESULT>::iterator	iterPlate;
	std::vector<char*>::iterator					iterPic;

	for (iterPlate = m_vPlateInfo.begin(); iterPlate != m_vPlateInfo.end(); iterPlate ++)
	{
		if (*iterPlate!= NULL)
		{
			delete *iterPlate;
		}
	}
	for (iterPic = m_vPicBuf.begin(); iterPic != m_vPicBuf.end(); iterPic ++)
	{
		if (*iterPic != NULL)
		{
			delete [](*iterPic);
		}
	}
	
	m_vPicBuf.clear();
	m_vPlateInfo.clear();
	m_vFlag.clear();
	if (m_hMutexPlate != NULL)
	{
		CloseHandle(m_hMutexPlate);
		m_hMutexPlate = NULL;
	}
}