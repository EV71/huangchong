
// VoiceTestDlg.h : ͷ�ļ�
//

#pragma once

//#include "Tdbjq.h"
// CVoiceTestDlg �Ի���
#include "TDKJClass.h"
class CVoiceTestDlg : public CDialog
{
// ����
public:
	CVoiceTestDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_VOICETEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
    BOOL PreTranslateMessage(MSG* pMsg);

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
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    clsTDKJClass m_TDKJClass;
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
};
