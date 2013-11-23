// SadpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SCCP.h"
#include "SadpDlg.h"




// CSadpDlg dialog
#define DEVICETYPE_FILENAME TEXT("DeviceType.ini")
HWND g_hwndSadp = NULL;
void __stdcall fSadpDataCallBack(char* series,
								 char* deviceid,
								 char* hwaddr,
								 char* praddr,
								 char* subnetmask,
								 unsigned int dev_type,
								 unsigned int port,
								 unsigned int enccnt,
								 unsigned int hdiskcnt,
								 char* sfwversion, 
								 char* dspversion, 
								 char* starttime,
								 int result);

IMPLEMENT_DYNAMIC(CSadpDlg, CDialog)

CSadpDlg::CSadpDlg(HMODULE hSadpModule,CWnd* pParent /*=NULL*/)
	: CDialog(CSadpDlg::IDD, pParent)
	,m_strDeviceID(_T(""))
	, m_strSoftwareVer(_T(""))
	, m_nDevPort(0)
	, m_strDevMac(_T(""))
	, m_bModifyDevice(FALSE)
	, m_strAdminPwd(_T(""))
{
	m_vSadpInfo.clear();
	this->m_hSadpModule = hSadpModule;
}

CSadpDlg::~CSadpDlg()
{
	ClearSadpInfo();
}

void CSadpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_listDevice);
	DDX_Text(pDX, IDC_EDIT_DEVICEID, m_strDeviceID);
	DDX_Text(pDX, IDC_EDIT_SOFTWAREVERSION, m_strSoftwareVer);
	DDX_Text(pDX, IDC_EDIT_DEVPORT, m_nDevPort);
	DDX_Text(pDX, IDC_EDIT_DEVMAC, m_strDevMac);
	DDX_Text(pDX, IDC_IPADDRESS_DEVIP,m_strDevIP);
	DDX_Text(pDX, IDC_IPADDRESS_SUBNETMASK,m_strSubnetMask);
	DDX_Text(pDX, IDC_EDIT_ADMINPWD, m_strAdminPwd);
	DDX_Control(pDX, IDC_IPADDRESS_DEVIP, m_ctrlDevIP);
	DDX_Control(pDX, IDC_IPADDRESS_SUBNETMASK, m_ctrlSubnetMask);
	DDX_Control(pDX, IDC_EDIT_DEVPORT, m_editDevPort);

}


BEGIN_MESSAGE_MAP(CSadpDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SADP, &CSadpDlg::OnMsgSadp)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_DEVICE, &CSadpDlg::OnLvnDeleteItemListDevice)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEVICE, &CSadpDlg::OnNMClickListDevice)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DEVICE, &CSadpDlg::OnNMRClickListDevice)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CSadpDlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_CANCELMODIFY, &CSadpDlg::OnBnClickedBtnCancelModify)
	ON_BN_CLICKED(IDC_BTN_SAVEDEVPARAM, &CSadpDlg::OnBnClickedBtnSaveDevParam)
	ON_BN_CLICKED(IDC_BTN_SELDEVICE, &CSadpDlg::OnBnClickedBtnSelDevice)
	ON_BN_CLICKED(IDC_BTN_REFRESHLIST, &CSadpDlg::OnBnClickedBtnRefreshList)
	ON_BN_CLICKED(IDC_BTN_MODIFY2, &CSadpDlg::OnBnClickedBtnModify2)
END_MESSAGE_MAP()


// CSadpDlg message handlers

BOOL CSadpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	if (InitSadpModuleFuncs() == FALSE)
	{
		AfxMessageBox(_T("������ʼ��ʧ��"));
		EndDialog(1);
		return false;
	}

	InitDevListCols();
	ArrangeDevListSize();

	g_hwndSadp = GetSafeHwnd();
	CString	strErrMsg;

	if (!m_pfnSadpStart(fSadpDataCallBack))
	{
		strErrMsg.Format(TEXT("�����豸������̳�ʼ��ʧ��(ʧ��ԭ��:������⹦��ʧ��)"));
		AfxMessageBox(strErrMsg);
		EndDialog(IDCANCEL);
		return FALSE;
		
	}
	
	InitCtrlState();	

	return TRUE;  
}

