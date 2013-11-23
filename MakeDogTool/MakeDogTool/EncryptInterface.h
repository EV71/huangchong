//����:����
//����:2011-08-18
//����:���ܹ������ӿ�ͷ�ļ�
//��Ȩ��Ϣ��CopyRight HIKVISION 
#ifndef ___ENCRYPT_INTERFACE_H__
#define ___ENCRYPT_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LINUX
	
#else
	#include <Windows.h>
#endif
//////////////////////////////////////////////////////////////////////////
//�������Ͷ���
//////////////////////////////////////////////////////////////////////////

#ifdef LINUX
	#ifndef NULL
	#define  NULL 0
	#endif 

	#ifndef S_OK  
	#define S_OK  1
	#endif 

	#ifndef S_FALSE  
	#define S_FALSE   0
	#endif 

	#ifndef TRUE  
	#define TRUE   1
	#endif 

	#ifndef FALSE  
	#define FALSE   0
	#endif 

	#ifndef BYTE
		typedef unsigned char BYTE;
	#endif 

	#ifndef  WORD
		typedef  unsigned short WORD;
	#endif

	#ifndef DWORD
		typedef unsigned long DWORD;
	#endif 

	#ifndef HRESULT
		typedef int  HRESULT;
	#endif

	#ifndef BOOL
		typedef unsigned char BOOL;
	#endif

	#ifndef UINT
		typedef unsigned int UINT;
	#endif 

	#ifndef USHORT
		typedef unsigned short  USHORT;
	#endif 

	#ifndef TCHAR 
		typedef char TCHAR, *PTCHAR;
	#endif
#endif




//�û���
enum  USER_GROUP
{
	USERGROUP_ADMIN,//��������Ա��
	USERGROUP_CUSTOMER,	//��ͨ�û���
	USERGROUP_DEVELOP	//������Ա��
};
//��Ʒ��
enum PRODUCT_GROUP
{
	PRODUCTGROUP_VIMS,//��Ƶ�羯��Ʒ
	PRODUCTGROUP_PARK//ͣ������Ʒ
};
//������Ƶ�羯ͼƬ�ͳ�������Ϣ��ƽ̨
enum  PLATFORM_TYPE
{
	PLATEFORM_NONE,//������ƽ̨
	PLATEFORM_8620//8620ƽ̨
};
//�������
#define  CODEC_ERR	1000
#define  DOG_ERR	2000
enum  ERROR_CODE
{
	CODEC_INITKEY_ERROR_BUF_NULL = CODEC_ERR,//CCodec::InitializeKey������Ϊ��
	CODEC_INITKEY_ERROR_BUF_OUT,//CCodec::InitializeKey���������
	CODEC_CRYPT_EROR_BUF_NULL,// CCodec::SetCryptData������Ϊ��
	CODEC_CRYPT_ERROR_BUF_OUT,// CCodec::SetCryptData���������
	CODEC_GETCRYPTDATA_ERROR_1		,//CCodec::GetCryptData
	CODEC_ENCRYPT_ERROR_1,//CCodec::Encrypt
	CODEC_DENCRYPT_ERROR_1//CCodec::DEcrypt
};

enum CRYPT_STATE
{
	STATE_ENCRYPT,//����״̬
	STATE_DECRYPT,//����״̬
	STATE_UNINIT//δ��ʼ��״̬

};
enum DOG_STATE
{

	STATE_BIND = 2, //�����ڰ�״̬
	STATE_NOT_BIND=3//������δ��״̬

};
//////////////////////////////////////////////////////////////////////////
//����DLL�����ö���
//////////////////////////////////////////////////////////////////////////

#ifndef ENCRYPT_API
	#ifdef  ENCRYPT_EXPORTS
		#define ENCRYPT_API __declspec(dllexport)
	#else
		#define ENCRYPT_API __declspec(dllimport)
	#endif
#endif

//////////////////////////////////////////////////////////////////////////
//�����ӿڶ���
//////////////////////////////////////////////////////////////////////////



/****************************************************************************************************
* @��������:MakePRDog
* @��  �ܣ��������ܹ�
* @��  ����
* @wDays		ӵ�е�ʹ������6
* @nChannels	�����õ����ͨ����   
* @nLanes		�����õ���󳵵���
* @nPlatForm   	����ƽ̨  ������  TRUE �� FALSE ��
* @nChannelType	ͨ������	
* @pResverd		Ԥ���ֶ�
* @����ֵ��		S_OK �������ܹ��ɹ�  S_FALSE �������ܹ�ʧ��
* @˵  ����		�˺������MicroDog���в���,�������Ĺ�������ȷ�Ϲ��Ѿ�������������װ�˶�Ӧ������
****************************************************************************************************/
ENCRYPT_API	HRESULT _cdecl MakePRDog(	 WORD wDays,
							   BYTE nChannels,
							   BYTE nLanes,
							   BYTE nPlatForm,
							   BYTE nChannelType );
/****************************************************************************************************
* @��������:MakeFRDog
* @��  �ܣ��������ܹ�
* @��  ����
* @wDays		ӵ�е�ʹ������6
* @nChannels	�����õ����ͨ����   
* @nLanes		�����õ���󳵵���
* @nPlatForm   	����ƽ̨  ������  TRUE �� FALSE ��
* @nChannelType	ͨ������	
* @pResverd		Ԥ���ֶ�
* @����ֵ��		S_OK �������ܹ��ɹ�  S_FALSE �������ܹ�ʧ��
* @˵  ����		�˺������MicroDog���в���,�������Ĺ�������ȷ�Ϲ��Ѿ�������������װ�˶�Ӧ������
****************************************************************************************************/
ENCRYPT_API	HRESULT _cdecl MakeFRDog(	 WORD wDays,
							   BYTE nChannels,
							   BYTE nLanes,
							   BYTE nPlatForm,
							   BYTE nChannelType );

