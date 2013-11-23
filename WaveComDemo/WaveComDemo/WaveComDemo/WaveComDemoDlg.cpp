
// WaveComDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WaveComDemo.h"
#include "WaveComDemoDlg.h"

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


// CWaveComDemoDlg �Ի���




CWaveComDemoDlg::CWaveComDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaveComDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaveComDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWaveComDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BNCONNECT, &CWaveComDemoDlg::OnBnClickedBnconnect)
    ON_BN_CLICKED(IDC_BNSEND, &CWaveComDemoDlg::OnBnClickedBnsend)
    ON_BN_CLICKED(IDC_BNRECIEVE, &CWaveComDemoDlg::OnBnClickedBnrecieve)
    ON_BN_CLICKED(IDC_BNDELINDEX, &CWaveComDemoDlg::OnBnClickedBndelindex)
    ON_BN_CLICKED(IDC_BNCHECKAUTO, &CWaveComDemoDlg::OnBnClickedBncheckauto)
    ON_BN_CLICKED(IDC_BNCHECKNEW, &CWaveComDemoDlg::OnBnClickedBnchecknew)
    ON_BN_CLICKED(IDC_BNDISCONNECT, &CWaveComDemoDlg::OnBnClickedBndisconnect)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CWaveComDemoDlg ��Ϣ�������

BOOL CWaveComDemoDlg::OnInitDialog()
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
    SetDlgItemText(IDC_CBBAUD,_T("9600"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWaveComDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWaveComDemoDlg::OnPaint()
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
HCURSOR CWaveComDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWaveComDemoDlg::OnBnClickedBnconnect()
{
    // TODO: Add your control notification handler code here
    CString strType[256];
    int iPort = GetDlgItemInt(IDC_EDCOMPORT);
    int iBaud = GetDlgItemInt(IDC_CBBAUD);
    if(!m_clsSMSModem.SmsConnenction(iPort,iBaud,strType))
    {
        MessageBox(_T("���Ӷ���èʧ�ܣ�"));
        return;
    }
    MessageBox(_T("���Ӷ���è�ɹ���"));
    SetDlgItemText(IDC_EDTYPE,*strType);
    return;
}

void CWaveComDemoDlg::OnBnClickedBnsend()
{
    // TODO: Add your control notification handler code here
    CString cstrTel;
    GetDlgItemText(IDC_EDPHONENUM,cstrTel);
    CString cstrContent;
    GetDlgItemText(IDC_EDSENDCONTENT,cstrContent);
    if(!m_clsSMSModem.SmsSend(cstrTel,cstrContent))
    {
        MessageBox(_T("���Ͷ���ʧ�ܣ�"));
    }
    else
    {
        MessageBox(_T("���Ͷ��ųɹ���"));
    }
    return;
}

void CWaveComDemoDlg::OnBnClickedBnrecieve()
{
    // TODO: Add your control notification handler code here
    CString cstrRecType;
    GetDlgItemText(IDC_CBRECTYPE,cstrRecType);
    CString strRec;
    if(!m_clsSMSModem.SmsRecieve(cstrRecType,&strRec))
    {
        MessageBox(_T("���ն���ʧ�ܣ�"));
        return;
    }
    else
    {
        MessageBox(_T("���ն��ųɹ���"));
    }
    return;
}

void CWaveComDemoDlg::OnBnClickedBndelindex()
{
    // TODO: Add your control notification handler code here
    CString cstrIndex;
    GetDlgItemText(IDC_EDSMSINDEX,cstrIndex);
    if(!m_clsSMSModem.SmsDelete(cstrIndex))
    {
        MessageBox(_T("ɾ������ʧ�ܣ�"));
    }
    else
    {
        MessageBox(_T("ɾ�����ųɹ���"));
    }
    return;
}

void CWaveComDemoDlg::OnBnClickedBncheckauto()
{
    // TODO: Add your control notification handler code here
    if(!m_clsSMSModem.SmsAutoFlag())
    {
        SetDlgItemText(IDC_EDAUTO,_T("��֧��"));
    }
    else
    {
        SetDlgItemText(IDC_EDAUTO,_T("֧��"));
    }
}

void CWaveComDemoDlg::OnBnClickedBnchecknew()
{
    // TODO: Add your control notification handler code here
    if(!m_clsSMSModem.SmsNewFlag())
    {
        SetDlgItemText(IDC_EDNEW,_T("������Ϣ"));
    }
    else
    {
        SetDlgItemText(IDC_EDNEW,_T("������Ϣ"));
    }
}

void CWaveComDemoDlg::OnBnClickedBndisconnect()
{
    // TODO: Add your control notification handler code here
    if(!m_clsSMSModem.SmsDisconnection())
    {
        MessageBox(_T("�Ͽ�����èʧ�ܣ�"));
    }
    else
    {
        MessageBox(_T("�Ͽ�����è�ɹ���"));
    }
    return;
}

void CWaveComDemoDlg::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    m_clsSMSModem.SmsDisconnection();
    CDialog::OnClose();
}
