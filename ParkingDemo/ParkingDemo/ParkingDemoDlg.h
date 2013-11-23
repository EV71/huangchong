
// ParkingDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "HCNetSDK.h"
#include "OutPutDlg.h"
#include "GeneralDef.h"
#include <vector>
#include "afxwin.h"
#include "afxcmn.h"
using namespace std;


#define TREE_NODE_ROOT   0
#define TREE_NODE_DEVICE 1
#define TREE_NODE_CHAN   2

typedef struct _tagPlayWindow
{
	DWORD dwChanIndex; //ͨ��������ͨ��
	int iLeftPlaceNo;
	BOOL bHasLeftVehicle;
	CString strLeftPlate;	
	int iRightPlaceNo;
	BOOL bHasRightVehicle;
	CString strRightPlate;	
	_tagPlayWindow()
	{
		dwChanIndex = 0;
		iLeftPlaceNo = 0;
		bHasLeftVehicle = FALSE;
		strLeftPlate = "";		
		iRightPlaceNo = 0;
		bHasRightVehicle = FALSE;
		strRightPlate = "";	
	}
}PlayWindow;

typedef struct _tagDeviceInfo
{
	int  iUserId;
	//LONG lPlayHandle;
	LONG lAlarmHandle;
	
	char szDeviceName[64];
	char szDVRIP[16];
	WORD wDVRPort;
	char szUserName[32];
	char szPassword[32];
	BOOL bHasLogined;  //�Ƿ��Ѿ���¼
	BOOL bIsPlaying;   //�Ƿ����ڲ���

	HTREEITEM hDeviceItem; //��ǰDVR�豸�����

	PlayWindow struPlayWindow[MAX_OUTPUT_WINDOW_NUM];
	NET_DVR_DEVICEINFO_V30 lpDeviceInfo;	
	NET_DVR_IPPARACFG_V40 struIPParaCfgV40;
	STRU_CHANNEL_INFO struChanInfo[MAX_CHANNUM_V30*2]; //channel structure
	CHANNEL_INFO struZeroChan[16];	

	int iGroupNO;           //IP Group NO.
	int	iAnalogChanNum;		//analog channel number
	BOOL bIPRet;			//support IP conection
	LONG lFirstEnableChanIndex;	 //first enabled channel index

	 _tagDeviceInfo()
	 {
		 lAlarmHandle = -1;
		 iUserId = -1;
		 ZeroMemory(szDeviceName, sizeof(szDeviceName));
		 ZeroMemory(szDVRIP, sizeof(szDVRIP));
		 wDVRPort = 0;
		 ZeroMemory(szUserName, sizeof(szUserName));
		 ZeroMemory(szPassword, sizeof(szPassword));	
		 bHasLogined = FALSE;
		 bIsPlaying = FALSE; 
		 hDeviceItem = NULL;
		 ZeroMemory(&lpDeviceInfo, sizeof(lpDeviceInfo));
		 ZeroMemory(&struIPParaCfgV40, sizeof(struIPParaCfgV40));
		 ZeroMemory(&struChanInfo, sizeof(struChanInfo));
		 ZeroMemory(&struZeroChan, sizeof(struZeroChan));

		 iGroupNO = -1;
		 iAnalogChanNum = 0;
		 bIPRet	= FALSE;
		 lFirstEnableChanIndex = 0;
	 }
}DeviceInfo;

//CRITICAL_SECTION LOCK
class CGuard
{
public:
	CGuard(CRITICAL_SECTION *lpcsLock);
	~CGuard(void);
private:
	CRITICAL_SECTION *m_lpcsLock;
protected:
	CGuard(void);
};

inline CGuard::~CGuard(void)
{	
	LeaveCriticalSection(m_lpcsLock);	
}

inline CGuard::CGuard(CRITICAL_SECTION *lpcsLock)
: m_lpcsLock(lpcsLock)
{
	EnterCriticalSection(m_lpcsLock);
}

