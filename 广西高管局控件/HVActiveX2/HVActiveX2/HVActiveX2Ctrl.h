#pragma once

#include "BufferManager.h"
#include <gdiplus.h>
#include <GdiplusImaging.h>
#include <GdiplusImageCodec.h>
#include <vector>
//#define ONE_DEVICE
//#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

//�Զ�����Ϣ�ṹ��Ϳؼ���Ϣ�ṹ��
typedef struct _MESSAGWE
{
	char* pdata;
	int pDataLen;
	int dataType;		//0��ͼƬ1Ϊ���ƺ���

	/*���Ƹ�����Ϣ���壺
		���Ƹ�����Ϣ���복����ص�һ����Ϣ�����ַ�����ʽ���ڡ�
		�������������͡��������б�־���������ʱ�䡢���١�������ɫ�ȣ�Ŀǰ�ڶ�����·��ʶ��ϵͳ�У�ʹ�õ��ĳ��Ƹ�����Ϣֻ�г��������־���Ժ󻹻�����������������������Ϣ��
	���Ƹ�����Ϣ��ʽ�淶
		Ϊ��ʹ�ӳ��Ƹ�����Ϣ�ַ����л�ȡ�����ĵ�ֵ����㣬���ַ����ĸ�ʽͳһ���£�
		����Ϣ����:(���ð��)��Ϣֵ\n�����硱����������ʻ:��\n����ע����Ϣ��������Ϣֵ֮��һ���ǰ��ð�ţ����Ҳ����пո񣬸�����Ϣ�������ûس����ֿ����Ա�������һ����Ϣ��*/
	char* pAppinfo;		//������Ϣ

	int appinfolen;		///������Ϣ���ݳ���

	char* pdata_se;		//Ԥ������
	int pdata_se_len;	//Ԥ���������ݳ���
} resultMSG;

typedef struct _CArray//�ؼ���Ϣ�ṹ��
{
	LPUNKNOWN lpunknow;
	TCHAR Name[MAX_PATH];
} DispatchArray;

#ifndef ONE_DEVICE
typedef struct _tagDeviceInfo//�豸��Ϣ�ṹ�壬���ڹ�����豸��
{
	CString m_csIPAddr;//�豸IP
	CString m_csPort;//�豸�˿ں�
	LONG m_lUid;//�豸������
	LONG m_lAlarmHandle;//< �������
	CBufferManager * m_cBufferManager;//< ���ƴ洢
	_tagDeviceInfo()
	{
		m_csPort = _T("");
		m_csIPAddr = _T("");
		m_lUid = -1;
		m_lAlarmHandle = -1;
		m_cBufferManager = new CBufferManager();
		m_cBufferManager->InitBufferManage();
	}
	~_tagDeviceInfo()
	{
		m_cBufferManager->ClearBufferManage();
		delete m_cBufferManager;
		m_cBufferManager = NULL;
	}
}DeviceInfo,*pDeviceInfo;
#endif

#define MSG_REPAINT_RESULT (WM_USER + 113)
#define MSG_CLI_RESULT (WM_USER + 112)

// HVActiveX2Ctrl.h : Declaration of the CHVActiveX2Ctrl ActiveX Control class.


// CHVActiveX2Ctrl : See HVActiveX2Ctrl.cpp for implementation.

class CHVActiveX2Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CHVActiveX2Ctrl)

// Constructor
public:
	CHVActiveX2Ctrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CHVActiveX2Ctrl();

	DECLARE_OLECREATE_EX(CHVActiveX2Ctrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHVActiveX2Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHVActiveX2Ctrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHVActiveX2Ctrl)		// Type name and misc status

