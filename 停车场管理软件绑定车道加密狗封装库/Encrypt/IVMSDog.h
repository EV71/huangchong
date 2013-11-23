#ifndef  __IVMSDOG_H__
#define  __IVMSDOG_H__
#include "HikDog.h"

typedef struct  _tagCUSTOMINFO
{
	BYTE m_nChannels;
	BYTE m_nLanes;
	BOOL m_bConnPlatForm;
	BYTE m_nChannelType;
    
    BYTE m_nChannelsFace;
	BYTE m_nLanesFace;
	BOOL m_bConnPlatFormFace;
	BYTE m_nChannelTypeFace;
    
	BYTE m_nResverd3[4];
}CUSTOMINFO,*PCUSTOMINFO;
class CIVMSDog:public CHikDog
{
#define  MAX_IVMS_INFO_LEN   200
public:
	CIVMSDog();
	~CIVMSDog();

protected:
	//��ȡ���ܹ�--��̬
	virtual HRESULT ReadData( );
	//д���ܹ�--��̬
	virtual HRESULT WriteData( );
	//��BUF�н����Զ�����Ϣ
	virtual HRESULT GetCustomInfo( );
	//���Զ�����Ϣд��BUF
	virtual HRESULT SetCustomInfo( );
	//��ʼ������--��̬
	virtual HRESULT InitAllParam();
private:
	BYTE m_IVMSInfo[ MAX_IVMS_INFO_LEN ];

protected:
	CUSTOMINFO m_CustomInfo;

};


#endif//__IVMSDOG_H__