HBRUSH CSadpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CSadpDlg::OnDestroy()
{
	m_pfnSadpStop();
	//if(m_hSadpModule)
	//{
	//	FreeLibrary(m_hSadpModule);
	//	m_hSadpModule = NULL;
	//}
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

/** @fn		void CSadpDlg::InitDevListCols()
 *	@brief	��ʼ���豸�б�ؼ�
 *	@return	void
 */
void CSadpDlg::InitDevListCols()
{
	m_listDevice.InsertColumn(0,TEXT("���"),LVCFMT_CENTER);
	m_listDevice.InsertColumn(1,TEXT("�豸����"),LVCFMT_CENTER);
	m_listDevice.InsertColumn(2,TEXT("IP��ַ"),LVCFMT_LEFT);
	m_listDevice.InsertColumn(3,TEXT("�˿�"),LVCFMT_CENTER);
	m_listDevice.InsertColumn(4,TEXT("�豸���к�"),LVCFMT_LEFT);
	m_listDevice.InsertColumn(5,TEXT("��������"),LVCFMT_CENTER);
	m_listDevice.InsertColumn(6,TEXT("�����ַ"),LVCFMT_CENTER);
	m_listDevice.InsertColumn(7,TEXT("ͨ����"),LVCFMT_CENTER);
	m_listDevice.InsertColumn(8,TEXT("����汾"),LVCFMT_LEFT);
	m_listDevice.InsertColumn(9,TEXT("DSP�汾"),LVCFMT_LEFT);
	m_listDevice.InsertColumn(10,TEXT("����ʱ��"),LVCFMT_LEFT);
	m_listDevice.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}

/** @fn		void CSadpDlg::ArrangeDevListSize()
 *	@brief	��ʼ���豸�б��С
 *	@return	void
 */
void CSadpDlg::ArrangeDevListSize()
{
	CRect rcDevList;
	m_listDevice.GetClientRect(&rcDevList);

	int nDevListWidth  = rcDevList.Width();
	int nPerWidth = 35;
	m_listDevice.SetColumnWidth(0, nPerWidth * 2);
	m_listDevice.SetColumnWidth(1, nPerWidth * 3);
	m_listDevice.SetColumnWidth(2, nPerWidth * 4);
	m_listDevice.SetColumnWidth(3, nPerWidth * 2);
	m_listDevice.SetColumnWidth(4, nPerWidth * 8);
	m_listDevice.SetColumnWidth(5, nPerWidth * 4);
	m_listDevice.SetColumnWidth(6, nPerWidth * 4);
	m_listDevice.SetColumnWidth(7, nPerWidth * 2);
	m_listDevice.SetColumnWidth(8, nPerWidth * 4);
	m_listDevice.SetColumnWidth(9, nPerWidth * 4);
	m_listDevice.SetColumnWidth(10,nPerWidth * 4);
}

/** @fn		void CSadpDlg::UpdateCtrlState()
 *	@brief	���¿ؼ�״̬
 *	@return	void
 */
void CSadpDlg::UpdateCtrlState()
{   
	GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(!m_bModifyDevice);
	GetDlgItem(IDC_BTN_MODIFY2)->EnableWindow(!m_bModifyDevice);
	GetDlgItem(IDC_BTN_CANCELMODIFY)->EnableWindow(m_bModifyDevice);
	GetDlgItem(IDC_BTN_SAVEDEVPARAM)->EnableWindow(m_bModifyDevice);
	((CEdit*)(GetDlgItem(IDC_EDIT_DEVPORT)))->EnableWindow(m_bModifyDevice);
	((CEdit*)(GetDlgItem(IDC_EDIT_ADMINPWD)))->EnableWindow(m_bModifyDevice);
	((CEdit*)(GetDlgItem(IDC_EDIT_DEVPORT)))->EnableWindow(m_bModifyDevice);
	GetDlgItem(IDC_IPADDRESS_DEVIP)->EnableWindow(m_bModifyDevice);
	GetDlgItem(IDC_IPADDRESS_SUBNETMASK)->EnableWindow(m_bModifyDevice);
}

/** @fn		void CSadpDlg::InitCtrlState()
 *	@brief	��ʼ���ؼ�״̬
 *	@return	void
 */
void CSadpDlg::InitCtrlState()
{
	GetDlgItem(IDC_IPADDRESS_DEVIP)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS_SUBNETMASK)->EnableWindow(FALSE);
	((CEdit*)(GetDlgItem(IDC_EDIT_DEVPORT)))->EnableWindow(TRUE);
	((CEdit*)(GetDlgItem(IDC_EDIT_ADMINPWD)))->EnableWindow(FALSE);
	((CEdit*)(GetDlgItem(IDC_EDIT_DEVPORT)))->EnableWindow(FALSE);
	((CEdit*)(GetDlgItem(IDC_EDIT_ADMINPWD)))->SetLimitText(PASSWD_LEN);
	GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_MODIFY2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CANCELMODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SAVEDEVPARAM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SELDEVICE)->EnableWindow(FALSE);
	m_editDevPort.SetLimitText(5);
}

