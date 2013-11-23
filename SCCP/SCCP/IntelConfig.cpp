// IntelConfig.cpp : implementation file
//

#include "stdafx.h"
#include "SCCP.h"
#include "IntelConfig.h"
#define DLL_TEST

// CIntelConfig dialog

IMPLEMENT_DYNAMIC(CIntelConfig, CDialog)

CIntelConfig::CIntelConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CIntelConfig::IDD, pParent)
	,m_hIntelCfgModule(NULL)
	, m_pNET_DVR_CreateWndFunc(NULL)
	, m_pNET_DVR_SetIntelDevCfgFunc(NULL)
	, m_pNET_DVR_SetIntelChanCfgFunc(NULL)
	, m_pNET_DVR_DllPreTranslateMessageFunc(NULL)
	, m_pNET_DVR_DestroyDlgFunc(NULL)
	, m_pNET_DVR_SetMonitorInfoFunc(NULL)
{

}

CIntelConfig::~CIntelConfig()
{
}

void CIntelConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIntelConfig, CDialog)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_PLATECFGDLG_DETROY, &CIntelConfig::OnPlateCfgDlgDestroy)
END_MESSAGE_MAP()


// CIntelConfig message handlers

BOOL CIntelConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CenterWindow();

	SetWindowText(_T("��������"));
	SetDlgRect(CRect(0, 0, MINWIDTH + 7, MINHEIGHT + 30));

#ifdef DLL_TEST
	if (InitIntelCfgModFunc() == FALSE)
	{
		AfxMessageBox(_T("��������ʧ��(ʧ��ԭ��:���ӿ⺯������ʧ��)"));
		EndDialog(1);
		return false;
	}
#endif

	//��������ģ�鴴������
	if (!CreateIntelCfgModuleWnd())
	{
		AfxMessageBox(_T("��������ʧ��(ʧ��ԭ��:��������ʧ��)"));
		EndDialog(1);
		return false;
	}

	//��ʾ��������ģ��ͨ�����ý���
	ShowIntelCfgModuleChanCfg();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/** @fn		void CIntelConfig::SetIntelCfgDeviceInfo(NET_INTELCFG_DEVLOGININFO *pDevInfo)
 *	@brief	����������Ϣ
 *	@param	[IN]	pDevInfo	������Ϣ
 *	@return	void
 */
void CIntelConfig::SetIntelCfgDeviceInfo(NET_INTELCFG_DEVLOGININFO *pDevInfo)
{
	if (pDevInfo == NULL)
	{
		return;
	}

	memcpy(&m_stDevLoginInfo, pDevInfo, sizeof(NET_INTELCFG_DEVLOGININFO));
}



/** @fn		void CIntelConfig::SetDlgRect(CRect rtDlg)
 *	@brief	���öԻ���
 *	@param	[IN]	rtDlg	�Ի���λ��
 *	@return void
 */
void CIntelConfig::SetDlgRect(CRect rtDlg)
{
	//��ʼ����������λ��
	CRect rtWnd(0, 0, 0, 0);
	GetWindowRect(&rtWnd);
	rtWnd.right = rtWnd.left + rtDlg.Width();
	rtWnd.bottom = rtWnd.top + rtDlg.Height();

	MoveWindow(rtWnd);
}

/** @fn		bool CIntelConfig::CreateIntelCfgModuleWnd()
 *	@brief	�����������ÿⴰ��
 *	@return	bool	true��ʾ�ɹ�������ʧ��
 */
