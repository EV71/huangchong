// ToHvShowCtrl.cpp : Implementation of the CToHvShowCtrl ActiveX Control class.

#include "stdafx.h"
#include "ToHvShow.h"
#include "ToHvShowCtrl.h"
#include "ToHvShowPropPage.h"
std::vector<pDeviceInfo> CToHvShowCtrl::m_vecDeviceInfoTable;
//LONG CToHvShowCtrl::m_lCurrentUid;//��ʶ��ǰ�����豸Uid
//LONG CToHvShowCtrl::m_lLoginUid;//��ʶ��ǰ��¼�豸Uid�����ڲ�����
//CRITICAL_SECTION CToHvShowCtrl::m_csVecLock;
//HANDLE CToHvShowCtrl::m_hLogFile = NULL;					///< ��־�ļ����
//HANDLE CToHvShowCtrl::m_hMutexLogFile = NULL;			///< ��־�ļ���
//LONG CToHvShowCtrl::m_LogFile = 1;//�Ƿ��ӡ��־���ļ��С�
//LONG volatile g_callback = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CToHvShowCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CToHvShowCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_USER+100,OnRecieve)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CToHvShowCtrl, COleControl)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "RecvSnapImageFlag", dispidRecvSnapImageFlag, m_RecvSnapImageFlag, OnRecvSnapImageFlagChanged, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "RecvPlateImageFlag", dispidRecvPlateImageFlag, m_RecvPlateImageFlag, OnRecvPlateImageFlagChanged, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "RecvPlateBinImageFlag", dispidRecvPlateBinImageFlag, m_RecvPlateBinImageFlag, OnRecvPlateBinImageFlagChanged, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "RecvSnapDriverImageFlag", dispidRecvSnapDriverImageFlag, m_RecvSnapDriverImageFlag, OnRecvSnapDriverImageFlagChanged, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "AutoSaveFlag", dispidAutoSaveFlag, m_AutoSaveFlag, OnAutoSaveFlagChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "ShowPlateImage", dispidShowPlateImage, m_ShowPlateImage, OnShowPlateImageChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "ShowFirstImage", dispidShowFirstImage, m_ShowFirstImage, OnShowFirstImageChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "ShowSecondImage", dispidShowSecondImage, m_ShowSecondImage, OnShowSecondImageChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "ShowPlateResult", dispidShowPlateResult, m_ShowPlateResult, OnShowPlateResultChanged, VT_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "ConnectTo", dispidConnectTo, ConnectTo, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "GetStatus", dispidGetStatus, GetStatus, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CToHvShowCtrl, "Disconnect", dispidDisconnect, Disconnect, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CToHvShowCtrl, "SetImgSavePath", dispidSetImgSavePath, SetImgSavePath, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "GetPlate", dispidGetPlate, GetPlate, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CToHvShowCtrl, "GetPlateColor", dispidGetPlateColor, GetPlateColor, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CToHvShowCtrl, "GetPlateInfo", dispidGetPlateInfo, GetPlateInfo, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CToHvShowCtrl, "SaveSnapImage", dispidSaveSnapImage, SaveSnapImage, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "SaveSnapImage2", dispidSaveSnapImage2, SaveSnapImage2, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "SavePlateImage", dispidSavePlateImage, SavePlateImage, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "SavePlateBinImage", dispidSavePlateBinImage, SavePlateBinImage, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "SavePlateBin2BMP", dispidSavePlateBin2BMP, SavePlateBin2BMP, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CToHvShowCtrl, "GetImageRecTime", dispidGetImageRecTime, GetImageRecTime, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CToHvShowCtrl, "GetImageFileName", dispidGetImageFileName, GetImageFileName, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CToHvShowCtrl, "GetImageDataFromMem", dispidGetImageDataFromMem, GetImageDataFromMem, VT_BSTR, VTS_I4 VTS_PVARIANT VTS_PI4)
	DISP_PROPERTY_NOTIFY_ID(CToHvShowCtrl, "LogFile", dispidLogFile, m_LogFile, OnLogFileChanged, VT_I4)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CToHvShowCtrl, COleControl)
	EVENT_CUSTOM_ID("OnReceivePlate", eventidOnReceivePlate, OnReceivePlate, VTS_NONE)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CToHvShowCtrl, 1)
	PROPPAGEID(CToHvShowPropPage::guid)
END_PROPPAGEIDS(CToHvShowCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CToHvShowCtrl, "TOHVSHOW.ToHvShowCtrl.1",
	0xb38e8e73, 0x1451, 0x470f, 0x8e, 0xf, 0xe7, 0x1b, 0x9a, 0xfb, 0x3f, 0x53)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CToHvShowCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DToHvShow =
		{ 0xC683820E, 0x70D4, 0x43E5, { 0xA0, 0x3D, 0xBB, 0xB9, 0x45, 0xF2, 0xEB, 0x2A } };
const IID BASED_CODE IID_DToHvShowEvents =
		{ 0xFB8A8CB8, 0x869A, 0x4457, { 0x8A, 0x97, 0xE6, 0x8E, 0x58, 0xD2, 0xA8, 0xA0 } };



// Control type information

static const DWORD BASED_CODE _dwToHvShowOleMisc =
/*	OLEMISC_INVISIBLEATRUNTIME |*/
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CToHvShowCtrl, IDS_TOHVSHOW, _dwToHvShowOleMisc)



// CToHvShowCtrl::CToHvShowCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CToHvShowCtrl

BOOL CToHvShowCtrl::CToHvShowCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_TOHVSHOW,
			IDB_TOHVSHOW,
			afxRegApartmentThreading,
			_dwToHvShowOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CToHvShowCtrl::CToHvShowCtrl - Constructor

CToHvShowCtrl::CToHvShowCtrl()
{
	InitializeIIDs(&IID_DToHvShow, &IID_DToHvShowEvents);
	// TODO: Initialize your control's instance data here.
	m_iBinBMPSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*2 + 20*112;//BMP ָ����С
	m_pchPlateBinBMP = new char[m_iBinBMPSize];
	m_fChangingCtrlName = false;
	m_hWndParent = NULL;
	m_hMutexLogFile = NULL;
	m_hLogFile = NULL;
	m_LogFile = 1;
#ifndef ONE_DEVICE
	InitializeCriticalSectionAndSpinCount(&m_csVecLock,4000);//�����ٽ���
	m_lCurrentUid = -1;
	m_lLoginUid = -1;
#else
	m_csPort = _T("");
	m_csIPAddr = _T("");
	m_lUid = -1;
	m_lAlarmHandle = -1;
	m_cBufferManager.InitBufferManage();
#endif
	m_csImagePath = _T("C:\\Image");
	//��ʼ��GDI
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	if(m_pClientSite)
	{
		EnumAllControlNames();//��ȡ���пؼ�����
	}
	if (m_LogFile == 1)
	{
		CreateLogFile();
	}
}



// CToHvShowCtrl::~CToHvShowCtrl - Destructor

CToHvShowCtrl::~CToHvShowCtrl()
{
	// TODO: Cleanup your control's instance data here.
	if(m_pchPlateBinBMP)
	{
		delete [] m_pchPlateBinBMP;
		m_pchPlateBinBMP = NULL;
	}
#ifndef ONE_DEVICE
	EnterCriticalSection(&m_csVecLock);
	m_vecDeviceInfoTable.clear();//���������豸����
	LeaveCriticalSection(&m_csVecLock);
	DeleteCriticalSection(&m_csVecLock);//�ͷ��ٽ���
#endif
}



// CToHvShowCtrl::OnDraw - Drawing function

void CToHvShowCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}



// CToHvShowCtrl::DoPropExchange - Persistence support

void CToHvShowCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
	PX_Long(pPX,_T("RecvSnapImageFlag"),m_RecvSnapImageFlag,1);
	PX_Long(pPX,_T("RecvPlateImageFlag"),m_RecvPlateImageFlag,1);
	PX_Long(pPX,_T("RecvPlateBinImageFlag"),m_RecvPlateBinImageFlag,1);
	PX_Long(pPX,_T("RecvSnapDriverImageFlag"),m_RecvSnapDriverImageFlag,1);
	PX_Short(pPX,_T("AutoSaveFlag"),m_AutoSaveFlag,0);
	PX_String(pPX,_T("ShowPlateImage"),m_ShowPlateImage,_T("ShowPlateImage"));
	PX_String(pPX,_T("ShowFirstImage"),m_ShowFirstImage,_T("ShowFirstImage"));
	PX_String(pPX,_T("ShowSecondImage"),m_ShowSecondImage,_T("ShowSecondImage"));
	PX_String(pPX,_T("ShowPlateResult"),m_ShowPlateResult,_T("ShowPlateResult"));
	//////////////////////////////////////////////�Զ�������
	PX_Long(pPX,_T("LogFile"),m_LogFile,1);
}



// CToHvShowCtrl::OnResetState - Reset control to default state

void CToHvShowCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


