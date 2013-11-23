
// PicInfoToolDlg.h : ͷ�ļ�
//

#pragma once

#include "afxwin.h"
#include "DecProcess.h"
#include "ImageShowStatic.h"
// CPicInfoToolDlg �Ի���
class CPicInfoToolDlg : public CDialog
{
// ����
public:
	CPicInfoToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PICINFOTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
private:
	DecProcess m_DecProcess;
public:
	afx_msg void ClearAllContent();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CImageShowStatic m_ShowImage;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
