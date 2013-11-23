#pragma once
//#include "NetIoNvr.h"
#include "incCn/HCNetSDK.h"
#define NET_IO_PREV_CHAN_VALID 0x040001	//ѯ�ʶ˿��Ƿ���Ч
#define NET_IO_PREV_CHAN_START 0x040002	//ͨ����ʼȡ��
#define NET_IO_PREV_CHAN_STOP 0x040003	//ͨ��ֹͣȡ��
#define NET_IO_PREV_CHAN_HEAD 0x040004	//ͨ��ȡͷ

#define MAX_CHANNEL_NUM 32

typedef enum
{
	NET_IO_Type_None,  //��Ч
	NET_IO_Type_Normal,//�Ǹ���ͨ��
	NET_IO_Type_HD     //����ͨ��
}NET_IO_ChanType;

typedef struct zzNetRealPlayCallbackParam{
	LPVOID p;
	//int devid;
	int chan;
	bool bMaster;
	zzNetRealPlayCallbackParam()
	{
		p = NULL;
		chan = -1;
		//devid = -1;
		bMaster = true;
	}
}NET_IO_NET_REALPLAY_PARAM;

#ifdef NET_IO_NVR_DLL_DEFINE
#define NET_IO_NVR_API _declspec(dllexport)
#else
#define NET_IO_NVR_API _declspec(dllimport)
#endif


#ifndef NET_IO_NVR_DLL_DEFINE

#ifndef _COMMU_DEFINE_H__XX
#define _COMMU_DEFINE_H__XX
#endif

#ifndef MAX_VERTEX_NUM
#define MAX_VERTEX_NUM 10
#endif

#ifndef MAX_MASK_NUM 
#define MAX_MASK_NUM 4
#endif

#ifndef MAX_INTERVAL_NUM
#define MAX_INTERVAL_NUM 4
#endif

#ifndef NAME_LEN
#define NAME_LEN 32
#endif

#ifndef SERIALNO_LEN 
#define SERIALNO_LEN 48
#endif

#ifndef MACADDR_LEN
#define MACADDR_LEN 6
#endif

#ifndef MAX_CHJC_NUM
#define MAX_CHJC_NUM 3
#endif

#ifndef MAX_LANERECT_NUM 
#define MAX_LANERECT_NUM 5
#endif

#define NET_DVR_SYSHEAD			1	//ϵͳͷ����
#define NET_DVR_STREAMDATA		2	//��Ƶ�����ݣ�����������������Ƶ�ֿ�����Ƶ�����ݣ�
#define NET_DVR_AUDIOSTREAMDATA	3	//��Ƶ������
#define NET_DVR_STD_VIDEODATA	4	//��׼��Ƶ������
#define NET_DVR_STD_AUDIODATA	5	//��׼��Ƶ������
#define NET_DVR_PRIVATE_DATA    112 //˽������,����������Ϣ


