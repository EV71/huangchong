#pragma  once

#include <winsock2.h>
#include <stdio.h>
#include <TCHAR.H>
#include <vector>
#include <map>

using namespace std;

#include <windows.h>

typedef unsigned __int64 UINT64;
typedef unsigned int     UINT32;
typedef unsigned short   UINT16;
typedef unsigned char    UINT8;
typedef short            INT16;
typedef signed char      INT8;

#define MAXNAMELEN     260
#define MAXPATHLEN     260

#define RECVTIMEOUT    1*1000*60 
#define SENDTIMEOUT    2*1000*60

#define MINPACKETLEN       120
#define UCIPACKETLEN       112

#define MAX_PLATE_JPEG_SIZE  10*1024  //����ͼƬ��С����
#define MAX_CAR_JPEG_SIZE    600 *1024  // ����ͼƬ��С����

#define PLATE_JPEG_SIZE_ADDR 120  //����JPEG��ͨѶЭ�����ʼλ��

#define MAX_PLATE_LEN        16
#define MAX_CARD_LEN         30 
#define DATA_LISTEN_PORT    8682  //���ݼ����˿�
#define CMD_LISTEN_PORT     8680  //ָ������˿�

// ͣ����ͨѶЭ���ϴ���������
typedef struct _tagCMR_TrafficData
{
    UINT16  nVehicleNo;                        // �������   
    UINT16  nLaneId;                           // ������
    char    chPlateNo[MAX_PLATE_LEN];     // ����
    UINT16  nPlateConfidence;                  // �������Ŷ�
    UINT8   nRecognitionCharacterNo;           // ʶ���ַ�����
    UINT8   nReserved_1;                       // Ԥ��
    INT16   nRecognitionCharacterConfiendce[10];  //ʶ���ַ����Ŷ�
    UINT8   nVehicleColor;                        // ������ɫ
    UINT8   nVehicleColorDeep;                    // ������ɫ��ǳ
    UINT16  nReserved_2;                          // Ԥ��
    char    nPassTime[8];                         // ����ʱ��
    UINT16  nTypeIO;                              // ������� 
    UINT16  nTypeVehicle;                         // �������
    UINT32  nTypePark;                            // ͣ�����
    char    chCardNo[MAX_CARD_LEN];           // ����
    UINT16  nReserved_3;                          // Ԥ��
    UINT32  nDoorIndex;                           // ����ڱ��
    UINT32  nOutMode;                             // �������
    UINT32  nOpPersonIndex;                       // ������Ա���
    char    nStopTime[8];                         // ͣ��ʱ��
    UINT8   nReserved_4;                          // Ԥ��
    UINT8   nTypeAlarm;                           // �������
    UINT8   nRecChanNo;                           // ����¼��ͨ��
    UINT8   nReserved_5;                          // Ԥ��

    UINT32  nPlateJpegSize;                       // ����ͼƬ��С
    UINT8   *pnPlateJpegData;                     // ����ͼƬ����
    UINT32  nCarJpegSize;                         // ����ͼƬ��С
    UINT8   *pnCarJpegData;                       // ����ͼƬ����
    UINT32  nCarJpeg1Size;                       //  ����ͼƬ1��С
    UINT8   *pnCarJpeg1Data;                     // ����ͼƬ1����

    _tagCMR_TrafficData()
    {
        nOpPersonIndex = 0;
        chPlateNo[0] = '\0';
        chCardNo[0] = '\0';
        pnPlateJpegData = NULL;
        pnCarJpegData = NULL;
        pnCarJpeg1Data = NULL;

    }

}CMR_TrafficData,*pCMR_TrafficData;


//�ն˷��������쳵����Ϣ�ϴ�
typedef struct _tagUCI_TrafficData{
	char chPlateNo[MAX_PLATE_LEN];     // ���ƺ���
	char chCarType[20];						//��������
	char chCarColor[12];						//������ɫ
	char chOwnerName[32];					//��������
	char chCardNum[30];						//����
	char chReserved[2];						//Ԥ��
	_tagUCI_TrafficData()
	{
		chPlateNo[0]='\0';
		chCarType[0]='\0';
		chCarColor[0]='\0';
		chOwnerName[0]='\0';
		chCardNum[0]='\0';
		chReserved[0]='\0';
	}
}UCI_TrafficData, *pUCI_TrafficData;


#define COMU_REQUEST	1
#define COMU_RESPONSE	2

const char SynInfo[] = {'G','D','W','S','I','C'};
#define SYN_HEADER_SIZE     (sizeof(SynInfo))

#define MAX_PLATE_NUM_SIZE 16
#define BINARY_IMG_SIZE    280
#define MAX_PLATE_JPEG_SIZE 10*1024
#define MAX_VEHICLE_JPEG_SIZE 600*1024
#define HR_IMG_WIDTH        1600
#define HR_IMG_HEIGHT       1200
#define HF_IMG_WIDTH        1600
#define HF_IMG_HEIGHT       300



#define MAX_BUFFER_SIZE 600*1024
#define LISTENPORT 8682

#define TYPE_IN    0
#define TYPE_OUT   1

//ͨѶͷ
typedef struct _tagGDW_PacketHead
    {
    unsigned int dwDataLen;			//�����峤��
    unsigned short wDataType;		//��������
    unsigned short wCheckSum;		//У���
    unsigned short wCommandType;	//��������
    unsigned short wCommand;		//����
    unsigned short wError;			//������
    unsigned short wReserved;		//����λ
    //Ĭ�Ϲ��캯��
    _tagGDW_PacketHead(void)
        :dwDataLen(0)
        ,wDataType(0)
        ,wCheckSum(0)
        ,wCommandType(0)
        ,wCommand(0)
        ,wError(0)
        ,wReserved(0)
        {
        //��
        }
    }GDW_PacketHead,*pGDW_PacketHead;


unsigned short CheckSum(unsigned short *pBuffer, UINT32 nSize);
