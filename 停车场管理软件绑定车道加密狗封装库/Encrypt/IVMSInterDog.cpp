#include "IVMSInterDog.h"

CIVMSInterDog::CIVMSInterDog()
{

}
CIVMSInterDog::~CIVMSInterDog()
{

}

HRESULT CIVMSInterDog::GetBindHardWareInfo( BYTE * const pStr,int  nStrLen )
{

	return  S_OK;
}
//�����ܹ��Ƿ���
HRESULT CIVMSInterDog::CheckDogAlive()
{
	return S_OK;
}
HRESULT CIVMSInterDog::GetDogAccess( CUSTOMINFO &nCustomInfo )
{
	memcpy( &nCustomInfo,&m_CustomInfo,sizeof( nCustomInfo ) );
	return S_OK;
}
/****************************************************************************************************
* @��������:	CheckDogBind
* @��  �ܣ�		�������ܹ�����Ϊ
* @��  ����		
* @����ֵ��		S_OK �Ѱ� -2  ��δ��-4 �Ѿ����������� -5 ������ ����--��ȡ���ܹ�����
* @˵  ����		��������ʱ��Ĭ����δ�󶨵ģ��������һ�ε��ô˺�����ʱ�򣬻���ʾ�û��Ƿ�󶨣����ѡ���
				����ܹ���Զ��˵��԰�
****************************************************************************************************/
HRESULT CIVMSInterDog::CheckDogBind( )
{
	HRESULT hr =  CHikDog::CheckDogBind(  );
	if( S_OK == hr )
	{
		///Do Nothing
	}
	else if ( -1 == hr || -3 == hr )
	{
		#ifdef LINUX
				printf("��ȡ������Ϣʧ��");
		#else 
		#ifdef WIN32
				/*MessageBox(NULL,"�޷���ȡ���ܹ�����ȷ���Ƿ���뺣�����ܹ�!",
					"���ܹ���ʾ��Ϣ",MB_OK|MB_ICONWARNING );*/
		#endif
		#endif
	}
	else if ( -2 == hr )
	{
		int nRet = 0;
		#ifdef LINUX
				printf("��ȡ������Ϣʧ��");
		#else 
		#ifdef WIN32
				

				/*nRet= MessageBox(NULL,"�Ƿ�ȷ�ϰ󶨴˼��ܹ�?\nһ���󶨴˵��ԣ��������Խ��޷�ʹ�ô˹�!",
					"���ܹ���ʾ��Ϣ",MB_YESNO|MB_ICONQUESTION );
				if( IDYES == nRet )
				{
					hr = BindDog();
					if( S_OK == hr )
					{
						MessageBox(NULL,"���ܹ��Ѱ󶨱���",
							"���ܹ���ʾ��Ϣ",MB_OK|MB_ICONWARNING);
					}
					else
					{
						MessageBox(NULL,"���ܹ��󶨱���ʧ��",
							"���ܹ���ʾ��Ϣ",MB_OK|MB_ICONWARNING);
					}
				}*/
		#endif
		#endif
	}
	else if ( -4 == hr )
	{
		#ifdef LINUX
				printf("�˹��Ѿ�����ĵ��԰�");
		#else 
		#ifdef WIN32
				/*MessageBox(NULL,"������ʹ�õļ��ܹ��Ѿ����������ԣ������ڴ˻���ʹ��!",
					"���ܹ���ʾ��Ϣ",MB_OK|MB_ICONWARNING);*/
		#endif 
		#endif
	}
	else if ( -5 == hr )
	{
		#ifdef LINUX
				printf("���ܹ��ѹ���");
		#else 
		#ifdef WIN32
				/*MessageBox(NULL,"��Ŀǰʹ�õļ��ܹ��Ѿ����ڣ����뺣����ϵ!",
					"���ܹ���ʾ��Ϣ",MB_OK|MB_ICONWARNING);*/
		#endif
		#endif
	}
	else
	{
		#ifdef LINUX
			printf("�޷�ʶ��ļ��ܹ�");
		#else 
		#ifdef WIN32
				/*MessageBox(NULL,"�޷���ȡ���ܹ�����ȷ���Ƿ���뺣�����ܹ�!",
					"���ܹ���ʾ��Ϣ",MB_OK|MB_ICONWARNING);*/
		#endif
		#endif
	}	
	return hr;
}