#define GET_CAM_BASICCFG				0x030c01		//��ȡ����������ò��� NET_DVR_DEVICECFG_V40 NET_DVR_DEVICECFG
#define SET_CAM_BASICCFG                0x030c02    //���������������
#define GET_CAM_COMPRESSCFG				0x030c03		//��ȡ���ѹ������ NET_DVR_COMPRESSIONCFG
#define SET_CAM_COMPRESSCFG             0x030c04    //�������ѹ������
#define GET_CAM_OSDCFG				    0x030c05		//��ȡ���OSD���� NET_DVR_PICCFG
#define SET_CAM_OSDCFG                  0x030c06   //�������OSD����
#define GET_CAM_NETCFG				    0x030c07	//��ȡ����������ò��� NET_DVR_NETCFG
#define SET_CAM_NETCFG                  0x030c08 //��������������
#define GET_CAM_PLATECFG				0x030c09	//��ȡ�����ʶ���� NET_DVR_SPRCFG
#define SET_CAM_PLATECFG                0x030c0a       //���������ʶ����
#define GET_CAM_FACECFG			        0x030c0b//��ȡ�����������
#define SET_CAM_FACECFG                 0x030c0c       //�������������
#define GET_CAM_VEDIO_FRONTCFG			0x030c0d//��ȡ�����Ƶ���ò��� NET_DVR_CAMERAPARAMCFG
#define SET_CAM_VEDIO_FRONTCFG          0x030c0e//���������Ƶ���ò���
#define GET_CAM_PLATE_BRTCFG            0x030c0f//��ȡ�������Ȳ������� NET_DVR_PLCCFG
#define SET_CAM_PLATE_BRTCFG            0x030c10 //���ó������Ȳ�������
#define GET_CAM_ABILITYCFG              0x030c11 //��ȡ������������� NET_DVR_SNAPENABLECFG 
#define SET_CAM_ABILITYCFG              0x030c12 //�����������������
#define GET_CAM_IMAGEOVERLAY              0x030c13 //��ȡ����ַ����Ӳ��� NET_DVR_IMAGEOVERLAYCFG
#define SET_CAM_IMAGEOVERLAY              0x030c14 //��������ַ����Ӳ���
#define GET_CAM_FLASHCFG                0x030c15 //��ȡ�������Ʋ��� NET_DVR_FLASH_OUTCFG
#define SET_CAM_FLASHCFG                0x030c16 //�����������Ʋ���
#define GET_CAM_IO_INCFG                0x030c17 //��ȡIO������� NET_DVR_IO_INCFG
#define SET_CAM_IO_INCFG                0x030c18 //����IO�������
#define GET_CAM_IO_OUTCFG               0x030c19 //��ȡIO������� NET_DVR_IO_OUTCFG
#define SET_CAM_IO_OUTCFG               0x030c1a //����IO�������
#define GET_CAM_IO_SNAPCFG              0x030c1b //��ȡIO����Ȧ�������� NET_DVR_SNAPCFG
#define SET_CAM_IO_SNAPCFG              0x030c1c //����IO����Ȧ��������
#define SET_CAM_REBOOT                  0x030c1d //���Զ������ NET_DVR_RebootDVR
#define SET_CAM_UPDATE                  0x030c1e //���Զ������ NET_DVR_Upgrade
#define SET_CAM_DEFAULT                 0x030c1f //����ָ�Ĭ�ϲ���

// ����ṹ��
typedef struct _tagCAM_INFO
{
	BYTE byChannel;  // �����ͨ����
	BYTE byIoChannel; // ���IO ����ͨ���� 0xff Ϊδʹ��
	BYTE byRes[2]; //Ԥ����0

	_tagCAM_INFO()
	{
		byChannel = 0;
		byIoChannel = 0xff;
		memset(byRes,0,sizeof(byRes));
	}

}CAM_INFO,*LPCAM_INFO;

//�������������Ϣ
typedef struct _tagCAM_BASIC_CFG
{
	DWORD dwSize;
	BYTE  byCamName[NAME_LEN]; // ͨ������

	//----------�����ֶξ�Ϊֻ���ֶ�
	BYTE  byDeviceType; // �������
	BYTE  byChannelNum; //���ͨ����Ŀ
	BYTE  byIoNum;  // IOͨ����Ŀ 
	BYTE  byRes1;  //Ԥ������0

	BYTE  sSerialNumber[SERIALNO_LEN]; // ���к�
	DWORD dwSoftwareVersion;  //����汾��,��16λ�����汾,��16λ�Ǵΰ汾
	DWORD dwSoftwareBuildDate; //�����������,0xYYYYMMDD  
	DWORD dwDSPSoftwareVersion;//DSP����汾,��16λ�����汾,��16λ�Ǵΰ汾
	DWORD dwDSPSoftwareBuildDate; //DSP ����������� OxYYYYMMDD
	DWORD dwHardwareVersion; // //Ӳ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	DWORD dwRes; //Ԥ���� 0

}CAM_BASIC_CFG,*LPCAM_BASIC_CFG;

typedef struct _tagSET_CAM_BASIC_CFG
{
	CAM_INFO stCamInfo;
	CAM_BASIC_CFG stCamBasicCfg;
}SET_CAM_BASIC_CFG,*LPSET_CAM_BASIC_CFG;