/** @fn		BOOL CSadpDlg::InitSadpModuleFuncs()
 *	@brief	��ʼ��Sadpģ�麯��
 *	@return	BOOL	TRUE��ʾ�ɹ�������ʧ��
 */
BOOL CSadpDlg::InitSadpModuleFuncs()
{
	//CString strModuleName = _T("Sadp.dll");
	//m_hSadpModule = LoadLibrary(strModuleName);
	//if (m_hSadpModule == NULL)
	//{
	//	return false;
	//}

	m_pfnSadpSendUpdateIP = (PFN_SADP_SENDUPDATEIP)GetProcAddress(m_hSadpModule, "SADP_SendUpdateIp");
	if (m_pfnSadpSendUpdateIP == NULL)
	{
		return false;
	}

	m_pfnSadpStart	= (PFN_SADP_START)GetProcAddress(m_hSadpModule, "SADP_Start");
	if (m_pfnSadpStart == NULL)
	{
		return false;
	}
	m_pfnSadpStop = (PFN_SADP_STOP)GetProcAddress(m_hSadpModule, "SADP_Stop");
	if (m_pfnSadpStop == NULL)
	{
		return false;
	}
	return TRUE;
}

/** @fn		LRESULT CSadpDlg::OnMsgSadp(WPARAM wParam,LPARAM lParam)
 *	@breif	�豸�����Ϣ
 *	@param	[IN]	wParam	��Ϣ����
 *	@param	[IN]	lParam	��Ϣ����
 *	@return	LRESULT	��Ϣ����ֵ
 */
LRESULT CSadpDlg::OnMsgSadp(WPARAM wParam,LPARAM lParam)
{
	SADPINFO* pSadpInfo = (SADPINFO*)wParam;
	if (pSadpInfo == NULL)
	{
		return 0;
	}
	switch(pSadpInfo->nResult)
	{
	case SADP_RESTART:	
	case SADP_ADD:		
		Add2DevList(pSadpInfo);
		break;
	case SADP_DEC:		
		DelDeviceFromList(pSadpInfo);
		break;
	case SADP_UPDATE:	
		UpdateDeviceList(pSadpInfo);
		break;
	default:
		break;
	}

	return 0;
}

/** @fn		void CSadpDlg::Add2DevList(const SADPINFO* pSadpInfo)
 *	@brief	���豸�б������豸
 *	@param	[IN]	pSadpInfo	�豸��Ϣ
 *	@return	void
 */
