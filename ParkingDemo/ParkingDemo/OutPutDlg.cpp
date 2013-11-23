// OutPutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ParkingDemo.h"
#include "ParkingDemoDlg.h"
#include "OutPutDlg.h"
#include "plaympeg4.h"
#include <gdiplus.h>
using namespace Gdiplus;



LONG lPort; //ȫ�ֵĲ��ſ�port��

void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* dwUser)
{
	HWND hWnd=GetConsoleWindow();

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //ϵͳͷ

		if (!PlayM4_GetPort(&lPort))  //��ȡ���ſ�δʹ�õ�ͨ����
		{
			break;
		}
		//m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
			{
				break;
			}
			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 1024*1024)) //�����ӿ�
			{
				break;
			}
			if (!PlayM4_Play(lPort, hWnd)) //���ſ�ʼ
			{
				break;
			}
		}
	case NET_DVR_STREAMDATA:   //��������
		if (dwBufSize > 0 && lPort != -1)
		{
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			} 
		}
	}
}


IMPLEMENT_DYNAMIC(COutPutDlg, CDialog)

COutPutDlg::COutPutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COutPutDlg::IDD, pParent)
	, m_strLeftPlateNo(_T(""))
	, m_strRightPlateNo(_T(""))
	, m_iLeftPlaceNo(0)
	, m_iRightPlaceNo(0)
{
	m_bHasLeftVehicle = FALSE;
	m_bHasRightVehicle = FALSE;
	m_bSeleted = FALSE;
	m_iUserId = -1;
	m_iChanId = -1;
	m_lPlayHandle = -1;

	m_RedColor=RGB(255,0,0);        
	m_GreenColor=RGB(0,255,0);      
	m_BlackColor=RGB(255,255,255);
	m_RedBrush.CreateSolidBrush(m_RedColor);      
	m_GreenBrush.CreateSolidBrush(m_GreenColor);    
	
	g_DC = NULL;
	m_bCsDlg = FALSE;	

}

COutPutDlg::~COutPutDlg()
{
}

void COutPutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_LEFT_PLATE_NO, m_strLeftPlateNo);
	DDX_Text(pDX, IDC_STATIC_RIGHT_PLATE_NO, m_strRightPlateNo);
	DDX_Text(pDX, IDC_STATIC_LEFT_PLACE_NO, m_iLeftPlaceNo);
	DDX_Text(pDX, IDC_STATIC_RIGHT_PLACE_NO, m_iRightPlaceNo);
	DDX_Control(pDX, IDC_STATIC_PreView, m_Static_Pic);
}


BEGIN_MESSAGE_MAP(COutPutDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COutPutDlg ��Ϣ�������
// ѡ�д˻���
void COutPutDlg::SelectThis(void)
{
	m_bSeleted = TRUE;
	RefreshThis();
	return;
}

// ȡ��ѡ�д˻���
void COutPutDlg::CancelSelect(void)
{
	m_bSeleted = FALSE;
	RefreshThis();
	return;
}

// �ڴ˻��沥��
void COutPutDlg::PlayThis(int iUserId, int iChanId)
{
	CParkingDemoDlg *pDlg = (CParkingDemoDlg*)theApp.GetMainWnd();
	ASSERT(pDlg != NULL);

	if (iUserId < 0 || iChanId < 1 || m_lPlayHandle != -1)
	{
		return;
	}
	m_iUserId = iUserId;
	m_iChanId = iChanId;


	//����Ԥ�������ûص�������	
	NET_DVR_CLIENTINFO ClientInfo = {0};
	ClientInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PreView)->GetSafeHwnd();//NULL;         //��ҪSDK����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
	ClientInfo.lChannel     = iChanId;       //Ԥ��ͨ����
	ClientInfo.lLinkMode    = 1;        //���λ(31)Ϊ0��ʾ��������Ϊ1��ʾ������0��30λ��ʾ���ӷ�ʽ��0��TCP��ʽ��1��UDP��ʽ��2���ಥ��ʽ��3��RTP��ʽ;
	ClientInfo.sMultiCastIP = NULL;     //�ಥ��ַ����Ҫ�ಥԤ��ʱ����

	BOOL bPreviewBlock = false;         //�������������Ƿ�������0����1����
	m_lPlayHandle = NET_DVR_RealPlay_V30(m_iUserId, &ClientInfo, NULL, NULL, 0);
	if (m_lPlayHandle < 0)
	{
		//TRACE("NET_DVR_RealPlay_V30 error\n");
		NET_DVR_Logout(m_iUserId);
		NET_DVR_Cleanup();
		return;
	}
	

	//RefreshThis();
	return;
}

