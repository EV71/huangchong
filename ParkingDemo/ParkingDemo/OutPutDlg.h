#pragma once
#include "HCNetSDK.h"
#include "afxwin.h"
#include <gdiplus.h>
#pragma  comment (lib, "gdiplus.lib")
using namespace Gdiplus;

class COutPutDlg : public CDialog
{
	DECLARE_DYNAMIC(COutPutDlg)

public:
	COutPutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COutPutDlg();

// �Ի�������
	enum { IDD = IDD_OUTPUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_strLeftPlateNo;
	CString m_strRightPlateNo;
	int m_iLeftPlaceNo;
	int m_iRightPlaceNo;
	BOOL m_bHasLeftVehicle;
	BOOL m_bHasRightVehicle;

	int m_iNum;
	BOOL m_bSeleted;
	int m_iUserId;
	int m_iChanId;
	long m_lPlayHandle;

	// ѡ�д˻���
	void SelectThis(void);
	// ȡ��ѡ�д˻���
	void CancelSelect(void);
	// �ڴ˻��沥��
	void PlayThis(int iUserId, int iChanId);
	// ֹͣ�˻��沥��
	void StopThis(void);
	// ǿ��ˢ�´���
	void RefreshThis(void);

	void UpdateWindow(void);
	void ResetWindow(void);

	NET_DVR_DISPLAY_PARA m_struCardPlayParam;//m_struCardPlayPara


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	COLORREF m_RedColor;  //��ɫ
	COLORREF m_GreenColor;//��ɫ
	COLORREF m_BlackColor;//��ɫ

	CBrush m_RedBrush;    // ��ɫ��ˢ
	CBrush m_GreenBrush;  // ��ɫ��ˢ


	//*****************************


	
	

	CStatic m_Static_Pic;
	virtual BOOL OnInitDialog();

	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();



	CDC*             g_DC;
	CRect            g_rect;
	CRITICAL_SECTION g_cs;
	BOOL    m_bCsDlg;

	void DrawPicture(int iPicSize, unsigned char* pic); 

	
};
