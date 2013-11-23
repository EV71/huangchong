
// SccpTestDlg.h : header file
//

#pragma once
#include "sccpctrl1.h"

#define	RETVAL_OK							0x0		///< ��ȷ
#define RETVAL_DEPLOYMEMT_FAIL				0x1		///< ����ʧ��
#define	RETVAL_SET_ALARM_CALL_BACK_FAIL		0x2		///< ���ñ����ص�����ʧ��
#define RETVAL_CLEAN_ALARM_FAIL				0x3		///< ��������ʧ��
#define RETVAL_CANCEL						0x4		///< ȡ��

#define RETVAL_ERROR						-0x1	///< ����
#define RETVAL_STOP_REALPLAY_ERROR			-0x2	///< ֹͣԤ������
#define RETVAL_LOGOUT_ERROR					-0x3	///< �ǳ��豸ʧ��
#define RETVAL_LOGIN_ERROR					-0x4	///< ��¼�豸ʧ��
#define RETVAL_DEVICE_NOT_LOGIN				-0x5	///< �豸û�е�¼
#define RETVAL_REALPLAY_ERROR				-0x6	///< Ԥ��ʧ��
#define RETVAL_INVALID_PARAM				-0x7	///< ��Ч����
#define RETVAL_GET_PLATE_INFO_ERROR			-0x8	///< ��ȡ������Ϣʧ��
#define RETVAL_SAVE_PIC_ERROR				-0x9	///< ����ͼƬʧ��
#define RETVAL_HAVE_NO_IMAGE				-0xA	///< û��ͼƬ
#define RETVAL_NOT_RECV_PIC					-0xB	///< ��ǰ����²�����ͼƬ
#define RETVAL_SHOOT_ERROR					-0xC	///< ץ��ʧ��
#define RETVAL_DEVICE_CONNECT_ERROR			-0xD	///< �豸������
// CSccpTestDlg dialog
class CSccpTestDlg : public CDialog
{
// Construction
public:
	CSccpTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCCPTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private:
	CSccpctrl1 m_ctlSccp;
protected:
	HICON m_hIcon;
	bool m_isStart;
	void SetStatus(int iRet);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	DECLARE_EVENTSINK_MAP()
	void OnPlateReceiveSccpctrl1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedBtsetcode();
};