//ѹ������
typedef struct _tagCAM_COMPRESS_INFO
{
	BYTE byStreamType;  // �������� 0-��Ƶ����1-������
	BYTE byResolution;  // �ֱ��� 0-DCIF��1-CIF��2-QCIF��3-4CIF��4-2CIF��16-VGA��17-UXGA��18-SVGA��19-HD720p��20-XVGA��21-HD900p��22-SXGAp��27-1920*1080��28-2560*1920��29-1600*304��30-2048*1536��31-2448*2048��32-2448*1200��33-2448*800��34-XGA��1024*768����35-SXGA��1280*1024��,36-WD1(960*576/960*480),37-1080i 

	BYTE byBitrateType; // �������� 0-������ 1-������
	BYTE byPicQuality;  //ͼƬ����  0��ã�1�κã�2 �Ϻã�3 һ�㣬4�ϲ5 ��
	DWORD dwVideoBitrate; //����0-������1-16K(����)��2-32K��3-48k��4-64K��5-80K��6-96K��7-128K��8-160k��9-192K��10-224K��11-256K��12-320K��13-384K��14-448K��15-512K��16-640K��17-768K��18-896K��19-1024K��20-1280K��21-1536K��22-1792K��23-2048K��24-2560K��25-3072K��26-4096K��27-5120K��28-6144K��29-7168K��30-8192K��
	//���λ(31λ)�ó�1��ʾ���Զ���������0��30λ��ʾ����ֵ����Сֵ16k

	DWORD dwVideoFrameRate; //֡�� 0-ȫ����1-1/16��2-1/8��3-1/4��4-1/2��5-1��6-2��7-4��8-6��9-8��10-10��11-12��12-16��13-20��14-15��15-18��16��22 
	WORD  wIntervalFrameI; //I֡��� 0xffff��Ч
	BYTE byIntervalBPFrame; // ֡��ʽ 0 -BBP֡ 1 BP֡ 2-��P֡,0xff��Ч
	BYTE byRes1;            //Ԥ�� ��0
	BYTE byVideoEncType; //��Ƶ�������� 0-˽��264��1-��׼h264��2-��׼mpeg4��7-M-JPEG��0xff-��Ч
	BYTE byAudioEncType; // //��Ƶ�������� 0-OggVorbis��1-G711_U��2-G711_A��0xff-��Ч
	BYTE byRes[10];
}CAM_COMPRESS_INFO,*LPCAM_COMPRESS_INFO;

typedef struct _tagCAM_COMPRESS_CFG
{
	DWORD dwSize;
	CAM_COMPRESS_INFO stMainRecordParam; //������
	CAM_COMPRESS_INFO stSubRecordParam;  // ������
	CAM_COMPRESS_INFO stRes[2]; //Ԥ���� 0
}CAM_COMPRESS_CFG,*LPCAM_CAMPRESS_CFG;

typedef struct _tagSET_CAM_COMPRESS_CFG
{
	CAM_INFO stCamInfo;
	CAM_COMPRESS_CFG stCamCompressCfg;
}SET_CAM_COMPRESS_CFG,*LPSET_CAM_COMPRESS_CFG;

typedef struct _tagCAM_OSD_CFG
{
	DWORD dwSize; // �ṹ���С
	DWORD dwShowOSD; //Ԥ��ͼ�����Ƿ���ʾOSD 0- ����ʾ��1��ʾ
	WORD  wOSDTopLeftX; //OSD �� x����
	WORD  wOSDTopLeftY; //OSD �� y����

	BYTE  byOSDType; // OSD������ 0��XXXX-XX-XX ������ 1��XX-XX-XXXX ������ 
	// 2��XXXX��XX��XX��  3��XX��XX��XXXX��  4��XX-XX-XXXX ������ 5��XX��XX��XXXX��
	BYTE  byDispWeek; // �Ƿ���ʾ ���� 0-����ʾ��1��ʾ
	BYTE  byOSDAttrib;// OSD ���� 1- ͸������˸ 2 - ͸��������˸ 3- ��˸����͸�� 4 ��͸��������˸
	BYTE  byHourOSDType; //Сʱ�� 0 - 24 Сʱ�� 1- ��ʾ12 Сʱ am/pm��
	BYTE  byRes[12]; //Ԥ�� ��0                        

}CAM_OSD_CFG,*LPCAM_OSD_CFG;

typedef struct _tagSET_CAM_OSD_CFG
{
	CAM_INFO stCamInfo;
	CAM_OSD_CFG stCamOSDCfg;
}SET_CAM_OSD_CFG,*LPSET_CAM_OSD_CFG;


