#pragma once
#define STATIC_LOAD_IO_NVR
#include "NetIoNvrDll.h"
#include "OperMysql.h"
#include "Config.h"
#include "Log.h"

//�豸�ṹ��
typedef struct _tagDevice{
	int CamID;//�����Ӧ���ݿ�id
	int IsUsing;
	long LoginHandle;
	char Head[300];
	char SubHead[300];
	long HeadLength;
	long SubHeadLength;
	long PlayHandle;
	long SubHandle;
	long HeadHandle;
	NET_IO_NET_REALPLAY_PARAM MainParam;
	NET_IO_NET_REALPLAY_PARAM SubParam;
	NET_DVR_DEVICEINFO_V30 DeviceInfo;
	_tagDevice()
	{
		CamID = -1;
		IsUsing = 0;
		LoginHandle = -1;
		ZeroMemory(Head,sizeof(Head));
		HeadLength = -1;
		ZeroMemory(SubHead,sizeof(SubHead));
		SubHeadLength = -1;
		PlayHandle = -1;
		SubHandle = -1;
		HeadHandle = -1;
		ZeroMemory(&DeviceInfo,sizeof(DeviceInfo));
	}
	~_tagDevice()
	{
		if (HeadHandle >= 0)
		{
			NET_DVR_StopRealPlay(HeadHandle);
			HeadHandle = -1;
		}
		if (PlayHandle >= 0)
		{
			NET_DVR_StopRealPlay(PlayHandle);
			PlayHandle = -1;
		}
		if (SubHandle >= 0)
		{
			NET_DVR_StopRealPlay(SubHandle);
			SubHandle = -1;
		}
		if (LoginHandle >=0)
		{
			NET_DVR_Logout_V30(LoginHandle);
			LoginHandle = -1;
		}
	}
}DEVICE,*pDEVICE;

//����ȡ������ָ������
typedef void(__stdcall *fRealDataCallBack_V30)(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
//Զ������������ûص�����ָ������
typedef int(__stdcall *pCfgDataCallBack)(int iChannel,int iCammandCode,char *recvbuf,char *sendbuf,int *iLen,int userdata,int param1,int param2);

//����ȡ���ص�����������Ӧ�õ���NET_IO_PutStreamȥ������������
void __stdcall RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);

// ������������Ļص�
/*�ص�����
1.ȡ�����֣��ص����������θ��������
	NET_IO_PREV_CHAN_VALID
	ѯ��ĳ��ͨ���Ƿ���á�
	��ʱ��sendbuf����һ��boolָ�룬���������*ȡֵ����true����false����
	NET_IO_PREV_CHAN_HEAD
	Ҫ��������ϵͳͷ
	��ʱ��recvbuf����һ��BOOL���ͣ���ָ�룩��ǿ��ת�����ͺ󣬵õ���ֵΪ�Ƿ�Ϊ��������
	�ٸ���iChannel����������Ӧ��ͷд��sendbuf��ָ���ڴ������У�����*iLen�и���ϵͳͷ�ĳ��ȡ�
	NET_IO_PREV_CHAN_START
	��ʱ��recvbuf����һ��BOOL���ͣ���ָ�룩��ǿ��ת�����ͺ󣬵õ���ֵΪ�Ƿ�Ϊ��������
	�ٸ���iChannel��������ʼȡ��ͨ��������������������
	�յ��������Ӧ��ʼʹ��NET_IO_PutStream���ṩ������
	NET_IO_PREV_CHAN_STOP
	ĳͨ���������Ӷ��رպ�ֹͣ���š�iChannelΪ��Ҫֹͣ��ͨ����
	�յ�����������ֹͣȡ��������������������ֹͣ��
2.���ò��֣����ݻص��������������recvbuf������ͬ�Ľṹ��ָ��������
	�����SETϵ��������������ɹ�ʱ���ص���������ֵΪ0����֮������ʧ�ܣ���ص�����Ӧ���ظ�����
	GETָ������Ҫǡ������дsendbuf��iLen�������ɹ�ʱ�ص���������0�����򷵻ظ�����
*/
/****
�ص���������˵��
int iChannel:ͨ����
int iCammandCode:������
char *recvbuf:���յ�����buffer��ΪԶ����������ʱ��Ϊ�����Ķ������ļ�����ȫ·��
char *sendbuf:���͵�����buffer
ilen         :�������ݳ���ָ��
int userdata �û��Զ�����������
int param1   ���I0����ʱΪIO��
int param2   δʹ��

���ͽ��յ�buffer ���ĳ���ΪMAX_CLIENT_DATA (2K bytes)
*****/
int __stdcall CfgDataCallBack(int iChannel,int iCammandCode,char *recvbuf,char *sendbuf,int *iLen,int userdata,int param1,int param2);