void CSadpDlg::Add2DevList(const SADPINFO* pSadpInfo)
{
	if (pSadpInfo == NULL)
	{
		return;
	}
	int nDeviceIndex = GetDeviceIndex(pSadpInfo);
	if (nDeviceIndex == -1)
	{
		int nItemIndex = m_listDevice.GetItemCount();
		CString strTmpText = TEXT("");
		CString strDevNo   = TEXT("");;
		strDevNo.Format(TEXT("%04d"),nItemIndex);
		m_listDevice.InsertItem(nItemIndex,strDevNo);
		m_listDevice.SetItemText(nItemIndex,1,GetDeviceTypeName(pSadpInfo->nDevType));
		m_listDevice.SetItemText(nItemIndex,2,pSadpInfo->strDevIP);
		strTmpText.Format(TEXT("%d"),pSadpInfo->nDevPort);
		m_listDevice.SetItemText(nItemIndex,3,strTmpText);
		strTmpText.Format(TEXT(" %s"),pSadpInfo->strDeviceID);
		m_listDevice.SetItemText(nItemIndex,4,strTmpText);
		m_listDevice.SetItemText(nItemIndex,5,pSadpInfo->strSubnetMask);
		m_listDevice.SetItemText(nItemIndex,6,pSadpInfo->strNetworkAddr);
		strTmpText.Format(TEXT("%d"),pSadpInfo->nChanNum);
		m_listDevice.SetItemText(nItemIndex,7,strTmpText);
		m_listDevice.SetItemText(nItemIndex,8,pSadpInfo->strSoftwareVersion);
		m_listDevice.SetItemText(nItemIndex,9,pSadpInfo->strDspVersion);
		m_listDevice.SetItemText(nItemIndex,10,pSadpInfo->strStartTime);
		m_vSadpInfo.push_back((SADPINFO*)pSadpInfo);
	}
	else
	{
		UpdateDeviceList(pSadpInfo,nDeviceIndex);
	}
}

/** @fn		void CSadpDlg::DelDeviceFromList(const SADPINFO* pSadpInfoSrc)
 *	@brief	���豸�б���ɾ������
 *	@param	[IN]	pSadpInfoSrc	ɾ����Ϣ
 *	@return	void
 */
void CSadpDlg::DelDeviceFromList(const SADPINFO* pSadpInfoSrc)
{
	if (pSadpInfoSrc == NULL)
	{
		return;
	}
	int nDeviceIndex = GetDeviceIndex(pSadpInfoSrc);
	if (nDeviceIndex != -1)
	{
		SADPINFO *pSadInfo = m_vSadpInfo[nDeviceIndex];

		m_listDevice.DeleteItem(nDeviceIndex);
		std::vector<PSADPINFO>::iterator iter = m_vSadpInfo.begin();
		while (nDeviceIndex)
		{
			iter ++;
			nDeviceIndex --;
		}
		m_vSadpInfo.erase(iter);
		delete pSadInfo;
	}
	delete pSadpInfoSrc;
}

/** @fn		void CSadpDlg::UpdateDeviceList(const SADPINFO* pUpdateSadpInfo,int nUpdateDevIndex )
 *	@brief	�����豸�б�
 *	@param	[IN]	pUpdateSadpInfo	Ҫ���µ��豸��Ϣ
 *	@param	[IN]	pUpdateDevIndex	Ҫ���µ��豸���
 *	@return	void
 */