ENCRYPT_API HRESULT _cdecl MakeDog(	BYTE nChannelsPlate,
					   BYTE nChannelsFace,
					   BYTE nPlatForm);
/****************************************************************************************************
* @��������:	CheckDogBind
* @��  �ܣ�		�жϼ��ܹ��Ƿ��Ѿ���
* @��  ����		��
* @����ֵ��		S_OK �Ѿ���  S_FALSE δ�� 
* @˵  ����		���ô˺������Զ�ȡ���ܹ��İ���Ϣ���жϴ˹��Ƿ��Ѿ��ͱ��Ӳ����
				����Ѿ��󶨣�����ͨ������ GetBindHardWareInfo����ȡ�󶨵�Ӳ����Ϣ

****************************************************************************************************/
ENCRYPT_API HRESULT _cdecl CheckDogBind( void );


/****************************************************************************************************
* @��������:	StatusValidate
* @��  �ܣ�		�жϼ��ܹ��Ƿ����
* @��  ����		��
* @����ֵ��		0 ����  1 ������ 
* @˵  ����		�жϹ��Ƿ���ڣ�0Ϊ���ڲ��Ѿ��󶨣�1Ϊ�����ڻ���û��
****************************************************************************************************/
ENCRYPT_API HRESULT _cdecl StatusValidate( void );




/****************************************************************************************************
* @��������:	GetBindHardWareInfo
* @��  �ܣ�		��ȡ�󶨵�Ӳ����Ϣ���Է�ֹ�û��ڻ������ܹ���������޷�ʶ����ܹ��İ󶨶���
* @��  ����		
* @pStr			�������������Ӳ��ID
* @nStrLen      ��ǿ�д�����Ϣ����󳤶�
* @����ֵ��		S_OK ��ȡ�ɹ�  S_FALSE ��ȡʶ�� 
* @˵  ����		������ܹ�δ�󶨣���᷵��ʧ�ܣ�������ܹ��Ѿ��󶨣���������»���pStr����Ӳ��ID��
****************************************************************************************************/
ENCRYPT_API HRESULT _cdecl GetBindHardWareInfo( BYTE * const pStr,int  nStrLen );

/****************************************************************************************************
* @��������:GetDogPRAccess
* @��  �ܣ�		��ȡ���ܹ��еĳ���ʶ����Ϣ
* @��  ���� 
* @nPRChannels   	��������õ����ͨ����
* @nPRLanes		��������õ���󳵵���
* @bPRConnPlatForm����Ƿ������ƽ̨ TRUE �� FALSE ��
* @nPRChannelType	���ͨ������
* @bPRFlag	          �����ʶ���Ƿ����� 1����������0��δ����
* @����ֵ��		S_OK ��ȡ��Ϣ�ɹ�  S_FALSE ��ȡ��Ϣʧ��
* @˵  ����		��ȡ���ܹ��󶨵�Ȩ����Ϣ
****************************************************************************************************/
ENCRYPT_API HRESULT _cdecl GetDogPRAccess( 
	BYTE &nPRChannels,
	BYTE &nPRLanes,
	BOOL &bPRConnPlatForm,
	BYTE &nPRChannelType,
	BOOL &bPRFlag);


/****************************************************************************************************
* @��������:GetDogFRAccess
* @��  �ܣ�		��ȡ���ܹ�������ʶ����Ϣ
* @��  ���� 
* @nFRChannels   	��������õ����ͨ����
* @nFRLanes		��������õ���󳵵���
* @bFRConnPlatForm����Ƿ������ƽ̨ TRUE �� FALSE ��
* @nFRChannelType	���ͨ������
* @bFRFlag	          �������ʶ���Ƿ����� 1����������0��δ����
* @����ֵ��		S_OK ��ȡ��Ϣ�ɹ�  S_FALSE ��ȡ��Ϣʧ��
* @˵  ����		��ȡ���ܹ��󶨵�Ȩ����Ϣ
****************************************************************************************************/
ENCRYPT_API HRESULT _cdecl GetDogFRAccess( 
	BYTE &nFRChannels,
	BYTE &nFRLanes,
	BOOL &bFRConnPlatForm,
	BYTE &nFRChannelType,
	BOOL &bFRFlag);

/****************************************************************************************************
* @��������:GetDogAccess
* @��  �ܣ�		��ȡ���ܹ��е�Ȩ��
* @��  ���� 
* @nUserGroup	����û�����   
* @nUseDate		���ӵ�е�ʹ������
* @nChannels   	��������õ����ͨ����
* @nLanes		��������õ���󳵵���
* @bConnPlatForm����Ƿ������ƽ̨ TRUE �� FALSE ��
* @nChannelType	���ͨ������
* @pResverd		���Ԥ���ֶ�
* @����ֵ��		S_OK ��ȡ��Ϣ�ɹ�  S_FALSE ��ȡ��Ϣʧ��
* @˵  ����		��ȡ���ܹ��󶨵�Ȩ����Ϣ
****************************************************************************************************/
ENCRYPT_API HRESULT _cdecl GetDogAccess(BYTE &nChannelsPlate,
							BYTE &nChannelsFace,
							BYTE &nPlatForm,
							BOOL &bFRFlag);

#ifdef __cplusplus
}
#endif

#endif //___ENCRYPT_INTERFACE_H__