// IP ��ַ
typedef struct 
{		
	char	sIpV4[16];						/* IPv4��ַ */
	BYTE	byRes[128];						/* ���� */
}NET_IPADDR, *LPNET_IPADDR;

typedef struct _tagCAM_NET_CFG
{
	DWORD dwSize; // �ṹ���С
	NET_IPADDR stCamIP; // ���IP��ַ
	NET_IPADDR stMaskIP; // ���������ַ
	NET_IPADDR stGateIP;  // ���ص�ַ
	NET_IPADDR stDNSIP;   //DNS ��ַ

	BYTE byMacAddr[MACADDR_LEN]; // ����
	WORD wDVRPort;               // ��������˿�
	WORD wMTU;                   //MTU ��С
	DWORD dwNetInterface;        //1-10MBase-T��2-10MBase-Tȫ˫����3-100MBase-TX
	//4-100Mȫ˫����5-10M/100M/1000M����Ӧ
	NET_IPADDR stDnsServer1IPAddr; //˽��������ַ
	WORD wHttpPort; //http �����˿�
	BYTE byRes[32]; //Ԥ��
}CAM_NET_CFG,*LPCAM_NET_CFG;

typedef struct _tagSET_CAM_NET_CFG
{
	CAM_INFO stCamInfo;
	CAM_NET_CFG stCamNetCfg;
}SET_CAM_NET_CFG,*LPSET_CAM_NET_CFG; 

typedef struct _tagNET_VCA_RECT
{
	float fX;               //�߽�����Ͻǵ��X������, 0.001~1
	float fY;               //�߽�����Ͻǵ��Y������, 0.001~1
	float fWidth;           //�߽��Ŀ��, 0.001~1
	float fHeight;          //�߽��ĸ߶�, 0.001~1
}NET_VCA_RECT1, *LPNET_VCA_RECT1;

// ���Ʋ�������
typedef struct _tagCAM_PLATE_CFG
{
	DWORD dwSize;
	BYTE  byDefaultCHN[MAX_CHJC_NUM]; // Ĭ��ʡ��
	BYTE  byTotalLaneNum; //ʶ��ĳ�����
	BYTE  byPlateOSD; //0 - �����ӳ��� 1 ���ӳ��Ʋ�ɫͼƬ
	WORD  wDesignedPlateWidth; // ������ƿ��
	NET_VCA_RECT1 struLaneRect[MAX_LANERECT_NUM]; //ʶ������
	BYTE  byRes[32]; //Ԥ��
}CAM_PLATE_CFG,*LPCAM_PLATE_CFG;

typedef struct _tagSET_CAM_PLATE_CFG
{
	CAM_INFO stCamInfo;
	CAM_PLATE_CFG stCamPlateCfg;
}SET_CAM_PLATE_CFG,*LPSET_CAM_PLATE_CFG;

typedef struct _tagFACE_RECT
{
	float fLeft;        //�߽�����Ͻǵ��X������, 0.001~1        
	float fTop;         //�߽�����Ͻǵ��Y������, 0.001~1
	float fWidth;       //�߽��Ŀ��, 0.001~1
	float fHeight;     //�߽��ĸ߶�, 0.001~1
}FACE_RECT,*LPFACE_RECT;

typedef struct _tagFACE_POINT
{
	float fX;  // x����
	float fY;  // y����
}FACE_POINT,*LPFACE_POINT;

typedef struct FACE_MASK_AREA
{
	UINT32 nVertexNum;
	FACE_POINT struFacePoint[MAX_VERTEX_NUM];
}FACE_MASK_AREA,*LP_FACE_MASK_AREA;

typedef struct _tagCAM_FACE_CFG
{
	DWORD dwSize;
	float fScoreLevel; // ������ֵ
	float fLikeLevel;   // ���ƶ���ֵ
	UINT32 nDetectAreaSence;  //�������������
	float fTargetGenSpeed;    // Ŀ�������ٶ�

	UINT32    nDetectAreaNum;//����������
	FACE_POINT struDectAreaPt[MAX_VERTEX_NUM];//������򶥵���
	WORD       wFilter;  // 0 �����óߴ��������1 ���óߴ������
	WORD       wFilterType;// ����������
	FACE_RECT  stMinTargetFrame; // ��СĿ���
	FACE_RECT  stMaxTargetFrame;  //���Ŀ���
	UINT32     nMaskAreaNum; //�����������
	FACE_MASK_AREA struMaskArea[MAX_MASK_NUM]; // ��������
	BYTE       byRes[32]; //Ԥ�� ��0

}CAM_FACE_CFG,*LPCAM_FACE_CFG;

