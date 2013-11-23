#pragma once


#include "hiksadp.h"
#include <vector>

#define SADP_TEST

/** @struct	 _SADPINFO_
* @brief	 SADP��Ϣ
*/
#define		WM_SADP							WM_USER + 26	//�豸Ѳ��
typedef struct _SADPINFO_
{
	CString		strSeries;				///< ������				
	CString		strDeviceID;			///< �豸ID
	CString		strNetworkAddr;			///< �����ַ
	CString		strDevIP;				///< �豸IP
	CString		strSubnetMask;			///< ��������
	CString		strSoftwareVersion;		///< ����汾
	CString		strDspVersion;			///< Dsp�汾
	CString		strStartTime;			///< ����ʱ��
	int			nDevType;				///< �豸����
	int			nDevPort;				///< �豸�˿�
	int			nChanNum;				///< ͨ����Ŀ
	int			nDiskNum;				///< ������Ŀ
	int			nResult;				///< ���
}SADPINFO,*PSADPINFO;

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
typedef PINFO_ADAPTER (__stdcall *PFN_SADP_SYSINFO)();
typedef LONG (__stdcall *PFN_SADP_GETADAPNUM)();
typedef BOOL (__stdcall *PFN_SADP_SENDSETUSERPASSWORD)(char* desDLC,char* desIP,char* subnetmask,char* passwd,char* port);

// CSadpDlg dialog
class CSadpDlg : public CDialog
{
	DECLARE_DYNAMIC(CSadpDlg)

public:
	CSadpDlg(HMODULE	 hSadpModule,CWnd* pParent = NULL);   // standard constructor
	//inline CSadpDlg()
	//{
	//	this->m_hSadpModule = hSadpModule;
	//}
	virtual ~CSadpDlg();

// Dialog Data
	enum { IDD = IDD_DLG_SADP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnMsgSadp(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLvnDeleteItemListDevice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListDevice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnCancelModify();
	afx_msg void OnBnClickedBtnSaveDevParam();
	afx_msg void OnBnClickedBtnSelDevice();
	afx_msg void OnBnClickedBtnRefreshList();

	DECLARE_MESSAGE_MAP()
	void InitCtrlState();
	void UpdateCtrlState();
	void InitDevListCols();
	void ArrangeDevListSize();
	void Add2DevList(const SADPINFO *pSadpInfo);
	void DelDeviceFromList(const SADPINFO* pSadpInfo);
	void UpdateDeviceList(const SADPINFO* pSadpInfo,int nDeviceIndex = -1);
	
	CString GetDeviceTypeName(int nDevType);
	int  GetDeviceIndex(const SADPINFO* pSadpInfo);
	BOOL ValidateParams();
	void ClearSadpInfo();
public:
	CString GetSelDeviceIP()   const;
	int     GetSelDevicePort() const;
	BOOL	InitSadpModuleFuncs();

public:
	CString						m_strDeviceID;			///< �豸ID
	CString						m_strSoftwareVer;		///< ����汾
	CString						m_strDevIP;				///< �豸IP
	CString						m_strSubnetMask;		///< ��������
	CString						m_strDevMac;			///< MAC��ַ
	CString						m_strAdminPwd;			///< ����
	int							m_nDevPort;				///< �˿�
	BOOL						m_bModifyDevice;		///< �Ƿ��޸�
	CIPAddressCtrl				m_ctrlDevIP;			///< �豸IP�ؼ�
	CIPAddressCtrl				m_ctrlSubnetMask;		///< ��������ؼ�
	CEdit						m_editDevPort;			///< �豸�˿ڿؼ�
	CListCtrl					m_listDevice;			///< �豸�б�ؼ�
	std::vector<SADPINFO *>		m_vSadpInfo;			///< �豸��Ϣ



	HMODULE						m_hSadpModule;
	PFN_SADP_STOP				m_pfnSadpStop;
	PFN_SADP_START				m_pfnSadpStart;
	PFN_SADP_SENDUPDATEIP		m_pfnSadpSendUpdateIP;

	afx_msg void OnBnClickedBtnModify2();
};
