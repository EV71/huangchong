
// VoiceTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VoiceTest.h"
#include "VoiceTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVoiceTestDlg �Ի���




CVoiceTestDlg::CVoiceTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVoiceTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVoiceTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CVoiceTestDlg::PreTranslateMessage(MSG* pMsg) 
{	
    if(WM_KEYDOWN == pMsg->message)
    {
        CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDINPUT);
        ASSERT(pEdit);
        if(pMsg->hwnd == pEdit->GetSafeHwnd() && VK_RETURN == pMsg->wParam)
        {
            NextDlgCtrl();
            OnBnClickedButton1();
            return TRUE;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CVoiceTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, &CVoiceTestDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CVoiceTestDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CVoiceTestDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CVoiceTestDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CVoiceTestDlg ��Ϣ�������

BOOL CVoiceTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVoiceTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVoiceTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVoiceTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVoiceTestDlg::OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here
    CString cstrInput;
    GetDlgItemText(IDC_EDINPUT,cstrInput);
    if(!(cstrInput.IsEmpty()))
    {
        USES_CONVERSION;
        m_TDKJClass.TDKJ_Cmd(W2A(cstrInput.GetBuffer(0)));
        cstrInput.ReleaseBuffer();
    }
}

void CVoiceTestDlg::OnBnClickedButton2()
{
    // TODO: Add your control notification handler code here
    int iParkingTime = 0;
    CString cstrShouldPay;
    CString cstrFinalPay;
    iParkingTime = GetDlgItemInt(IDC_EDPARKTIME);
    GetDlgItemText(IDC_EDSHOULDPAY,cstrShouldPay);
    GetDlgItemText(IDC_EDFINALPAY,cstrFinalPay);
    if(iParkingTime > 0)
    {
        USES_CONVERSION;
        m_TDKJClass.TDKJ_VoiceShow(iParkingTime,atof(W2A(cstrShouldPay.GetBuffer(0))),atof(W2A(cstrFinalPay.GetBuffer(0))));
    }
}

void CVoiceTestDlg::OnBnClickedButton3()
{
    // TODO: Add your control notification handler code here
    m_TDKJClass.TDKJ_Wait();
}

void CVoiceTestDlg::OnBnClickedButton4()
{
    // TODO: Add your control notification handler code here
    m_TDKJClass.TDKJ_Clear();
}
