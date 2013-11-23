// CommuPark.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CommuPark.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CCommuParkApp

BEGIN_MESSAGE_MAP(CCommuParkApp, CWinApp)
END_MESSAGE_MAP()


// CCommuParkApp construction

CCommuParkApp::CCommuParkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCommuParkApp object

CCommuParkApp theApp;


// CCommuParkApp initialization

BOOL CCommuParkApp::InitInstance()
{
	CWinApp::InitInstance();
	//_crtBreakAlloc = 237;

	return TRUE;
}

/**
ȫ�ֱ���

*/
CConfig g_config("PMS.ini");
Termin  g_Termin(g_config);
extern UCI_TrafficData g_UCIData;
extern CRITICAL_SECTION g_csUCI;



/*�����Ƿ�װ��ͨѶ����ýӿ�
*/


/** 
ָ�������ļ���·�����ú�����Ҫ���ȱ����ã�ȷ�������ļ�ָ����ȷ
�����ļ������������ 
����:
UploadConfig     // �ϴ�������
    Port          ���ݴ�������������˿�8682
    IP            ���ݴ��������IP��ַ
    SendInterval  �������ݷ��ͼ�����Ժ���Ϊ��λ
    UploadMode    �ϴ�ģʽ��1Ϊʵʱ�������ȣ�0 Ϊ��ʷ��������
DBConfig        // MYSQL ����������
    DBServer    // MYSQL ���ݿ�����IP ��ַ
    DBName      //       ���ݿ�����
    DBUser               ���ݿ��û���
    DBPassword           ���ݿ��¼����
    DBPort         MYSQL ��������˿�
SYSTEM             // ��־������
    PRINTCMDFLAG       // �Ƿ��ӡ��־ 0����ӡ 1 ��ӡ
    SAVELASTLOGFILEFLAG  // �Ƿ񱣴��ϴε���־��¼ 0������ 1 ����
    SAVEFULLLOGFILEFLAG  // �Ƿ񱣴�ȫ����־       0������ 1 ����
    LOGFILENAME          // Ĭ�ϵ���־����
    MESSAGESTOTAL_THOUSAND // ��־�ļ���Ϣ����

*/
extern "C" BOOL PASCAL EXPORT InitIniFile(char chFileName[256])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    CString strFileName = chFileName;
    g_config.SetFilePath(strFileName);
    return TRUE;
    
}
// ��ʼ��ͨѶ�⣬�ú���ֻ����InitIniFile() ����ã�������Ч
extern "C" BOOL PASCAL EXPORT InitLib()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return  g_Termin.Init(g_config);
    
}
// ����ʼ��ͨѶ�⣬������
extern "C" BOOL PASCAL EXPORT UnInitLib()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return TRUE;

}
// ��ʼ��д��־�Ĺ����� ���� ��ͣ�����ն������ʹ��ʱ�������ļ�·���봫���InitIniFile����һ��  
extern "C" BOOL PASCAL EXPORT InitLog(char chFileName[256])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CString strFileName = chFileName;
    CPowerInfo::Init(strFileName);
    return TRUE;
}
// ����ʼ��д��־������
extern "C" BOOL PASCAL EXPORT UnInitLog()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CPowerInfo::Stop();
    return TRUE;
}
// д��־����
extern "C" BOOL PASCAL EXPORT AddLog(CString strLog)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CPowerInfo::WLog(strLog);
    return TRUE;
}

/*
�����ϴ��������ݷ��񼰼�������ͨ��
*/
extern "C" BOOL PASCAL EXPORT StartServer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	return g_Termin.Start();
				
}

/**
ֹͣ�ϴ����ݷ��񣬹ر�����ͨ���ļ���
*/

extern "C" BOOL PASCAL EXPORT StopServer()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    return g_Termin.Stop();
}


/**
Уʱ�������ú���ֻ���ڿ����ϴ����ݷ������ã����򲻿��á�
*/
extern "C" BOOL PASCAL EXPORT CheckTime()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    return g_Termin.CheckTime();
   
}

/**
�ն˷��������쳵����Ϣ�ϴ�������ʵ���ն˷��������쳵����Ϣ���ն������ĵ������ϴ�
*/
extern "C" BOOL PASCAL EXPORT UCIUpdate(char *PlateNo, char *CarType, char *CarColor, char *OwnerName, char *CardNum, char *Reserved)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString strTmp;
	EnterCriticalSection(&g_csUCI);
	memset(&g_UCIData,0,sizeof(g_UCIData));
	memcpy(g_UCIData.chPlateNo,PlateNo,strlen(PlateNo)); 
	memcpy(g_UCIData.chCarType,CarType,strlen(CarType));
	memcpy(g_UCIData.chCarColor,CarColor,strlen(CarColor));
	memcpy(g_UCIData.chOwnerName,OwnerName,strlen(OwnerName));
	memcpy(g_UCIData.chCardNum,CardNum,strlen(CardNum));
	memcpy(g_UCIData.chReserved,Reserved,strlen(Reserved));
	if(g_Termin.SendUCIData())
	{
 		LeaveCriticalSection(&g_csUCI);
		return true;
	}
	else
	{
		if(!g_Termin.SaveTmpUCI())
		{
		    strTmp.Format("SaveTmpUCI ERROR!");
                    OutputDebugString(strTmp);
                    CPowerInfo::WLog(strTmp);	
		}
		else
		{
		    strTmp.Format("SaveTmpUCI SUCCESS!");
                    OutputDebugString(strTmp);
                    CPowerInfo::WLog(strTmp);
		}
		LeaveCriticalSection(&g_csUCI);
		return false;
	}
}