CString g_csPlateData;//��������,ȫ�ֱ�������Ҫԭ�����·�����Ϣ�ͻ��˲���ʱ���������ݶ�ʧ��
//��Ϣ��������������Ϣ��
LRESULT CToHvShowCtrl::OnRecieve(WPARAM wParam, LPARAM lParam)
{
	//��ؼ��������ݣ�֮�������ⷢ����Ϣ��
	NET_DVR_PLATE_RESULT		stPlateInfo;
	memset(&stPlateInfo, 0, sizeof(stPlateInfo));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == true)
	{
		if (m_AutoSaveFlag == 1)
		{
			// ��ǰ�Զ�����ͼƬ
			WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ǰ�Զ�����ͼƬ������"));
			SaveSnapImage(GetImageFileName(0));
			SavePlateImage(GetImageFileName(1));
			SavePlateBinImage(GetImageFileName(2));
			SaveSnapImage2(GetImageFileName(3));
			SavePlateBin2BMP(GetImageFileName(4));
		}
		////////////////////////////////////////////////////////////////////////////
		if(m_pClientSite)
		{
			EnumAllControlNames();//��ȡ���пؼ�����
		}
		resultMSG msg = {0};
		/////////////////////////////////////////////////////////////////������Ϣ
		USES_CONVERSION;
		//csPlateData.Format(_T("%s%s"),stPlateInfo.struPlateInfo.byColor==0?_T("��"):
		//												stPlateInfo.struPlateInfo.byColor==1?_T("��"):
		//												stPlateInfo.struPlateInfo.byColor==2?_T("��"):
		//												stPlateInfo.struPlateInfo.byColor==3?_T("��"):_T("")
		//												,A2W(stPlateInfo.struPlateInfo.sLicense));
		g_csPlateData.Format(_T("%s"),A2W(stPlateInfo.struPlateInfo.sLicense));
		if(g_csPlateData == _T("�޳���") || g_csPlateData == _T(""))
		{
			g_csPlateData = _T("δ���");
		}
		char* strPlate = W2A(g_csPlateData.GetBuffer(0));
		msg.pdata = strPlate;
		msg.pDataLen = strlen (strPlate);
		msg.dataType = 1; // 1���ַ���
		SendData(m_ShowPlateResult, msg.pdata, msg.pDataLen, 1, &msg);
		g_csPlateData.ReleaseBuffer();
		///////////////////////////////////////////////////////////////////����ͼƬ
		msg.pdata = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(1);
		msg.pDataLen = stPlateInfo.dwPicPlateLen;
		msg.dataType = 0;  // 0 ��ͼƬ
		SendData(m_ShowPlateImage, msg.pdata, msg.pDataLen, 0, &msg);
		///////////////////////////////////////////////////////////////////����ͼƬ
		msg.pdata = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(0);
		msg.pDataLen = stPlateInfo.dwPicLen;
		msg.dataType = 0;  // 0 ��ͼƬ
		SendData(m_ShowFirstImage, msg.pdata, msg.pDataLen, 0, &msg);
		///////////////////////////////////////////////////////////////////����ͼƬ
		msg.pdata = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(3);
		msg.pDataLen = stPlateInfo.dwCarPicLen;
		msg.dataType = 0;  // 0 ��ͼƬ
		SendData(m_ShowSecondImage, msg.pdata, msg.pDataLen, 0, &msg);
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == true)
	{
		if (m_AutoSaveFlag == 1)
		{
			// ��ǰ�Զ�����ͼƬ
			WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ǰ�Զ�����ͼƬ������"));
			SaveSnapImage(GetImageFileName(0));
			SavePlateImage(GetImageFileName(1));
			SavePlateBinImage(GetImageFileName(2));
			SaveSnapImage2(GetImageFileName(3));
			SavePlateBin2BMP(GetImageFileName(4));
		}
		////////////////////////////////////////////////////////////////////////////
		if(m_pClientSite)
		{
			EnumAllControlNames();//��ȡ���пؼ�����
		}
		resultMSG msg = {0};
		/////////////////////////////////////////////////////////////////������Ϣ
		USES_CONVERSION;
		//csPlateData.Format(_T("%s%s"),stPlateInfo.struPlateInfo.byColor==0?_T("��"):
		//												stPlateInfo.struPlateInfo.byColor==1?_T("��"):
		//												stPlateInfo.struPlateInfo.byColor==2?_T("��"):
		//												stPlateInfo.struPlateInfo.byColor==3?_T("��"):_T("")
		//												,A2W(stPlateInfo.struPlateInfo.sLicense));
		g_csPlateData.Format(_T("%s"),A2W(stPlateInfo.struPlateInfo.sLicense));
		if(g_csPlateData == _T("�޳���") || g_csPlateData == _T(""))
		{
			g_csPlateData = _T("δ���");
		}
		char* strPlate = W2A(g_csPlateData.GetBuffer(0));
		msg.pdata = strPlate;
		msg.pDataLen = strlen (strPlate);
		msg.dataType = 1; // 1���ַ���
		SendData(m_ShowPlateResult, msg.pdata, msg.pDataLen, 1, &msg);
		g_csPlateData.ReleaseBuffer();
		///////////////////////////////////////////////////////////////////����ͼƬ
		msg.pdata = m_cBufferManager.GetPicBuffer(1);
		msg.pDataLen = stPlateInfo.dwPicPlateLen;
		msg.dataType = 0;  // 0 ��ͼƬ
		SendData(m_ShowPlateImage, msg.pdata, msg.pDataLen, 0, &msg);
		///////////////////////////////////////////////////////////////////����ͼƬ
		msg.pdata = m_cBufferManager.GetPicBuffer(0);
		msg.pDataLen = stPlateInfo.dwPicLen;
		msg.dataType = 0;  // 0 ��ͼƬ
		SendData(m_ShowFirstImage, msg.pdata, msg.pDataLen, 0, &msg);
		///////////////////////////////////////////////////////////////////����ͼƬ
		msg.pdata = m_cBufferManager.GetPicBuffer(3);
		msg.pDataLen = stPlateInfo.dwCarPicLen;
		msg.dataType = 0;  // 0 ��ͼƬ
		SendData(m_ShowSecondImage, msg.pdata, msg.pDataLen, 0, &msg);
	}
#endif
	OnReceivePlate();
	return 0;
}

// CToHvShowCtrl message handlers

void CToHvShowCtrl::OnRecvSnapImageFlagChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�RecvSnapImageFlag���ԣ� %d"), m_RecvSnapImageFlag);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x1);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnRecvPlateImageFlagChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�RecvPlateImage���ԣ� %d"), m_RecvPlateImageFlag);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x2);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnRecvPlateBinImageFlagChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�RecvPlateBinImageFlag���ԣ� %d"), m_RecvPlateBinImageFlag);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x3);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnRecvSnapDriverImageFlagChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�RecvSnapDriverImageFlag���ԣ� %d"), m_RecvSnapDriverImageFlag);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x4);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnAutoSaveFlagChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�AutoSaveFlag���ԣ� %d"), m_AutoSaveFlag);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x5);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnShowPlateImageChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�ShowPlateImage���ԣ� %s"), m_ShowPlateImage);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x6);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnShowFirstImageChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�ShowFirstImage���ԣ� %s"), m_ShowFirstImage);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x7);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnShowSecondImageChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�ShowSecondImage���ԣ� %s"), m_ShowSecondImage);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x8);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnShowPlateResultChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�ShowPlateResult���ԣ� %s"), m_ShowPlateResult);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x9);
	SetModifiedFlag();
}

void CToHvShowCtrl::OnLogFileChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	CString csLog;
	csLog.Format(_T("�޸�LogFile���ԣ� %d"), m_LogFile);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	BoundPropertyChanged(0x19);
	SetModifiedFlag();
}


///////////////////////////////////////////////////////////////////////////////////////
//�ж��Ƿ�Ϊ��ȷ��IP��ʽ
bool isIPAddress(const char *s)  
{  
	const char *pChar;  
	bool rv = true;  
	int tmp1, tmp2, tmp3, tmp4, i;  

	while( 1 )  
	{  
		i = sscanf_s(s, "%d.%d.%d.%d", &tmp1, &tmp2, &tmp3, &tmp4);  

		if( i != 4 )  
		{  
			rv = false;  
			break;  
		}  

		if( (tmp1 > 255) || (tmp2 > 255) || (tmp3 > 255) || (tmp4 > 255) )  
		{  
			rv = false;  
			break;  
		}  

		for( pChar = s; *pChar != 0; pChar++ )  
		{  
			if( (*pChar != '.')  
				&& ((*pChar < '0') || (*pChar > '9')) )  
			{  
				rv = false;  
				break;  
			}  
		}  
		break;  
	}  

	return rv;  
}  



