#pragma once

// SCCPCtrl.h : Declaration of the CSCCPCtrl ActiveX Control class.


// CSCCPCtrl : See SCCPCtrl.cpp for implementation.

#include "BufferManager.h"
#include <gdiplus.h>
#include <GdiplusImaging.h>
#include <GdiplusImageCodec.h>


#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;








typedef BOOL(__stdcall *PFN_SADP_START)(void(CALLBACK *fHandleDataCallBack)(
										char*        szSeries,
										char*        szDeviceid,
										char*        szHwaddr,
										char*        szPraddr,
										char*        szSubnetmask,
										unsigned int nDevtype,
										unsigned int nPort,
										unsigned int nEnccnt,
										unsigned int nHdiskcnt,
										char*        szSfwversion, 
										char*        szDspversion, 
										char*        szStarttime,
										int          result));
typedef BOOL(__stdcall *PFN_SADP_STOP)();
typedef BOOL(__stdcall *PFN_SADP_SENDINQUIRY)();
typedef BOOL(__stdcall *PFN_SADP_CONFIGLOAD)(char* devFilename);
typedef BOOL(__stdcall *PFN_SADP_SENDUPDATEIP)(char* desDLC,char *desIP,char* subnetmask,char * passwd,char * port);
typedef LONG (__stdcall *PFN_SADP_GETADAPNUM)();
typedef BOOL (__stdcall *PFN_SADP_SENDSETUSERPASSWORD)(char* desDLC,char* desIP,char* subnetmask,char* passwd,char* port);



class CSCCPCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSCCPCtrl)

// Constructor
public:
	CSCCPCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CSCCPCtrl();

	DECLARE_OLECREATE_EX(CSCCPCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CSCCPCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSCCPCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSCCPCtrl)		// Type name and misc status

// Message maps
	afx_msg LRESULT  OnRecieve(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidSetSFZ = 25L,
		dispidGetPort = 24L,
		dispidGetIPAddr = 23L,
		dispidDeviceInitOk = 22,
		eventidOnPlateReceive = 1L,
		dispidTrigger = 21L,
		dispidSavePlateBinImage = 20L,
		dispidLogFile = 19,
		dispidRecvPlateBinImageFlag = 18,
		dispidRecvImageFlag = 17,
		dispidRecvPlateImageFlag = 16,
		dispidSavePlateImage = 12L,
		dispidSaveImage = 11L,
		dispidGetPlateColor = 10L,
		dispidGetPlate = 9L,
		dispidGetStatus = 8L,
		dispidStopVideo = 7L,
		dispidStarVideo = 6L,
		dispidConfig = 5L,
		dispidSetUp = 4L,
		dispidClose = 3L,
		dispidOpenCom = 2L,
		dispidOpenNet = 1L
	};
private:
	NET_DVR_DEVICEINFO_V30			m_stDeviceInfo;				///< �豸��Ϣ
	NET_INTELCFG_DEVLOGININFO		m_stDevLogInfo;				///< �豸��Ϣ

	LONG							m_lUserID;					///< ��¼��Ϣ
	LONG							m_lPreviewHandle;			///< Ԥ�����
	HWND							m_hPreviewHandle;			///vfwԤ�����
	LONG							m_lAlarmHandle;				///< �������
	CBufferManager					m_cBufferManager;			///< ���ƴ洢
	HANDLE							m_hLogFile;					///< ��־�ļ����
	HANDLE							m_hMutexLogFile;			///< ������Ϣ��
	CString							m_strIPAddr;				///< IP��ַ
	CString							m_strPort;					///< �˿ں�
	HMODULE							m_hSadpModule;
	PFN_SADP_STOP				m_pfnSadpStop;
	PFN_SADP_START				m_pfnSadpStart;
	PFN_SADP_SENDUPDATEIP		m_pfnSadpSendUpdateIP;
	ULONG_PTR					m_gdiplusToken;		//GDI����

public:
	LONG							m_RecvPlateImageFlag;		///< �Ƿ���ܳ���ͼƬ����
	LONG							m_RecvImageFlag;			///< �Ƿ����ͼƬ����
	LONG							m_RecvPlateBinImageFlag;	///< �Ƿ���ܶ�ֵͼ����
	LONG							m_LogFile;					///<  �Ƿ������־�ļ�����
	VARIANT_BOOL					m_DeviceInitOk;				///< �豸�Ƿ���������
public:
	//�����µĳ���
	void InsertNewPlate(LPNET_DVR_PLATE_RESULT pPlateInfo);
public:
	// ���ò���
	LONG SetUpAlarm();
	// ��������
	LONG CleanAlarm();
	//����ͼƬ
	BOOL SavePic(LPCTSTR lpPath, LPCTSTR lpPicName, BYTE * pImage, DWORD dwPicDataLen);
	//д��־�ļ�
	VOID WriteLogFile(LPCTSTR szFun,BOOL bError, LPCTSTR szLog);
	//������־�ļ�
	BOOL CreateLogFile();
	//�����ļ�·��
	BOOL CreateFileDir(LPCTSTR lpPath);
	// ��ʼ��
	void InitCtrl();
	//HANDLE m_hThread;
	//static DWORD WINAPI FunProc(LPVOID lpParameter);
	LONG OpenNet(LPCTSTR szIP, LONG nPort);
	LONG OpenCom(LONG nComPort, LONG nBaudRate, LONG nParity, LONG nByteSize, LONG nStopBit);
	LONG Close(void);
	LONG SetUp(LONG nTypeId);
	LONG Config(LONG nTypeId);
	LONG StarVideo(void);
	LONG StopVideo(void);
	LONG GetStatus(void);
	BSTR GetPlate(void);
	BSTR GetPlateColor(void);
	LONG SaveImage(LPCTSTR szPath, LPCTSTR szFileName, LONG nWidth, LONG nHeight, LONG nQuality, LONG nImageType);
	LONG SavePlateBinImage(LPCTSTR szPath, LPCTSTR szFileName);
	LONG Trigger(void);
	LONG SavePlateImage(LPCTSTR szPath, LPCTSTR szFileName);

	void OnRecvPlateImageFlagChanged(void);
	void OnRecvImageFlagChanged(void);
	void OnRecvPlateBinImageFlagChanged(void);
	void OnLogFileChanged(void);
	void OnDeviceInitOkChanged(void);

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	BOOL ConvertImgBytes2HBITMAP(BYTE* pImageBuffer,DWORD dwImageDataLen, int iWidth, int iHeight, WCHAR * szFileNae);

	void OnPlateReceive(void)
	{
		FireEvent(eventidOnPlateReceive, EVENT_PARAM(VTS_NONE));
	}
public:
	afx_msg void OnDestroy();

public:
	BSTR GetIPAddr(void);
	BSTR GetPort(void);
public:
	LONG SetSFZ(LPCTSTR name);
};