void CSadpDlg::UpdateDeviceList(const SADPINFO* pUpdateSadpInfo,int nUpdateDevIndex /*= -1*/)
{
	if (pUpdateSadpInfo == NULL)
	{
		return;
	}
	int nDesDevIndex = nUpdateDevIndex;
	if (nDesDevIndex == -1)
	{
		nDesDevIndex = GetDeviceIndex(pUpdateSadpInfo);
	}
	if (nDesDevIndex >= 0 && nDesDevIndex < m_listDevice.GetItemCount())
	{
		CString strTmpText;
		m_listDevice.SetItemText(nDesDevIndex ,1,GetDeviceTypeName(pUpdateSadpInfo->nDevType));
		m_listDevice.SetItemText(nDesDevIndex ,2,pUpdateSadpInfo->strDevIP);
		strTmpText.Format(TEXT(" %s"),pUpdateSadpInfo->strDeviceID);
		m_listDevice.SetItemText(nDesDevIndex ,4,strTmpText);
		m_listDevice.SetItemText(nDesDevIndex ,5,pUpdateSadpInfo->strSubnetMask);
		m_listDevice.SetItemText(nDesDevIndex ,6,pUpdateSadpInfo->strNetworkAddr);
		strTmpText.Format(TEXT("%d"),pUpdateSadpInfo->nChanNum);
		m_listDevice.SetItemText(nDesDevIndex ,7,strTmpText);
		m_listDevice.SetItemText(nDesDevIndex ,8,pUpdateSadpInfo->strSoftwareVersion);
		m_listDevice.SetItemText(nDesDevIndex ,9,pUpdateSadpInfo->strDspVersion);
		m_listDevice.SetItemText(nDesDevIndex ,10,pUpdateSadpInfo->strStartTime);
		SADPINFO* pSadpInfoDest = m_vSadpInfo[nDesDevIndex];
		if (pSadpInfoDest != NULL)
		{
			delete pSadpInfoDest;
		}
		m_vSadpInfo[nDesDevIndex] =(SADPINFO*) pUpdateSadpInfo;
	}
}

/** @fn		int CSadpDlg::GetDeviceIndex(const SADPINFO* pSadpInfoSrc)
 *	@brief	��ȡ�豸���б��еı��
 *	@param	[IN]	pSadpInfoSrc	�豸��Ϣ
 *	@return	int		�豸���б��еı��
 */
int CSadpDlg::GetDeviceIndex(const SADPINFO* pSadpInfoSrc)
{
	int nDeviceIndex = -1;
	if (pSadpInfoSrc != NULL)
	{   
		int nItemCount = m_vSadpInfo.size();
		for (int i = 0; i < nItemCount; i++)
		{
			SADPINFO* pSadpInfoDest = (SADPINFO*)m_vSadpInfo[i];
			if (pSadpInfoDest != NULL)
			{    
				CString strNetworkAddrSrc = pSadpInfoSrc->strNetworkAddr;
				CString strNetworkAddDest = pSadpInfoDest->strNetworkAddr;
				if (   strNetworkAddDest.CompareNoCase(strNetworkAddrSrc) == 0
					&& pSadpInfoDest->nDevPort == pSadpInfoSrc->nDevPort)
				{
					nDeviceIndex = i;
					break;
				}
			}
		}
	}
	return nDeviceIndex;
}

/** @fn		void CSadpDlg::OnLvnDeleteItemListDevice(NMHDR *pNMHDR, LRESULT *pResult)
 *	@brief	ɾ���豸
 *	@param	[IN]	pNMHDR	��Ϣ����
 *	@param	[OUT]	pResult	����ֵ
 *	@return	void
 */
void CSadpDlg::OnLvnDeleteItemListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
// 	int nItemIndex     = pNMLV->iItem;
// 	if (nItemIndex != -1)
// 	{
// 		SADPINFO* pSadpInfo = m_vSadpInfo(nItemIndex);
// 		if (pSadpInfo != NULL)
// 		{
// 			delete pSadpInfo;
// 		}
// 	}
	*pResult = 0;
}

/** @fn		CString CSadpDlg::GetDeviceTypeName(int nDevType)
 *	@brief	��ȡ�豸��������
 *	@param	[IN]	nDevType	�豸����
 *	@return	CString	�豸����
 */
