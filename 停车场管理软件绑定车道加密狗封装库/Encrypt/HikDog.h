#ifndef  __HIKLOG_H__
#define  __HIKLOG_H__

//#include "Log.h"
#include "Codec.h"
#include "Dog.h"
#include "HardWareInfo.h"
#define HIK_COMPANY_NAME "HIK"
//�洢��Ϣ����Ϣͷ
typedef struct tagINFO_HEADER	//4�ֽڶ���
{
	BYTE m_BaseInfoAddr;//������Ϣ��ַ
	BYTE m_BaseInfoLen;//������Ϣ����
	BYTE m_CustomInfoAddr;//�Զ�����Ϣ��ַ
	BYTE m_CustomInfoLen;//�Զ�����Ϣ����
	BYTE m_Resver1[ 4 ];//Ԥ����Ϣ1
}INFO_HEADER;
//�洢�Ļ�����Ϣ����Ϣʵ��
typedef struct tagBASEINFO_BODY
{
	BYTE m_CompanyName[4];//��˾����
	BYTE m_HareWareID[MAX_INFO_LEN];//Ӳ��ID
	BYTE m_bBind;//�Ƿ��
	BYTE m_BindDate[4];//������
	WORD m_UseDays;//ʹ������
	BYTE m_UserGroup;//�û���
	BYTE m_Resver2[4];//Ԥ����Ϣ2
}BASEINFO_BODY;

class  CHikDog:/*public CLog,*/public CCodec,public CDog,CHardWareInfo
{
	public:
		CHikDog();
		~CHikDog();
	public:
		//�󶨼��ܹ�
		virtual HRESULT  BindDog( );
		//������ܹ��Ƿ��Ѿ���
		virtual HRESULT  CheckDogBind( );
	protected:
		//������--��̬
		virtual HRESULT  ReadData( );
		//д����--��̬
		virtual HRESULT  WriteData( );
		//���ú���������Ϣ��Ҫд���buf��
		virtual HRESULT  SetHikInfo( );
		//�Ӷ�ȡ��Ϣ�л�ȡ����������Ϣ
		virtual HRESULT  GetHikInfo( );
		//��������-��̬
		virtual HRESULT  Encrypt();
		//��������--��̬
		virtual HRESULT  Decrypt();
		//ʹ��Ȩ���Ƿ����
		BOOL ISDateOff( BYTE nDate[4] ,WORD nDays );
	protected:
	
		//��ʼ�����в���
		HRESULT InitAllParam();
	protected:
		INFO_HEADER m_InfoHeader;
		BASEINFO_BODY m_InfoBody;
};


#endif//__HIKLOG_H__