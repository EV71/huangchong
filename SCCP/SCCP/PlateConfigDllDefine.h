/** @file    PlateConfigDllDefine.h
  * @note    HangZhou Hikvision Software Co.,Ltd.All Right Reserved.
  * @brief   ���ļ��ǳ���ʶ������dllͷ�ļ�
  *
  * @author  ����yf2
  * @date    2011/10/27
  */
#ifndef PLATE_CONFIG_DLL_DEFINE_H
#define PLATE_CONFIG_DLL_DEFINE_H

#ifdef  PLATE_CONFIG_DLL_EXMPORT
#define AFX_PLATECONFIG_API extern "C" _declspec(dllexport)
#else
#define AFX_PLATECONFIG_API extern "C" _declspec(dllimport)
#endif

#define DEVVCATAB		1			                      //ͨ��������Ϣ����
#define PLAYWNDWIDTH  352
#define PLAYWNDHEIGHT 288
#define MINWIDTH	850
#define MINHEIGHT	690

#define NAME_LEN			    32                       //�û�������
#define PASSWD_LEN			    16                       //���볤��
#define CHAN_INFO_LEN           128                      //��ص���Ϣ����

#define WNDREMAINLEN	7	                             //�Ի���߿�������
#define WM_PLATECFGDLG_DETROY	WM_USER + 1110

//�������԰汾 --byshm
enum{LANG_CHI = 0,                                       //��������
     LANG_ENG,		                                     //Ӣ��
     LANG_TRAD,	                                         //����
     LANG_RUS,
     LANG_PLS,
     LANG_FRCH, 
     LANG_SPA,
     LANG_CORA,
     LANG_GMN,
     LANG_ITAL,
     LANG_POR,                                           //��������
};

//tabҳ���ô������
typedef enum tag_Sub_PlateConfig_Tab
{
	SUB_CONFIG_TAB_ARITH = 0,			                //����ʶ������
	SUB_CONFIG_TAB_PLATE,				                //�㷨���������
}SUB_PLATECONFIG_TAB, *LPSUB_PLATECONFIG_TAB;


//���ڲ���
typedef struct
{
	int			iTabShow;								//Զ���������ô���ѡ����ʾ������ҳ
	int			iLanguage;								//Զ���������ô��ڵ���������
	HWND		hParWnd;								//Զ���������ô��ڵĸ�����
	CRect		rcWndRect;								//Զ���������ô��ڵĴ�С
	bool		bFixedSize;								//����λ���Ƿ�̶�

	COLORREF	clrPen;									//Զ���������ô������б����ߵĻ���
	LOGBRUSH	lbBackBrush;							//Զ���������ô����еı�����ɫ��ˢ
	LOGBRUSH	lbTitleBkBrush;							//Զ���������ô����еı����ɫ��ˢ
	LOGBRUSH	lbListTitleBkBr;						//Զ���������ô����е��б��ͷ��ɫ��ˢ
	LOGBRUSH	lbStaticBkBrush;						//Զ���������ô��ڵľ�̬���ɫ��ˢ
	LOGBRUSH	lbEditBrush;							//Զ���������ô��ڵı༭���ɫ��ˢ
	LOGBRUSH	lbSelBkBrush;							//Զ���������ô��ڵ��б�ѡ�е�ɫ��ˢ

	//Ԥ��λ
	LOGBRUSH	lbRes1;									
	LOGBRUSH	lbRes2;
	DWORD		dwRes1;												
	DWORD		dwRes2;
	void NET_INTELCFG_WNDPARAM()
	{
		iTabShow			=	DEVVCATAB;
		iLanguage			=	LANG_CHI;
		hParWnd				=	NULL;
		rcWndRect.SetRect(0,0,MINWIDTH,MINHEIGHT);
		bFixedSize			=	true;

		clrPen				= RGB(107,107,107);
		lbBackBrush.lbColor = RGB(204,204,204);
		lbBackBrush.lbStyle = BS_SOLID;
		lbTitleBkBrush.lbColor = RGB(148,148,148);
		lbTitleBkBrush.lbStyle = BS_SOLID;
		lbListTitleBkBr.lbColor = RGB(174,174,174);
		lbListTitleBkBr.lbStyle = BS_SOLID;
		lbStaticBkBrush.lbColor = RGB(209,209,209);
		lbStaticBkBrush.lbStyle = BS_SOLID;
		lbEditBrush.lbColor = RGB(228,228,228);
		lbEditBrush.lbStyle = BS_SOLID;
		lbSelBkBrush.lbColor = RGB(49,106,197);
		lbSelBkBrush.lbStyle = BS_SOLID;

		ZeroMemory(&lbRes1, sizeof(LOGBRUSH));
		ZeroMemory(&lbRes2, sizeof(LOGBRUSH));
		dwRes1               = 0;
		dwRes2               = 0;
	}
}NET_INTELCFG_WNDPARAM,*LPNET_INTELCFG_WNDPARAM;
//��½�豸��Ϣ
typedef struct tag_NET_INTELCFG_DEVLOGININFO
{
	char	chDevIP[16];				//�豸IP
	char	chUserName[NAME_LEN];		//�û���
	char	chPassword[PASSWD_LEN];		//����
	int		iChanNum;					//��1��ʼ
	int		iMediaSrvNum;				//��ý������������ݲ�֧�֣�
	WORD	wDevPort;					//�豸�˿�
	LONG	lConnectType;				//����sdk�ķ�ʽ���Ƿ�ͨ����ý��ı�־
	LPVOID	pMediaSrvDir;				//��ý��·��ָ��
	BYTE	res[8];
	tag_NET_INTELCFG_DEVLOGININFO()
	{
		iChanNum = 1;
		wDevPort = 8000;
		lConnectType = 0;
		iMediaSrvNum = 0;
		pMediaSrvDir = NULL;
		ZeroMemory(chDevIP, 16);
		ZeroMemory(chUserName, NAME_LEN);
		ZeroMemory(chPassword, PASSWD_LEN);
		ZeroMemory(res, 8);
	}
}NET_INTELCFG_DEVLOGININFO,*LPNET_INTELCFG_DEVLOGININFO ;