CString CSadpDlg::GetDeviceTypeName(int nDevType)
{   
	CString strModuleFileName;
	CString strModuleFileDir;
	CString strDevTypeFilePath;
	GetModuleFileName(NULL,strModuleFileName.GetBuffer(MAX_PATH),MAX_PATH);
	strModuleFileName.ReleaseBuffer();

	int nFlashPos = strModuleFileName.ReverseFind(TEXT('\\'));
	strModuleFileDir = strModuleFileName.Left(nFlashPos);
	if (strModuleFileDir.Right(1) != TEXT("\\"))
	{
		strModuleFileDir += TEXT("\\");
	}
	strDevTypeFilePath += strModuleFileDir + DEVICETYPE_FILENAME;

	CString strDevTypeNum;
	strDevTypeNum.Format(TEXT("%d"),nDevType);

	CString strDevTypeName;
	GetPrivateProfileString(TEXT("Type"),strDevTypeNum, TEXT("δ֪"), strDevTypeName.GetBuffer(MAX_PATH), MAX_PATH, strDevTypeFilePath);
	strDevTypeName.ReleaseBuffer();
	return strDevTypeName;
}

/** @fn		void CSadpDlg::OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
 *	@brief	�����豸�б�
 *	@param	[IN]	pNMHDR	��������
 *	@param	[OUT]	pResult	����ֵ
 *	@return	void
 */
void CSadpDlg::OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		SADPINFO* pSadpInfo = m_vSadpInfo[pNMItemActivate->iItem];
		if (pSadpInfo != NULL)
		{
			m_strDeviceID    = pSadpInfo->strDeviceID;
			m_strSoftwareVer = pSadpInfo->strSoftwareVersion;
			m_strDevIP       = pSadpInfo->strDevIP;
			m_strSubnetMask  = pSadpInfo->strSubnetMask;
			m_nDevPort       = pSadpInfo->nDevPort;
			m_strDevMac      = pSadpInfo->strNetworkAddr;
		}
	}
	else
	{
		m_strDeviceID    = TEXT("");
		m_strSoftwareVer = TEXT("");
		m_strDevIP       = TEXT("");
		m_strSubnetMask  = TEXT("");
		m_nDevPort       = 8000;
		m_strDevMac      = TEXT("");
		m_strAdminPwd    = TEXT("");
		m_bModifyDevice  = FALSE;
	}
	GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(pNMItemActivate->iItem != -1);
	GetDlgItem(IDC_BTN_MODIFY2)->EnableWindow(pNMItemActivate->iItem != -1);
	GetDlgItem(IDC_BTN_SELDEVICE)->EnableWindow(pNMItemActivate->iItem != -1);
	UpdateData(FALSE);
	UpdateCtrlState();
	*pResult = 0;
}

/** @fn		void CSadpDlg::OnNMRClickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
 *	@brief	�һ��豸�б�
 *	@param	[IN]	pNMHDR	��������
 *	@param	[OUT]	pResult	����ֵ
 *	@return	void
 */
void CSadpDlg::OnNMRClickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickListDevice(pNMHDR,pResult);
}

/** @fn		void CSadpDlg::OnBnClickedBtnModify()
 *	@brief	����޸İ�ť
 *	@return	void
 */
void CSadpDlg::OnBnClickedBtnModify()
{
	m_bModifyDevice = TRUE;
	UpdateCtrlState();
}

/** @fn		void CSadpDlg::OnBnClickedBtnCancelModify()
 *	@brief	���ȡ���޸İ�ť
 *	@return	void
 */
void CSadpDlg::OnBnClickedBtnCancelModify()
{
	m_bModifyDevice = FALSE;
	UpdateCtrlState();
}

/** @fn		void CSadpDlg::OnBnClickedBtnSaveDevParam()
 *	@brief	������水ť
 *	@return	void
 */
