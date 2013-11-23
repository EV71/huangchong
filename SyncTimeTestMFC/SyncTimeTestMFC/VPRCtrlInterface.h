#ifndef __VPRCTRLINTERFACE__
#define __VPRCTRLINTERFACE__

//���ݽṹ����
//typedef unsigned char UINT8;
//typedef unsigned int UINT32;
//typedef unsigned int UINT;
//#define WINAPI      __stdcall
//typedef void *HANDLE;
//#define EXPORT
//typedef unsigned char BYTE;
//typedef long BOOL;
//typedef unsigned long ULONG;
//typedef long LONG;
//typedef unsigned short USHORT;
//typedef void *HINSTANCE;
typedef struct tagVedioPara
{
	int Brightness;//����(0-255)
	int Contrast;//�Աȶ�(0-127)
	int Saturation; //���Ͷ�(0-127)
	int Hue;//ɫ��(0-255)
}VEDIO_PARA,*PVEDIO_PARA;

typedef struct _GDW_IMAGE_INFO_
{
	UINT8	IsSendPic; 				//ͼƬ�Ƿ���    0-������ 1-����
	UINT8	JpegQuality;	     	//Jpegѹ������   1/2/3  1Ϊѹ��Ч�����
	UINT8	IsAddPlate;
	UINT8	res;
}GDW_IMAGE_INFO,*pGDW_IMAGE_INFO;

typedef struct tagVehiclePara
{
	UINT8 CaptureCmd;   			//ץ��     0-��Ȧ����ץ�� 1-��Ƶ����ץ�� 2-�ֶ�����ץ�� 3-��ͼ���ݲ���
	UINT8 byteUseLED;        		//ʹ��LED����  0-��ʹ��1-ʹ��LED, 2-ʹ�������
	UINT8 IsSendBinImage;  	//���ƶ�ֵͼ   0-������ 1-����
	UINT8 NearAddLiscence;  //�������ӳ��� �� 0������ 1����
	UINT8 NearAddTime;	    //����ͼ�е���ʱ��
	UINT8 res[3];
	UINT32 CameraType;	  			//�������
	UINT8 def_name[4];   				//Ĭ��ʡ��
	GDW_IMAGE_INFO	plateJpegInfo; 		//��ɫ����ͼ��Ϣ
	GDW_IMAGE_INFO	nearJpegInfo;  		//����JPEGͼ��Ϣ	
	UINT  	platePosX;		//���Ƶ���X����
	UINT  	platePosY;		//���Ƶ���Y����
	UINT  liscencePosX;		//���Ƶ���X���꣨OSD)
	UINT  liscencePosY;		//���Ƶ���Y���꣨OSD)
	UINT  timePosX;			//�ַ�����X���꣨OSD)
	UINT  timePosY;			//���Ƶ���Y���꣨OSD)
} Veicle_Para,*pVeicle_Para;

enum EquType
{
	HD976=0,
	DVS=1,
	NVR=2
};
typedef enum {
   StandardNone                   = 0x80000000,
   StandardNTSC                   = 0x00000001,
   StandardPAL                    = 0x00000002,
   StandardSECAM                  = 0x00000004,
} VideoStandard_t;  
typedef void (*TypeSadpStart)(char*,char*,	
										  char* ,	
										  char* ,	
										  char* ,	
										  unsigned int ,
										  unsigned int ,
										  unsigned int ,
										  unsigned int ,
										  char*,
										  char*, 
										  char*,
										  int);
/*****************************************************************
������: VPR_Init
����:   ϵͳ��ʼ��
����:   EquType i_equType;�豸����
����ֵ:
TRUE      �ɹ�
FALSE      ʧ��
��ע:
******************************************************************/
extern "C" bool WINAPI  EXPORT VPR_Init(EquType i_equType);
/*****************************************************************
������: VPR_CameraInit
����:   �������
����:
EquType i_equType;�豸����
io_uID        <0:ϵͳ���������ı�š�2:ͨ����>
o_handle  <2:����ͨ�����>
i_pchPort   <0:�����ʽ����:127.0.0.1:8000<admin,12345>>
i_hWndHandle  ������Ϣ�Ĵ�����<0,2>
i_uMsg        �û��Զ�����Ϣ����hWndHandle��ΪNULLʱ��
��⵽���µĳ���ʶ������׼���õ�ǰ���ƻ�������Ϣ��
��::PostMessage ������hWndHandle����uMsg��Ϣ������WPARAM����ΪuID��
LPARAM����Ϊ0.<0,2>
����ֵ:
TRUE        ��������ɹ���������uID���
FALSE       �������ʧ��
��ע:
������³�����Ϣ������׼���ó��ƻ�������Ȼ����Ϣ��
******************************************************************/
extern "C" bool WINAPI  EXPORT VPR_CameraInit(EquType i_equType,
											  int& io_uID,
											  HANDLE &o_handle,
											  char * i_pchPort,
											  HWND i_hWndHandle,
											  UINT i_uMsg
											  );