typedef struct _tagSET_CAM_FACE_CFG
{
	CAM_INFO stCamInfo;
	CAM_FACE_CFG stCamFaceCfg;
}SET_CAM_FACE_CFG,*LPSET_CAM_FACE_CFG;

#define MAXRANGE 30

// typedef struct WhiteBalance
// {
// 	int range[MAXRANGE];
// 	CString strRangeName[MAXRANGE];
// 	int iRGainMin;
// 	int iRGainMax;
// 	int iBGainMin;
// 	int iBGainMax;
// 	bool bWhiteBalance;
// 	WhiteBalance()
// 	{
// 		bWhiteBalance = false;
// 		memset(range, -1, sizeof(int) * MAXRANGE);
// 
// 		iRGainMin = 0;
// 		iRGainMax = 255;
// 		iBGainMin = 0;
// 		iBGainMax = 255;
// 
// 		strRangeName[0] = "�ֶ���ƽ��";
// 		strRangeName[1] = "�Զ���ƽ��1";
// 		strRangeName[2] = "�Զ���ƽ��2";
// 		strRangeName[3] = "�Զ�����";
// 		//			strRangeName[0] = g_HikStrSrc.fGetString(IDS_CCDMANUALWHITEBALANCE);
// 		//			strRangeName[1] = g_HikStrSrc.fGetString(IDS_CCDAUTOBALANCE1);
// 		//			strRangeName[2] = g_HikStrSrc.fGetString(IDS_CCDAUTOBALANCE2);
// 		//			strRangeName[3] = g_HikStrSrc.fGetString(IDS_CCDAUTOCTRL);
// 	}
// 
// 	void InitWhiteBalance()
// 	{
// 		bWhiteBalance = false;
// 		memset(range, -1, sizeof(int) * MAXRANGE);
// 
// 		iRGainMin = 0;
// 		iRGainMax = 255;
// 		iBGainMin = 0;
// 		iBGainMax = 255;
// 
// 		strRangeName[0] = "�ֶ���ƽ��";
// 		strRangeName[1] = "�Զ���ƽ��1";
// 		strRangeName[2] = "�Զ���ƽ��2";
// 		strRangeName[3] = "�Զ�����";
// 		//			strRangeName[0] = g_HikStrSrc.fGetString(IDS_CCDMANUALWHITEBALANCE);
// 		//			strRangeName[1] = g_HikStrSrc.fGetString(IDS_CCDAUTOBALANCE1);
// 		//			strRangeName[2] = g_HikStrSrc.fGetString(IDS_CCDAUTOBALANCE2);
// 		//			strRangeName[3] = g_HikStrSrc.fGetString(IDS_CCDAUTOCTRL);
// 	}
// }NET_IO_WHITEBALANCE;

typedef struct{  
	BYTE       byWhiteBalanceMode;
	BYTE       byWhiteBalanceModeRGain;
	BYTE       byWhiteBalanceModeBGain;
	BYTE       byRes[5];
}NET_IO_WHITEBALANCE, *LPNET_IO_WHITEBALANCE;

typedef struct _tagCAM_VEDIO_CFG
{
	DWORD dwSize;
	DWORD dwBright; //����
	DWORD dwContrast; // �Աȶ�
	DWORD dwAcute;     // ���
	DWORD dwSaturation; // ���Ͷ�

	//�����ֶν�IPC��Ч
	BYTE byVedioGain; // ��Ƶ����
	BYTE byVedioShutterSpeed; //��Ƶ�����ٶ�
	BYTE byBlackPwl; // �ڵ�ƽ����
	BYTE byJPEGQuality; // JPEG ͼƬ����
	BYTE byDynamicContrastEn; //��̬�Աȶ���ǿ 0- ����ǿ 1 -��ǿ
	BYTE byDynamicContrast; //��̬�Աȶ� 0-100
	BYTE byCaptureGain; //ǰ��ץ������
	BYTE byCaptureShutterSpeed; //ǰ��ץ���ٶ�

	NET_IO_WHITEBALANCE struWhiteBalance; //��ƽ������
	BYTE byRes[32];//Ԥ��
}CAM_VEDIO_CFG,*LPCAM_VEDIO_CFG;