void CToHvShowCtrl::ConnectTo(LPCTSTR strAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString tmp;
	// TODO: Add your dispatch handler code here
#ifndef ONE_DEVICE
	pDeviceInfo pDeviceinfoAdd = new DeviceInfo();
	//if(m_lUid>=0)
	//{
	//	Disconnect();
	//}
	if(strAddr == NULL)
	{
		return;
	}
	CString csAddr(strAddr);
	int pos = csAddr.Find(_T(":"),0);
	USES_CONVERSION;
	if(pos == -1)//ֻ����IP��Ĭ�϶˿�Ϊ8000
	{
		pDeviceinfoAdd->m_csIPAddr = csAddr;

		if(isIPAddress(W2A(pDeviceinfoAdd->m_csIPAddr.GetBuffer(0))))
		{
			pDeviceinfoAdd->m_csIPAddr.ReleaseBuffer();
			pDeviceinfoAdd->m_csPort = _T("8000");
		}
		else
		{
			pDeviceinfoAdd->m_csIPAddr.ReleaseBuffer();
			pDeviceinfoAdd->m_csIPAddr = _T("");
			pDeviceinfoAdd->m_csPort = _T("");
			pDeviceinfoAdd->m_lUid = -1;
			return;
		}
	}
	else//����IP�Ͷ˿ں� IP:Port ����ʽ
	{
		pDeviceinfoAdd->m_csIPAddr = csAddr.Left(pos);
		pDeviceinfoAdd->m_csPort = csAddr.Right(csAddr.GetLength() - pos - 1);
		if(isIPAddress(W2A(pDeviceinfoAdd->m_csIPAddr.GetBuffer(0))))
		{
			int iPort = atoi(W2A(pDeviceinfoAdd->m_csPort.GetBuffer(0)));
			if(iPort >= 1 && iPort <= 65535)
			{
				pDeviceinfoAdd->m_csIPAddr.ReleaseBuffer();
				pDeviceinfoAdd->m_csPort.ReleaseBuffer();
			}
			else
			{
				pDeviceinfoAdd->m_csIPAddr.ReleaseBuffer();
				pDeviceinfoAdd->m_csPort.ReleaseBuffer();
				pDeviceinfoAdd->m_csIPAddr = _T("");
				pDeviceinfoAdd->m_csPort = _T("");
				pDeviceinfoAdd->m_lUid = -1;
				return;
			}
		}
		else
		{
			pDeviceinfoAdd->m_csIPAddr.ReleaseBuffer();
			pDeviceinfoAdd->m_csIPAddr = _T("");
			pDeviceinfoAdd->m_csPort = _T("");
			pDeviceinfoAdd->m_lUid = -1;
			return;
		}
	}
	//�����е��˴���˵������Ĳ���Ϊ��ȷ�Ĳ�����֮�󼴿�ʼ�����豸
	memset(&m_stDeviceInfo, 0, sizeof(m_stDeviceInfo));
	pDeviceinfoAdd->m_lUid = NET_DVR_Login_V30(W2A(pDeviceinfoAdd->m_csIPAddr.GetBuffer(0)), atoi(W2A(pDeviceinfoAdd->m_csPort.GetBuffer(0))), "admin", "12345", &m_stDeviceInfo);
	m_lLoginUid = pDeviceinfoAdd->m_lUid;
	pDeviceinfoAdd->m_csIPAddr.ReleaseBuffer();
	pDeviceinfoAdd->m_csPort.ReleaseBuffer();

	if (pDeviceinfoAdd->m_lUid == -1)
	{
		tmp.Format(_T("��¼�豸: %s ʧ��!!"),pDeviceinfoAdd->m_csIPAddr);
		WriteLogFile((CA2T)__FUNCTION__, TRUE, tmp);
		return /*RETVAL_LOGIN_ERROR*/;
	}
	////////////////////////////////////////////////////////////////////
	EnterCriticalSection(&m_csVecLock);
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while(iter != m_vecDeviceInfoTable.end())
	{
		if((*iter)->m_csIPAddr == pDeviceinfoAdd->m_csIPAddr)
		{
			LeaveCriticalSection(&m_csVecLock);
			NET_DVR_Logout(m_lLoginUid);
			tmp.Format(_T("���豸 %s uid:%d �Ѿ���¼������"),pDeviceinfoAdd->m_csIPAddr,(*iter)->m_lUid);
			WriteLogFile((CA2T)__FUNCTION__, TRUE, tmp);
			//WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("���豸�Ѿ���¼������"));
			return;
		}
		iter ++;
	}
	m_vecDeviceInfoTable.push_back(pDeviceinfoAdd);
	LeaveCriticalSection(&m_csVecLock);
	///////////////////////////////////////////////////////
	tmp.Format(_T("���豸 %s uid:%d ��¼�ɹ�������"),pDeviceinfoAdd->m_csIPAddr,pDeviceinfoAdd->m_lUid);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, tmp);

	if(SetUpAlarm() > 0)
	{
		tmp.Format(_T("���豸 %s uid:%d ����ʧ�ܣ�����"),pDeviceinfoAdd->m_csIPAddr,pDeviceinfoAdd->m_lUid);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, tmp);
	}
	else
	{
		tmp.Format(_T("���豸 %s uid:%d �����ɹ�������"),pDeviceinfoAdd->m_csIPAddr,pDeviceinfoAdd->m_lUid);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, tmp);
	}
	return;
#else
	if(m_lUid>=0)
	{
		Disconnect();
	}
	if(strAddr == NULL)
	{
		return;
	}
	CString csAddr(strAddr);
	int pos = csAddr.Find(_T(":"),0);
	USES_CONVERSION;
	if(pos == -1)//ֻ����IP��Ĭ�϶˿�Ϊ8000
	{
		m_csIPAddr = csAddr;

		if(isIPAddress(W2A(m_csIPAddr.GetBuffer(0))))
		{
			m_csIPAddr.ReleaseBuffer();
			m_csPort = _T("8000");
		}
		else
		{
			m_csIPAddr.ReleaseBuffer();
			m_csIPAddr = _T("");
			m_csPort = _T("");
			m_lUid = -1;
			return;
		}
	}
	else//����IP�Ͷ˿ں� IP:Port ����ʽ
	{
		m_csIPAddr = csAddr.Left(pos);
		m_csPort = csAddr.Right(csAddr.GetLength() - pos - 1);
		if(isIPAddress(W2A(m_csIPAddr.GetBuffer(0))))
		{
			int iPort = atoi(W2A(m_csPort.GetBuffer(0)));
			if(iPort >= 1 && iPort <= 65535)
			{
				m_csIPAddr.ReleaseBuffer();
				m_csPort.ReleaseBuffer();
			}
			else
			{
				m_csIPAddr.ReleaseBuffer();
				m_csPort.ReleaseBuffer();
				m_csIPAddr = _T("");
				m_csPort = _T("");
				m_lUid = -1;
				return;
			}
		}
		else
		{
			m_csIPAddr.ReleaseBuffer();
			m_csIPAddr = _T("");
			m_csPort = _T("");
			m_lUid = -1;
			return;
		}
	}
	//�����е��˴���˵������Ĳ���Ϊ��ȷ�Ĳ�����֮�󼴿�ʼ�����豸
	memset(&m_stDeviceInfo, 0, sizeof(m_stDeviceInfo));
	m_lUid = NET_DVR_Login_V30(W2A(m_csIPAddr.GetBuffer(0)), atoi(W2A(m_csPort.GetBuffer(0))), "admin", "12345", &m_stDeviceInfo);
	m_csIPAddr.ReleaseBuffer();
	m_csPort.ReleaseBuffer();

	if (m_lUid == -1)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��¼�豸ʧ��"));
		return /*RETVAL_LOGIN_ERROR*/;
	}
	WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��¼�豸"));

	if(SetUpAlarm() > 0)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("����ʧ��"));
	}
	else
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("�����ɹ�"));
	}
	return;
#endif
}

LONG CToHvShowCtrl::GetStatus(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	BOOL	bRet = TRUE;
	LONG lRet = -2;
	NET_DVR_DEVICEINFO_V30 stDeviceInfo;
	LONG		lUserID;
#ifndef ONE_DEVICE
	EnterCriticalSection(&m_csVecLock);
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while (iter != m_vecDeviceInfoTable.end())
	{
		if(lRet == -2)
		{
			lRet = 0;//��һ�ν���whileѭ����Ϊ�˷�ֹ��һ��ѭ��������������ȷ�Ľ������ʵ�����豸��˵����¼ʧ�ܡ�
		}
		if((*iter)->m_lUid >= 0)
		{
			memset(&stDeviceInfo, 0, sizeof(NET_DVR_DEVICEINFO_V30));
			USES_CONVERSION;
			lUserID = NET_DVR_Login_V30(W2A((*iter)->m_csIPAddr.GetBuffer(0)), atoi(W2A((*iter)->m_csPort.GetBuffer(0))), "admin", "12345", &stDeviceInfo);
			(*iter)->m_csIPAddr.ReleaseBuffer();
			(*iter)->m_csPort.ReleaseBuffer();
			if (lUserID == -1)
			{
				CString tmp;
				tmp.Format(_T("�豸״̬�쳣,���IPΪ %s"),(*iter)->m_csIPAddr);
				WriteLogFile((CA2T)__FUNCTION__, TRUE, tmp);
				lRet = -1;
			}
			bRet = NET_DVR_Logout(lUserID);
		}
		else
		{
			CString tmp;
			tmp.Format(_T("�豸״̬�쳣,���IPΪ %s"),(*iter)->m_csIPAddr);
			WriteLogFile((CA2T)__FUNCTION__, TRUE, tmp);
			lRet = -1;
		}
		iter++;
	}
	Invalidate(TRUE);
	LeaveCriticalSection(&m_csVecLock);
	return lRet;
#else
	if (m_lUid < 0)
	{
		return RETVAL_ERROR;
	}
	memset(&stDeviceInfo, 0, sizeof(NET_DVR_DEVICEINFO_V30));
	USES_CONVERSION;
	lUserID = NET_DVR_Login_V30(W2A(m_csIPAddr.GetBuffer(0)), atoi(W2A(m_csPort.GetBuffer(0))), "admin", "12345", &stDeviceInfo);
	m_csIPAddr.ReleaseBuffer();
	m_csPort.ReleaseBuffer();
	if (lUserID == -1)
	{
		return RETVAL_ERROR;
	}
	bRet = NET_DVR_Logout(lUserID);
	if (bRet == TRUE)
	{
		return RETVAL_OK;
	}
	return RETVAL_ERROR;
#endif
}



void CToHvShowCtrl::Disconnect(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your dispatch handler code here
	CleanAlarm();	
#ifndef ONE_DEVICE
	EnterCriticalSection(&m_csVecLock);
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while (iter != m_vecDeviceInfoTable.end())
	{
		if((*iter)->m_lUid >= 0)
		{
			if(!NET_DVR_Logout((*iter)->m_lUid))
			{
				CString tmp;
				tmp.Format(_T("�ǳ��豸ʧ��,���IPΪ %s"),(*iter)->m_csIPAddr);
				WriteLogFile((CA2T)__FUNCTION__, TRUE, tmp);
			}
			else
			{
				(*iter)->m_lUid = -1;
				delete (*iter);
			}
		}
		iter++;
	}
	Invalidate(TRUE);
	m_vecDeviceInfoTable.clear();
	LeaveCriticalSection(&m_csVecLock);
#else
	if (m_lUid < 0)
	{
		Invalidate(TRUE);
		return /*RETVAL_OK*/;		
	}
	BOOL  bRet = NET_DVR_Logout(m_lUid);
	if (bRet == FALSE)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("�ر��豸ʧ��"));
		return /*RETVAL_LOGOUT_ERROR*/;
	}
	m_lUid = -1;
	Invalidate(TRUE);