void CSadpDlg::OnBnClickedBtnSaveDevParam()
{   
	UpdateData(TRUE);
	if (!ValidateParams())
	{
		return;
	}
	CString strDevPort;
	BOOL bResult;
	strDevPort.Format(TEXT("%d"),m_nDevPort);
	bResult = m_pfnSadpSendUpdateIP(CT2A(m_strDevMac),CT2A(m_strDevIP),CT2A(m_strSubnetMask),CT2A(m_strAdminPwd),CT2A(strDevPort));
	if(bResult)
	{
		AfxMessageBox(TEXT("�����豸�����ɹ�"));
		NET_DVR_DEVICEINFO_V30 stDeviceInfo;
		memset(&stDeviceInfo, 0, sizeof(stDeviceInfo));
		int lUserID = -1;
		lUserID = NET_DVR_Login_V30((CT2A)m_strDevIP, m_nDevPort, "admin", "12345", &stDeviceInfo);
		if(lUserID != -1)
		{
			NET_DVR_RebootDVR(lUserID);
			BOOL  bRet = NET_DVR_Logout(lUserID);
		}
	}
	else
	{
		AfxMessageBox(TEXT("�����豸����ʧ��"));
	}
}

/** @fn		void CSadpDlg::OnBnClickedBtnSelDevice()
 *	@brief	���ѡ���豸��ť
 *	@return	void
 */
void CSadpDlg::OnBnClickedBtnSelDevice()
{
	EndDialog(IDOK);
}

/** @fn		void CSadpDlg::OnBnClickedBtnRefreshList()
 *	@brief	���ˢ���б�ť
 *	@return	void
 */
void CSadpDlg::OnBnClickedBtnRefreshList()
{   
	m_listDevice.SetRedraw(FALSE);
	m_listDevice.DeleteAllItems();
	m_listDevice.SetRedraw(TRUE);
	ClearSadpInfo();
	m_pfnSadpStop();
	m_pfnSadpStart(fSadpDataCallBack);
		
}

/** @fn		CString CSadpDlg::GetSelDeviceIP() const
 *	@brief	��ȡѡ���IP
 *	@return	CString	ѡ���豸��IP
 */
CString CSadpDlg::GetSelDeviceIP() const
{
	return m_strDevIP;
}

/** @fn		int CSadpDlg::GetSelDevicePort() const
 *	@brief	��ȡѡ���豸�Ķ˿�
 *	@return	int	ѡ��Ķ˿�
 */
int CSadpDlg::GetSelDevicePort() const
{
	return m_nDevPort;
}

/** @fn		BOOL CSadpDlg::ValidateParams()
 *	@brief	�������Ƿ���ȷ
 *	@return	BOOL	TUREb��ʾ��ȷ������ʧ��
 */
BOOL CSadpDlg::ValidateParams()
{
	UpdateData(TRUE);

	BOOL bCheckValid  = TRUE;
	CString strErrMsg = TEXT("");
	DWORD dwDevIP;
	int nNonBlankField = m_ctrlDevIP.GetAddress(dwDevIP);
	if (bCheckValid && nNonBlankField < 4)
	{
		strErrMsg.Format(TEXT("�޸��豸����ʧ��(ʧ��ԭ��:�豸IP������)"));
		bCheckValid = FALSE;
	}
	nNonBlankField = m_ctrlSubnetMask.GetAddress(dwDevIP);
	if (bCheckValid && nNonBlankField < 4)
	{
		strErrMsg.Format(TEXT("�޸��豸����ʧ��(ʧ��ԭ��:�������벻����)"));
		bCheckValid = FALSE;
	}
	if (bCheckValid && (m_nDevPort <= 0 || m_nDevPort > 65535))
	{
		strErrMsg.Format(TEXT("�޸��豸����ʧ��(ʧ��ԭ��:�˿ں�Ӧ�� 1 - 65535֮��)"));
		bCheckValid = FALSE;
	}
	if (!bCheckValid)
	{
		AfxMessageBox(strErrMsg);
		return FALSE;
	}
	return TRUE;
}