//��ص���Ϣ
typedef struct tag_NET_INTELCFG_MONITORINFO
{
	char chChanName[CHAN_INFO_LEN];      //��ص�����
	char chDevName[CHAN_INFO_LEN];       //�����豸����
}NET_INTELCFG_MONITORINFO, *LPNET_INTELCFG_MONITORINFO;


/** @fn       NET_DVR_SetMonitorInfo(LPNET_INTELCFG_MONITORINFO pMonitorInfo)
  * @brief    ���ü�ص���Ϣ  
  * @param    pMonitorInfo  :��ص���Ϣ
  * @return   void   
  */
AFX_PLATECONFIG_API void __stdcall NET_DVR_SetMonitorInfo(LPNET_INTELCFG_MONITORINFO pMonitorInfo);

/** @fn       NET_DVR_CreateWnd(LPNET_INTELCFG_WNDPARAM pIntelWndParam)
  * @brief    ����Զ�����ô���  
  * @param    pIntelWndParam  :Զ���������ô��ڻ�ˢ�������ھ�������ڴ�С�������������Ϣ
  * @return   true : �������ڳɹ� ;false: ��������ʧ�� 
  */
AFX_PLATECONFIG_API bool __stdcall NET_DVR_CreateWnd(LPNET_INTELCFG_WNDPARAM pIntelWndParam);

/** @fn       NET_DVR_SetIntelligentCfg
  * @brief    ��ʼ�������豸���ý�����Ϣ����ʾ����  
  * @param    pDevLoginInfo  :�豸��½��Ϣ
  * @return   true : �����豸�����ʼ����ɹ���ʾ; false: �����豸����δ�ɹ���ʾ  
  */
AFX_PLATECONFIG_API bool __stdcall NET_DVR_SetIntelligentCfg(LPNET_INTELCFG_DEVLOGININFO pDevLoginInfo);

/** @fn       NET_DVR_SetChanIntelligentCfg(LPNET_INTELCFG_DEVLOGININFO pDevLoginInfo)
  * @brief    ��ʼ������ͨ�����ý�����Ϣ����ʾ����  
  * @param    LPNET_INTELCFG_DEVLOGININFO pDevLoginInfo  :�豸��½��Ϣ
  * @return   true : ����ͨ�������ʼ����ɹ���ʾ; false: ����ͨ������δ�ɹ���ʾ    
  */
AFX_PLATECONFIG_API bool __stdcall NET_DVR_SetChanIntelligentCfg(LPNET_INTELCFG_DEVLOGININFO pDevLoginInfo);

/** @fn       NET_DVR_DllPreTranslateMessage(MSG *pMsg)
  * @brief    ��ȡ�����ڵ�PreTranslateMessage��Ϣ���ڶ�̬���н�����Ӧ  
  * @param    MSG * pMsg  :��ȡ����Ϣ
  * @return   true �� ��ȡ��Ϣ�ɹ�; false�� ��ȡ��Ϣʧ��
  */
AFX_PLATECONFIG_API bool __stdcall NET_DVR_DllPreTranslateMessage(MSG *pMsg);

/** @fn       NET_DVR_DestroyDlg(bool bExit = false)
  * @brief    �ر�Զ�����ô���  
  * @param    bool bExit  :�Ƿ��ǳ����˳�
  * @return   true �� ���ٴ��ڳɹ�; false�� ���ٴ���ʧ��  
  */
AFX_PLATECONFIG_API bool __stdcall NET_DVR_DestroyDlg(bool bExit = false);

#endif