typedef struct _tagSET_CAM_VEDIO_CFG
{
	CAM_INFO stCamInfo;
	CAM_VEDIO_CFG stCamVedioCfg;
}SET_CAM_VEDIO_CFG,*LPSET_CAM_VEDIO_CFG;

typedef struct _tagCAM_PLATE_BRT_CFG
{
	DWORD dwSize;
	BYTE  byPicEnable;  //�Ƿ����ó������Ȳ�����Ĭ�����ã�0-�رգ�1-����
	BYTE  byPlateExpectedBright; // ����Ԥ������Ĭ��Ϊ50��ΧΪ0��100
	BYTE  byTradeOffFlash; ////�Ƿ��������Ӱ�� 0�رգ�1����
	//ʹ������Ʋ���ʱ��������Ǽ�������Ƶ�������ǿЧӦ������Ҫ//��Ϊ1������Ϊ0
	BYTE  byCorrectFactor;//����ϵ�� Ĭ��Ϊ50
	BYTE  byRes[32]; //Ԥ�� ��0 
}CAM_PLATE_BRT_CFG,*LPCAM_PLATE_BRT_CFG;

typedef struct _tagSET_CAM_PLATE_BRT_CFG
{
	CAM_INFO stCamInfo;
	CAM_PLATE_BRT_CFG stCamPlateBrtCfg;
}SET_CAM_PLATE_BRT_CFG,*LPSET_CAM_PLATE_BRT_CFG;

typedef struct _tagCAM_ABILITY_CFG
{
	DWORD dwSize;
	BYTE  byPlateEnable; //�Ƿ�֧�ֳ���ʶ�� 0-��֧�֣�1- ֧��
	BYTE  byFrameFlip;  //ͼ���Ƿ�ת 0-����ת 1-��ת
	WORD  wFlipAngle;   // ͼƬ��ת�Ƕ� 0��90��180��270
	WORD  wLightPhase;    //��λ ȡֵ��Χ(0,360)
	BYTE  byLightSyncPower; // �Ƿ��źŵƵ�Դͬ�� 0-��ͬ�� 1 ͬ��
	BYTE  byFrequency;  //�ź�Ƶ��
	BYTE  byUploadSDEnable;  //�Ƿ��Զ��ϴ�SDͼƬ 0�� 1��
	//--------�����ֶν�IPC��Ч�������ֶν�ģ�������Ч

	BYTE  byPlateMode;       //ʶ��ģʽ����(��Ids-65xx֧��)0-��Ƶ���� 1�ⲿ����
	BYTE  byBlackLightMode;  // ���ⲹ��ģʽ 0-�رձ��ⲹ�� 1-�������ⲹ�� 2-����ǿ������
	BYTE  byColorBlackMode;  // ��ת��ģʽ 0-�Զ���ת�� 1-�ڰ�ģʽ��2��ɫģʽ
	BYTE  byApertureMode;    // ��Ȧģʽ��0 ���ӹ�Ȧ 1�Զ���Ȧ
	BYTE  byShutterValue;    //����ֵ ȡֵ��Χ[0,12]
	BYTE byRes[30]; //Ԥ�� ��0
}CAM_ABILITY_CFG,*LPCAM_ABILITY_CFG;

typedef struct _tagSET_CAM_ABILITY_CFG
{
	CAM_INFO stCamInfo;
	CAM_ABILITY_CFG stCamAbilityCfg;
}SET_CAM_ABILITY_CFG,*LPSET_CAM_ABILITY_CFG;

