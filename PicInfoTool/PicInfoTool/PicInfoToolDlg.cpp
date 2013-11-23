
// PicInfoToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PicInfoTool.h"
#include "PicInfoToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//char TMP[3];
//#define ITOA(i) memset(TMP,0,3);itoa(i,TMP,10);


//#define LIGHTSTAT(i)  ITOA(i)_LIGHTSTAT(TMP)

#define CHANNELLINE(i) IDC_STATIC_LINE##i
#define CHANNEL(i) IDC_EDIT_CHANNEL_##i
#define LIGHTSTAT(i) IDC_EDIT_LIGHT_##i
#define LIGHTATTRI(i) IDC_ATTRI_LIGHT_##i


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


// CPicInfoToolDlg �Ի���




CPicInfoToolDlg::CPicInfoToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPicInfoToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPicInfoToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_IMAGE, m_ShowImage);
}

BEGIN_MESSAGE_MAP(CPicInfoToolDlg, CDialog)
//	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CPicInfoToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPicInfoToolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPicInfoToolDlg::OnBnClickedButton3)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPicInfoToolDlg ��Ϣ�������

BOOL CPicInfoToolDlg::OnInitDialog()
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


void CPicInfoToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	CRect rect;	
	CRect rect1;
	CRect rect2;
	CRect rect3;
	CRect rect4;


	// �����ؼ�λ��
	GetClientRect(&rect);
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_OPEN);
	if(NULL != pWnd)
	{
		((CWnd*)GetDlgItem(IDC_OPEN))->GetClientRect(&rect3);
	}
	pWnd = NULL;
	pWnd = (CWnd*)GetDlgItem(IDC_STATIC_FORGET);
	if(NULL != pWnd)
	{
		((CWnd*)GetDlgItem(IDC_STATIC_FORGET))->GetClientRect(&rect4);
	}

	rect1.top = rect3.top +20;
	rect1.left = rect3.right+30;
	rect1.right = rect.right - 10;
	rect1.bottom = rect.bottom-25;

	// Group�ؼ�src
	if ( ((CWnd *)GetDlgItem(IDC_STATIC_IMAGE_GROUP))->GetSafeHwnd()!=NULL && ((CWnd *)GetDlgItem(IDC_STATIC_IMAGE_GROUP))->IsWindowVisible()  )
	{
		((CWnd *)GetDlgItem(IDC_STATIC_IMAGE_GROUP))->MoveWindow(rect1);
	}

	// ��̬ͼ��ؼ�2 src
	rect2.top = rect1.top + 15;
	rect2.left = rect1.left + 15;
	rect2.right = rect1.right - 10; //��̬�ı��ؼ����ƶ�1/3�����ڿ��
	rect2.bottom = rect1.bottom - 10;;//��̬�ı��ؼ����ƶ�������ڸ߶�
	if ( ((CWnd *)GetDlgItem(IDC_SHOW_IMAGE))->GetSafeHwnd()!=NULL && ((CWnd *)GetDlgItem(IDC_SHOW_IMAGE))->IsWindowVisible()  )
	{
		((CWnd *)GetDlgItem(IDC_SHOW_IMAGE))->MoveWindow(rect2);
	}

	if ( ((CWnd *)GetDlgItem(IDC_STATIC_FORGET))->GetSafeHwnd()!=NULL && ((CWnd *)GetDlgItem(IDC_STATIC_FORGET))->IsWindowVisible()  )
	{
		rect4.top = rect.bottom - 22;
		rect4.bottom =rect.bottom - 8;
		rect4.left = rect.left + 30;
		rect4.right = rect4.right  + 30;
		((CWnd *)GetDlgItem(IDC_STATIC_FORGET))->MoveWindow(rect4);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPicInfoToolDlg::OnPaint()
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
HCURSOR CPicInfoToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//���������Ϣ
void CPicInfoToolDlg::ClearAllContent()
{
	//��Ϣͷ��ʾ
	if(NULL != GetDlgItem(IDC_COMBO_PROTOCAL))
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_PROTOCAL))->SetCurSel(3);
	}
	if(NULL != GetDlgItem(IDC_EDIT_CHECK))
	{
		SetDlgItemText(IDC_EDIT_CHECK,"");
	}
	//ץ����Ϣ��ʾ
	if(NULL != GetDlgItem(IDC_COMBO_COMBINE))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_COMBINE))->SetCurSel(2);
	}
	if(NULL != GetDlgItem(IDC_EDIT_SNAPTIME))
	{
		SetDlgItemText(IDC_EDIT_SNAPTIME,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_SNAPPLACE))
	{
		SetDlgItemText(IDC_EDIT_SNAPPLACE,"");
	}
	if(NULL != GetDlgItem(IDC_COMBO_VIOLATION))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_VIOLATION))->SetCurSel(13);
	}
	if(NULL != GetDlgItem(IDC_EDIT_SPEED))
	{
		SetDlgItemText(IDC_EDIT_SPEED,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_LIMITSPEED))
	{
		SetDlgItemText(IDC_EDIT_LIMITSPEED,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_CHANNELNO))
	{
		SetDlgItemText(IDC_EDIT_CHANNELNO,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_PLATENO))
	{
		SetDlgItemText(IDC_EDIT_PLATENO,"");
	}
	if(NULL != GetDlgItem(IDC_COMBO_CARCOLOR))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_CARCOLOR))->SetCurSel(13);
	}
	if(NULL != GetDlgItem(IDC_EDIT_CARID))
	{
		SetDlgItemText(IDC_EDIT_CARID,"");
	}

	if(NULL != GetDlgItem(IDC_EDIT_TRACK1))
	{
		SetDlgItemText(IDC_EDIT_TRACK1,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_TRACK2))
	{
		SetDlgItemText(IDC_EDIT_TRACK2,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_TRACK3))
	{
		SetDlgItemText(IDC_EDIT_TRACK3,"");
	}

	if(NULL != GetDlgItem(IDC_EDIT_FrameNO1))
	{
		SetDlgItemText(IDC_EDIT_FrameNO1,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_FRAMENO2))
	{
		SetDlgItemText(IDC_EDIT_FRAMENO2,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_FRAMENO3))
	{
		SetDlgItemText(IDC_EDIT_FRAMENO3,"");
	}
	//��ʼ��������ʾ
	if(NULL != GetDlgItem(IDC_EDIT_V_REC1))
	{
		SetDlgItemText(IDC_EDIT_V_REC1,"");
	}
	//if(NULL != GetDlgItem(IDC_EDIT_V_REC2))
	//{
	//	SetDlgItemText(IDC_EDIT_V_REC2,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_REC3))
	//{
	//	SetDlgItemText(IDC_EDIT_V_REC3,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_REC4))
	//{
	//	SetDlgItemText(IDC_EDIT_V_REC4,"");
	//}

	if(NULL != GetDlgItem(IDC_EDIT_V_CHOICE1))
	{
		SetDlgItemText(IDC_EDIT_V_CHOICE1,"");
	}
	//if(NULL != GetDlgItem(IDC_EDIT_V_CHOICE2))
	//{
	//	SetDlgItemText(IDC_EDIT_V_CHOICE2,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_CHOICE3))
	//{
	//	SetDlgItemText(IDC_EDIT_V_CHOICE3,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_CHOICE4))
	//{
	//	SetDlgItemText(IDC_EDIT_V_CHOICE4,"");
	//}

	if(NULL != GetDlgItem(IDC_EDIT_V_TRACK1))
	{
		SetDlgItemText(IDC_EDIT_V_TRACK1,"");
	}
	//if(NULL != GetDlgItem(IDC_EDIT_V_TRACK2))
	//{
	//	SetDlgItemText(IDC_EDIT_V_TRACK2,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_TRACK3))
	//{
	//	SetDlgItemText(IDC_EDIT_V_TRACK3,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_TRACK4))
	//{
	//	SetDlgItemText(IDC_EDIT_V_TRACK4,"");
	//}

	if(NULL != GetDlgItem(IDC_EDIT_V_VIO1))
	{
		SetDlgItemText(IDC_EDIT_V_VIO1,"");
	}
	//if(NULL != GetDlgItem(IDC_EDIT_V_VIO2))
	//{
	//	SetDlgItemText(IDC_EDIT_V_VIO2,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_VIO3))
	//{
	//	SetDlgItemText(IDC_EDIT_V_VIO3,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_VIO4))
	//{
	//	SetDlgItemText(IDC_EDIT_V_VIO4,"");
	//}

	if(NULL != GetDlgItem(IDC_EDIT_V_LIGHT1))
	{
		SetDlgItemText(IDC_EDIT_V_LIGHT1,"");
	}
	//if(NULL != GetDlgItem(IDC_EDIT_V_LIGHT2))
	//{
	//	SetDlgItemText(IDC_EDIT_V_LIGHT2,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_LIGHT3))
	//{
	//	SetDlgItemText(IDC_EDIT_V_LIGHT3,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_LIGHT4))
	//{
	//	SetDlgItemText(IDC_EDIT_V_LIGHT4,"");
	//}

	if(NULL != GetDlgItem(IDC_EDIT_V_BACK1))
	{
		SetDlgItemText(IDC_EDIT_V_BACK1,"");
	}
	//if(NULL != GetDlgItem(IDC_EDIT_V_BACK2))
	//{
	//	SetDlgItemText(IDC_EDIT_V_BACK2,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_BACK3))
	//{
	//	SetDlgItemText(IDC_EDIT_V_BACK3,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_BACK4))
	//{
	//	SetDlgItemText(IDC_EDIT_V_BACK4,"");
	//}

	if(NULL != GetDlgItem(IDC_EDIT_V_MULTIFRAME1))
	{
		SetDlgItemText(IDC_EDIT_V_MULTIFRAME1,"");
	}
	//if(NULL != GetDlgItem(IDC_EDIT_V_MULTIFRAME2))
	//{
	//	SetDlgItemText(IDC_EDIT_V_MULTIFRAME2,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_MULTIFRAME3))
	//{
	//	SetDlgItemText(IDC_EDIT_V_MULTIFRAME3,"");
	//}
	//if(NULL != GetDlgItem(IDC_EDIT_V_MULTIFRAME4))
	//{
	//	SetDlgItemText(IDC_EDIT_V_MULTIFRAME4,"");
	//}

	if(NULL != GetDlgItem(IDC_EDIT_CHANNELNUM))
	{
		SetDlgItemText(IDC_EDIT_CHANNELNUM,"");
	}

	if(NULL != GetDlgItem(IDC_EDIT_LIGHTNUM))
	{
		SetDlgItemText(IDC_EDIT_LIGHTNUM,"");
	}

	if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_1))
	{
		SetDlgItemText(IDC_ATTRI_LIGHT_1,"");
	}
	if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_2))
	{
		SetDlgItemText(IDC_ATTRI_LIGHT_2,"");
	}
	if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_3))
	{
		SetDlgItemText(IDC_ATTRI_LIGHT_3,"");
	}
	if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_4))
	{
		SetDlgItemText(IDC_ATTRI_LIGHT_4,"");
	}
	if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_5))
	{
		SetDlgItemText(IDC_ATTRI_LIGHT_5,"");
	}
	if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_6))
	{
		SetDlgItemText(IDC_ATTRI_LIGHT_6,"");
	}
	//ʵʱ��Ϣ��ʾ
	if(NULL != GetDlgItem(IDC_EDIT_LIGHTDEGREE))
	{
		SetDlgItemText(IDC_EDIT_LIGHTDEGREE,"");
	}

	if(NULL != GetDlgItem(IDC_EDIT_CONTRAST))
	{
		SetDlgItemText(IDC_EDIT_CONTRAST,"");
	}

	if(NULL != GetDlgItem(IDC_EDIT_LIGHT_1))
	{
		SetDlgItemText(IDC_EDIT_LIGHT_1,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_LIGHT_2))
	{
		SetDlgItemText(IDC_EDIT_LIGHT_2,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_LIGHT_3))
	{
		SetDlgItemText(IDC_EDIT_LIGHT_3,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_LIGHT_4))
	{
		SetDlgItemText(IDC_EDIT_LIGHT_4,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_LIGHT_5))
	{
		SetDlgItemText(IDC_EDIT_LIGHT_5,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_LIGHT_6))
	{
		SetDlgItemText(IDC_EDIT_LIGHT_6,"");
	}

	if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_1))
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_1,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_2))
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_2,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_3))
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_3,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_4))
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_4,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_5))
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_5,"");
	}
	if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_6))
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_6,"");
	}
}