#ifndef STATIC_LOAD_IO_NVR
//����ָ�����Ͷ��弯
typedef int(__cdecl  *pfuncNET_IO_Initialize)(void);
typedef int(__cdecl  *pfuncNET_IO_Finalize )(void);
typedef int(__cdecl  *pfuncNET_IO_StartService)(UINT Port);
typedef int(__cdecl  *pfuncNET_IO_StopService)(void);
typedef int(__cdecl  *pfuncNET_IO_PutStream)(int Channel, bool bIsMasterStream, char* Stream, int StreamLength,int FrameType);
typedef int(__cdecl  *pfuncNET_IO_SetCallBackCfgData)(pCfgDataCallBack pDataFunc,int userdata);
typedef int(__cdecl  *pfuncNET_IO_SetDeviceBuffer)(int* DeviceType);
#endif
//ͨѶ����
class clsNetIONvr
{
private:
	clsNetIONvr(void);
	~clsNetIONvr(void);
public:
	void ServerStart();
	void ServerStop();
	static int m_iServerFlag;
#ifndef STATIC_LOAD_IO_NVR
private:
	pfuncNET_IO_Initialize NET_IO_Initialize;
	pfuncNET_IO_Finalize NET_IO_Finalize;
	HMODULE m_hModule;
public:
	pfuncNET_IO_StartService NET_IO_StartService;
	pfuncNET_IO_StopService NET_IO_StopService;
	pfuncNET_IO_PutStream NET_IO_PutStream;
	pfuncNET_IO_SetCallBackCfgData NET_IO_SetCallBackCfgData;
	pfuncNET_IO_SetDeviceBuffer NET_IO_SetDeviceBuffer;
#endif
	static clsNetIONvr* GetInstance();
	static void LeaveInstance();
private:
	static clsNetIONvr *m_pInstance;//ʵ��ָ��
	static CRITICAL_SECTION m_csLock;//ʵ������������߳�����
	//��Ƕ�࣬�����ͷ�m_pInstanceָ��
	//class CGarbo{
	//public:
	//	~CGarbo()
	//	{
	//		if(clsNetIONvr::m_pInstance)
	//		{
	//			delete clsNetIONvr::m_pInstance;
	//			clsNetIONvr::m_pInstance = NULL;
	//		}
	//	}
	//	static CGarbo m_Carbo;
	//};
	//
public:
	static COpMySQL m_OperMysql;//���ݿ������

	static CConfig m_Config;//�����ļ���
	CString	m_strDBServer;
	CString	m_strDBName; 
	CString	m_strDBUser;   
	CString	m_strDBPwd;   
	CString	m_strDBPort;
	CString m_strNetIoPort;