typedef struct _tagCAM_IMAGEOVERLAY_CFG
{
	DWORD dwSize;
	BYTE  byOverlayInfo; //����ʹ�ܿ��� 0-�����ӣ�1-����
	BYTE  byOverlayMonitorInfo; //�Ƿ���Ӽ�ص���Ϣ 0-�����ӣ�1-����
	BYTE  byOverlayTime;   // �Ƿ����ʱ�� 0-�����ӣ�1-����
	BYTE  byOverSpeed;  ////�Ƿ�����ٶ� 0-�����ӣ�1-����
	BYTE  byOverlaySpeeding; // �Ƿ���ӳ��ٱ��� 0-�����ӣ�1-����
	BYTE  byOverlayLimitFlag; //�Ƿ�������ٱ�� 0-�����ӣ�1-����
	BYTE  byOverlayPlate;     //�Ƿ���ӳ��� 0-�����ӣ�1-����
	BYTE  byOverlayColor;      //�Ƿ���ӳ�����ɫ 0-�����ӣ�1-����
	BYTE  byOverlayLength;     // �Ƿ���ӳ��� 0-�����ӣ�1-����
	BYTE  byOverlayType;       // �Ƿ���ӳ��� 0- �����ӣ�1-����
	BYTE  byOverlayColorDepth; //�Ƿ���ӳ�����ɫ��ǳ 0-�����ӣ�1-����
	BYTE  byOverlayDriveChan;   //�Ƿ���ӳ��� 0-������ 1-����
	BYTE  byOverlayMillSec;     //�Ƿ���Ӻ�����Ϣ 0-�����ӣ�1-����
	BYTE  byOverlayIllegalInfo;  //�Ƿ����Υ����Ϣ 0-������ 1-����
	BYTE  byOverlayRedOnTime;    // �Ƿ���Ӻ������ʱ�� 0-�����ӣ�1-����
	BYTE  byRes1;                //Ԥ�� �� 0
	BYTE  byMonitor1;            //��ص�1
	BYTE  byMonitor2;            //��ص�2
	BYTE  byRes2[34]; //Ԥ���� 0

}CAM_IMAGEOVERLAY_CFG,*LPCAM_IMAGEOVERLAY_CFG;

typedef struct _tagSET_CAM_IMAGEOVERLAY_CFG
{
	CAM_INFO stCamInfo;
	CAM_IMAGEOVERLAY_CFG stCamImageOverlayCfg;
}SET_CAM_IMAGEOVERLAY_CFG,*LPSET_CAM_IMAGEOVERLAY_CFG;


typedef struct _tagCAM_FLASH_CFG
{
	DWORD dwSize;
	BYTE  byCamAddr; //�����485��ַ,0xFF��ʾ��Ч
	BYTE  byFlashAddr; //����ƿ���С�� 485��ַ��0xFF��ʾ��Ч
	BYTE  byRes[2]; //Ԥ�� ��0
	float fPhase; // ����ƿ���С�� ��λȡֵ��Χ
	float fDutyRate;//
	UINT32 nFreqValue;  //����ƿ���С�� Ƶ�ʲ��� ȡֵ 0-4
	BYTE   byMode; //�������˸ģʽ 0- ������1--����2-- ��������3-����
	BYTE   byRelatedIoIn; //����ƹ�������IO�ţ�������ʱ���˲�����Ч������
	BYTE   byRecognizedLane; // ������IO�� ��λ��ʾ,bit0 ��ʾio1 �Ƿ���� 0-��������1����
	BYTE   byDetectBrightness; // �Զ��������ʹ������� 0- ����� 1- ���
	BYTE   byBrightnessThreld;// ʹ�������������ֵ����Χ [0-100],������ֵ��
	BYTE   byStartHour; //��ʼʱ�� ��λСʱ
	BYTE   byStartMinute; //��ʼʱ�䵥λ�� ȡֵ��Χ[0,59]
	BYTE   byEndHour;    // ����ʱ�� ��λСʱ��ȡֵ��Χ[0��23]
	BYTE   byEndMinute; // ����ʱ�� ��λ�֣�ȡֵ��Χ[0,59]
	BYTE   byFlashLightEnable; //������Ƿ��� 0 -�أ�1 - ��
	BYTE   byRes2[6];//Ԥ���� 0

}CAM_FLASH_CFG,*LPCAM_FLASH_CFG;

typedef struct _tagSET_CAM_FLASH_CFG
{
	CAM_INFO stCamInfo;
	CAM_FLASH_CFG stCamFlashCfg;
}SET_CAM_FLASH_CFG,*LPSET_CAM_FLASH_CFG;

