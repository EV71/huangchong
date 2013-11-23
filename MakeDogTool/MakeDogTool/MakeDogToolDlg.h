// MakeDogToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "config.h"
#ifndef BYTE
typedef unsigned char BYTE;
#endif 

#ifndef  WORD
typedef  unsigned short WORD;
#endif
// CMakeDogToolDlg �Ի���
class CMakeDogToolDlg : public CDialog
{
// ����
public:
	CMakeDogToolDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMakeDogToolDlg();
// �Ի�������
	enum { IDD = IDD_MAKEDOGTOOL_DIALOG };

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
	HBRUSH m_hbrush;
	bool m_bChangeStatus;
	CComboBox m_ccbDeviceType;
	CComboBox m_ccbSetPlatform;
	CComboBox m_ccbGetPlatform;
	CConfig *m_pConfig;
	afx_msg void OnBnClickedTestDog();
	afx_msg void OnBnClickedMakeDog();
	//afx_msg void OnBnClickedMakeFRDog();
	afx_msg void OnBnClickedReadDog();
	//afx_msg void OnBnClickedReadFRDog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