// ֹͣ�˻��沥��
void COutPutDlg::StopThis(void)
{
	if (m_lPlayHandle == -1)
	{
		return;
	}
	if(NET_DVR_StopRealPlay(m_lPlayHandle))
	{
		m_lPlayHandle = -1;
		m_iUserId = -1;
		m_iChanId = -1;
		RefreshThis();
	}
	return;
}

// ǿ��ˢ�´���
void COutPutDlg::RefreshThis(void)
{
	InvalidateRect(NULL);
	SendMessage(WM_NCPAINT,0,0);
}

void COutPutDlg::UpdateWindow(void)
{
	UpdateData(FALSE);
	//Invalidate();
	GetDlgItem(IDC_STATIC_LEFT_PLACE_NO)->Invalidate();
	GetDlgItem(IDC_STATIC_RIGHT_PLACE_NO)->Invalidate();
}

void COutPutDlg::ResetWindow(void)
{	
	m_bHasLeftVehicle = FALSE;
	m_bHasRightVehicle = FALSE;
	m_strLeftPlateNo = "";
	m_strRightPlateNo = "";
	UpdateWindow();
}

HBRUSH COutPutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_LEFT_PLACE_NO)
	{		
		if (m_bHasLeftVehicle)
		{
			pDC->SetTextColor(m_GreenColor);
			pDC->SetBkColor(m_RedColor);
			hbr=(HBRUSH)m_RedBrush;//�ؼ��������ɫ
		}
		else
		{
			pDC->SetTextColor(m_RedColor);
			pDC->SetBkColor(m_GreenColor);
			hbr=(HBRUSH)m_GreenBrush;//GetStockObject(LTGRAY_BRUSH);//�ؼ��������ɫ
		}
		
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_RIGHT_PLACE_NO)
	{		
		if (m_bHasRightVehicle)
		{
			pDC->SetTextColor(m_GreenColor);
			pDC->SetBkColor(m_RedColor);
			hbr=(HBRUSH)m_RedBrush;//�ؼ��������ɫ
		}
		else
		{
			pDC->SetTextColor(m_RedColor);
			pDC->SetBkColor(m_GreenColor);
			hbr=(HBRUSH)m_GreenBrush;//�ؼ��������ɫ
		}
	}
    //Invalidate(NULL);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL COutPutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	g_DC = m_Static_Pic.GetDC();
	if (NULL == g_DC)
	{
		AfxMessageBox("��ȡDCʧ��");
		return FALSE;
	}
	m_Static_Pic.GetClientRect(&g_rect);
	m_bCsDlg = InitializeCriticalSectionAndSpinCount(&g_cs, 4000);
	if (FALSE == m_bCsDlg)
	{
		AfxMessageBox("��ʼ��DC�ٽ���ʧ��") ;
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void COutPutDlg::OnDestroy()
{
	CDialog::OnDestroy();

	if (NULL != g_DC)
	{
		ReleaseDC(g_DC);
	}
	
	if (m_bCsDlg)
	{
		DeleteCriticalSection(&g_cs);
		m_bCsDlg = FALSE;
	}

}

void COutPutDlg::DrawPicture(int iPicSize, unsigned char* pic) 
{
	DWORD iBufferSize = iPicSize;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, iBufferSize);
	void* pData = GlobalLock(hGlobal);
	if (pData == NULL)
	{
		GlobalUnlock(hGlobal);
		GlobalFree(hGlobal);
		AfxMessageBox("ȫ���ڴ����ʧ��");
		return;
	}

	memcpy(pData,pic,iBufferSize);
	GlobalUnlock(hGlobal);
	IStream* pStream = NULL;
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK)
	{
// 		CImage image;
// 		image.Load(pStream);
// 		image.Draw(g_DC->GetSafeHdc(), 0,0,g_rect.Width(),g_rect.Height());

		Image* image = NULL;
		image = Image::FromStream(pStream);
		if (NULL == image)
		{
			AfxMessageBox("��ʼ��imageʧ��");
			return;
		}
		Graphics graphics(g_DC->m_hDC);
		graphics.DrawImage(image,0,0,g_rect.Width(), g_rect.Height());

	}
	if (pStream != NULL)
	{ 
		pStream->Release();
	}
	GlobalFree(hGlobal);
}

void COutPutDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}



void COutPutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting	
	UpdateWindow();	
}