/************************************************************************/
/* ��ͼƬ							                                                                        */
/************************************************************************/
void CPicInfoToolDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if(m_DecProcess.OpenProcessFile())
	{
		ClearAllContent();
		((CImageShowStatic*)GetDlgItem(IDC_SHOW_IMAGE))->SetImagePointer(NULL,0,0);
		SetDlgItemText(IDC_EDIT_PATH,m_DecProcess.m_FilePathName);
	}

	Invalidate(TRUE);
}

/************************************************************************/
/* ��ȡ��Ϣ							                                                                        */
/************************************************************************/
void CPicInfoToolDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	pJD_INFO_HEADER pHeader = &(m_DecProcess.m_JD_INFO.m_Header);
	pJD_SNAP_INFO pSnapInfo = &(m_DecProcess.m_JD_INFO.m_SnapInfo);
	pJD_PARAM_INFO pParamInit = &(m_DecProcess.m_JD_INFO.m_ParamInit);
	pJD_RUNTIME_INFO pRunTime = &(m_DecProcess.m_JD_INFO.m_RunTime);

	((CImageShowStatic*)GetDlgItem(IDC_SHOW_IMAGE))->SetImagePointer(m_DecProcess.m_RGBStream,m_DecProcess.m_JPGInfo.image_width,m_DecProcess.m_JPGInfo.image_height);
	
	if(0 == strcmp(m_DecProcess.m_JD_INFO.m_Header.m_Flag,"VARMSJD"))
	{
		//��Ϣͷ��ʾ
		if(NULL != GetDlgItem(IDC_COMBO_PROTOCAL))
		{
			((CComboBox *)GetDlgItem(IDC_COMBO_PROTOCAL))->SetCurSel(pHeader->m_nVersion>2?2:pHeader->m_nVersion-1>=0?pHeader->m_nVersion-1:0);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CHECK))
		{
			SetDlgItemText(IDC_EDIT_CHECK,pHeader->m_Flag);
		}
		//ץ����Ϣ��ʾ
		if(NULL != GetDlgItem(IDC_COMBO_COMBINE))
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_COMBINE))->SetCurSel(pSnapInfo->m_MergMode);
		}
		if(NULL != GetDlgItem(IDC_EDIT_SNAPTIME))
		{
			CString snaptime;
			snaptime.Format("%0.4d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d:%0.3d",pSnapInfo->m_SnapTime.wYear,
																												pSnapInfo->m_SnapTime.wMonth,
																												pSnapInfo->m_SnapTime.wDay,
																												pSnapInfo->m_SnapTime.wHour,
																												pSnapInfo->m_SnapTime.wMinute,
																												pSnapInfo->m_SnapTime.wSecond,
																												pSnapInfo->m_SnapTime.wMillisecond);
			SetDlgItemText(IDC_EDIT_SNAPTIME,snaptime);
		}
		if(NULL != GetDlgItem(IDC_EDIT_SNAPPLACE))
		{
			SetDlgItemText(IDC_EDIT_SNAPPLACE,pSnapInfo->m_szSnapAddr);
		}
		if(NULL != GetDlgItem(IDC_COMBO_VIOLATION))
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_VIOLATION))->SetCurSel(pSnapInfo->m_nSnapType == 0? \
																											0:pSnapInfo->m_nSnapType == 1018? \
																											1:pSnapInfo->m_nSnapType == 1019? \
																											2:pSnapInfo->m_nSnapType == 1042? \
																											3:pSnapInfo->m_nSnapType == 1208? \
																											4:pSnapInfo->m_nSnapType == 1211? \
																											5:pSnapInfo->m_nSnapType == 1228? \
																											6:pSnapInfo->m_nSnapType == 1229? \
																											7:pSnapInfo->m_nSnapType == 1230? \
																											8:pSnapInfo->m_nSnapType == 1301? \
																											9:pSnapInfo->m_nSnapType == 1302? \
																											10:pSnapInfo->m_nSnapType == 1303? \
																											11:pSnapInfo->m_nSnapType == 1603?
																											12:13);
		}
		if(NULL != GetDlgItem(IDC_EDIT_SPEED))
		{
			SetDlgItemInt(IDC_EDIT_SPEED,pSnapInfo->m_nCarSpeed);
		}
		if(NULL != GetDlgItem(IDC_EDIT_LIMITSPEED))
		{
			SetDlgItemInt(IDC_EDIT_LIMITSPEED,pSnapInfo->m_nSpeedLimited);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CHANNELNO))
		{
			SetDlgItemInt(IDC_EDIT_CHANNELNO,pSnapInfo->m_nLaneID);
		}
		if(NULL != GetDlgItem(IDC_EDIT_PLATENO))
		{
			SetDlgItemText(IDC_EDIT_PLATENO,pSnapInfo->m_cPlateNum);
		}
		if(NULL != GetDlgItem(IDC_COMBO_CARCOLOR))
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_CARCOLOR))->SetCurSel(pSnapInfo->m_nCarColor);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CARID))
		{
			SetDlgItemInt(IDC_EDIT_CARID,pSnapInfo->m_nCarID);
		}

		if(NULL != GetDlgItem(IDC_EDIT_TRACK1))
		{
			SetDlgItemInt(IDC_EDIT_TRACK1,pSnapInfo->m_nLPTState[0]);
		}
		if(NULL != GetDlgItem(IDC_EDIT_TRACK2))
		{
			SetDlgItemInt(IDC_EDIT_TRACK2,pSnapInfo->m_nLPTState[1]);
		}
		if(NULL != GetDlgItem(IDC_EDIT_TRACK3))
		{
			SetDlgItemInt(IDC_EDIT_TRACK3,pSnapInfo->m_nLPTState[2]);
		}

		if(NULL != GetDlgItem(IDC_EDIT_FrameNO1))
		{
			//char temp[20] = {0};
			//itoa(pSnapInfo->m_nFrameNum[0],temp,10);
			SetDlgItemInt(IDC_EDIT_FrameNO1,pSnapInfo->m_nFrameNum[0],FALSE);
			//SetDlgItemText(IDC_EDIT_FrameNO1,temp);
		}
		if(NULL != GetDlgItem(IDC_EDIT_FRAMENO2))
		{
			SetDlgItemInt(IDC_EDIT_FRAMENO2,pSnapInfo->m_nFrameNum[1],FALSE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_FRAMENO3))
		{
			SetDlgItemInt(IDC_EDIT_FRAMENO3,pSnapInfo->m_nFrameNum[2],FALSE);
		}
		//��ʼ��������ʾ
		if(NULL != GetDlgItem(IDC_EDIT_V_REC1))
		{
			CString csRecV;
			csRecV.Format("V%d.%d.%d.%d",pParamInit->m_Version[0][0],pParamInit->m_Version[0][1],pParamInit->m_Version[0][2],pParamInit->m_Version[0][3]);
			SetDlgItemText(IDC_EDIT_V_REC1,csRecV);
		}
		

		if(NULL != GetDlgItem(IDC_EDIT_V_CHOICE1))
		{
			CString csChoiceV;
			csChoiceV.Format("V%d.%d.%d.%d",pParamInit->m_Version[1][0],pParamInit->m_Version[1][1],pParamInit->m_Version[1][2],pParamInit->m_Version[1][3]);
			SetDlgItemText(IDC_EDIT_V_CHOICE1,csChoiceV);
		}

		if(NULL != GetDlgItem(IDC_EDIT_V_TRACK1))
		{
			CString csTrackV;
			csTrackV.Format("V%d.%d.%d.%d",pParamInit->m_Version[2][0],pParamInit->m_Version[2][1],pParamInit->m_Version[2][2],pParamInit->m_Version[2][3]);
			SetDlgItemText(IDC_EDIT_V_TRACK1,csTrackV);
		}
		

		if(NULL != GetDlgItem(IDC_EDIT_V_VIO1))
		{
			CString csVioV;
			csVioV.Format("V%d.%d.%d.%d",pParamInit->m_Version[3][0],pParamInit->m_Version[3][1],pParamInit->m_Version[3][2],pParamInit->m_Version[3][3]);
			SetDlgItemText(IDC_EDIT_V_VIO1,csVioV);
			//SetDlgItemInt(IDC_EDIT_V_VIO1,pParamInit->m_Version[3][0]);
		}
		

		if(NULL != GetDlgItem(IDC_EDIT_V_LIGHT1))
		{
			CString csLightV;
			csLightV.Format("V%d.%d.%d.%d",pParamInit->m_Version[4][0],pParamInit->m_Version[4][1],pParamInit->m_Version[4][2],pParamInit->m_Version[4][3]);
			SetDlgItemText(IDC_EDIT_V_LIGHT1,csLightV);
			//SetDlgItemInt(IDC_EDIT_V_LIGHT1,pParamInit->m_Version[4][0]);
		}
		

		if(NULL != GetDlgItem(IDC_EDIT_V_BACK1))
		{
			CString csBackV;
			csBackV.Format("V%d.%d.%d.%d",pParamInit->m_Version[5][0],pParamInit->m_Version[5][1],pParamInit->m_Version[5][2],pParamInit->m_Version[5][3]);
			SetDlgItemText(IDC_EDIT_V_BACK1,csBackV);
			//SetDlgItemInt(IDC_EDIT_V_BACK1,pParamInit->m_Version[5][0]);
		}
		

		if(NULL != GetDlgItem(IDC_EDIT_V_MULTIFRAME1))
		{
			CString csMultiFrameV;
			csMultiFrameV.Format("V%d.%d.%d.%d",pParamInit->m_Version[6][0],pParamInit->m_Version[6][1],pParamInit->m_Version[6][2],pParamInit->m_Version[6][3]);
			SetDlgItemText(IDC_EDIT_V_MULTIFRAME1,csMultiFrameV);
			//SetDlgItemInt(IDC_EDIT_V_MULTIFRAME1,pParamInit->m_Version[6][0]);
		}
		

		if(NULL != GetDlgItem(IDC_EDIT_CHANNELNUM))
		{
			SetDlgItemInt(IDC_EDIT_CHANNELNUM,pParamInit->m_LaneNum);
		}

		if(NULL != GetDlgItem(IDC_EDIT_LIGHTNUM))
		{
			SetDlgItemInt(IDC_EDIT_LIGHTNUM,pParamInit->m_LightNum);
		}

		
		if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_1)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum>=1)
		{
			GetDlgItem(IDC_ATTRI_LIGHT_1)->ShowWindow(SW_SHOW);
			if(pParamInit->m_LightCls[0] == 1)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_1,"ֱ�е�");
			}
			else if(pParamInit->m_LightCls[0] == 2)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_1,"��ת��");
			}
			else if(pParamInit->m_LightCls[0] == 3)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_1,"��ת��");
			}
			else
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_1,"");
			}
		}
		else
		{
			GetDlgItem(IDC_ATTRI_LIGHT_1)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_2)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum>=2)
		{
			GetDlgItem(IDC_ATTRI_LIGHT_2)->ShowWindow(SW_SHOW);
			if(pParamInit->m_LightCls[1] == 1)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_2,"ֱ�е�");
			}
			else if(pParamInit->m_LightCls[1] == 2)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_2,"��ת��");
			}
			else if(pParamInit->m_LightCls[1] == 3)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_2,"��ת��");
			}
			else
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_2,"");
			}
		}
		else
		{
			GetDlgItem(IDC_ATTRI_LIGHT_2)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_3)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum>=3)
		{
			GetDlgItem(IDC_ATTRI_LIGHT_3)->ShowWindow(SW_SHOW);
			if(pParamInit->m_LightCls[2] == 1)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_3,"ֱ�е�");
			}
			else if(pParamInit->m_LightCls[2] == 2)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_3,"��ת��");
			}
			else if(pParamInit->m_LightCls[2] == 3)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_3,"��ת��");
			}
			else
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_3,"");
			}
		}
		else
		{
			GetDlgItem(IDC_ATTRI_LIGHT_3)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_4)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum>=4)
		{
			GetDlgItem(IDC_ATTRI_LIGHT_4)->ShowWindow(SW_SHOW);
			if(pParamInit->m_LightCls[3] == 1)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_4,"ֱ�е�");
			}
			else if(pParamInit->m_LightCls[3] == 2)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_4,"��ת��");
			}
			else if(pParamInit->m_LightCls[3] == 3)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_4,"��ת��");
			}
			else
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_4,"");
			}
		}
		else
		{
			GetDlgItem(IDC_ATTRI_LIGHT_4)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_5)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum>=5)
		{
			GetDlgItem(IDC_ATTRI_LIGHT_5)->ShowWindow(SW_SHOW);
			if(pParamInit->m_LightCls[4] == 1)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_5,"ֱ�е�");
			}
			else if(pParamInit->m_LightCls[4] == 2)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_5,"��ת��");
			}
			else if(pParamInit->m_LightCls[4] == 3)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_5,"��ת��");
			}
			else
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_5,"");
			}
		}
		else
		{
			GetDlgItem(IDC_ATTRI_LIGHT_5)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_ATTRI_LIGHT_6)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum>=6)
		{
			GetDlgItem(IDC_ATTRI_LIGHT_6)->ShowWindow(SW_SHOW);
			if(pParamInit->m_LightCls[5] == 1)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_6,"ֱ�е�");
			}
			else if(pParamInit->m_LightCls[5] == 2)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_6,"��ת��");
			}
			else if(pParamInit->m_LightCls[5] == 3)
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_6,"��ת��");
			}
			else
			{
				SetDlgItemText(IDC_ATTRI_LIGHT_6,"");
			}
		}
		else
		{
			GetDlgItem(IDC_ATTRI_LIGHT_6)->ShowWindow(SW_HIDE);
		}
		
		//ʵʱ��Ϣ��ʾ
		if(NULL != GetDlgItem(IDC_EDIT_LIGHTDEGREE))
		{
			SetDlgItemInt(IDC_EDIT_LIGHTDEGREE,pRunTime->m_nBright);
		}

		if(NULL != GetDlgItem(IDC_EDIT_CONTRAST))
		{
			SetDlgItemInt(IDC_EDIT_CONTRAST,pRunTime->m_nContrast);
		}

		if(NULL != GetDlgItem(IDC_EDIT_LIGHT_1)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum >=1)
		{
			GetDlgItem(IDC_EDIT_LIGHT_1)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLightStatus[0] == 0)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_1,"���");
			}
			else if(pRunTime->m_nLightStatus[0] == 1)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_1,"�̵�");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_LIGHT_1,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_LIGHT_1)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_LIGHT_2)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum >=2)
		{
			GetDlgItem(IDC_EDIT_LIGHT_2)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLightStatus[1] == 0)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_2,"���");
			}
			else if(pRunTime->m_nLightStatus[1] == 1)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_2,"�̵�");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_LIGHT_2,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_LIGHT_2)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_LIGHT_3)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum >=3)
		{
			GetDlgItem(IDC_EDIT_LIGHT_3)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLightStatus[2] == 0)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_3,"���");
			}
			else if(pRunTime->m_nLightStatus[2] == 1)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_3,"�̵�");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_LIGHT_3,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_LIGHT_3)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_LIGHT_4)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum >=4)
		{
			GetDlgItem(IDC_EDIT_LIGHT_4)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLightStatus[3] == 0)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_4,"���");
			}
			else if(pRunTime->m_nLightStatus[3] == 1)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_4,"�̵�");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_LIGHT_4,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_LIGHT_4)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_LIGHT_5)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum >=5)
		{
			GetDlgItem(IDC_EDIT_LIGHT_5)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLightStatus[4] == 0)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_5,"���");
			}
			else if(pRunTime->m_nLightStatus[4] == 1)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_5,"�̵�");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_LIGHT_5,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_LIGHT_5)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_LIGHT_6)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LightNum >=6)
		{
			GetDlgItem(IDC_EDIT_LIGHT_6)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLightStatus[5] == 0)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_6,"���");
			}
			else if(pRunTime->m_nLightStatus[5] == 1)
			{
				SetDlgItemText(IDC_EDIT_LIGHT_6,"�̵�");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_LIGHT_6,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_LIGHT_6)->ShowWindow(SW_HIDE);
		}

		if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_1)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LaneNum>=1)
		{
			GetDlgItem(IDC_EDIT_CHANNEL_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LINE1)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLaneStatus[0] == 0)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"���г���");
			}
			else if(pRunTime->m_nLaneStatus[0] == 1)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"ֱ�г���");
			}
			else if(pRunTime->m_nLaneStatus[0] == 2)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[0] == 3)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[0] == 4)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[0] == 5)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[0] == 6)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"��ת��ת����");
			}
			else if(pRunTime->m_nLaneStatus[0] == 7)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"ֱ����ת��ת����");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_1,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_CHANNEL_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LINE1)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_2)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LaneNum>=2)
		{
			GetDlgItem(IDC_EDIT_CHANNEL_2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LINE2)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLaneStatus[1] == 0)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"���г���");
			}
			else if(pRunTime->m_nLaneStatus[1] == 1)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"ֱ�г���");
			}
			else if(pRunTime->m_nLaneStatus[1] == 2)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[1] == 3)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[1] == 4)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[1] == 5)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[1] == 6)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"��ת��ת����");
			}
			else if(pRunTime->m_nLaneStatus[1] == 7)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"ֱ����ת��ת����");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_CHANNEL_2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LINE2)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_3)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LaneNum>=3)
		{
			GetDlgItem(IDC_EDIT_CHANNEL_3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LINE3)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLaneStatus[2] == 0)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"���г���");
			}
			else if(pRunTime->m_nLaneStatus[2] == 1)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"ֱ�г���");
			}
			else if(pRunTime->m_nLaneStatus[2] == 2)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[2] == 3)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[2] == 4)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[2] == 5)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[2] == 6)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"��ת��ת����");
			}
			else if(pRunTime->m_nLaneStatus[2] == 7)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_3,"ֱ����ת��ת����");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_2,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_CHANNEL_3)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LINE3)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_4)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LaneNum>=4)
		{
			GetDlgItem(IDC_EDIT_CHANNEL_4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LINE4)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLaneStatus[3] == 0)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"���г���");
			}
			else if(pRunTime->m_nLaneStatus[3] == 1)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"ֱ�г���");
			}
			else if(pRunTime->m_nLaneStatus[3] == 2)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[3] == 3)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[3] == 4)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[3] == 5)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[3] == 6)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"��ת��ת����");
			}
			else if(pRunTime->m_nLaneStatus[3] == 7)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"ֱ����ת��ת����");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_4,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_CHANNEL_4)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LINE4)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_5)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LaneNum>=5)
		{
			GetDlgItem(IDC_EDIT_CHANNEL_5)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LINE5)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLaneStatus[4] == 0)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"���г���");
			}
			else if(pRunTime->m_nLaneStatus[4] == 1)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"ֱ�г���");
			}
			else if(pRunTime->m_nLaneStatus[4] == 2)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[4] == 3)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[4] == 4)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[4] == 5)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[4] == 6)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"��ת��ת����");
			}
			else if(pRunTime->m_nLaneStatus[4] == 7)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"ֱ����ת��ת����");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_5,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_CHANNEL_5)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LINE5)->ShowWindow(SW_HIDE);
		}
		if(NULL != GetDlgItem(IDC_EDIT_CHANNEL_6)&&m_DecProcess.m_JD_INFO.m_ParamInit.m_LaneNum>=6)
		{
			GetDlgItem(IDC_EDIT_CHANNEL_6)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LINE6)->ShowWindow(SW_SHOW);
			if(pRunTime->m_nLaneStatus[5] == 0)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"���г���");
			}
			else if(pRunTime->m_nLaneStatus[5] == 1)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"ֱ�г���");
			}
			else if(pRunTime->m_nLaneStatus[5] == 2)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[5] == 3)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[5] == 4)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"��ת����");
			}
			else if(pRunTime->m_nLaneStatus[5] == 5)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"ֱ����ת����");
			}
			else if(pRunTime->m_nLaneStatus[5] == 6)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"��ת��ת����");
			}
			else if(pRunTime->m_nLaneStatus[5] == 7)
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"ֱ����ת��ת����");
			}
			else
			{
				SetDlgItemText(IDC_EDIT_CHANNEL_6,"");
			}
		}
		else
		{
			GetDlgItem(IDC_EDIT_CHANNEL_6)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LINE6)->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		MessageBox("У����Ϣ����","��ʾ",MB_OK);
	}
	Invalidate(TRUE);
}

void CPicInfoToolDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	if(!m_DecProcess.m_FilePathName.IsEmpty())
	{
		char csGetPlateNo[32] = {0};
		GetDlgItemText(IDC_EDIT_PLATENO,csGetPlateNo,32);
		if(strlen(csGetPlateNo))
		{
			memset(m_DecProcess.m_JD_INFO.m_SnapInfo.m_cPlateNum,0,32);
			GetDlgItemText(IDC_EDIT_PLATENO,m_DecProcess.m_JD_INFO.m_SnapInfo.m_cPlateNum,32);
			m_DecProcess.m_JD_INFO.m_SnapInfo.m_nCarColor = ((CComboBox*)GetDlgItem(IDC_COMBO_CARCOLOR))->GetCurSel();
		}
		m_DecProcess.SaveProcessFile();
	}
}



void CPicInfoToolDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_SHOW_IMAGE);
	if(NULL != pWnd)
	{
		((CWnd*)GetDlgItem(IDC_SHOW_IMAGE))->GetClientRect(&rect);
	}
	if(rect.left<=point.x && rect.right >= point.x && rect.bottom >= point.y && rect.top <= point.y)
	{
		CString tmp;
		tmp.Format("X:%d,Y:%d",point.x,point.y);
		SetDlgItemText(IDC_LOCATION,tmp);
	}
 	CDialog::OnMouseMove(nFlags, point);
}
