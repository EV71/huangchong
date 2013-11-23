#ifndef HIKSADP_H
#define HIKSADP_H

#define  CSADP_API extern"C" __declspec(dllimport)

	//��Ϣ����������
	#define SADP_ADD		  1			//����һ�豸
	#define SADP_UPDATE		  2			//�����豸
	#define SADP_DEC		  3			//�豸����
	#define SADP_RESTART	  4			//�豸��������
	#define SADP_UPDATEFAIL	  5			//�豸����ʧ��

    #define SADP_SETFAIL      6         //�豸��������ʧ��
    #define SADP_SET          7         //�豸��������ɹ�

	typedef unsigned char u_int8_t;
	typedef unsigned short u_int16_t;
	typedef unsigned int u_int32_t;

	// ������Ϣ
	typedef struct tagAdapterInfo          
	{
		char szDeviceName[128];           // ����
		char szIPAddrStr[16];             // IP
		char szHWAddrStr[18];             // MAC
		DWORD dwIndex;                    // ���
		UINT  DhcpEnabled;
	}INFO_ADAPTER, *PINFO_ADAPTER;

	CSADP_API BOOL  __stdcall SADP_Start(void(CALLBACK *HandleDataCallBack)(char* series,char* deviceid,
						char* hwaddr,char* praddr,char* subnetmask,unsigned int dev_type,unsigned int port,\
						unsigned int enccnt, unsigned int hdiskcnt,char* sfwversion, char* dspversion, char* starttime,int result));
	CSADP_API BOOL  __stdcall SADP_Stop();
	CSADP_API BOOL  __stdcall SADP_SendInquiry();
	CSADP_API BOOL  __stdcall SADP_ConfigLoad(char * devFilename);
	CSADP_API BOOL  __stdcall SADP_SendUpdateIp(char * desDLC,char *desIP,char* subnetmask,char * passwd,char * port);
	CSADP_API PINFO_ADAPTER __stdcall SADP_SysInfo();
	CSADP_API LONG __stdcall SADP_GetAdapNum();
	CSADP_API BOOL  __stdcall SADP_SendSetUserPasswd(char* desDLC,char* desIP,char* subnetmask,char* passwd,char* port);

#endif



