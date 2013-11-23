/***********************************************************************
* 
* ��Ȩ��Ϣ��Copyright (c) 2010, ���ݺ�������������޹�˾
* 
* �ļ����ƣ�jpegdec.h
* �ļ���ʶ��HIKVISION_JPGDEC_LIB_JPEGDEC_H_
* ժ    Ҫ����������JPEG�������ӿ�ͷ�ļ�
*
* ��ǰ�汾��1.1.0
* ��    �ߣ��Ƴ��
* ��    �ڣ�2011��8��29��
* ��    ע�����Ǹߵ������Ƶ�һ���汾������һ�����ļ�ͷ����ӵ�����Ϣ�Ľӿ�
*           ͬʱΪ�˱�����SDK���jpeg����ģ��������ֳ�ͻ����ӿ����ּ���ǰ
*           ׺��HKGDW��
*
* ��ǰ�汾��1.0.2
* ��    �ߣ��ݺ���
* ��    �ڣ�2011��7��7��
* ��    ע��������С����ʵ������������
*
* ��ǰ�汾��1.0.1
* ��    �ߣ��ݺ���
* ��    �ڣ�2010��9��9��
* ��    ע��֧��Basline YUV422 JPEGͼƬ����
*
* ��ǰ�汾��1.0.0
* ��    �ߣ��ݺ���
* ��    �ڣ�2010��8��5��
* ��    ע��֧��Baseline JPEG����
************************************************************************
*/

#ifndef HIK_JPGDEC_LIB_JPEGDEC_H_
#define HIK_JPGDEC_LIB_JPEGDEC_H_