#endif
	WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("�ر��豸"));
	return ;
}

void CToHvShowCtrl::SetImgSavePath(LPCTSTR strPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if (strPath == NULL)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��Ч����"));
		return ;
	}

	m_csImagePath.Format(_T("%s"),strPath);
	while(m_csImagePath.GetAt(m_csImagePath.GetLength() - 1) == _T('\\'))
	{
		m_csImagePath.Delete(m_csImagePath.GetLength() - 1);
	}
	CString csLog;
	csLog.Format(_T("���ñ���·��Ϊ�� %s"), m_csImagePath);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);
}

BSTR CToHvShowCtrl::GetPlate(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here
	NET_DVR_PLATE_RESULT		stPlateInfo;
	memset(&stPlateInfo, 0, sizeof(stPlateInfo));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == true)
	{
		strResult.Format(_T("%s"),(CA2T)(stPlateInfo.struPlateInfo.sLicense));
		if (strResult != _T("�޳���") && strResult != _T(""))
		{
			strResult.Delete(0);
		}
		else
		{
			strResult = _T("δ���");
		}
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == true)
	{
		strResult.Format(_T("%s"),(CA2T)(stPlateInfo.struPlateInfo.sLicense));
		if (strResult != _T("�޳���") && strResult != _T(""))
		{
			strResult.Delete(0);
		}
		else
		{
			strResult = _T("δ���");
		}
	}
#endif

	CString csLog = _T("��ȡ���ƺ���:	");
	csLog += strResult;
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);
	
	return strResult.AllocSysString();
}

BSTR CToHvShowCtrl::GetPlateColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here
	NET_DVR_PLATE_RESULT		stPlateInfo;
	memset(&stPlateInfo, 0, sizeof(stPlateInfo));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == true)
	{
		//strResult.Format(_T("%s"),(CA2T)(stPlateInfo.struPlateInfo.byColor));
		switch(stPlateInfo.struPlateInfo.byColor)
		{
		case VCA_BLUE_PLATE:
			{
				strResult = _T("��");
			}
			break;
		case VCA_YELLOW_PLATE:
			{
				strResult = _T("��");
			}
			break;
		case VCA_WHITE_PLATE:
			{
				strResult = _T("��");
			}
			break;
		case VCA_BLACK_PLATE:
			{
				strResult = _T("��");
			}
			break;
		default:
			{
				strResult = _T("��");
			}
		}
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == true)
	{
		//strResult.Format(_T("%s"),(CA2T)(stPlateInfo.struPlateInfo.byColor));
		switch(stPlateInfo.struPlateInfo.byColor)
		{
		case VCA_BLUE_PLATE:
			{
				strResult = _T("��");
			}
			break;
		case VCA_YELLOW_PLATE:
			{
				strResult = _T("��");
			}
			break;
		case VCA_WHITE_PLATE:
			{
				strResult = _T("��");
			}
			break;
		case VCA_BLACK_PLATE:
			{
				strResult = _T("��");
			}
			break;
		default:
			{
				strResult = _T("��");
			}
		}
	}
#endif

	CString csLog = _T("��ȡ������ɫΪ:	");
	csLog += strResult;
	WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);

	return strResult.AllocSysString();
}

BSTR CToHvShowCtrl::GetPlateInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here
	NET_DVR_PLATE_RESULT		stPlateInfo;
	memset(&stPlateInfo, 0, sizeof(stPlateInfo));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == true)
	{
		switch(stPlateInfo.struVehicleInfo.byIllegalType)
		{
		case 3:
			{
				strResult.Format(_T("%s"),_T("����������ʻ:��\n"));
			}
			break;
		default:
			{
				strResult.Format(_T("%s"),_T("����������ʻ:��\n"));
			}
			break;
		}
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == true)
	{
		switch(stPlateInfo.struVehicleInfo.byIllegalType)
		{
		case 3:
			{
				strResult.Format(_T("%s"),_T("����������ʻ:��\n"));
			}
			break;
		default:
			{
				strResult.Format(_T("%s"),_T("����������ʻ:��\n"));
			}
			break;
		}
	}
#endif
	return strResult.AllocSysString();
}

LONG CToHvShowCtrl::SaveSnapImage(LPCTSTR strFileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG		retVal = RETVAL_OK;
	NET_DVR_PLATE_RESULT stPlateInfo;

	if (strFileName == NULL)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��Ч����"));
		return RETVAL_INVALID_PARAM;
	}
	if (m_RecvSnapImageFlag == 0)
	{
		// ���ڲ�����ͼƬ
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ǰ������ͼƬ"));
		return RETVAL_NOT_RECV_PIC;
	}
	memset(&stPlateInfo, 0, sizeof(NET_DVR_PLATE_RESULT));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	//����·��
	CString csfullPath;
	csfullPath.Format(_T("%s"),strFileName);
	if (csfullPath.GetLength() >= MAX_PATH)
	{ 
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("ͼƬ·��������ץͼʧ��"));;
		return -1;
	}
	if (CreateFileDir(csfullPath) == FALSE)
	{
		return -1;
	}
#ifndef ONE_DEVICE
	char * pchpic = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(0);
#else
	char * pchpic = m_cBufferManager.GetPicBuffer(0);
#endif
	if (pchpic != NULL && stPlateInfo.dwPicLen != 0)
	{
		if (SavePic(csfullPath, (BYTE *)pchpic, stPlateInfo.dwPicLen) == FALSE)
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("���泵��ͼƬʧ��"));
			retVal = RETVAL_SAVE_PIC_ERROR;
		}
	}
	else
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("û�г���ͼƬ"));
		retVal = RETVAL_HAVE_NO_IMAGE;
	}
	if (retVal == RETVAL_OK)
	{
		CString		csLog;
		csLog.Format(_T("���泵��ͼƬ�� ��ַ��%s"), csfullPath);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);
	}
	
	return retVal;
}

LONG CToHvShowCtrl::SaveSnapImage2(LPCTSTR strFileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG		retVal = RETVAL_OK;
	NET_DVR_PLATE_RESULT	stPlateInfo;

	if (strFileName == NULL)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��Ч����"));
		return RETVAL_INVALID_PARAM;
	}
	if (m_RecvSnapDriverImageFlag == 0)
	{
		// ���ڲ�����ͼƬ
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ǰ������ͼƬ"));
		return RETVAL_NOT_RECV_PIC;
	}
	memset(&stPlateInfo, 0, sizeof(NET_DVR_PLATE_RESULT));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	CString csfullPath;
	csfullPath.Format(_T("%s"),strFileName);
	if (csfullPath.GetLength() >= MAX_PATH)
	{ 
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("ͼƬ·��������ץͼʧ��"));;
		return -1;
	}
	if (CreateFileDir(csfullPath) == FALSE)
	{
		return -1;
	}
#ifndef ONE_DEVICE
	char * pchpic = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(3);
#else
	char * pchpic = m_cBufferManager.GetPicBuffer(3);
#endif
	if (pchpic != NULL && stPlateInfo.dwCarPicLen != 0)
	{
		if (SavePic(csfullPath, (BYTE *)pchpic, stPlateInfo.dwCarPicLen) == FALSE)
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("���泵��ͼƬʧ��"));
			retVal = RETVAL_SAVE_PIC_ERROR;
		}
	}
	else
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("û�г���ͼƬ"));
		retVal = RETVAL_HAVE_NO_IMAGE;
	}
	if (retVal == RETVAL_OK)
	{
		CString		csLog;
		csLog.Format(_T("���泵��ͼƬ�� ��ַ��%s"), csfullPath);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);
	}

	return retVal;
}

LONG CToHvShowCtrl::SavePlateImage(LPCTSTR strFileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG		retVal = RETVAL_OK;
	NET_DVR_PLATE_RESULT	stPlateInfo;

	if (strFileName == NULL)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��Ч����"));
		return RETVAL_INVALID_PARAM;
	}
	if (m_RecvPlateImageFlag == 0)
	{
		// ���ڲ�����ͼƬ
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ǰ������ͼƬ"));
		return RETVAL_NOT_RECV_PIC;
	}
	memset(&stPlateInfo, 0, sizeof(NET_DVR_PLATE_RESULT));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	CString csfullPath;
	csfullPath.Format(_T("%s"),strFileName);
	if (csfullPath.GetLength() >= MAX_PATH)
	{ 
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("ͼƬ·��������ץͼʧ��"));;
		return -1;
	}
	if (CreateFileDir(csfullPath) == FALSE)
	{
		return -1;
	}
#ifndef ONE_DEVICE
	char * pchpic = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(1);
#else
	char * pchpic = m_cBufferManager.GetPicBuffer(1);
#endif
	if (pchpic != NULL && stPlateInfo.dwPicPlateLen != 0)
	{
		if (SavePic(csfullPath, (BYTE *)pchpic, stPlateInfo.dwPicPlateLen) == FALSE)
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("���泵��ͼƬʧ��"));
			retVal = RETVAL_SAVE_PIC_ERROR;
		}
	}
	else
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("û�г���ͼƬ"));
		retVal = RETVAL_HAVE_NO_IMAGE;
	}
	if (retVal == RETVAL_OK)
	{
		CString		csLog;
		csLog.Format(_T("���泵��ͼƬ�� ��ַ��%s"), csfullPath);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);
	}

	return retVal;
}

