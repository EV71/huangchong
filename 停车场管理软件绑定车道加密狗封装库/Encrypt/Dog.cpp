#include "Dog.h"

short int DogAddr,DogBytes;
unsigned long DogPassword, NewPassword,DogResult;
unsigned char DogCascade;
void * DogData;

CDog::CDog()
{
	memset( m_pMemoryBuf,0,sizeof( m_pMemoryBuf ) );
	m_BufLen = 0;
}
CDog::~CDog()
{

}
/****************************************************************************************************
* @��������:	WriteData
* @��  �ܣ�		�����ܹ�д����
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		�����ܹ�ǰ128�ڴ�д����
****************************************************************************************************/
HRESULT CDog::WriteData()
{	
	DogPassword = 0;
	DogBytes = MAX_PRIVATE_MEMORY_LEN;
	DogData = &m_pMemoryBuf[0];
	DogAddr = 0x00;
	m_BufLen = DogBytes;
	//�����ݽ��к�У�鱣֤�䲻���Ķ�
	if( S_OK != SetSum() )
	{
		//WriteLog( "д���ܹ�-У���ʧ��\r\n" );
		return S_FALSE;
	}
	//д����
	if( 0 != WriteDog() )
	{
		//WriteLog( "д���ܹ�-д��ʧ��\r\n" );
		return S_FALSE;
	}
	return S_OK;
}
/****************************************************************************************************
* @��������:	ReadData
* @��  �ܣ�		�Ӽ��ܹ��ж�ȡ���� ��ȡ��Ҫ�� MAX_PRIVATE_MEMORY_LEN ���ȵ����ݷ��뻺����
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		��ȡ����������ͨ�༭��--ǰ128�ֽ�
****************************************************************************************************/
HRESULT CDog::ReadData()
{
	DogAddr = 0;
	DogBytes = MAX_PRIVATE_MEMORY_LEN;
	DogData = &m_pMemoryBuf[0];
	//��ȡ����
	if( 0 != ReadDog() )
	{	
		//WriteLog( "��ȡ���ܹ�-��ȡʧ��\r\n" );
		return -1;
	}
	m_BufLen = DogBytes;
	//��У�� ��֤���ݲ��Ǻ���д��ȥ��
	/*if( S_OK != CheckSum() )
	{
		WriteLog( "��ȡ���ܹ�-У���ʧ��\r\n" );
		return -2;
	}*/

	return S_OK;
}
/****************************************************************************************************
* @��������:	CheckSum
* @��  �ܣ�		��һԪ������к�У��
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		ҪУ���֮ǰ��Ҫ��m_pMemoryBuf���и�ֵ��Ҳ����˵��Ҫ�ɹ����� ReadData 
				��buf�е�ָ����Ϣ���к�У�� --ǰ128���ֽ�
****************************************************************************************************/
HRESULT CDog::CheckSum( )
{
	BYTE nSum = 0;
	if( 0 >= m_BufLen || MAX_PRIVATE_MEMORY_LEN <m_BufLen )
	{
		return -1;
	}

	for( int i=0;i<m_BufLen-2;i++ )
	{
		nSum += m_pMemoryBuf[ i ];
	}

	if( nSum != m_pMemoryBuf[ m_BufLen-1] )
	{
		return -2;
	}
	return S_OK;
}
/****************************************************************************************************
* @��������:	SetSum
* @��  �ܣ�		��һԪ�������ú�У��
* @��  ����		��
* @����ֵ��		S_OK �����ɹ�,���� ���ض�Ӧ�Ĵ������
* @˵  ����		��buf�е�ָ����Ϣ --ǰ128���ֽ�����У���
****************************************************************************************************/
HRESULT CDog::SetSum( )
{
	BYTE nSum = 0;
	if( 0 >= m_BufLen || MAX_PRIVATE_MEMORY_LEN <m_BufLen )
	{
		return S_FALSE;
	}

	for( int i=0;i<m_BufLen-2;i++ )
	{
		nSum += m_pMemoryBuf[ i ];
	}
	 m_pMemoryBuf[ m_BufLen-1] = nSum;
	return S_OK;
}