typedef struct _tagCAM_IO_IN_CFG
{
	DWORD dwSize; 
	BYTE  byIoInStatus; // �����IO��״̬ 0-�½��أ�1�����أ�2- �����غ��½��أ�3-�ߵ�ƽ��4-�͵�ƽ
	BYTE  byRes[7];//Ԥ���� 0
}CAM_IO_IN_CFG,*LPCAM_IO_IN_CFG;

typedef struct _tagSET_CAM_IO_IN_CFG
{
	CAM_INFO stCamInfo;
	CAM_IO_IN_CFG stCamIoInCfg;
}SET_CAM_IO_IN_CFG,*LPSET_CAM_IO_IN_CFG;

typedef struct _tagCAM_IO_OUT_CFG
{
	DWORD dwSize;
	BYTE  byDefaultStatus; // IO Ĭ��״̬ 0-�͵�ƽ 1- �ߵ�ƽ
	BYTE  byIoOutStatus;  // IO��Чʱ״̬ 0-�͵�ƽ 1- �ߵ�ƽ��2- ����
	WORD  wAheadTime;     // ���IO��ǰʱ�� ��λus,ȡֵ��Χ [0,300]
	DWORD dwTimePluse;    // ������ʱ�� ��λ us
	DWORD dwTimeDelay;    // IO��Ч����ʱ�� ��λus
	BYTE  byFreqMulti;    // ��Ƶ��ȡֵ��Χ[1,15] 
	BYTE  byDutyRate;     // ռ�ձ� ��λ%[0,40]
	BYTE  byRes[6]; //Ԥ�� ��0
}CAM_IO_OUT_CFG,LPCAM_IO_OUT_CFG;

typedef struct _tagSET_IO_OUT_CFG
{
	CAM_INFO stCamInfo;
	CAM_IO_OUT_CFG stCamIoOutCfg;  
}SET_IO_OUT_CFG,*LPSET_IO_OUT_CFG;

typedef struct _tagCAM_IO_SNAP_CFG
{
	DWORD dwSize;
	BYTE  byRelatedDriveWay; // ����IO�����ĳ����� ȡֵ��Χ [0-9]
	BYTE  bySnapTimes; // ��Ȧץ�Ĵ��� 0-��ץ�� ��0 Ϊץ�Ĵ��� ���Ϊ5��
	WORD wSnapWaitTime;   //ץ�ĵȴ�ʱ�� ��λms,ȡֵ��Χ [0,6000]
	WORD wIntervalTime[MAX_INTERVAL_NUM]; // ץ�ļ��ʱ�� ��λms,ȡֵ��Χ[67,60000]
	BYTE byRes[24]; //Ԥ����0
}CAM_IO_SNAP_CFG,*LPCAM_IO_SNAP_CFG;

typedef struct _tagSET_CAM_IO_SNAP_CFG
{
	CAM_INFO stCamInfo;
	CAM_IO_SNAP_CFG stCamIoSnapCfg;

}SET_CAM_IO_SNAP_CFG,*LPSET_CAM_IO_SNAP_CFG;

#endif

// ������������Ļص�
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
#if defined(STATIC_LOAD_IO_NVR)
typedef int (CALLBACK *pCfgDataCallBack)(int iChannel, int iCammandCode,char *recvbuf,char *sendbuf,int *iLen,int userdata,int param1,int param2);

#ifdef __cplusplus
extern "C"
{
#endif
	int NET_IO_NVR_API NET_IO_Initialize();
	int NET_IO_NVR_API NET_IO_Finalize();

	int NET_IO_NVR_API NET_IO_StartService(UINT Port);
	int NET_IO_NVR_API NET_IO_StopService(void);
	
	int NET_IO_NVR_API NET_IO_PutStream(int Channel, bool bIsMasterStream, char* Stream, int StreamLength, int FrameType);
	
    int NET_IO_NVR_API NET_IO_SetCallBackCfgData(pCfgDataCallBack pDataFunc,int userdata);

	int NET_IO_NVR_API NET_IO_SetDeviceBuffer(int* DeviceType);

#ifdef __cplusplus
}
#endif

#endif




