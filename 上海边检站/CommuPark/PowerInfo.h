// PowerInfo.h: interface for the CPowerInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "Config.h"

#if !defined(AFX_POWERINFO_H__0A93100A_0600_4DC8_AEA0_4AEA6EF05887__INCLUDED_)
#define AFX_POWERINFO_H__0A93100A_0600_4DC8_AEA0_4AEA6EF05887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPowerInfo  
{
public:
	CPowerInfo();
//	CPowerInfo::CPowerInfo(CConfig config);

	static void Log(LPCTSTR lpType, LPCTSTR lpTitle, LPCTSTR lpEvent);
	static void WLog(LPCTSTR lpszMsg){AddLog(lpszMsg);}
	static void SaveLastLogFile(BOOL bSave);
	static void PrintHexData(LPCTSTR lpType, BYTE* pbyData, DWORD dwLen);
	static void PrintASCIIData(LPCTSTR lpType, BYTE* pbyData, DWORD dwLen);

private:
	static void AddLog(LPCTSTR lpszMsg);
	static CRITICAL_SECTION m_csFile;		//������¼�ļ�

public:
	static void Stop();
	static void Init(CString strIniFileName);
	//static DWORD m_dwRefresh;			//λ��ֵ��ȡˢ�´���
	//static DWORD m_dwWrite;				//дλ��ֵ����
	//static DWORD m_dwWriteErr;			//дλ��ֵ�������
	//static DWORD m_dwTcpReceiveCount;	//TCPͨ���յ��İ���
	//static DWORD m_dwTcpSendCount;		//TCPͨ�ŷ��͵İ���

	static CString m_strFileName;		//��־�ļ���
	static DWORD m_dwMsgTotal;			//��־����
	static BOOL m_bSaveLastLog;			//����ʱ�Ƿ񱣴��ϴε���־
	static BOOL m_bSaveFullLog;			//LOG�ļ���ʱ�Ƿ񱣴�
	static BOOL m_bPrintCmdFlag;		//�Ƿ��ӡ������Log�ļ���
};

#endif // !defined(AFX_POWERINFO_H__0A93100A_0600_4DC8_AEA0_4AEA6EF05887__INCLUDED_)
