// MakeDogToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MakeDogTool.h"
#include "MakeDogToolDlg.h"
#include "EncryptInterface.h"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"Encrypt.lib")

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


// CMakeDogToolDlg �Ի���




CMakeDogToolDlg::CMakeDogToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeDogToolDlg::IDD, pParent)
{
	m_pConfig = new CConfig("./MakeTool.ini");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMakeDogToolDlg::~CMakeDogToolDlg()
{
	delete m_pConfig;
	m_pConfig = NULL;
}

void CMakeDogToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ccbDeviceType);
	DDX_Control(pDX, IDC_COMBO2, m_ccbSetPlatform);
	DDX_Control(pDX, IDC_COMBO3, m_ccbGetPlatform);
}

BEGIN_MESSAGE_MAP(CMakeDogToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMakeDogToolDlg::OnBnClickedTestDog)
	ON_BN_CLICKED(IDC_BUTTON2, &CMakeDogToolDlg::OnBnClickedMakeDog)
	//ON_BN_CLICKED(IDC_BUTTON3, &CMakeDogToolDlg::OnBnClickedMakeFRDog)
	ON_BN_CLICKED(IDC_BUTTON4, &CMakeDogToolDlg::OnBnClickedReadDog)
	//ON_BN_CLICKED(IDC_BUTTON5, &CMakeDogToolDlg::OnBnClickedReadFRDog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMakeDogToolDlg::OnCbnSelchangeCombo1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMakeDogToolDlg ��Ϣ�������

HBRUSH CMakeDogToolDlg::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC,pWnd,nCtlColor);
	if(nCtlColor == CTLCOLOR_DLG||CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkColor(RGB(210,230,211));
		HBRUSH B = CreateSolidBrush(RGB(210,230,211));
		return B;
	}
	if(nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(RGB(0,0,255));
		//pDC->SetBkColor(RGB(210,230,211));
		//HBRUSH B = CreateSolidBrush(RGB(210,230,211));
		//return B;
	}
	return hbr;
}
BOOL CMakeDogToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	m_hbrush=CreateSolidBrush(RGB(210,230,211));
	int iTempSoftWare = m_pConfig->ReadConfig("LastConfigParam","SoftWareType",NULL);
	int iTempPRChan = m_pConfig->ReadConfig("LastConfigParam","PRChannels",NULL);
	int iTempFRChan = m_pConfig->ReadConfig("LastConfigParam","FRChannels",NULL);
	int iTempDevice = m_pConfig->ReadConfig("LastConfigParam","DeviceType",NULL);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(iTempSoftWare);
	if(iTempSoftWare != 7)
	{
		m_bChangeStatus = false;
		BYTE nplatform;	
		BYTE nChannelsPlate;
		BYTE nChannelsFace;
		((CComboBox*)GetDlgItem(IDC_COMBO2))->EnableWindow(FALSE);
		((CEdit *)GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
		((CEdit *)GetDlgItem(IDC_EDIT7))->EnableWindow(FALSE);
		switch(iTempSoftWare)
		{
		case 0:
			{
				nChannelsPlate = 4;
				nChannelsFace = 2;
				nplatform = 1;	
			}
			break;
		case 1:
			{
				nChannelsPlate = 8;
				nChannelsFace = 0;
				nplatform = 1;
			}
			break;
		case 2:
			{
				nChannelsPlate = 2;
				nChannelsFace = 0;
				nplatform = 2;
			}
			break;
		case 3:
			{
				nChannelsPlate = 2;
				nChannelsFace = 2;
				nplatform = 2;
			}
			break;
		case 4:
			{
				nChannelsPlate = 4;
				nChannelsFace = 0;
				nplatform = 2;
			}
			break;
		case 5:
			{
				nChannelsPlate = 2;
				nChannelsFace = 2;
				nplatform = 3;
			}
			break;
		case 6:
			{
				nChannelsPlate = 4;
				nChannelsFace = 0;
				nplatform = 3;
			}
			break;
		default:
			{
				return FALSE;
			}
		}
		SetDlgItemInt(IDC_EDIT2,nChannelsPlate);
		SetDlgItemInt(IDC_EDIT7,nChannelsFace);
		((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(nplatform);
	}
	else
	{
		m_bChangeStatus = true;
		((CComboBox*)GetDlgItem(IDC_COMBO2))->EnableWindow(TRUE);
		((CEdit *)GetDlgItem(IDC_EDIT2))->EnableWindow(TRUE);
		((CEdit *)GetDlgItem(IDC_EDIT7))->EnableWindow(TRUE);
		switch(iTempDevice)
		{
		case 1:
			{
				((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
			}
			break;
		case 2:
			{
				((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(2);
			}
			break;
		case 3:
			{
				((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(1);
			}
			break;
		case 4:
			{
				((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(3);
			}
			break;
		default:
			{
				((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(3);
			}
		}
		SetDlgItemInt(IDC_EDIT2,iTempPRChan);
		SetDlgItemInt(IDC_EDIT7,iTempFRChan);
	}
	//SetDlgItemInt(IDC_EDIT1,0);
	//SetDlgItemInt(IDC_EDIT2,0);
	//SetDlgItemInt(IDC_EDIT3,0);
	//SetDlgItemInt(IDC_EDIT4,0);
	//SetDlgItemInt(IDC_EDIT5,0);
	//SetDlgItemInt(IDC_EDIT6,0);
	//SetDlgItemInt(IDC_EDIT7,0);
	//SetDlgItemInt(IDC_EDIT8,0);
	//SetDlgItemInt(IDC_EDIT9,0);
	//SetDlgItemInt(IDC_EDIT10,0);
	//((CComboBox *)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
	//((CComboBox *)GetDlgItem(IDC_COMBO3))->SetCurSel(1);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMakeDogToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMakeDogToolDlg::OnPaint()
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
HCURSOR CMakeDogToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMakeDogToolDlg::OnBnClickedTestDog()
{
	// TODO: Add your control notification handler code here
	int result = StatusValidate();
	if(result == 0)
	{
		MessageBox("������,��������ʹ�ã�����");
	}
	else
	{
		MessageBox("�������ڻ򲻿�����ʹ�ã�����");
	}
}
void CMakeDogToolDlg::OnBnClickedMakeDog()
{
	// TODO: Add your control notification handler code here
	CString csDeviceType;
	BYTE nplatform;	
	BYTE nChannelsPlate;
	BYTE nChannelsFace;
	BYTE bMode = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	switch(bMode)
	{
	case 0:
		{
			nChannelsPlate = 4;
			nChannelsFace = 2;
			nplatform = 1;	
		}
		break;
	case 1:
		{
			nChannelsPlate = 8;
			nChannelsFace = 0;
			nplatform = 1;
		}
		break;
	case 2:
		{
			nChannelsPlate = 2;
			nChannelsFace = 0;
			nplatform = 2;
		}
		break;
	case 3:
		{
			nChannelsPlate = 2;
			nChannelsFace = 2;
			nplatform = 2;
		}
		break;
	case 4:
		{
			nChannelsPlate = 4;
			nChannelsFace = 0;
			nplatform = 2;
		}
		break;
	case 5:
		{
			nChannelsPlate = 2;
			nChannelsFace = 2;
			nplatform = 3;
		}
		break;
	case 6:
		{
			nChannelsPlate = 4;
			nChannelsFace = 0;
			nplatform = 3;
		}
		break;
	case 7:
		{
			nChannelsPlate = (BYTE)GetDlgItemInt(IDC_EDIT2);
			nChannelsFace = (BYTE)GetDlgItemInt(IDC_EDIT7);
			BYTE temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
			switch(temp)
			{
			case 0:
				{
					nplatform = 1;
				}
				break;
			case 1:
				{
					nplatform = 3;
				}
				break;
			case 2:
				{
					nplatform = 2;
				}
				break;
			case 3:
				{
					nplatform = 4;
				}
				break;
			default:
				{
					nplatform = 4;
				}
			}
		}
		break;
	default:
		{
			return;
		}
	}
	switch(nplatform)
	{
	case 1:
		{
			csDeviceType = "����";
		}
		break;
	case 2:
		{
			csDeviceType = "ģ��";
		}
		break;
	case 3:
		{
			csDeviceType = "����";
		}
		break;
	default:
		{
			csDeviceType = "����";
		}
	}
	HRESULT hr = MakeDog(
				nChannelsPlate,
				nChannelsFace,
				nplatform);
	if(hr == S_OK)
	{
		CString csTemp;
		csTemp.Format("������ʶ���ɹ�������\n�豸����Ϊ��%s��\n�󶨳���ʶ��·��Ϊ��%d��\n������ʶ��·��Ϊ��%d��",csDeviceType,nChannelsPlate,nChannelsFace);
		MessageBox(csTemp);
		char ch[16] ={0};
		itoa(bMode,ch,10);
		m_pConfig->WriteConfig("LastConfigParam","SoftWareType",ch);
		memset(ch,0,16);
		itoa(nChannelsPlate,ch,10);
		m_pConfig->WriteConfig("LastConfigParam","PRChannels",ch);
		memset(ch,0,16);
		itoa(nChannelsFace,ch,10);
		m_pConfig->WriteConfig("LastConfigParam","FRChannels",ch);
		memset(ch,0,16);
		itoa(nplatform,ch,10);
		m_pConfig->WriteConfig("LastConfigParam","DeviceType",ch);
	}
	else
	{
		MessageBox("������ʶ��ʧ�ܣ�����");
	}
}

void CMakeDogToolDlg::OnBnClickedReadDog()
{
	// TODO: Add your control notification handler code here
	//m_cePROutChannels;
	//m_cePROutLanes;
	//m_cePROutPlatForm;
	//m_cePROutChannelType;

	BYTE nChannelsPlate;// = (BYTE)GetDlgItemInt(IDC_EDIT2);
	BYTE nChannelsFace;// = (BYTE)GetDlgItemInt(IDC_EDIT7);
	BYTE nplatform;// = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	BOOL bPRFlag;
	HRESULT hr = GetDogAccess( 
			nChannelsPlate,
			nChannelsFace,
			nplatform,
			bPRFlag );
	if( S_FALSE == hr)
	{
		MessageBox("�������ڻ��Ѿ����ڣ�����");
		return;
	}
	SetDlgItemInt(IDC_EDIT11,nChannelsPlate);
	SetDlgItemInt(IDC_EDIT15,nChannelsFace);
	SetDlgItemInt(IDC_EDIT19,bPRFlag);
	switch(nplatform)
	{
	case 1:
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(0);
		}
		break;
	case 2:
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(2);
		}
		break;
	case 3:
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(1);
		}
		break;
	case 4:
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(3);
		}
		break;
	default:
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(3);
		}
	}
	
}

void CMakeDogToolDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bool nflag = false;
	BYTE nChannelsPlate;// = (BYTE)GetDlgItemInt(IDC_EDIT2);
	BYTE nChannelsFace;// = (BYTE)GetDlgItemInt(IDC_EDIT7);
	BYTE nplatform;// = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	BYTE bMode = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	if(bMode != 7)
	{
		nflag = false;
	}
	else
	{
		nflag = true;
	}
	if(nflag != m_bChangeStatus)
	{
		if(nflag)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO2))->EnableWindow(TRUE);
			((CEdit *)GetDlgItem(IDC_EDIT2))->EnableWindow(TRUE);
			((CEdit *)GetDlgItem(IDC_EDIT7))->EnableWindow(TRUE);
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO2))->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_EDIT7))->EnableWindow(FALSE);
		}
	}
	switch(bMode)
	{
	case 0:
		{
			nChannelsPlate = 4;
			nChannelsFace = 2;
			nplatform = 0;	
		}
		break;
	case 1:
		{
			nChannelsPlate = 8;
			nChannelsFace = 0;
			nplatform = 0;
		}
		break;
	case 2:
		{
			nChannelsPlate = 2;
			nChannelsFace = 0;
			nplatform = 2;
		}
		break;
	case 3:
		{
			nChannelsPlate = 2;
			nChannelsFace = 2;
			nplatform = 2;
		}
		break;
	case 4:
		{
			nChannelsPlate = 4;
			nChannelsFace = 0;
			nplatform = 2;
		}
		break;
	case 5:
		{
			nChannelsPlate = 2;
			nChannelsFace = 2;
			nplatform = 1;
		}
		break;
	case 6:
		{
			nChannelsPlate = 4;
			nChannelsFace = 0;
			nplatform = 1;
		}
		break;
	case 7:
		{
			nChannelsPlate = 0;
			nChannelsFace = 0;
			nplatform = 0;
		}
		break;
	default:
		{
			return;
		}
	}
	SetDlgItemInt(IDC_EDIT2,nChannelsPlate);
	SetDlgItemInt(IDC_EDIT7,nChannelsFace);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(nplatform);
	m_bChangeStatus = nflag;
}