#ifdef __cplusplus
extern "C" {
#endif 


//״̬�붨��
#define HIK_JPGDEC_LIB_S_OK			0x00000001   //�����ɹ�


//�����붨��
#define HIK_JPGDEC_LIB_E_NULL		0x80000001	 //�ڴ����������ָ��

#define HIK_JPGDEC_LIB_E_DQT		0x80000010	 //�����������
#define HIK_JPGDEC_LIB_E_DHT		0x80000011	 //�����huffman���
#define HIK_JPGDEC_LIB_E_LSEJPG		0x80000012	 //��֧��LS-JPEG
#define HIK_JPGDEC_LIB_E_S0F5_15	0x80000013	 //��֧��SOF5~SOF15
#define HIK_JPGDEC_LIB_E_APP        0x80000014	 //APP�ν������
#define HIK_JPGDEC_LIB_E_NOSOS      0x80000015	 //SOS�β�����
#define HIK_JPGDEC_LIB_E_SIZE   	0x80000016	 //ͼ���С����
#define HIK_JPGDEC_LIB_E_BITSP  	0x80000017	 //���ؾ��ȳ���
#define HIK_JPGDEC_LIB_E_SOS    	0x80000018	 //�����SOS
#define HIK_JPGDEC_LIB_E_SOF    	0x80000019	 //�����SOF
#define HIK_JPGDEC_LIB_E_PIXFMT 	0x8000001A	 //��������ظ�ʽ
#define HIK_JPGDEC_LIB_E_PRGJPG		0x8000001B	 //��֧��Progressive DCT
#define HIK_JPGDEC_LIB_E_COM        0x8000001C   //COM��Ϣ����


//���ظ�ʽ����
#define HIK_JPGDEC_PIXFMT_YUV420     1			//YUV 420��ʽ
#define HIK_JPGDEC_PIXFMT_YUV440     2			//
#define HIK_JPGDEC_PIXFMT_YUV422     3			//
#define HIK_JPGDEC_PIXFMT_YUV444     4			//
#define HIK_JPGDEC_PIXFMT_GRAY8      5			//
#define HIK_JPGDEC_PIXFMT_UNKNOWN    0			//δ֪��ʽ


#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
	typedef int HRESULT;
#endif // 



#ifndef _YUV_FRAME_
#define _YUV_FRAME_
	typedef struct
	{
		unsigned char *y;
		unsigned char *u;
		unsigned char *v;

	}YUV_FRAME;
#endif 

//JPEG���������ò���
typedef struct _HKGDW_JPEG_DECODER_PARAMETERS 
{
	unsigned int image_width;		//ͼ����ʾ���
	unsigned int image_height;		//ͼ����ʾ�߶�

	unsigned int   sdram_size;		//��������Ҫ�Ļ����С
	unsigned char *sdram_buffer;    //�����������ַ

}HKGDW_JPEG_DECODER_PARAMETERS;


//JPEGͼƬ��Ϣ
typedef struct _HKGDW_JPEG_IMAGE_INOF 
{
	unsigned int image_width;     //ͼ����
	unsigned int image_height;    //ͼ��߶�
	unsigned int pix_fmt;         //���ظ�ʽ
	unsigned int nb_components;   //��ɫ������Ŀ
	unsigned int progressive_dct; //�Ƿ�֧��ProgressiveDCT

}HKGDW_JPEG_IMAGE_INOF;

//������Ϣ�ṹ��
typedef struct _HKGDW_JPEG_COM_INFO 
{
    int   com_len;		  //������Ϣ���ȣ��ɿ��ڲ����
    int   buffer_size;    //������Ϣ�����С������С�ڵ�����Ϣ���ȣ���������СС����Ϣ���ȣ����ڻ᷵�ش���
    unsigned char *com_buffer;    //���Ի����ַ���˻����ַ�ɿ��ⲿ������ͷ�

}HKGDW_JPEG_COM_INFO;

/******************************************************************************
* ��  �ܣ���ȡJPEGͼ����Ϣ
* ��  ����param - JPEG��������ʼ������	[out]
*		   bits - ���JPEG�����Ļ���	[in]
*          bits_size - ������С			[in]
*         
* ����ֵ���ɹ�����HIK_JPGDEC_LIB_S_OK, ʧ�ܷ��ش�����
* ��  ע��
* ��  ��: 2010/8/9
******************************************************************************/
HRESULT HKGDW_JPGDEC_GetImageInfo(HKGDW_JPEG_IMAGE_INOF *param, unsigned char *bits, unsigned int bits_size);




/******************************************************************************
* ��  �ܣ���ȡJPEG���������軺���С
* ��  ����param - JPEG��������ʼ������	[in]
*         
* ����ֵ���ɹ�����HIK_JPGDEC_LIB_S_OK, ʧ�ܷ��ش�����
* ��  ע��
* ��  ��: 2010/8/9
******************************************************************************/
HRESULT HKGDW_JPGDEC_GetMemSize(HKGDW_JPEG_DECODER_PARAMETERS *param);



/******************************************************************************
* ��  �ܣ�����JPEG������
* ��  ����param  - JPEG��������ʼ������	[in]
*         handle - ָ����������       [out]
*         
* ����ֵ���ɹ�����HIK_JPGDEC_LIB_S_OK, ʧ�ܷ��ش�����
* ��  ע��
* ��  ��: 2010/8/9
******************************************************************************/
HRESULT HKGDW_JPGDEC_Create(HKGDW_JPEG_DECODER_PARAMETERS *param, void **handle);




/******************************************************************************
* ��  �ܣ���һ֡JPEG�������н���
* ��  ���� handle	 - ���������			[in]
*		   bits		 - ���JPEG�����Ļ���	[in]
*          bits_size - ������С			    [in]
*		   frame	 - ָ�������YUV֡����	[out]
*          com_info  - ������Ϣ             [out]
*         
* ����ֵ���ɹ�����HIK_JPGDEC_LIB_S_OK, ʧ�ܷ��ش�����
* ��  ע��������bits�Ļ����СΪ(image_width * image_height * 3 / 2) �����
* ��  ��: 2010/8/9
******************************************************************************/
HRESULT HKGDW_JPGDEC_Decode(void *handle, unsigned char *bits, unsigned int bits_size, YUV_FRAME *outfrm, HKGDW_JPEG_COM_INFO *com_info);




#ifdef __cplusplus
}
#endif

#endif