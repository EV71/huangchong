#pragma once


// CPlaceInfoDlg �Ի���

class CPlaceInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlaceInfoDlg)

public:
	CPlaceInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlaceInfoDlg();

// �Ի�������
	enum { IDD = IDD_PLACEINFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iChanNo;
	int m_iLeftPlaceNo;
	int m_iRightPlaceNo;
};
