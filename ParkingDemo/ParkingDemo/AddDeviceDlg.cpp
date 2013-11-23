// AddDeviceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ParkingDemo.h"
#include "ParkingDemoDlg.h"
#include "AddDeviceDlg.h"


// CAddDeviceDlg �Ի���

IMPLEMENT_DYNAMIC(CAddDeviceDlg, CDialog)

CAddDeviceDlg::CAddDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDeviceDlg::IDD, pParent)
	, m_lPort(8000)
	, m_strUserName(_T("admin"))
	, m_strPassWord(_T("12345"))
	, m_iBeginPlaceNo(1)
	, m_strDeviceIP(_T("10.64.59.14"))
{

}

CAddDeviceDlg::~CAddDeviceDlg()
{
}

void CAddDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_lPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassWord);
	DDX_Text(pDX, IDC_EDIT_BEGIN_PLACE_NO, m_iBeginPlaceNo);
	DDX_Text(pDX, IDC_EDIT_PARKING_NAME, m_strDeviceName);
	DDX_Text(pDX, IDC_EDIT_DEVICE_IP, m_strDeviceIP);

}


BEGIN_MESSAGE_MAP(CAddDeviceDlg, CDialog)
END_MESSAGE_MAP()


// CAddDeviceDlg ��Ϣ�������

BOOL CAddDeviceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (!NET_DVR_Init())
	{
		return FALSE;
	}

	CParkingDemoDlg * pDlg = (CParkingDemoDlg*)theApp.GetMainWnd();
	ASSERT(pDlg != NULL);

	m_strDeviceName.Format("�豸%d",pDlg->m_iTotalDeviceIndex);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