	static CLog m_CLog;//��־�ļ���
public:
	int m_iDevicesTable[MAX_CHANNEL_NUM];//���ڼ�¼�豸��λ�ã�ΪNET_IO_SetDeviceBuffer�Ĳ�����0��15Ϊ���������16��31Ϊ51xx�豸.
	DEVICE m_Devices[MAX_CHANNEL_NUM];//�豸��������
	//��ȡ�����豸
	void GetAllAccessDevices();
private:
	BOOL m_InitFlag;
public:
	BOOL GetDLLStatus(void);
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//���������ඨ�岿��
class clsCfgParam
{
public:
	clsCfgParam(void);
	~clsCfgParam(void);
public:
	static bool funcNET_IO_PREV_CHAN_VALID_Cam(DEVICE *d,char *sendbuf);
	static bool funcNET_IO_PREV_CHAN_START_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcNET_IO_PREV_CHAN_STOP_Cam(DEVICE *d);
	static bool funcNET_IO_PREV_CHAN_HEAD_Cam(DEVICE *d,int iChannel,char *recvbuf,char *sendbuf,int *iLen,void *pNetIoNvr);

	static bool funcGET_CAM_BASICCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_BASICCFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_COMPRESSCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_COMPRESSCFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_OSDCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_OSDCFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_NETCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_NETCFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_PLATECFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_PLATECFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_FACECFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_FACECFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_VEDIO_FRONTCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_VEDIO_FRONTCFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_PLATE_BRTCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_PLATE_BRTCFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_ABILITYCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_ABILITYCFG_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_IMAGEOVERLAY_Cam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_IMAGEOVERLAY_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_FLASHCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_FLASHCFG_Cam(DEVICE *d,char *recvbuf,int iChannel,int param1);
	static bool funcGET_CAM_IO_INCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_IO_INCFG_Cam(DEVICE *d,char *recvbuf,int iChannel,int param1);
	static bool funcGET_CAM_IO_OUTCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_IO_OUTCFG_Cam(DEVICE *d,char *recvbuf,int iChannel,int param1);
	static bool funcGET_CAM_IO_SNAPCFG_Cam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_IO_SNAPCFG_Cam(DEVICE *d,char *recvbuf,int iChannel,int param1);

	static bool funcSET_CAM_REBOOT_Cam(DEVICE *d,int iChannel);
	static bool funcSET_CAM_UPDATE_Cam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcSET_CAM_DEFAULT_Cam(DEVICE *d,int iChannel);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static bool funcNET_IO_PREV_CHAN_VALID_MCam(DEVICE *d,char *sendbuf);
	static bool funcNET_IO_PREV_CHAN_START_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcNET_IO_PREV_CHAN_STOP_MCam(DEVICE *d);
	static bool funcNET_IO_PREV_CHAN_HEAD_MCam(DEVICE *d,int iChannel,char *recvbuf,char *sendbuf,int *iLen,void *pNetIoNvr);

	static bool funcGET_CAM_BASICCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_BASICCFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_COMPRESSCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_COMPRESSCFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_OSDCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_OSDCFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_NETCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_NETCFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_PLATECFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_PLATECFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_FACECFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_FACECFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_VEDIO_FRONTCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_VEDIO_FRONTCFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_PLATE_BRTCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_PLATE_BRTCFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_ABILITYCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_ABILITYCFG_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_IMAGEOVERLAY_MCam(DEVICE *d,char *sendbuf,int iChannel,int *iLen);
	static bool funcSET_CAM_IMAGEOVERLAY_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcGET_CAM_FLASHCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_FLASHCFG_MCam(DEVICE *d,char *recvbuf,int iChannel,int param1);
	static bool funcGET_CAM_IO_INCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_IO_INCFG_MCam(DEVICE *d,char *recvbuf,int iChannel,int param1);
	static bool funcGET_CAM_IO_OUTCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_IO_OUTCFG_MCam(DEVICE *d,char *recvbuf,int iChannel,int param1);
	static bool funcGET_CAM_IO_SNAPCFG_MCam(DEVICE *d,char *sendbuf,int iChannel,int param1,int *iLen);
	static bool funcSET_CAM_IO_SNAPCFG_MCam(DEVICE *d,char *recvbuf,int iChannel,int param1);

	static bool funcSET_CAM_REBOOT_MCam(DEVICE *d,int iChannel);
	static bool funcSET_CAM_UPDATE_MCam(DEVICE *d,char *recvbuf,int iChannel);
	static bool funcSET_CAM_DEFAULT_MCam(DEVICE *d,int iChannel);
};