bool CIntelConfig::CreateIntelCfgModuleWnd()
{
#ifdef DLL_TEST
	if (m_pNET_DVR_CreateWndFunc == NULL)
	{
		return false;
	}
#endif
	//������Ϣ
	NET_INTELCFG_WNDPARAM struIntelCfgWndParam		=	{0};

	struIntelCfgWndParam.iTabShow					=	SUB_CONFIG_TAB_ARITH;
	struIntelCfgWndParam.iLanguage					=	LANG_CHI;
	struIntelCfgWndParam.hParWnd					=	m_hWnd;//GetSafeHwnd();
	struIntelCfgWndParam.rcWndRect.top				=	0;
	struIntelCfgWndParam.rcWndRect.bottom			=	struIntelCfgWndParam.rcWndRect.top + MINHEIGHT;
	struIntelCfgWndParam.rcWndRect.left				=	0;
	struIntelCfgWndParam.rcWndRect.right			=	struIntelCfgWndParam.rcWndRect.left + MINWIDTH;
	struIntelCfgWndParam.bFixedSize					=	true;

	struIntelCfgWndParam.clrPen						=	RGB(107,107,107);
	struIntelCfgWndParam.lbBackBrush.lbColor		=	RGB(204,204,204);
	struIntelCfgWndParam.lbBackBrush.lbStyle		=	BS_SOLID;
	struIntelCfgWndParam.lbTitleBkBrush.lbColor		=	RGB(148,148,148);
	struIntelCfgWndParam.lbTitleBkBrush.lbStyle		=	BS_SOLID;
	struIntelCfgWndParam.lbListTitleBkBr.lbColor	=	RGB(174,174,174);
	struIntelCfgWndParam.lbListTitleBkBr.lbStyle	=	BS_SOLID;
	struIntelCfgWndParam.lbStaticBkBrush.lbColor	=	RGB(209,209,209);
	struIntelCfgWndParam.lbStaticBkBrush.lbStyle	=	BS_SOLID;
	struIntelCfgWndParam.lbEditBrush.lbColor		=	RGB(228,228,228);
	struIntelCfgWndParam.lbEditBrush.lbStyle		=	BS_SOLID;
	struIntelCfgWndParam.lbSelBkBrush.lbColor		=	RGB(49,106,197);
	struIntelCfgWndParam.lbSelBkBrush.lbStyle		=	BS_SOLID;
#ifdef DLL_TEST
	return m_pNET_DVR_CreateWndFunc(&struIntelCfgWndParam);
#else
	return NET_DVR_CreateWnd(&struIntelCfgWndParam);
#endif
}

/** @fn		bool CIntelConfig::ShowIntelCfgModuleChanCfg()
 *	@brief	��ʾ��������ģ��ͨ�����ý���
 *	@return bool true ��ʾ�ɹ�������ʧ��
 */
bool CIntelConfig::ShowIntelCfgModuleChanCfg()
{
#ifdef DLL_TEST
	if (m_pNET_DVR_SetIntelChanCfgFunc == NULL)
	{
		return false;
	}
#endif
	NET_INTELCFG_MONITORINFO		stMonitorInfo;
	
	memset(&stMonitorInfo, 0, sizeof(NET_INTELCFG_MONITORINFO));
	sprintf_s(stMonitorInfo.chDevName,CHAN_INFO_LEN, "%s", m_stDevLoginInfo.chDevIP);
	sprintf_s(stMonitorInfo.chChanName,CHAN_INFO_LEN, "%d", m_stDevLoginInfo.iChanNum);
#ifdef DLL_TEST
	m_pNET_DVR_SetMonitorInfoFunc(&stMonitorInfo);
	
	return m_pNET_DVR_SetIntelChanCfgFunc(&m_stDevLoginInfo);
#else
	NET_DVR_SetMonitorInfo(&stMonitorInfo);
	return NET_DVR_SetChanIntelligentCfg(&m_stDevLoginInfo);
#endif
}

/** @fn		void CIntelConfig::OnDestroy()
 *	@brief	���ٴ���
 *	@return	void
 */
void CIntelConfig::OnDestroy()
{
#ifdef DLL_TEST
	if (m_pNET_DVR_DestroyDlgFunc != NULL)
	{
		m_pNET_DVR_DestroyDlgFunc(TRUE);
	}

	//ж��ģ��
	if (m_hIntelCfgModule != NULL)
	{
		FreeLibrary(m_hIntelCfgModule);
		m_hIntelCfgModule = NULL;
	}
#else
	NET_DVR_DestroyDlg(TRUE);
#endif
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
}

/** @fn		bool CIntelConfig::ShowIntelCfgModuleDevCfg()
 *	@brief	��ʾ�����豸��Դ���ý���
 *	@return	bool	true��ʾ�ɹ�������ʧ��
 */