LONG CToHvShowCtrl::SavePlateBinImage(LPCTSTR strFileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG		retVal = RETVAL_OK;
	NET_DVR_PLATE_RESULT	stPlateInfo;

	if (strFileName == NULL)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��Ч����"));
		return RETVAL_INVALID_PARAM;
	}
	if (m_RecvPlateBinImageFlag == 0)
	{
		// ���ڲ�����ͼƬ
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ǰ������ͼƬ"));
		return RETVAL_NOT_RECV_PIC;
	}
	memset(&stPlateInfo, 0, sizeof(NET_DVR_PLATE_RESULT));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	CString csfullPath;
	csfullPath.Format(_T("%s"),strFileName);
	if (csfullPath.GetLength() >= MAX_PATH)
	{ 
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("ͼƬ·��������ץͼʧ��"));;
		return -1;
	}
	if (CreateFileDir(csfullPath) == FALSE)
	{
		return -1;
	}
#ifndef ONE_DEVICE
	char * pchpic = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(2);
#else
	char * pchpic = m_cBufferManager.GetPicBuffer(2);
#endif
	if (pchpic != NULL && stPlateInfo.dwBinPicLen != 0)
	{
		if (SavePic(csfullPath, (BYTE *)pchpic, stPlateInfo.dwBinPicLen) == FALSE)
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("���泵�ƶ�ֵͼƬʧ��"));
			retVal = RETVAL_SAVE_PIC_ERROR;
		}
	}
	else
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("û�г��ƶ�ֵͼƬ"));
		retVal = RETVAL_HAVE_NO_IMAGE;
	}
	if (retVal == RETVAL_OK)
	{
		CString		csLog;
		csLog.Format(_T("���泵�ƶ�ֵͼƬ�� ��ַ��%s"), csfullPath);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);
	}

	return retVal;
}

LONG CToHvShowCtrl::SavePlateBin2BMP(LPCTSTR strFileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG		retVal = RETVAL_OK;
	NET_DVR_PLATE_RESULT	stPlateInfo;

	if (strFileName == NULL)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��Ч����"));
		return RETVAL_INVALID_PARAM;
	}
	if (m_RecvPlateBinImageFlag == 0)
	{
		// ���ڲ�����ͼƬ
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ǰ������ͼƬ"));
		return RETVAL_NOT_RECV_PIC;
	}
	memset(&stPlateInfo, 0, sizeof(NET_DVR_PLATE_RESULT));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#else
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && m_cBufferManager.GetPlateInfo(&stPlateInfo) == false)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��ȡͼƬʧ��"));;
		return RETVAL_GET_PLATE_INFO_ERROR;
	}
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	CString csfullPath;
	csfullPath.Format(_T("%s"),strFileName);
	if (csfullPath.GetLength() >= MAX_PATH)
	{ 
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("ͼƬ·��������ץͼʧ��"));;
		return -1;
	}
	if (CreateFileDir(csfullPath) == FALSE)
	{
		return -1;
	}

#ifndef ONE_DEVICE
	char * pchpic = GetBufferManagerByUid(m_lCurrentUid)->GetPicBuffer(2);
#else
	char * pchpic = m_cBufferManager.GetPicBuffer(2);
#endif

	if (pchpic != NULL && stPlateInfo.dwBinPicLen != 0)
	{
		memset(m_pchPlateBinBMP,0,m_iBinBMPSize);
		if(0 == ConvertBin2BmpData((BYTE *)pchpic,(BYTE *)m_pchPlateBinBMP,&m_iBinBMPSize))
		{
			if (SavePic(csfullPath, (BYTE *)m_pchPlateBinBMP, m_iBinBMPSize) == FALSE)
			{
				WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("���泵�ƶ�ֵͼBMPʧ��"));
				retVal = RETVAL_SAVE_PIC_ERROR;
			}
		}
		else
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("ת�����ƶ�ֵͼBMPʧ��"));
			retVal = RETVAL_SAVE_PIC_ERROR;
		}
	}
	else
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("û�г��ƶ�ֵͼBMP"));
		retVal = RETVAL_HAVE_NO_IMAGE;
	}
	if (retVal == RETVAL_OK)
	{
		CString		csLog;
		csLog.Format(_T("���泵�ƶ�ֵBMPͼƬ�� ��ַ��%s"), csfullPath);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, csLog);
	}
	return retVal;
}

BSTR CToHvShowCtrl::GetImageRecTime(LONG lImgType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here
	NET_DVR_PLATE_RESULT		stPlateInfo;
	memset(&stPlateInfo, 0, sizeof(stPlateInfo));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == true)
	{
		USES_CONVERSION;
		strResult.Format(_T("%s"),A2W((char *)(stPlateInfo.byAbsTime)));//yyyy4mm6dd8hh10mm12ss14xxx
		strResult.Insert(14,_T('-'));
		strResult.Insert(12,_T(':'));
		strResult.Insert(10,_T(':'));
		strResult.Insert(8,_T(' '));
		strResult.Insert(6,_T('-'));
		strResult.Insert(4,_T('-'));
	}
	else
	{
		strResult = _T("");
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == true)
	{
		USES_CONVERSION;
		strResult.Format(_T("%s"),A2W((char *)(stPlateInfo.byAbsTime)));//yyyy4mm6dd8hh10mm12ss14xxx
		strResult.Insert(14,_T('-'));
		strResult.Insert(12,_T(':'));
		strResult.Insert(10,_T(':'));
		strResult.Insert(8,_T(' '));
		strResult.Insert(6,_T('-'));
		strResult.Insert(4,_T('-'));
	}
	else
	{
		strResult = _T("");
	}
#endif

	return strResult.AllocSysString();
}

BSTR CToHvShowCtrl::GetImageFileName(LONG lImgType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here
	NET_DVR_PLATE_RESULT		stPlateInfo;
	memset(&stPlateInfo, 0, sizeof(stPlateInfo));
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->GetPlateInfo(&stPlateInfo) == true)
	{
		//����·��
		CString csGetTimeDir;
		CString csFileName;
		USES_CONVERSION;
		csGetTimeDir.Format(_T("%s"),A2W((char *)(stPlateInfo.byAbsTime)));
		csFileName.Format(_T("%s"),csGetTimeDir.Right(9));
		csFileName.Insert(9,_T('-'));
		csFileName.Insert(6,_T('-'));
		///////////////////////////////////////////////////////////////////////
		switch(lImgType)
		{
		case 0:
			{
				csFileName += _T("fullimg.jpg");
			}
			break;
		case 1:
			{
				csFileName += _T("plateimg.jpg");
			}
			break;
		case 2:
			{
				csFileName += _T("binimg.bin");
			}
			break;
		case 3:
			{
				csFileName += _T("driver.jpg");
			}
			break;
		case 4:
			{
				csFileName += _T("binimg.bmp");
			}
			break;
		default:
			{
				csFileName += _T("fullimg.jpg");
			}
		}
		strResult.Format(_T("%s\\%s\\%s\\%s"), m_csImagePath, GetIPAddrByUid(m_lCurrentUid),csGetTimeDir.Left(8),csFileName);
	}
#else
	if (m_cBufferManager.GetPlateInfo(&stPlateInfo) == true)
	{
		//����·��
		CString csGetTimeDir;
		CString csFileName;
		USES_CONVERSION;
		csGetTimeDir.Format(_T("%s"),A2W((char *)(stPlateInfo.byAbsTime)));
		csFileName.Format(_T("%s"),csGetTimeDir.Right(9));
		csFileName.Insert(9,_T('-'));
		csFileName.Insert(6,_T('-'));
		///////////////////////////////////////////////////////////////////////
		switch(lImgType)
		{
		case 0:
			{
				csFileName += _T("fullimg.jpg");
			}
			break;
		case 1:
			{
				csFileName += _T("plateimg.jpg");
			}
			break;
		case 2:
			{
				csFileName += _T("binimg.bin");
			}
			break;
		case 3:
			{
				csFileName += _T("driver.jpg");
			}
			break;
		case 4:
			{
				csFileName += _T("binimg.bmp");
			}
			break;
		default:
			{
				csFileName += _T("fullimg.jpg");
			}
		}
		strResult.Format(_T("%s\\%s\\%s\\%s"), m_csImagePath, m_csIPAddr,csGetTimeDir.Left(8),csFileName);
	}
#endif

	if (strResult.GetLength() >= MAX_PATH)
	{ 
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("ͼƬ·��������ץͼʧ��"));
		strResult = _T("");
		return strResult.AllocSysString();
	}
	return strResult.AllocSysString();
}

