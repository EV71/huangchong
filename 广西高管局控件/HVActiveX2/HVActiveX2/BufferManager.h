#pragma once
#include "stdafx.h"
#include <vector>
class CHVActiveX2Ctrl;
//#define LOCK_MUTEX

class CBufferManager
{
public:
	CBufferManager(void);
	~CBufferManager(void);
	// ��ʼ��buffer
	bool InitBufferManage();
	// ���복����Ϣ
	bool InsertPlateInfo(LPNET_DVR_PLATE_RESULT pPlateInfo,CHVActiveX2Ctrl *pHandle);
	// ��ȡ������Ϣ
	bool GetPlateInfo(LPNET_DVR_PLATE_RESULT pPlateInfo);
	// ��ȡͼƬBuffer��Ϣ
	char* GetPicBuffer(LONG lPicType);
	// ���buffer
	void ClearBufferManage();
private:
	std::vector<LPNET_DVR_PLATE_RESULT> m_vPlateInfo;			///< ������Ϣ
	std::vector<char *>					m_vPicBuf;				///< ͼƬbuf
	std::vector<bool>					m_vFlag;				///< ��Ǹó�����Ϣ�Ƿ��ȡ��
	ULONG								m_nPlateIndex;			///< ��������
	ULONG								m_nPicIndex;			///< ͼƬ����
	BOOL								m_bEmpty;				///< ������Ϣ�Ƿ�Ϊ��
#ifdef LOCK_MUTEX
	HANDLE								m_hMutexPlate;			///< ������Ϣ��
#else
	CRITICAL_SECTION					m_csLockPlate;
#endif
};