/*****************************************************************
������: VPR_CameraQuit
����:   �Ͽ���ָ����������ӻ��˳�ָ����ͨ��
����:	
EquType i_equType;�豸����
i_uID         <0:������.2:ͨ�����>
����ֵ:
TRUE        �ر�����ɹ�
FALSE       �ر����ʧ��
��ע:������ֹͣԤ������ִ�д˺���
******************************************************************/
extern "C" bool WINAPI  EXPORT VPR_CameraQuit(EquType i_equType,int *i_uID);

/*****************************************************************
������: VPR_Quit
����:  ϵͳ�ر��˳�
����:	EquType i_equType;�豸����
����ֵ:
TRUE        �رճɹ�
FALSE       �ر�ʧ��
��ע:
******************************************************************/
extern "C" bool WINAPI  EXPORT VPR_Quit(EquType i_equType);

/************************************************************************************
�������� VPR_SetCameraVideoPara
���ܣ����ó���ʶ�����
������
EquType i_equType;�豸����
int i_uID��<0:������.2.ͨ����>
i_VehiclePara ����ʶ���������<2>
����ֵ���ɹ�TRUE��ʧ��FALSE
��ע��
**************************************************************************************/
//extern "C" bool WINAPI  VPR_SetCameraPRPara(EquType i_equType,int i_uID,Vehicle_Para i_VehiclePara)
extern "C" bool WINAPI  VPR_SetCameraPRPara(EquType i_equType,int i_uID);
/*****************************************************************
������: VPR_CameraCapture
����:   �Է�������ʽ��ָ�����������ץ��ͼ��ʶ����ָ��
����:
EquType i_equType;�豸����
i_uID         <0:������.2:ͨ����>
����ֵ:
TRUE        �ѽ�������
FALSE       ��������(��ͨѶ����)
��ע:   �ú���Ϊ������ʽ����������������
******************************************************************/
extern "C" bool WINAPI  EXPORT VPR_CameraCapture(EquType i_equType,int i_uID);
/*****************************************************************
������:  VPR_GetVehicleInfo
����:    ��ȡ��ǰ���ƻ������еĳ��ƺš����ƶ�ֵ��ͼƬ�Լ�����ץ��ͼ��
����:	
EquType i_equType;�豸����
i_uID               <0:������2:ͨ���ţ������жϸ��豸�Ƿ��Ѿ����ã�>
o_pchPlate          ���صĳ��ƺ�(���������ȡ�32���ֽ�)<0,2>
o_piByteBinImagLen  ���صĳ��ƶ�ֵ��ͼƬ���ֽڳ���<0,2>
o_pbByteBinImage    ���صĳ��ƶ�ֵ��ͼƬ����(��������280���ֽ�)<0,2>
o_piJpegImageLen    ���صĳ���ץ��ͼƬ��С<0,2>
o_pbByteJpegImage   ���صĳ���ͼƬ���ݣ�JPEG/24bit��ʽ(��������200K���ֽ�)<0,2>
o_pVehicleWayNo     ���س�����<0,2>
o_pVehicleColor     ���صĳ�����ɫ<0,2>
����ֵ:
TRUE              �ɹ�
FALSE             ��������(��ͨѶ����)
��ע:    ���۳ɹ��������������ʶ���ǵ�ǰ�������е���Ϣ
******************************************************************/
extern "C" bool WINAPI  EXPORT VPR_GetVehicleInfo(EquType i_equType,
												  int i_uID,
												  char * o_pchPlate,
												  int * o_piByteBinImagLen,
												  BYTE * o_pbByteBinImage,
												  int * o_piJpegImageLen,
												  BYTE *o_pbByteJpegImage,
												  char *o_pVehicleWayNo,
												  char *o_pPlateColor);