// Message maps
	afx_msg LRESULT  OnRecieve(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidLogFile = 25,
		eventidOnReceivePlate = 1L,
		dispidGetImageDataFromMem = 24L,
		dispidGetImageFileName = 23L,
		dispidGetImageRecTime = 22L,
		dispidSavePlateBin2BMP = 21L,
		dispidSavePlateBinImage = 20L,
		dispidSavePlateImage = 19L,
		dispidSaveSnapImage2 = 18L,
		dispidSaveSnapImage = 17L,
		dispidGetPlateInfo = 16L,
		dispidGetPlateColor = 15L,
		dispidGetPlate = 14L,
		dispidSetImgSavePath = 13L,
		dispidDisconnect = 12L,
		dispidGetStatus = 11L,
		dispidConnectTo = 10L,
		dispidShowPlateResult = 9,
		dispidShowSecondImage = 8,
		dispidShowFirstImage = 7,
		dispidShowPlateImage = 6,
		dispidAutoSaveFlag = 5,
		dispidRecvSnapDriverImageFlag = 4,
		dispidRecvPlateBinImageFlag = 3,
		dispidRecvPlateImageFlag = 2,
		dispidRecvSnapImageFlag = 1
	};
protected:
	CArray< DispatchArray > m_ArrayDispatch; //��ȡ�ؼ���Ϣ�������
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////����
	void OnRecvSnapImageFlagChanged(void);
	LONG m_RecvSnapImageFlag;//�Ƿ���ճ�����ͼ���أ�0��ʾ�����ճ���ͼƬ����0��ʾ���ճ���ͼƬ��
	void OnRecvPlateImageFlagChanged(void);
	LONG m_RecvPlateImageFlag;//�Ƿ���ճ���Сͼ���أ�0��ʾ�����ճ���ͼƬ����0��ʾ���ճ���ͼƬ��
	void OnRecvPlateBinImageFlagChanged(void);
	LONG m_RecvPlateBinImageFlag;//�Ƿ���ճ��ƶ�ֵ��ͼ���أ�0��ʾ�����ճ��ƶ�ֵ��ͼƬ����0��ʾ���ճ��ƶ�ֵ��ͼƬ��
	void OnRecvSnapDriverImageFlagChanged(void);
	LONG m_RecvSnapDriverImageFlag;//�Ƿ���ճ���ͼ���أ�0��ʾ�����ճ���ͼƬ����0��ʾ���ճ���ͼƬ��
	void OnAutoSaveFlagChanged(void);
	VARIANT_BOOL m_AutoSaveFlag;//�Ƿ��Զ�����ʶ�������أ�trueΪ�Զ����棬falseΪ���Զ����档
	void OnShowPlateImageChanged(void);
	CString m_ShowPlateImage;//��ʾ����ͼHVSHOW�ؼ��� 
	void OnShowFirstImageChanged(void);
	CString m_ShowFirstImage;//��ʾ������ͼHVSHOW�ؼ��� 
	void OnShowSecondImageChanged(void);
	CString m_ShowSecondImage;//��ʾ����ͼHVSHOW�ؼ���
	void OnShowPlateResultChanged(void);
	CString m_ShowPlateResult;//��ʾ���ƺ���HVSHOW�ؼ���
	//////////////////////////////////////////////////////////////////////////////////�Զ�������
	void OnLogFileChanged(void);
	LONG m_LogFile;//�Ƿ��ӡ��־���ļ��С�
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////���ƽӿں���

	/*���ӵ�����ʶ������strAddrΪ����ʶ������IP��ַ�Ӷ˿ںŻ���IP��ַ��
	���硰192.168.0.18:9999�����ߡ�192.168.0.18�����Ƿ����ӳɹ�����
	ͨ��GetStatus������������ȡ�á�*/
	void ConnectTo(LPCTSTR strAddr);

	/*ȡ�õ�ǰ������״̬��
	���ܵķ���ֵ�������£�
	0��������
	-1���ѶϿ�*/
	LONG GetStatus(void);

	/*�Ͽ���ǰ���ӡ�*/
	void Disconnect(void);

	/*���Զ��洢��Чʱ������ͼ��Ҫ�洢��Ŀ¼���ļ�������Ŀ¼�ɿؼ��Զ����ɡ�
	��Ŀ¼���ļ����������򡰴洢Ŀ¼\\�豸IP\\����\\�ļ����������磺
	����Ŀ¼Ϊ��d:\\image��
	�豸IPΪ��192.16.1.12��
	�Զ�����Ŀ¼Ϊ��d:\\image \\192.16.1.12\\20111025\\��
	ȫ��ͼ�ļ�����165949-031-fullimg.jpg��
	����ͼ�ļ�����165949-031-driver.jpg��
	��ֵ��ͼ�ļ�����165949-031-binimg.bin��
	����ͼ�ļ�����165949-031-plateimg.jpg��*/
	void SetImgSavePath(LPCTSTR strPath);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////��ȡ��Ϣ�ͱ������ӿں���

	/*ȡ�õ�ǰ��⵽�ĳ��ƺ��롣
	��û��ʶ����ʱ������ǡ�δ��⡱*/
	BSTR GetPlate(void);

	/*ȡ�õ�ǰ��⵽�ĳ�����ɫ�����ơ��������������ס������ڡ�����
	��û�м�⵽������ɫʱ������ǿ��ַ���*/
	BSTR GetPlateColor(void);

	/*ȡ�õ�ǰ���Ƶĸ�����Ϣ
	�����١��������ȡ�������ɫ�ȣ�
	Ŀǰ����������ʻ���뱣���ڳ��Ƹ�����Ϣ�У�
	�����ʽ��6����*/
	BSTR GetPlateInfo(void);

	/*���泵��ȫ��ͼ��ָ�����ļ�������0��ʾ�ɹ���*/
	LONG SaveSnapImage(LPCTSTR strFileName);

	/*���泵����ͼ��ָ�����ļ�������0��ʾ�ɹ���*/
	LONG SaveSnapImage2(LPCTSTR strFileName);

	/*���泵��ͼƬ��ָ���ļ�������0��ʾ�ɹ���*/
	LONG SavePlateImage(LPCTSTR strFileName);

	/*���泵�ƶ�ֵ��ͼƬ��ָ���ļ�������0��ʾ�ɹ���*/
	LONG SavePlateBinImage(LPCTSTR strFileName);

	/*�����ֵͼΪBMPͼ������0��ʾ�ɹ���*/
	LONG SavePlateBin2BMP(LPCTSTR strFileName);

	/*���ؽ���ͼ���ʱ�䣬0ȫ��ͼ��1����ͼ��2��ֵ��ͼ��3����ͼ
	ʱ���ʽ������˵����2011-10-25 12:33:32-345���������λ�Ǻ���*/
	BSTR GetImageRecTime(LONG lImgType);

	/*�Զ��洢ʱ����ȡ�ļ�����·�����ļ���
	�磺��D:\image\127.0.0.1\20111026\ 100021-718-fullimg.jpg��*/
	BSTR GetImageFileName(LONG lImgType);

	/*ȡ��������ͼƬ�ڴ����ݣ�����ȫ��ͼ������ͼ��
	��ֵ��ͼ������ͼ��
	lImgTypeΪ0��ʾȫ��ͼ��
	lImgTypeΪ1��ʾ����ͼ��
	lImgTypeΪ2��ʾ��ֵ��ͼ��
	lImgTypeΪ3��ʾ����ͼ
	pVarImgΪ��������
	lImgSize�������ݳ��ȡ�*/
	BSTR GetImageDataFromMem(LONG lImgType, VARIANT* pVarImg, LONG* lImgSize);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�¼�����

	/*ʶ����������Ϣ��
	�ڸ��¼��¿ɵ������½ӿں�����
	����GetPlate()ȡ�ó��ƽ����
	����GetPlateColor()ȡ�ó�����ɫ��
	����GetPlateInfo()ȡ�ó��Ƹ�����Ϣ��
	����SaveSnapImage ()���泵��ȫ����ָ�����ļ���
	����SaveSnapImage2 ()���泵������ͼ��ָ�����ļ���
	����SavePlateImage ()���泵��Сͼ��ָ�����ļ���
	����SavePlateBinImage ()���泵�ƶ�ֵ��ͼ��ָ�����ļ���
	����SavePlateBin2BMP()�����ֵͼΪBMPͼ��
	����GetImageRecTime��ȡͼ�����ʱ��
	����GetImageFileName��ȡ�Զ��洢ʱͼ�����·��
	����GetImageDataFromMem ()ȡ��������ͼƬ�ڴ����ݣ�����ȫ��ͼ������ͼ����ֵ��ͼ������ͼ��*/
	void OnReceivePlate(void)
	{
		FireEvent(eventidOnReceivePlate, EVENT_PARAM(VTS_NONE));
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�ӿ��ĵ��е��Զ��庯��
	bool m_fChangingCtrlName;
	HWND m_hWndParent;
	/*��ؼ���ʾ����
	const char* strControlName = ��showVideoImage��;
	extern char* pbData;
	extern long iLen;
	resultMsg msg;
	msg.pdata = pbData;
	msg.pdataLen = iLen;
	msg.dataType = 0;
	SendData (strControlName, pbData, iLen, 0, &msg);*/
	bool SendData( CString CtrlName, char *pdata, long datalen, long iType, resultMSG *pmsg );

	/*��ȡ����OLE�ؼ�*/
	void EnumAllControlNames();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�豸���豸��ȡ������Ϣ�ڵ�
private:
	NET_DVR_DEVICEINFO_V30 m_stDeviceInfo;				///< �豸��Ϣ
	//NET_INTELCFG_DEVLOGININFO m_stDevLogInfo;				///< �豸��Ϣ
#ifndef ONE_DEVICE
	CRITICAL_SECTION m_csVecLock;
	static std::vector<pDeviceInfo> m_vecDeviceInfoTable;//���豸��������
	CString GetIPAddrByUid(LONG uid);//��ȡ�豸IP
	CString GetPortByUid(LONG uid);//��ȡ�豸�˿�
	LONG GetAlarmHandleByUid(LONG uid);//��ȡ�������
	CBufferManager *GetBufferManagerByUid(LONG uid);//��ȡ��������� 
	pDeviceInfo GetDevicePtrByUid(LONG uid);//��ȡ�豸��Ϣ�ṹ��ָ��
public:
	LONG m_lCurrentUid;//��ʶ��ǰ�����豸Uid
	LONG m_lLoginUid;//��ʶ��ǰ��¼�豸Uid�����ڲ�����
#else
	CString m_csIPAddr;//�豸IP
	CString m_csPort;//�豸�˿ں�
	LONG m_lUid;//�豸������
	LONG m_lAlarmHandle;//< �������
	CBufferManager m_cBufferManager;//< ���ƴ洢
#endif

	ULONG_PTR m_gdiplusToken;		//GDI����
	CString m_csImagePath;//ͼƬ����·��
	char * m_pchPlateBinBMP;//���ƶ�ֵ��תBMPͼƬ
	unsigned int m_iBinBMPSize;//BMPͼƬ��С
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////��־���ܽڵ�
public:
	HANDLE							m_hLogFile;					///< ��־�ļ����
	HANDLE							m_hMutexLogFile;			///< ��־�ļ���
	//д��־�ļ�
	VOID WriteLogFile(LPCTSTR szFun,BOOL bError, LPCTSTR szLog);
	//������־�ļ�
	BOOL CreateLogFile();
	//�����ļ�·��
	BOOL CreateFileDir(LPCTSTR lpPath);
public:
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	BOOL ConvertImgBytes2HBITMAP(BYTE* pImageBuffer,DWORD dwImageDataLen, int iWidth, int iHeight, WCHAR * szFileNae);

	void InsertNewPlate(LPNET_DVR_PLATE_RESULT pPlateInfo);
	LONG SetUpAlarm();
	LONG CleanAlarm();
	BOOL SavePic(LPCTSTR strFileName, BYTE * pImage, DWORD dwPicDataLen);

	int BinImageFormatConvert(BYTE *pByteBinPacked,int iWidth, int iHeight);
	int ConvertBin2BmpData(BYTE *pByteBinPacked,BYTE *pByteBmpData,unsigned int *pnBmpDataLength);

public:
	afx_msg void OnDestroy();

};

