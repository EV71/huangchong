#pragma once


// CAddDeviceDlg �Ի���

class CAddDeviceDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDeviceDlg)

public:
	CAddDeviceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddDeviceDlg();

// �Ի�������
	enum { IDD = IDD_ADDDEVICE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDeviceName;
	CString m_strDeviceIP;
	long m_lPort;
	CString m_strUserName;
	CString m_strPassWord;
	int m_iBeginPlaceNo;

	virtual BOOL OnInitDialog();

};