BSTR CToHvShowCtrl::GetImageDataFromMem(LONG lImgType, VARIANT* pVarImg, LONG* lImgSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CToHvShowCtrl::SendData( CString CtrlName, char *pdata, long datalen, long iType, resultMSG *pmsg )
{
	bool freturn(false);
	bool find(false);
	if( m_fChangingCtrlName || CtrlName.IsEmpty() )
		return freturn;
	int icount = (int)m_ArrayDispatch.GetCount(); // ע��������麬������OLE�ؼ�, �������˵����λ�ȡ
	for( int i = 0;i < icount; i++ )
	{
		DispatchArray arraydis;
		memset(&arraydis,0,sizeof(DispatchArray));
		arraydis = m_ArrayDispatch.GetAt(i);
		CComDispatchDriver drivertmp(arraydis.lpunknow);
		if( CtrlName.Compare(arraydis.Name) == 0 )
		{
			VARIANT v1,v2;
			CComVariant var(datalen);
			CComVariant vartype(iType);
			VariantInit(&v1);
			VariantInit(&v2);
			v1.vt= VT_BYREF|VT_I1;
			v1.pcVal = pdata;
			v2 = var;
			if( pdata == NULL )
			{
				drivertmp.Invoke0(L"Clean");
			}
			else
			{
				drivertmp.Invoke1(L"SetType",&vartype,0);	//���ñ�����������
				HRESULT hr = drivertmp.Invoke2(L"SetData",&v1,&v2,0);	//��������
				if( SUCCEEDED(hr) )
				{
					freturn = true;
				}
			}
			find = true;
			break;
		}
	}
	if(!find)// ����Ҳ�����ص�����ͷ�������Ϣ��ʽ
	{
		HWND   hwndafter =   ::FindWindowEx(m_hWndParent,NULL,NULL,CtrlName);
		if( hwndafter )
		{
			if( pdata == NULL||datalen == 0 )
				::SendMessage(hwndafter,MSG_REPAINT_RESULT,0,NULL);
			else
				::SendMessage(hwndafter,MSG_CLI_RESULT,0,(LPARAM)pmsg);
		}
	}
	return freturn;
}

/*��ȡ����OLE�ؼ�*/
void CToHvShowCtrl::EnumAllControlNames()
{
	//�����ȡ���ھ��
	IOleInPlaceSite *pOleInPlaceSite = NULL;
	if (NOERROR==m_pClientSite->QueryInterface(IID_IOleInPlaceSite, (LPVOID *)(&pOleInPlaceSite)))
	{
		HRESULT hresult = pOleInPlaceSite->GetWindow((HWND *)&m_hWndParent); 
		if(FAILED(hresult))
		{
			return;
		}
		pOleInPlaceSite->Release();
	}

	//ȡ����
	LPOLECONTAINER lpContainer = NULL;
	LPENUMUNKNOWN lpEnumUnk = NULL;
	HRESULT hr = m_pClientSite->GetContainer(&lpContainer);
	if(FAILED(hr)) 
	{
		return;
	}
	m_fChangingCtrlName = true;
	if (lpContainer == NULL)
		return;
	hr = lpContainer->EnumObjects(OLECONTF_EMBEDDINGS | OLECONTF_OTHERS,&lpEnumUnk);
	if(FAILED(hr)) 
	{
		lpContainer->Release();
		return;
	}
	m_ArrayDispatch.RemoveAll();
	LPUNKNOWN lpUnk = NULL;
	while (lpEnumUnk->Next(1, &lpUnk, NULL) == S_OK)
	{
		CComDispatchDriver driver(lpUnk);
		CComVariant var;
		hr = driver.GetPropertyByName(L"ControlName",&var);
		if(SUCCEEDED(hr)) 
		{
			CString szTmp((LPCWSTR)var.bstrVal);
			if(szTmp.IsEmpty())
			{
				continue;
			}
			DispatchArray arraydis;
			memset(&arraydis,0,sizeof(DispatchArray));
			arraydis.lpunknow = lpUnk;
			szTmp.Append(_T("\0"));
			wcscpy_s(arraydis.Name,MAX_PATH,szTmp.GetBuffer());
			szTmp.ReleaseBuffer();
			m_ArrayDispatch.Add(arraydis);
		}
	}
	lpEnumUnk->Release();
	lpContainer->Release();
	m_fChangingCtrlName = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////��־ģ��

/** @fn		VOID CToHvShowCtrl::WriteLogFile(LPCTSTR szLog) 
 *	@brief	д��־
 *	@param	[IN]	szFun	������
 *	@param	[IN]	bError	�Ƿ�Ϊ����
 *	@param	[IN]	szLog	��־����
 *	@return	void
 */
VOID CToHvShowCtrl::WriteLogFile(LPCTSTR szFun, BOOL bError, LPCTSTR szLog) 
{
	if (m_LogFile == 0 || m_hLogFile == NULL || m_hMutexLogFile == NULL)
	{
		return ;
	}
	SetFilePointer(m_hLogFile, 0, NULL, FILE_END);
	CTime	cCurrentTime = CTime::GetCurrentTime();
	CString csLog = _T("");
	CString	csTmp = _T("");
	DWORD	dwLen = 0;
	char	szPrint[512];

	csLog = cCurrentTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	if (bError)
	{
		csTmp.Format(_T("\t%s:ERROR:\t%s"), szFun, szLog);
	}
	else
	{
		csTmp.Format(_T("\t%s:\t%s"), szFun, szLog);
	}
	csLog += csTmp;
	sprintf_s(szPrint,512,"%s\r\n", (CT2A)csLog);

	if (WaitForSingleObject(m_hMutexLogFile, INFINITE) != WAIT_OBJECT_0)
	{
		return;
	}
	if (WriteFile(m_hLogFile, szPrint, strlen(szPrint) + 1, &dwLen, NULL) == FALSE)
	{
		ReleaseMutex(m_hMutexLogFile);
		return;
	}
	ReleaseMutex(m_hMutexLogFile);
}

/** @fn		BOOL CToHvShowCtrl::CreateLogFile()
 *	@brief	������־�ļ�
 *	@return	BOOL	true��ʾ��ȷ������ʧ��
 */
BOOL CToHvShowCtrl::CreateLogFile()
{
	if (m_hLogFile != NULL)
	{
		return TRUE;
	}

	CTime	cCurrentTime = CTime::GetCurrentTime();
	CString	csPath;
	int			iPos = 0;
	csPath.Format(_T("%s%4d_%2d_%2d_log.txt"),LOG_FILE_PATH, cCurrentTime.GetYear(), cCurrentTime.GetMonth(), cCurrentTime.GetDay());
	while((iPos=csPath.Find(_T('\\'),iPos+1)) != -1)
	{
		CreateDirectory(csPath.Left(iPos),NULL);
	}
	
	m_hLogFile = CreateFile(csPath, 
								GENERIC_WRITE|GENERIC_READ,
								FILE_SHARE_READ|FILE_SHARE_WRITE,
								NULL,
								OPEN_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if (m_hLogFile == INVALID_HANDLE_VALUE)
	{
		m_hLogFile = NULL;
		return FALSE;
	}
	
	//�ƶ��ļ�ָ�뵽���
	DWORD	dwRet = 0;
	dwRet = SetFilePointer(m_hLogFile, 0, NULL, FILE_END);
	if (dwRet == 0xFFFFFFFF)
	{
		CloseHandle(m_hLogFile);
		m_hLogFile = NULL;
		return FALSE;
	}
	if (m_hMutexLogFile == NULL)
	{
		m_hMutexLogFile = CreateMutex(NULL, FALSE, NULL);
		if (m_hMutexLogFile == NULL)
		{
			return FALSE;
		}
	}
	return TRUE;
}


/** @fn		BOOL CToHvShowCtrl::CreateFileDir(LPCTSTR lpPath)
 *	@brief	����ָ�����ļ���
 *	@param	[IN]	lpPath	�ļ�·��
 *	@return	BOOL	TRUE��ʾ�ɹ�������ʧ��
 */
BOOL CToHvShowCtrl::CreateFileDir(LPCTSTR lpPath)
{
	if (lpPath == NULL)
	{
		return FALSE;
	}
	int			iPos=0;
	CString		strFilePath;

	strFilePath.Format(_T("%s"), lpPath);
	while((iPos=strFilePath.Find(_T('\\'),iPos+1)) != -1)
	{
		CreateDirectory(strFilePath.Left(iPos),NULL);
	}

	if (_taccess(strFilePath,0) == FALSE)
	{
		if (DeleteFile(strFilePath) == FALSE)
		{
			CString	csTmp = _T("ɾ��ԭ���Ѿ����ڵ��ļ�ʧ�ܣ�");
			csTmp += strFilePath;
			WriteLogFile((CA2T)__FUNCTION__, TRUE, csTmp);
			return FALSE;
		}
	}
	return TRUE;
}



int CToHvShowCtrl::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  nNum = 0;          
	UINT  nSize = 0;         

	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&nNum, &nSize);
	if(nSize == 0)
	{
		return -1;  
	}
	pImageCodecInfo = (ImageCodecInfo*)(malloc(nSize));
	if(pImageCodecInfo == NULL)
	{
		return -1;
	}
	GetImageEncoders(nNum, nSize, pImageCodecInfo);
	for(UINT i = 0; i < nNum; ++i)
	{
		if( wcscmp(pImageCodecInfo[i].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[i].Clsid;
			free(pImageCodecInfo);
			return i;  
		}    
	}
	free(pImageCodecInfo);
	return -1;  
}



BOOL CToHvShowCtrl::ConvertImgBytes2HBITMAP(BYTE* pImageBuffer,DWORD dwImageDataLen, int iWidth, int iHeight, WCHAR *  szFilePath)
{
	if (pImageBuffer == NULL || dwImageDataLen <= 0 )
	{
		return FALSE;
	}

	BOOL bResult = FALSE;
	HGLOBAL hImageMemory= GlobalAlloc(GMEM_MOVEABLE,dwImageDataLen);
	if (hImageMemory != NULL)
	{
		BYTE *pImageMemory= (BYTE*)GlobalLock(hImageMemory);
		if (pImageMemory != NULL)
		{
			memcpy_s(pImageMemory,dwImageDataLen,pImageBuffer,dwImageDataLen);
			GlobalUnlock(hImageMemory);

			IStream *pIStream;
			if (CreateStreamOnHGlobal(hImageMemory, false, &pIStream) == S_OK)
			{
				Bitmap  img(pIStream);
				Bitmap* pThumbnail = static_cast<Bitmap*>(img.GetThumbnailImage(iWidth, iHeight, NULL, NULL));
				if (pThumbnail != NULL)
				{
					CLSID pngClsid;

					GetEncoderClsid(L"image/jpeg", &pngClsid);


					Status status = pThumbnail->Save(szFilePath,&pngClsid,NULL);
					if (status != Ok)
					{   
						bResult =  FALSE;
					}
					else
					{
						bResult = TRUE;
					}

					delete pThumbnail;
				}
				pIStream->Release(); 
			}
		}
		GlobalFree(hImageMemory); 
	}
	return bResult;
}


/** @fn		void CToHvShowCtrl::InsertNewPlate(LPNET_DVR_PLATE_RESULT pPlateInfo)
 *	@brief	�����³�����Ϣ
 *	@param	[IN]	pPlateInfo		������Ϣ
 *	@return	void
 */
void CToHvShowCtrl::InsertNewPlate(LPNET_DVR_PLATE_RESULT pPlateInfo)
{
	if (pPlateInfo == NULL)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("�յ��µĳ�����ϢΪ��,�ص���"));
		return ;
	}
#ifndef ONE_DEVICE
	if (GetBufferManagerByUid(m_lCurrentUid) != NULL && GetBufferManagerByUid(m_lCurrentUid)->InsertPlateInfo(pPlateInfo,this) == true)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("�յ��µĳ�����Ϣ�����뻺��,�ص���"));
		::PostMessage(this->m_hWnd,WM_USER+100,NULL,NULL);
		return;
	}