// CParkingDemoDlg �Ի���
class CParkingDemoDlg : public CDialog
{
// ����
public:
	CParkingDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CParkingDemoDlg(void);

// �Ի�������
	enum { IDD = IDD_PARKINGDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:		
	COutPutDlg m_OutPutWindow[MAX_OUTPUT_WINDOW_NUM];

	HWND hWnd;
	LONG lRealPlayHandle;
	afx_msg void OnBnClickedOk();

	CString GetLocalIPAddr();
	BOOL CheckIPStr(CString ip);

	void SetOutputWindow(int n);
	//void SelectOutputWindow(int num);

	int m_iTotalDeviceIndex; //�豸���
	int m_iCurDeviceIndex;   //��ǰ�豸��š�����
	int m_iCurChanIndex;     //��ǰͨ����š�����
	DWORD	  m_dwNodeData;  //���ֵ
	CString   m_strNodeText; //��������

	vector<DeviceInfo> m_vDevices;

	CTreeCtrl m_treeDevices;
	HTREEITEM m_hRoot;			//���ڵ���
	HTREEITEM m_hCurDeviceItem; //��ǰDVR�豸�����
	HTREEITEM m_hCurChanItem;  //��ǰͨ�������
	HTREEITEM m_hSelect;
	HTREEITEM m_hParent;
	HTREEITEM m_hItem;      //������ĵ�ת��Ϊ��ǰѡ��ľ��

	HTREEITEM m_hDeviceItem;//������豸�����
	afx_msg void OnNMClickTreeDevice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeDevice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreeDevice(NMHDR *pNMHDR, LRESULT *pResult);
	int GetCurDeviceIndex(void);

	void LoginAll(); //��¼��ǰDVR�µ�ȫ�����
	void LogoutAll();//ע����ǰDVR�µ�ȫ�����

	void ResetOutPutWindow();
	void DeleteTreeChanNode(HTREEITEM hDeviceItem);

	void PlayAll(void); //���ŵ�ǰDVR�µ�ȫ�����
	void StopAll(void);	//ֹͣ��ǰDVR�µ�ȫ�����
	BOOL UpdateUI(void);

	afx_msg void OnTreeDevicePlay();
	afx_msg void OnTreeDeviceStopPlay();
	afx_msg void OnTreeDeviceDelete();
	afx_msg void OnTreedeviceLogin();
	afx_msg void OnTreedeviceLogout();

	LONG m_lListenHandle;

	void StartListen();
	void StopListen(); 

	CRITICAL_SECTION m_csLock;
	HANDLE m_hParkThread;     //ͣ��������ˢ���߳̾��	    
	CEvent m_evParkInfo;  //�˳��߳��¼�

	BOOL m_IsThreadRun;
	void FreshParkData(int iIndex);
	afx_msg LRESULT OnUpdateOutPutWindow(WPARAM wParam,LPARAM lParam);
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTreedeviceProperty();

	BOOL DoSetIPAccessCfg(int iDeviceIndex);
	BOOL DoGetDeviceResoureCfg(int iDeviceIndex, int iChanIndex);
	void RefreshIPDevLocalCfg(int iDeviceIndex);


	afx_msg void OnChanPlaceInfo();
	// ���ڱ�ʾ�Ƿ�����ʶ�ϴ��ı���
	BOOL m_bListenning;
	afx_msg void OnBnClickedButtonEnableUploadData();

	afx_msg void OnBnClickedButtonSetUploadCfg();
	CString m_strHostIP;
	int m_iHostPort;
	//CComboBox m_comboUploadStrategy;
	int m_iUploadInterval;
	int m_iUploadTimeOut;
	BOOL m_bSuspendUpload;

	NET_ITS_UPLOAD_CFG m_struUploadCfg;
	LONG m_lChannel;
	void OnBtnGet();
	void DrawWindowPicture(int iWndIndex);
	
	BOOL m_checkPicData;
	void DrawWindowPicture(int iWndIndex,int iPicSize, unsigned char* pic);
	afx_msg void OnBnClickedCheckPicData();
};