/*****************************************************************
������:  VPR_CheckCameraStatus
����:    ���ָ�������״̬
����:	 
EquType i_equType;�豸����
i_uID              ������<0>
o_pchVprDevStatus ������'\0'��β��״̬˵���ַ���(����������32���ֽ�)<0>
����ֵ:
0	����
1	����
��ע:
******************************************************************/
extern "C" bool WINAPI VPR_CheckCameraStatus(EquType i_equType,int i_uID,char *o_pchVprDevStatus);
/*****************************************************************
������:  VPR_StartCameraVideoPreview
����:    ������ƵԤ��
����:	EquType i_equType;�豸����
int *i_uID��<0:������2:ͨ����>
HWND i_WndHandle����ʾ���ھ��<0,2>
RECT *i_rect����ʾ�����ڵľ�������<2>
BOOLEAN i_bOverlay���Ƿ�����OverlayԤ��ģʽ*<2>
int i_VideoFormat����ƵԤ����ʽ��Ŀǰ��Ч��<2>
int i_FrameRate����ƵԤ��֡�ʣ�PAL��1-25��NTSC��1-30��<2>
����ֵ:
TRUE      �ɹ�
FALSE      ʧ��
��ע:
******************************************************************/
extern "C" bool WINAPI VPR_StartCameraVideoPreview(EquType i_equType,int *i_uID,HWND i_WndHandle,
												   RECT *i_rect,BOOLEAN i_bOverlay, int i_VideoFormat, int i_FrameRate);

/*****************************************************************
�������� VPR_StopCameraVideoPreview
���ܣ�ֹͣԤ��
������
EquType i_equType;�豸����
int i_uID��<0:������2 ͨ����>
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע��
******************************************************************/
extern "C" bool WINAPI  VPR_StopCameraVideoPreview(EquType i_equType,int *i_uID);

/************************************************************************************
�������� VPR_GetCameraVideoPara
���ܣ���ȡ��Ƶ����
������EquType i_equType;�豸����,
*i_uID��������
i_VideoStandard��Ƶ��ʽ,
o_VedioPara��Ƶ����
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע��
**************************************************************************************/
extern "C" int WINAPI VPR_GetCameraVideoPara(EquType i_equType,int *i_uID, VideoStandard_t *i_VideoStandard,PVEDIO_PARA o_VedioPara);

/************************************************************************************
�������� VPR_SetCameraVideoPara
���ܣ�������Ƶ����
������
EquType i_equType;�豸����
*i_uID��������
i_VedioPara��Ƶ����
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע��
**************************************************************************************/
extern "C" int WINAPI  VPR_SetCameraVideoPara(EquType i_equType,int *i_uID,VEDIO_PARA i_VedioPara);

/************************************************************************************
�������� VPR_StartCameraVideoCapture
���ܣ�����ͨ����������������
������EquType i_equType;�豸����
UINT ChannelType;ͨ�����ͣ�1����ͨ��2����ͨ����
int i_uID��������
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע��
**************************************************************************************/
extern "C" int WINAPI VPR_StartCameraVideoCapture(EquType i_equType,UINT i_ChannelType,int i_uID);