#else
	if (m_cBufferManager.InsertPlateInfo(pPlateInfo,this) == true)
	{
		WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("�յ��µĳ�����Ϣ�����뻺��,�ص���"));
		::PostMessage(this->m_hWnd,WM_USER+100,NULL,NULL);
		return;
	}
#endif
	WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("�յ��µĳ�����Ϣ���Ǵ��뻺��ʧ��,�ص���"));	
	return;
}


void CALLBACK MessageCallback (LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser)
{
	CToHvShowCtrl	*pMian	= (CToHvShowCtrl*)pUser;
	if (pMian == NULL)
	{
		return ;
	}
	if (lCommand != COMM_UPLOAD_PLATE_RESULT)
	{
		//���ǳ���ֱ�ӷ���
		return ;
	}
	if (pAlarmInfo == NULL)
	{
		return;
	}
#ifndef ONE_DEVICE
	USES_CONVERSION;
	pMian->m_lCurrentUid = pAlarmer->lUserID;
	CString strTmp;
	strTmp.Format(_T("New���ص�UidֵΪ��%d����Ч��Ϊ��%d , IPֵΪ %s, ��Ч��Ϊ�� %d"),pAlarmer->lUserID,pAlarmer->byUserIDValid,A2W((char*)(pAlarmer->sDeviceIP)),pAlarmer->byDeviceIPValid);
	pMian->WriteLogFile((CA2T)__FUNCTION__, FALSE, strTmp);
#endif
	LPNET_DVR_PLATE_RESULT	pPlate = (LPNET_DVR_PLATE_RESULT)pAlarmInfo;

	pMian->InsertNewPlate(pPlate);

}

/** @fn		VOID CToHvShowCtrl::SetUpAlarm()
 *	@brief	���ò���
 *	@return	LONG	0��ʾ�ɹ�������ʧ��
 */
LONG CToHvShowCtrl::SetUpAlarm()
{
	BOOL	bRet = FALSE;
	//��������
#ifndef ONE_DEVICE
	if (m_lLoginUid >= 0)
	{
		GetDevicePtrByUid(m_lLoginUid)->m_lAlarmHandle = NET_DVR_SetupAlarmChan_V30(m_lLoginUid);
		if (GetDevicePtrByUid(m_lLoginUid)->m_lAlarmHandle < 0)
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��������ʧ��"));
			return RETVAL_DEPLOYMEMT_FAIL;
		}
	}
	//���ò����ص�����
	bRet = NET_DVR_SetGuardMessageCallBack(GetDevicePtrByUid(m_lLoginUid)->m_lAlarmHandle,MessageCallback, this);
	if (bRet == FALSE)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("���ò����ص�����ʧ��"));
		return RETVAL_SET_ALARM_CALL_BACK_FAIL;
	}
#else
	if (m_lUid >= 0)
	{
		m_lAlarmHandle = NET_DVR_SetupAlarmChan_V30(m_lUid);
		if (m_lAlarmHandle < 0)
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��������ʧ��"));
			return RETVAL_DEPLOYMEMT_FAIL;
		}
	}
#endif

	WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��������"));
	return RETVAL_OK;
}


/** @fn		LONG CToHvShowCtrl::CleanAlarm()
 *	@brief	��������
 *	@return	LONG	0��ʾ�ɹ��� ����ʧ��
 */
LONG CToHvShowCtrl::CleanAlarm()
{
	BOOL	bRet = TRUE;
#ifndef ONE_DEVICE
	EnterCriticalSection(&m_csVecLock);
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while (iter != m_vecDeviceInfoTable.end())
	{
		if((*iter)->m_lAlarmHandle >= 0)
		{
			if(!NET_DVR_CloseAlarmChan_V30((*iter)->m_lAlarmHandle))
			{
				CString tmp;
				tmp.Format(_T("��������ʧ��,���IPΪ %s"),(*iter)->m_csIPAddr);
				WriteLogFile((CA2T)__FUNCTION__, TRUE, tmp);
				bRet = FALSE;
			}
			else
			{
				(*iter)->m_lAlarmHandle = -1;
			}
		}
		iter++;
	}
	LeaveCriticalSection(&m_csVecLock);
	return bRet;
#else
	if (m_lAlarmHandle < 0)
	{
		return RETVAL_OK;
	}
	bRet = NET_DVR_CloseAlarmChan_V30(m_lAlarmHandle);
	if (bRet == FALSE)
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("��������ʧ��"));
		return RETVAL_CLEAN_ALARM_FAIL;
	}
	m_lAlarmHandle = -1;
	WriteLogFile((CA2T)__FUNCTION__, FALSE, _T("��������"));
	return RETVAL_OK;
#endif
}

/** @fn		BOOL CSCCPCtrl::SavePic(LPCTSTR lpPath, LPCTSTR lpPicName, BYTE * pImage, DWORD dwPicDataLen)
 *	@brief	����ͼƬ
 *	@param	[IN]	lpPath		ͼƬ·��
 *	@param	[IN]	lpPicName	ͼƬ����
 *	@param	[IN]	pImage		ͼƬ����
 *	@param	[IN]	dwPicDataLenͼƬ����
 *	@return	BOOL	true��ʾ�ɹ�������ʧ��
 */
BOOL CToHvShowCtrl::SavePic(LPCTSTR strFileName, BYTE * pImage, DWORD dwPicDataLen)
{
	if (pImage == NULL || dwPicDataLen <= 0 
		|| strFileName == NULL)
	{
		return FALSE;
	}
	
	//CString csPath(lpPath);
	//�����"\"��β,ɾ��"\"
	//if (csPath.GetAt(csPath.GetLength() - 1) == _T('\\'))
	//{
	//	csPath.Delete(csPath.GetLength() - 1);
	//}
	//����·��
	CString csFullPath;
	csFullPath.Format(_T("%s"),strFileName);
	if (csFullPath.GetLength() >= MAX_PATH)
	{ 
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("ͼƬ·��������ץͼʧ��"));
		return FALSE;
	}
	//��·�����еģ��ĳ�#��
	//strFileName.Replace('?', '#');
	if (CreateFileDir(csFullPath) == FALSE)
	{
		return FALSE;
	}
	//дͼƬ�ļ�
	FILE* file;
	try
	{
		_tfopen_s(&file,csFullPath, _T("wb"));
		if (file == NULL) 
		{
			WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("����ͼƬ�ļ�ʧ�ܣ�"));
			return false;
		}
		fwrite(pImage, dwPicDataLen, 1, file);
		fclose(file);
	}
	catch (...)
	{
		if (file != NULL) 
		{
			fclose(file);
		}
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("����ͼƬ�ļ�����"));
		return false;
	}
	return true;
}


/***************************************************
�������ƣ�BinImageFormatConvert(BYTE *pByteBinPacked,int iWidth = 112,int iHeight=20)
�������ܣ���ֵͼ���ʽת����ת��Ϊ�ʺ�bmp�洢��ʽ
����˵����pBytePinPacked(BYTE*):ָ��ͼ�󻺳�����ָ��
	iWidth(int):
	iHeigth(int):��ֵͼ��Ŀ�Ⱥ͸߶�
����ֵ��1����ʾת���ɹ�
��ע�� ��
***************************************************/
int CToHvShowCtrl::BinImageFormatConvert(BYTE *pByteBinPacked,int iWidth, int iHeight)
{
	int i;
    int iWidthBytes = iWidth>>3;
	BYTE *pByteTemp;
	BYTE *pByteTemp2;
	BYTE *pByteTemp3;
	BYTE  sImageByte,sImageByte2;
	pByteTemp = new BYTE[iWidthBytes*iHeight];
    ASSERT(pByteTemp!=NULL);
	
	pByteTemp2 = pByteTemp + iWidthBytes*(iHeight-1);
	pByteTemp3 = pByteBinPacked;
	//���µߵ�ת��
	for(i=0;i<iHeight;i++)
	{
		memcpy(pByteTemp2,pByteTemp3,iWidthBytes);
		pByteTemp3+=iWidthBytes;
		pByteTemp2-=iWidthBytes;
	}
	memcpy(pByteBinPacked,pByteTemp,iWidthBytes*iHeight);
	
	//�ֽ���ǰ��bitλ����
	for(i=0;i<iWidthBytes*iHeight;i++)
	{
		sImageByte = pByteBinPacked[i];
		sImageByte2 = (BYTE)((sImageByte&0x80)>0);  
		sImageByte2 +=(BYTE)(((sImageByte&0x40)>0)<<1);
        sImageByte2 +=(BYTE)(((sImageByte&0x20)>0)<<2);
		sImageByte2 +=(BYTE)(((sImageByte&0x10)>0)<<3);
		sImageByte2 +=(BYTE)(((sImageByte&0x08)>0)<<4);
		sImageByte2 +=(BYTE)(((sImageByte&0x04)>0)<<5);
		sImageByte2 +=(BYTE)(((sImageByte&0x02)>0)<<6);
		sImageByte2 +=(BYTE)(((sImageByte&0x01)>0)<<7);
		pByteBinPacked[i] = sImageByte2;
	}
	delete [] pByteTemp;
	pByteTemp = NULL;
	return 1;
}

