
// WaveComDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "clsSMSModem.h"

// CWaveComDemoDlg �Ի���
class CWaveComDemoDlg : public CDialog
{
// ����
public:
	CWaveComDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WAVECOMDEMO_DIALOG };

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
    afx_msg void OnBnClickedBnconnect();
    afx_msg void OnBnClickedBnsend();
    afx_msg void OnBnClickedBnrecieve();
    afx_msg void OnBnClickedBndelindex();
    afx_msg void OnBnClickedBncheckauto();
    afx_msg void OnBnClickedBnchecknew();
    afx_msg void OnBnClickedBndisconnect();
    clsSMSModem m_clsSMSModem;
    afx_msg void OnClose();
};