bool CIntelConfig::ShowIntelCfgModuleDevCfg()
{
#ifdef DLL_TEST
	if (m_pNET_DVR_SetIntelDevCfgFunc == NULL)
	{
		return false;
	}
	return m_pNET_DVR_SetIntelDevCfgFunc(&m_stDevLoginInfo);
#else
	return NET_DVR_SetIntelligentCfg(&m_stDevLoginInfo);
#endif
}

void CIntelConfig::OnBnClickedOk()
{

}
void CIntelConfig::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

bool CIntelConfig::InitIntelCfgModFunc()
{
	//��ʼ������
	if (m_hIntelCfgModule != NULL)
	{
		FreeLibrary(m_hIntelCfgModule);
		m_hIntelCfgModule = NULL;
	}

	m_pNET_DVR_CreateWndFunc				=	NULL;
	m_pNET_DVR_SetIntelDevCfgFunc			=	NULL;
	m_pNET_DVR_SetIntelChanCfgFunc			=	NULL;
	m_pNET_DVR_DllPreTranslateMessageFunc	=	NULL;
	m_pNET_DVR_DestroyDlgFunc				=	NULL;
	m_pNET_DVR_SetShowRuleTabFunc			=   NULL;
	m_pNET_DVR_SetMonitorInfoFunc           =   NULL;



	CString strModuleName = _T("PlateConfigDll.dll");

	//����dll
	m_hIntelCfgModule = LoadLibrary(strModuleName);
	if (m_hIntelCfgModule == NULL)
	{
		return false;
	}

	//��ȡ���ÿⴴ�����ں�����ַ
	m_pNET_DVR_CreateWndFunc = (NET_DVR_CreateWndFunc)GetProcAddress(m_hIntelCfgModule, "NET_DVR_CreateWnd");
	if (m_pNET_DVR_CreateWndFunc == NULL)
	{
		return false;
	}

	m_pNET_DVR_SetIntelDevCfgFunc = (NET_DVR_SetIntelDevCfgFunc)GetProcAddress(m_hIntelCfgModule, "NET_DVR_SetIntelligentCfg");
	if (m_pNET_DVR_SetIntelDevCfgFunc == NULL)
	{
		return false;
	}

	m_pNET_DVR_SetIntelChanCfgFunc = (NET_DVR_SetIntelChanCfgFunc)GetProcAddress(m_hIntelCfgModule, "NET_DVR_SetChanIntelligentCfg");
	if (m_pNET_DVR_SetIntelChanCfgFunc == NULL)
	{
		return false;
	}

	m_pNET_DVR_DllPreTranslateMessageFunc = (NET_DVR_DllPreTranslateMessageFunc)GetProcAddress(m_hIntelCfgModule, "NET_DVR_DllPreTranslateMessage");
	if (m_pNET_DVR_DllPreTranslateMessageFunc == NULL)
	{
		return false;
	}

	m_pNET_DVR_DestroyDlgFunc = (NET_DVR_DestroyDlgFunc)GetProcAddress(m_hIntelCfgModule,"NET_DVR_DestroyDlg");
	if (m_pNET_DVR_DestroyDlgFunc == NULL)
	{
		return false;
	}
	m_pNET_DVR_SetMonitorInfoFunc = (NET_DVR_SetMonitorInfoFunc)GetProcAddress(m_hIntelCfgModule,"NET_DVR_SetMonitorInfo");
	if (m_pNET_DVR_SetMonitorInfoFunc == NULL)
	{
		return false;
	}
	return true;
}

/** @fn       LRESULT CIntelConfig::OnPlateCfgDlgDestroy(WPARAM wParam, LPARAM lParam)
  * @brief    �յ�������������ʱ��Ϣ�������Ի���Ҳ���йر�  
  * @param    WPARAM wParam  :
  * @param    LPARAM lParam  :
  * @return   LRESULT  
  */
LRESULT CIntelConfig::OnPlateCfgDlgDestroy(WPARAM wParam, LPARAM lParam)
{
	EndDialog(1);
#ifdef DLL_TEST
	if (m_pNET_DVR_DestroyDlgFunc != NULL)
	{
		m_pNET_DVR_DestroyDlgFunc(false);
	}
#else
	NET_DVR_DestroyDlg(false);
#endif

	return 1;
}