/** @fn		void CSadpDlg::ClearSadpInfo()
 *	@brief	���Sadp����
 *	@return	void
 */
void CSadpDlg::ClearSadpInfo()
{
	PSADPINFO pSadpInfo;
	std::vector<PSADPINFO>::iterator iter;
	for (iter = m_vSadpInfo.begin(); iter != m_vSadpInfo.end(); iter ++)
	{
		pSadpInfo = *iter;
		if (pSadpInfo != NULL)
		{
			delete pSadpInfo;
		}
	}
	m_vSadpInfo.clear();
}


/** @fn		void __stdcall fSadpDataCallBack(char* series,
											char* deviceid,
											char* hwaddr,
											char* praddr,
											char* subnetmask,
											unsigned int dev_type,
											unsigned int port,
											unsigned int enccnt, 
											unsigned int hdiskcnt,
											char* sfwversion,
											char* dspversion, 
											char* starttime,
											int result)
 *	@brief	�豸���ص�����
 *	@param	��
 *	@return	void
 */
void __stdcall fSadpDataCallBack(char* series,
								 char* deviceid,
								 char* hwaddr,
								 char* praddr,
								 char* subnetmask,
								 unsigned int dev_type,
								 unsigned int port,
								 unsigned int enccnt, 
								 unsigned int hdiskcnt,
								 char* sfwversion,
								 char* dspversion, 
								 char* starttime,
								 int result)
{

	try
	{
		SADPINFO* pSadpInfo = new SADPINFO;
		pSadpInfo->strSeries.Format(TEXT("%s"),CA2T(series));
		pSadpInfo->strDeviceID.Format(TEXT("%s"),CA2T(deviceid));
		pSadpInfo->strNetworkAddr.Format(TEXT("%s"),CA2T(hwaddr));
		pSadpInfo->strDevIP.Format(TEXT("%s"),CA2T(praddr));
		pSadpInfo->strSubnetMask.Format(TEXT("%s"),CA2T(subnetmask));
		pSadpInfo->strSoftwareVersion.Format(TEXT("%s"),CA2T(sfwversion));
		pSadpInfo->strDspVersion.Format(TEXT("%s"),CA2T(dspversion));
		pSadpInfo->strStartTime.Format(TEXT("%s"),CA2T(starttime));
		pSadpInfo->nDevType = dev_type;
		pSadpInfo->nDevPort = port;
		pSadpInfo->nChanNum = enccnt;
		pSadpInfo->nDiskNum = hdiskcnt;
		pSadpInfo->nResult  = result;

		if (IsWindow(g_hwndSadp) && enccnt == 2 && dev_type == 22392)
		{
			PostMessage(g_hwndSadp,WM_SADP,(WPARAM)pSadpInfo,0);
		}
	}
	catch(...)
	{
		//...
	}
	return;
}
void CSadpDlg::OnBnClickedBtnModify2()
{
	// TODO: Add your control notification handler code here
	NET_DVR_DEVICEINFO_V30 stDeviceInfo;
	memset(&stDeviceInfo, 0, sizeof(stDeviceInfo));
	int lUserID = -1;
	lUserID = NET_DVR_Login_V30((CT2A)m_strDevIP, m_nDevPort, "admin", "12345", &stDeviceInfo);
	if(lUserID != -1)
	{
		NET_DVR_RebootDVR(lUserID);
		BOOL  bRet = NET_DVR_Logout(lUserID);
		if(bRet)
		{
			AfxMessageBox(TEXT("�����ɹ�����ȴ��豸����..."));
		}
		else
		{
			AfxMessageBox(TEXT("LoginOut������ʧ�ܣ�"));
		}
	}
	else if(lUserID == -1)
	{
		AfxMessageBox(TEXT("Login������ʧ�ܣ�"));
	}
}