/*******************************************************************************
��������
	ConvertBin2BmpData
������
	����ֵ����ת��BMP���ݡ�
������
	BYTE *pByteBinPacked,			//��ֵͼ����
	BYTE *pByteBmpData				//Ҫ���ɵ�BMP����
	unsigned int *pnBmpDataLength	//���ɵ�BMP���ݵĴ�С
����ֵ��
	int
		0	�����ɹ�
		!=0	����ʧ��
��ע��
*******************************************************************************/
int CToHvShowCtrl::ConvertBin2BmpData(BYTE *pByteBinPacked, BYTE *pByteBmpData, unsigned int *pnBmpDataLength)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//
	if( pByteBmpData == NULL || pByteBinPacked == NULL)
	{
		return -1;
	}
	UINT dwBmpDataSize =  0;
	BYTE *pByteBmpDataTmp = pByteBmpData;
	//ת��BIN���ݸ�ʽ
	BinImageFormatConvert(
		pByteBinPacked,
		112, 20
		);
	//
	int iIndex;
	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER bmpih;
	RGBQUAD *bmpcolormap;
	
	bmpfh.bfType = 0x4D42; //"BM";	
	bmpfh.bfReserved1 = 0;
	bmpfh.bfReserved2 = 0;
	bmpfh.bfOffBits = sizeof(BITMAPFILEHEADER) + 
		sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*2;
	
	bmpih.biSize = sizeof(BITMAPINFOHEADER);
	bmpih.biWidth = 112;
	bmpih.biHeight = 20;
	bmpih.biPlanes = 1;
	bmpih.biBitCount = 1;
	bmpih.biCompression = 0;
	bmpih.biXPelsPerMeter = 0;
	bmpih.biYPelsPerMeter = 0;
	bmpih.biClrUsed = 0;
	bmpih.biClrImportant = 0;
	
	int ibyteWidth= (bmpih.biWidth*bmpih.biBitCount+31)/32*4;
    bmpih.biSizeImage = ibyteWidth * bmpih.biHeight;
	
	bmpfh.bfSize = bmpfh.bfOffBits + bmpih.biSizeImage;
    bmpcolormap =(RGBQUAD*) new BYTE[sizeof(RGBQUAD)*(1<<bmpih.biBitCount)];
	//ASSERT(bmpcolormap!=NULL);
	//��ɫ��
	for (iIndex=0; iIndex<2; iIndex++)
	{
		bmpcolormap[iIndex].rgbBlue =
			bmpcolormap[iIndex].rgbGreen =
			bmpcolormap[iIndex].rgbRed = iIndex*255;
		bmpcolormap[iIndex].rgbReserved = 0;
	}
	
	//ͼ������У��
	BYTE *pImageTemp;//[16*20];
	pImageTemp = (BYTE*) new BYTE[ibyteWidth * bmpih.biHeight];
    //ASSERT(pImageTemp!=NULL);
	
	int iWidthPacked = bmpih.biWidth>>3;
	memset(pImageTemp, 0, ibyteWidth * bmpih.biHeight);
	BYTE *pImageTemp2 = pImageTemp;
	BYTE *pImageTemp3 = pByteBinPacked;
	for(iIndex=0; iIndex<bmpih.biHeight; iIndex++)
	{
		memcpy(pImageTemp2, pImageTemp3, iWidthPacked);
		pImageTemp2 += ibyteWidth;
		pImageTemp3 += iWidthPacked;
	}	
	//
	memcpy( pByteBmpDataTmp, &bmpfh, sizeof(BITMAPFILEHEADER) );
	pByteBmpDataTmp += sizeof(BITMAPFILEHEADER);
	dwBmpDataSize += sizeof(BITMAPFILEHEADER);
	memcpy( pByteBmpDataTmp, &bmpih, sizeof(BITMAPINFOHEADER) );
	pByteBmpDataTmp += sizeof(BITMAPINFOHEADER);
	dwBmpDataSize += sizeof(BITMAPINFOHEADER);
	memcpy( pByteBmpDataTmp, bmpcolormap, sizeof(RGBQUAD)*2 );
	pByteBmpDataTmp += sizeof(RGBQUAD)*2;
	dwBmpDataSize += sizeof(RGBQUAD)*2;
	memcpy( pByteBmpDataTmp, pImageTemp, bmpih.biSizeImage );
	dwBmpDataSize += bmpih.biSizeImage;
	//
	*pnBmpDataLength = dwBmpDataSize;
	//
	delete[] pImageTemp;
	pImageTemp = NULL;
	delete[] bmpcolormap;
	bmpcolormap = NULL;
	
	return 0;
}
/** @fn		void CToHvShowCtrl::OnDestroy()
 *	@brief	������Ϣ
 *	@return	void
 */
void CToHvShowCtrl::OnDestroy()
{
#ifndef ONE_DEVICE
	Disconnect();
#else
	if(m_lUid>=0)
	{
		Disconnect();
	}
#endif
	if (m_hMutexLogFile != NULL)
	{
		CloseHandle(m_hMutexLogFile);
		m_hMutexLogFile = NULL;
	}
	if (m_hLogFile != NULL)
	{
		CloseHandle(m_hLogFile);
		m_hLogFile = NULL;
	}
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	COleControl::OnDestroy();
}


#ifndef ONE_DEVICE
CString CToHvShowCtrl::GetIPAddrByUid(LONG uid)//��ȡ�豸IP
{
	EnterCriticalSection(&m_csVecLock);
	CString csRet = _T("");
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while(iter != m_vecDeviceInfoTable.end())
	{
		if((*iter)->m_lUid == uid)
		{
			csRet = (*iter)->m_csIPAddr;
			LeaveCriticalSection(&m_csVecLock);
			return csRet;
		}
		iter++;
	}
	LeaveCriticalSection(&m_csVecLock);
	return csRet;
}

CString CToHvShowCtrl::GetPortByUid(LONG uid)//��ȡ�豸�˿�
{
	EnterCriticalSection(&m_csVecLock);
	CString csRet = _T("");
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while(iter != m_vecDeviceInfoTable.end())
	{
		if((*iter)->m_lUid == uid)
		{
			csRet = (*iter)->m_csPort;
			LeaveCriticalSection(&m_csVecLock);
			return csRet;
		}
		iter++;
	}
	LeaveCriticalSection(&m_csVecLock);
	return csRet;
}

LONG CToHvShowCtrl::GetAlarmHandleByUid(LONG uid)//��ȡ�������
{
	EnterCriticalSection(&m_csVecLock);
	LONG lRet = -1;
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while(iter != m_vecDeviceInfoTable.end())
	{
		if((*iter)->m_lUid == uid)
		{
			lRet = (*iter)->m_lAlarmHandle;
			LeaveCriticalSection(&m_csVecLock);
			return lRet;
		}
		iter++;
	}
	LeaveCriticalSection(&m_csVecLock);
	return lRet;
}

CBufferManager * CToHvShowCtrl::GetBufferManagerByUid(LONG uid)//��ȡ��������� 
{
	CString strTmp;
	strTmp.Format(_T("New������UidֵΪ��%d"),uid);
	WriteLogFile((CA2T)__FUNCTION__, FALSE, strTmp);
	EnterCriticalSection(&m_csVecLock);
	CBufferManager * pCBuff = NULL;
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while(iter != m_vecDeviceInfoTable.end())
	{
		strTmp.Format(_T("New����������������UidֵΪ��%d"),(*iter)->m_lUid);
		WriteLogFile((CA2T)__FUNCTION__, FALSE, strTmp);
		if((*iter)->m_lUid == uid)
		{
			pCBuff = ((*iter)->m_cBufferManager);
			LeaveCriticalSection(&m_csVecLock);
			return pCBuff;
		}
		iter++;
	}
	LeaveCriticalSection(&m_csVecLock);
	if(pCBuff == NULL )
	{
		WriteLogFile((CA2T)__FUNCTION__, TRUE, _T("New����ȡ������������ʧ�ܣ�����"));
	}
	return pCBuff;
}

pDeviceInfo CToHvShowCtrl::GetDevicePtrByUid(LONG uid)//��ȡ�豸��Ϣ�ṹ��ָ��
{
	EnterCriticalSection(&m_csVecLock);
	pDeviceInfo pDevice = NULL;
	std::vector<pDeviceInfo>::iterator iter = m_vecDeviceInfoTable.begin();
	while(iter != m_vecDeviceInfoTable.end())
	{
		if((*iter)->m_lUid == uid)
		{
			pDevice = (pDeviceInfo)(*iter);
			LeaveCriticalSection(&m_csVecLock);
			return pDevice;
		}
		iter++;
	}
	LeaveCriticalSection(&m_csVecLock);
	return pDevice;
}
#endif