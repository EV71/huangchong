#include "StdAfx.h"
#include "Log.h"
#include <Shlwapi.h> 
#include <sys/stat.h>
#include "Mutex.h"

CRITICAL_SECTION g_CriticalSectLog;//������־�ٽ���
CMutex g_mutex;

CLog::CLog(void)
{
	g_mutex.MutexCreate(&g_CriticalSectLog);
}

CLog::~CLog(void)
{
	g_mutex.MutexDestroy(&g_CriticalSectLog);
}
//��ȡ��ǰĿ¼·��
CString CLog::GetDirectoryPath()
{
	CString lpStrPath;
	const int nBufSize=512;
	TCHAR chBuf[nBufSize];
	ZeroMemory(chBuf,nBufSize);
	if(GetModuleFileName(NULL,chBuf,nBufSize))
	{		
		PathRemoveFileSpec(chBuf);
		lpStrPath=chBuf;
	}
	return lpStrPath;
}
CString CLog::GetUpDir(CString lpStrPath)
{
   int aa= lpStrPath.ReverseFind('\\');
   lpStrPath.Delete(aa,lpStrPath.GetLength()- aa);
   return lpStrPath;
}
CString strFileName;//�ļ���	
FILE* debugInfoFile;//�ļ�
//д��־�ļ�
BOOL CLog::SaveLogInfo(const char *pLogMsg)
{	
	CTime tmCurr;//��ǰʱ��
	CString strTimeCurr;//��ǰʱ��
	CString strDebug;//������Ϣ	
	tmCurr = CTime::GetCurrentTime();
	
	strTimeCurr = tmCurr.Format("%Y-%m-%d %H:%M:%S ");
	strDebug.Format("%s%s\r\n", strTimeCurr, pLogMsg);
	strFileName.Format("%s\\CamConfig_Log.txt", GetDirectoryPath());
	//Ϊ��־�����ٽ���
	g_mutex.Lock(&g_CriticalSectLog);
	fopen_s(&debugInfoFile,(char *)(LPCTSTR)strFileName,"a");
	if(debugInfoFile != NULL)
	{
		fprintf(
			debugInfoFile,
			"%s",
			strDebug
			);
		fclose(debugInfoFile);	
		//Ϊ��־�����ٽ���
		g_mutex.Unlock(&g_CriticalSectLog);
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

//������־�ļ�
BOOL CLog::ClearLogInfo()
{	
	strFileName.Format("%s\\CamConfig.txt", GetDirectoryPath());
	CFileStatus status;
	CFile::GetStatus(strFileName,status);
	ULONGLONG sizeOfFile=status.m_size;
	if (sizeOfFile > 1024 * 1024) //�����־�ļ���С����10M,���
	{		
		fopen_s(&debugInfoFile,strFileName, "w");
		if(debugInfoFile == NULL)
		{
			return TRUE;
		}
	}
	return FALSE;	
}