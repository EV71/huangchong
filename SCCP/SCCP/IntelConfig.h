#pragma once


// CIntelConfig dialog

//#define   DLL_TEST	
#undef	  DLL_TEST

class CIntelConfig : public CDialog
{
	DECLARE_DYNAMIC(CIntelConfig)

public:
	CIntelConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIntelConfig();

	void SetIntelCfgDeviceInfo(NET_INTELCFG_DEVLOGININFO *pDevInfo);

	// Dialog Data
	enum { IDD = IDD_DIALOG_INTEL_CONFIG };
	typedef enum _INTELE_ERR_CODE
	{      
		INTEL_ERR_NO = 0,                 //�޴���
		INTEL_ERR_MODULE_NOTFOUND,        //δ�ҵ���������ģ���ļ�
		INTEL_ERR_LOADMODULE_FAILED,      //��������ģ��ʧ��
		INTEL_ERR_LOADFUNCTION_FAILED,    //��ʼ������ģ�麯����ʧ��
		INTEL_ERR_SYSCHANEXCEPTION,       //ͨ���쳣
		INTEL_ERR_NOTHIKDEVICE,           //�Ǻ����豸
		INTEL_ERR_INVALIDCHANTYPE,        //�豸ͨ�����Ͳ��Ϸ�
		INTEL_ERR_GETCTRLCFG_FAILED       //��ȡͨ��������Ϣʧ��
	}INTEL_ERR_CODE;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnPlateCfgDlgDestroy(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	void SetDlgRect(CRect rtDlg);
	bool CreateIntelCfgModuleWnd();
	bool ShowIntelCfgModuleChanCfg();
	bool ShowIntelCfgModuleDevCfg();
	bool InitIntelCfgModFunc();


private:
	NET_INTELCFG_DEVLOGININFO		m_stDevLoginInfo;

	/*�������ÿ⵼���������Ͷ���*/
	typedef bool(__stdcall *NET_DVR_CreateWndFunc)(LPNET_INTELCFG_WNDPARAM pIntelWndParam);
	typedef bool(__stdcall *NET_DVR_SetIntelDevCfgFunc)(LPNET_INTELCFG_DEVLOGININFO pDevLoginInfo);
	typedef bool(__stdcall *NET_DVR_SetIntelChanCfgFunc)(LPNET_INTELCFG_DEVLOGININFO pDevLoginInfo);
	typedef bool(__stdcall *NET_DVR_DllPreTranslateMessageFunc)(MSG *pMsg);
	typedef bool(__stdcall *NET_DVR_DestroyDlgFunc)(bool bExit /* = false */);
	typedef bool(__stdcall *NET_DVR_SetShowRuleTabFunc)(bool bShowRuleTab /* = false */);
	typedef void(__stdcall *NET_DVR_SetMonitorInfoFunc)(LPNET_INTELCFG_MONITORINFO pMonitorInfo);



	//�������ÿ⵼������ָ��
	HMODULE								m_hIntelCfgModule;
	NET_DVR_CreateWndFunc				m_pNET_DVR_CreateWndFunc;
	NET_DVR_SetIntelDevCfgFunc			m_pNET_DVR_SetIntelDevCfgFunc;
	NET_DVR_SetIntelChanCfgFunc			m_pNET_DVR_SetIntelChanCfgFunc;
	NET_DVR_DllPreTranslateMessageFunc	m_pNET_DVR_DllPreTranslateMessageFunc;
	NET_DVR_DestroyDlgFunc				m_pNET_DVR_DestroyDlgFunc;
	NET_DVR_SetShowRuleTabFunc			m_pNET_DVR_SetShowRuleTabFunc;
	NET_DVR_SetMonitorInfoFunc          m_pNET_DVR_SetMonitorInfoFunc;

public:
	afx_msg void OnDestroy();
	afx_msg void OnClose();
};