/************************************************************************************
�������� VPR_StopCameraVideoCapture
���ܣ�ֹͣͨ����������������
������EquType i_equType;�豸����
UINT i_ChannelType;ͨ�����ͣ�1����ͨ��2����ͨ����
int i_uID��������
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע��
**************************************************************************************/
extern "C" int WINAPI VPR_StopCameraVideoCapture(EquType i_equType,UINT i_ChannelType,int i_uID);
/************************************************************************************
�������� VPR_SetCameraOsd
���ܣ�����OSD��ʾ������ǰ��ϵͳʱ������������ʱ�������Ϣ��������Ƶ֮�ϣ�������͸������
������EquType i_equType;�豸����
int i_uID��������
BOOL i_Enable��OSD�Ƿ���ʾ
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע��
**************************************************************************************/
extern "C" int WINAPI  VPR_SetCameraOsd(EquType i_equType,int i_uID, BOOL i_Enable);
/************************************************************************************
�������� VPR_SetCameraOsdDisplayModeEx
���ܣ�����OSD��ʾģʽ
������int i_uID��������
int i_Brightness��OSD��ʾ���ȡ�0���255����
BOOL i_Translucent��OSDͼ���Ƿ�����͸������
int i_param��Bit0���Ƿ��Զ�������ɫ��ת Bit16-23��ֱ�Ŵ��� Bit24-31ˮƽ �Ŵ���
int i_nLineCount��OSD��ʾ�����������Ϊ8��
USHORT **i_Format�������ַ���ʾ
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע��USHORT **Format�������ַ���ʾ�������ַ����ӵ�λ�úʹ���ĸ�ʽ����
����ÿһ�еĵ�һԪ��X�͵ڶ�Ԫ��Y �Ǹ��ִ��ڱ�׼4CIFͼ�����ʼλ�ã�X������16�ı�����Y������ͼ��߶���ȡֵ����0-575��PAL ��
��0-479��NTSC��������ASCII��Ҳ�����Ǻ��֣�����Ҫ��ʾ��ǰʱ��ʱ������ָ��Ϊ�̶���ʱ�䶨��ֵ����ֵ���£�
_OSD_YEAR4 ��λ������ʾ����2004
_OSD_YEAR2 ��λ������ʾ����02
_OSD_MONTH3 Ӣ�ĵ�����ʾ���� Jan
_OSD_MONTH2 ��λ���������ֵ�����ʾ����07
_OSD_DAY ��λ�İ��������ֵ�����ʾ����31
_OSD_WEEK3 Ӣ�ĵ�������ʾ����Tue
_OSD_CWEEK1 ���ĵ�������ʾ�������ڶ�
_OSD_HOUR24 24Сʱ��ʱ����ʾ����18
_OSD_HOUR12 12Сʱ��ʱ����ʾ����AM09��PM09
_OSD_MINUTE ��λ���ӵ���ʾ
_OSD_SECOND ��λ�����ʾ
�ڸ�ʽ�ַ�����ÿһ�����һ��Ԫ�ر�����NULL��0����β���������ʾ��������ݡ�
SetOsdDisplayModeEx����֧�����8��OSD�ַ�������ʾ��
**************************************************************************************/
extern "C" int WINAPI  VPR_SetCameraOsdDisplayModeEx(EquType i_equType,int i_uID,int i_color,
													 BOOL i_Translucent,int i_param,int i_nLineCount,USHORT **i_Format);
/************************************************************************************
�������� VPR_SetupCameraBitrateControl
���ܣ����ñ�����������ʡ�
������EquType i_equType;�豸����
*i_uID��<0:������2:ͨ�����>
ULONG i_Maxbps���������ʡ�ȡֵ��10000����<0,2>
����ֵ���ɹ�����0��ʧ�ܷ��ش����
��ע����NVR�У�����Ϊ0ʱ����������Ч������Ϊĳһ��������ʱ������������������ֵʱ��DSP���Զ����������������֤�������������ʣ�����������������������ʱ��DSP�����и��档�������<10%
**************************************************************************************/
extern "C" int WINAPI  VPR_SetupCameraBitrateControl(EquType i_equType,int *i_uID, ULONG i_MaxBps);

/************************************************************************************
�������� VPR_SADP_Start
���ܣ�SADP����
������
����ֵ��TRUE   �ɹ�
FALSE      ʧ��
��ע��
**************************************************************************************/
extern "C" bool WINAPI  VPR_SADP_Start(TypeSadpStart pfun);
/************************************************************************************
�������� VPR_GetCameraInfo
���ܣ����������豸����
����:
����ֵ��TRUE   �ɹ�
FALSE      ʧ��
��ע��
**************************************************************************************/
extern "C" bool WINAPI  VPR_SADP_SendInquiry();
/************************************************************************************
�������� VPR_SADP_SendUpdateIp
���ܣ������豸��IP��ַ�Ͷ˿ں�
������i_desDLC �豸�����ַ
i_desIP �豸IP��ַ��Ҫ�޸ĵ�IP��ַ
i_subnetmask IP��ַ��������
i_passwd �豸������
i_port �豸�˿ںŻ�Ҫ�޸ĵĶ˿ں�
����ֵ��TRUE      �ɹ�
FALSE      ʧ��
��ע��
**************************************************************************************/
extern "C" bool WINAPI  VPR_SADP_SendUpdateIp(char *i_desDLC,
									  char *i_desIP,
									  char *i_subnetmask,
									  char *i_passwd,
									  char *i_port
									  );
/************************************************************************************
��������  VPR_SADP_Stop()
���ܣ�ֹͣSADP
������
����ֵ��TRUE      �ɹ�
FALSE      ʧ��
��ע��
**************************************************************************************/
extern "C" bool WINAPI  VPR_SADP_Stop();



/*****************************************************************
������: DEV_SyncTime
����:   ʱ��ͬ��
����:   EquType i_equType;�豸����
����ֵ:
TRUE      �ɹ�
FALSE      ʧ��
��ע:
******************************************************************/
extern "C" bool WINAPI  EXPORT DEV_SyncTime(EquType i_equType,LONG lUserID);

#endif