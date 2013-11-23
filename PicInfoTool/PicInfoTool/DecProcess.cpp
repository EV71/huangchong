#include "stdafx.h"
#include "DecProcess.h"
//������ʽˮӡ������Ϊ0x80
unsigned char g_hik_watermark[1000] = {0x48, 0x57, 0x4d, 0x49, 0x80, 0x00, 0x60, 0x60, 0x60, 0x60, 0x99, 0x00, 0x00, 0x00, 0x60, 0x61,
															0x61, 0x61, 0x61, 0x61, 0x9a, 0x9b, 0x9c, 0x61, 0x61, 0x61, 0x62, 0x62, 0x61, 0x62, 0x61, 0x62,
															0x65, 0x65, 0x61, 0x65, 0x62, 0x62, 0x65, 0x62, 0x61, 0x65, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
															0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x62, 0x62, 0x61,
															0x62, 0x61, 0x62, 0x65, 0x65, 0x61 };


//////////////////////////////////////////////////////////////////
//����BMPλͼ�ļ�ͷ  
void ContructBhh(int nWidth,int nHeight,BITMAPFILEHEADER& bhh) //add 2010-9-04  
{  
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8 ; //ÿ��ʵ��ռ�õĴ�С��ÿ�ж�����䵽һ��4�ֽڱ߽磩  
	bhh.bfType = ((WORD) ('M' << 8) | 'B');  //'BM'  
	bhh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + widthStep * nHeight;  
	bhh.bfReserved1 = 0;  
	bhh.bfReserved2 = 0;  
	bhh.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);  

}  


//����BMP�ļ���Ϣͷ  
void ConstructBih(int nWidth,int nHeight,BITMAPINFOHEADER& bih)   
{  
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8 ;   

	bih.biSize=40;       // header size  
	bih.biWidth=nWidth;  
	bih.biHeight=nHeight;  
	bih.biPlanes=1;  
	bih.biBitCount=24;     // RGB encoded, 24 bit  
	bih.biCompression=BI_RGB;   // no compression ��ѹ��  
	bih.biSizeImage=widthStep*nHeight*3;  
	bih.biXPelsPerMeter=0;  
	bih.biYPelsPerMeter=0;  
	bih.biClrUsed=0;  
	bih.biClrImportant=0;   

}  

BOOL SaveDIB2Bmp(int fileNum, const char * fileName, const char * filePath, int iWidth, int iHeight, BYTE *pBuffer)  
{  

	BITMAPINFOHEADER bih;  
	ConstructBih(iWidth,iHeight,bih);  
	BITMAPFILEHEADER bhh;  
	ContructBhh(iWidth,iHeight,bhh);  

	TCHAR BMPFileName[1024];  
	int widthStep = (((iWidth * 24) + 31) & (~31)) / 8 ; //ÿ��ʵ��ռ�õĴ�С��ÿ�ж�����䵽һ��4�ֽڱ߽磩  
	int DIBSize = widthStep * iHeight ;  //buffer�Ĵ�С ���ֽ�Ϊ��λ��  

	//save  
	char path[1024];  
	char str[1024];  

	sprintf_s(str,"%d",fileNum);    
	strcat_s(str, fileName);  
	strcat_s(str,".bmp");  //frame100.bmp  
	sprintf_s(path,"%s", filePath);  
	strcat_s(path,str); //Path//frame100.bmp  

	strcpy_s(BMPFileName,sizeof(BMPFileName),path);  
	CFile file;  
	try  
	{  
		if(file.Open(BMPFileName,CFile::modeWrite | CFile::modeCreate))  
		{//д���ļ�  

			file.Write((LPSTR)&bhh,sizeof(BITMAPFILEHEADER));  
			file.Write((LPSTR)&bih,sizeof(BITMAPINFOHEADER));  
			file.Write(pBuffer,DIBSize);  
			file.Close();  
			return true;  
		}  

	}  
	catch (...)   
	{  
		AfxMessageBox("MyDC::SaveDIB2Bmp");  
	}  
	return false;  
}  
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//��������YUV2RGB411
//���룺
//		YUV:yuv411����
//		YUVsize:��С
//		width:ͼ���
//		length:ͼ���
//�����
//		RGB:RGBdata
//////////////////////////////////////////////////////////////////
BOOL YUV2RGB(unsigned char* YUV,int YUVsize,int width,int length,unsigned char* RGB,int RGBsize)
{
	if(YUVsize < width * length *3 || RGBsize < width * length *3)
	{
		return FALSE;
	}
	unsigned char * pRGB = RGB;
	unsigned char * pYUV = YUV;
	unsigned char y;
	unsigned char u;
	unsigned char v;
	for(int i = 0;i<width;i++)
	{
		for (int j = 0;j<length;j++)
		{
			y = pYUV[i*length+j];
			u = pYUV[length*width + (int)((i*length+j)/4)];
			v = pYUV[length*width*5/4 + (int)((i*length+j)/4)];

			pRGB[i*length*3+j*3] = max(0,min(255,(unsigned char)(y + 1.357*v-1.357*128)));
			pRGB[i*length*3+j*3+1] = max(0,min(255,(unsigned char)(y + 0.34375*128 + 0.703125*128 - 0.34375*u - 0.703125*v)));
			pRGB[i*length*3+j*3+2] = max(0,min(255,(unsigned char)(y + 1.734375*u-1.734375*128)));
		}
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
void UV12ToYYuv(BYTE *uv_src, BYTE *uv_dest, int width, int height)
{
	int i, j;
	BYTE *s[2];
	BYTE *uv_dest_last;
	int nHalfWidth = width/2;
	s[0] = uv_src; // U
	s[1] = s[0] + width*height/4; // V
	for (i = 0; i < height; i++) 
	{
		if (i % 2 == 0 )
		{
			uv_dest_last = uv_dest;
			for (j = 0; j < nHalfWidth; j++) 
			{
				uv_dest[0] = s[1][j];
				uv_dest[1] = s[0][j];
				uv_dest += 2;
			}
		}
		else
		{
			memcpy(uv_dest, uv_dest_last, width);
			uv_dest += width;
			s[0] += nHalfWidth;
			s[1] += nHalfWidth;
		}
	}
}

#ifndef LIMITE_VAL_TH
#define LIMITE_VAL_TH(val, maxval, minval) \
	if(val > maxval)                    \
{                                   \
	val = maxval;                   \
}                                   \
else if(val < minval)               \
{                                   \
	val = minval;                   \
}
#endif

#define YUV2RGB(y, u, v, r, g, b)               \
	r = ( 298*(y-16) + 409*(v-128) +128) >> 8;  \
	g = ( 298*(y-16) - 100*(v-128) - 208*(u-128) + 128 ) >> 8;\
	b = ( 298*(y-16) + 516*(u-128) +128) >> 8;  \
	LIMITE_VAL_TH(r, 255, 0);                       \
	LIMITE_VAL_TH(g, 255, 0);                       \
	LIMITE_VAL_TH(b, 255, 0);

BOOL YYUVToRgb24 (BYTE *yuv_src,int yuvsize, int width, int height,BYTE *dest,int destsize)
{
	if(yuvsize < width * height *3 || destsize < width * height *3)
	{
		return FALSE;
	}
	BYTE *yy_src;
	BYTE *uv_src;
	yy_src = yuv_src;
	uv_src = yuv_src+width*height;
	int i,j;
	int y0, y1, u, v;
	int r, g, b;
	BYTE *s[2];
	s[0] = yy_src;      // Y
	s[1] = uv_src;      // UV
	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width; j+=2) 
		{
			y0 = s[0][j];
			y1 = s[0][j+1];
			u = s[1][j];
			v = s[1][j+1];
			YUV2RGB (y0, u, v, r, g, b);
			*dest++ = r;    // ͼ��ʵ��ΪBGRģʽ
			*dest++ = g;
			*dest++ = b;
			YUV2RGB (y1, u, v, r, g, b);
			*dest++ = r;    // ͼ��ʵ��ΪBGRģʽ
			*dest++ = g;
			*dest++ = b;
		}
		s[0] += width;
		s[1] += width;
	}
	return TRUE;
}
//420תRGB
void YUV2RGB_FLOAT(unsigned char *yuv_buffer, unsigned char *rgb_buffer, int width, int height)
{
	unsigned char *u_buffer,*v_buffer;
	float u1,uv1,v1;
	float u,v;
	int len;
	int r,g,b;
	int x,y;
	int rgb_ptr,y_ptr;

	len=width*height;

	u_buffer=yuv_buffer+len;
	len=len/4;
	v_buffer=u_buffer+len;

	rgb_ptr=0;
	y_ptr=0;

	for(y=0; y<height; y++)
		for(x=0; x<width; x++)
		{
			u=u_buffer[(int)(x/2) + (int)(y/2)*(int)(width/2)]-128;
			v=v_buffer[(int)(x/2) + (int)(y/2)*(int)(width/2)]-128;

			v1=(1.13983*(float)v);
			uv1=-(0.39466*(float)u)-(0.58060*(float)v);
			u1=(2.03211*(float)u);

			r=yuv_buffer[y_ptr] + v1;
			g=yuv_buffer[y_ptr] + uv1;
			b=yuv_buffer[y_ptr] + u1;

			if (r>255) r=255;
			if (g>255) g=255;
			if (b>255) b=255;

			if (r<0) r=0;
			if (g<0) g=0;
			if (b<0) b=0;

			rgb_buffer[rgb_ptr]=b;
			rgb_buffer[rgb_ptr+1]=g;
			rgb_buffer[rgb_ptr+2]=r;


			y_ptr++;
			rgb_ptr+=3;
		}
}
////////////////////////////////////////////////////////////////////////////////
DecProcess::DecProcess()
{
	m_PicFile = NULL;
	m_FileStreamBuf = new unsigned char[FILE_BUFF];
	m_YUVStream = new unsigned char[FILE_BUFF];
	//m_YUVStream422 = new unsigned char[FILE_BUFF];
	m_ComInfo.com_buffer = new unsigned char[COM_BUFF];
	m_RGBStream = new unsigned char[RGB_BUFF];
	m_ComInfo.buffer_size = COM_BUFF;
}

DecProcess::~DecProcess()
{
	if(m_PicFile)
	{
		fclose(m_PicFile);
		m_PicFile = NULL;
	}
	if(m_FileStreamBuf)
	{
		delete [] m_FileStreamBuf;
		m_FileStreamBuf = NULL;
	}
	if(m_YUVStream)
	{
		delete [] m_YUVStream;
		m_YUVStream = NULL;
	}
	//if(m_YUVStream422)
	//{
	//	delete [] m_YUVStream422;
	//	m_YUVStream422 = NULL;
	//}
	if(m_ComInfo.com_buffer)
	{
		delete [] m_ComInfo.com_buffer;
		m_ComInfo.com_buffer = NULL;
	}
	if(m_RGBStream)
	{
		delete [] m_RGBStream;
		m_RGBStream = NULL;
	}
}

/************************************************************************/
/* ��ͼƬ                                                                     */
/************************************************************************/
BOOL DecProcess::OpenProcessFile()
{
	if(m_PicFile)
	{
		fclose(m_PicFile);
		m_PicFile = NULL;
	}
	CFileDialog filedialog( TRUE, 
									NULL, 
									NULL, 
									OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
									"JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||");
	if(IDOK == filedialog.DoModal())
	{
		m_FilePathName = filedialog.GetPathName();
		fopen_s(&m_PicFile,m_FilePathName.GetBuffer(0),"ab+");
		if(NULL == m_PicFile)
		{
			MessageBox(NULL,"�ļ���ʧ�ܣ�","����",MB_OK);
		}
		if(GetFileCommentInfo())
		{
			fclose(m_PicFile);
			return TRUE;
		}
		else
		{
			fclose(m_PicFile);
			return FALSE;
		}
	}
	return FALSE;
}
/*****************************************************************
������: SaveProcessFile
����: д��ͼƬ��Ϣ
����: ��
����ֵ:BOOL��true�ɹ���falseʧ��
��ע:
******************************************************************/
BOOL DecProcess::SaveProcessFile()
{
	HKGDW_JPGENC_PARAM enc_param;
	HKGDW_JPGENC_IMAGE_PARAM image;
	YUV_FRAME frame;
	void* handle;
	int size = m_JPGInfo.image_height*m_JPGInfo.image_width*3/2;
	int ret;
	enc_param.width     = m_JPGInfo.image_width;
	enc_param.height    = m_JPGInfo.image_height;
	enc_param.quality   = QUALITY;
	enc_param.insert_watermarker = 1;
	if(HKGDW_JPGENC_GetMemSize(&enc_param) != HIK_JPGENC_LIB_S_OK)
	{  
		MessageBox(NULL,"Error: JPGENC_GetMemSize ERROR.","����",MB_OK);
		return FALSE;
	}

	if((enc_param.sdram_buf = malloc(enc_param.sdram_buf_size)) == NULL)
	{
		MessageBox(NULL,"Error: sdram_buf malloc failed.","����",MB_OK);
		return FALSE;
	}
	HKGDW_JPGENC_Create(&enc_param, &handle);
	////////////////////////////////////////////////////////////////////////
	frame.y = m_YUVStream;
	frame.u = m_YUVStream + m_JPGInfo.image_height*m_JPGInfo.image_width;
	frame.v = m_YUVStream + m_JPGInfo.image_height*m_JPGInfo.image_width*5/4;

	image.frame  = &frame;
	image.width  = m_JPGInfo.image_width;
	image.height = m_JPGInfo.image_height;
	image.size   = size;

	//HIK�����ˮӡ��ʽΪ�� ��0~4 byteΪˮӡ��ʼ�룬һ��Ϊ0x494d5748���������壩��0x494d5755���û����壩
	//                      ��5~6 byteΪˮӡ����
	image.watermarker_data = g_hik_watermark;
	image.watermarker_len  = *(unsigned short*)(&g_hik_watermark[4]);
	
	int sizeJD_INFO = sizeof(JD_INFO);
	for(int i=0;i<sizeJD_INFO;i++)
	{
		m_ComInfo.com_buffer[i] = ((unsigned char *)(&m_JD_INFO))[i];
	}

	image.comment_data = m_ComInfo.com_buffer;
	image.comment_len = m_ComInfo.com_len < 0 ? 0 : m_ComInfo.com_len;

	if((image.bitstream = (unsigned char*)malloc(size)) == NULL)
	{
		MessageBox(NULL,"Error: bitstream malloc failed.","����",MB_OK);
		free(enc_param.sdram_buf);
		enc_param.sdram_buf = NULL;
		return FALSE;
	}
	HKGDW_JPGENC_SetQuality(handle, QUALITY);

	ret = HKGDW_JPGENC_Compress(handle, &image);
	if(ret != HIK_JPGENC_LIB_S_OK)
	{
		MessageBox(NULL,"Error: jpeg_compress_data failed.","����",MB_OK);
		free(image.bitstream);
		image.bitstream = NULL;
		free(enc_param.sdram_buf);
		enc_param.sdram_buf = NULL;
		return FALSE;
	}

	//����RGBͼ�񣬿�RGBЧ����������
	//{
	//	SaveDIB2Bmp(1, "TempRGB", "C:\\",m_JPGInfo.image_width , m_JPGInfo.image_height, m_RGBStream);  
	//}

	//fseek(m_PicFile,0,SEEK_SET);
	FILE *outfile;
	fopen_s(&outfile,m_FilePathName,"wb");
	
	if(!fwrite(image.bitstream, image.length, 1, outfile))
	{
		MessageBox(NULL,"Error:output stream file failed.","����",MB_OK);
		free(image.bitstream);
		image.bitstream = NULL;
		free(enc_param.sdram_buf);
		enc_param.sdram_buf = NULL;
		return FALSE;
	}
	fclose(outfile);
	free(image.bitstream);
	image.bitstream = NULL;
	free(enc_param.sdram_buf);
	enc_param.sdram_buf = NULL;

	return TRUE;
}

/************************************************************************/
/* ��ȡͼƬ��Ϣ.�����߱�ʶ��ʾ��ͼƬ��	                                                                        */
/************************************************************************/
/*****************************************************************
������: GetFileCommentInfo
����: ��ȡͼƬ��Ϣ������ȡRGB������
����: ��
����ֵ:BOOL��true�ɹ���falseʧ��
��ע:
******************************************************************/
BOOL DecProcess::GetFileCommentInfo()
{
	try
	{
		memset(m_FileStreamBuf,0,FILE_BUFF);
		memset(m_YUVStream,0,FILE_BUFF);
		memset(m_ComInfo.com_buffer,0,COM_BUFF);
		fseek(m_PicFile,0,SEEK_END);
		m_JPGFileSize = ftell(m_PicFile);
		fseek(m_PicFile,0,SEEK_SET);
		fread(m_FileStreamBuf,m_JPGFileSize,1,m_PicFile);
		if(HKGDW_JPGDEC_GetImageInfo(&m_JPGInfo, m_FileStreamBuf, m_JPGFileSize) < 0) //��ȡjpegͼƬ��Ϣ
		{
			MessageBox(NULL,"Error: could not get image info.","����",MB_OK);
			return FALSE;
		}

		int dec_result = 0;
		HKGDW_JPEG_DECODER_PARAMETERS decparam, *dec = &decparam;
		void *handle;
		YUV_FRAME outframe;

		int imageWidth;//����ͼƬ�Ŀ��
		int imageHeight;//����ͼƬ�ĸ߶�

		//����ͼƬ��YUVֵ
		outframe.y = m_YUVStream;
		outframe.u = outframe.y + m_JPGInfo.image_height * m_JPGInfo.image_width;
		outframe.v = outframe.u + m_JPGInfo.image_height * m_JPGInfo.image_width / 4;

		dec->image_height = m_JPGInfo.image_height;
		dec->image_width  = m_JPGInfo.image_width;

		imageHeight = m_JPGInfo.image_height;
		imageWidth = m_JPGInfo.image_width;
		//��ȡJPEG���������軺���С
		HKGDW_JPGDEC_GetMemSize(dec);
		if((dec->sdram_buffer = new unsigned char[dec->sdram_size]) == NULL)
		{
			MessageBox(NULL,"Error: malloc decoder buffer failed.","����",MB_OK);
			return FALSE;
		}

		//����JPEG������
		HKGDW_JPGDEC_Create(dec, &handle); 

		dec_result = HKGDW_JPGDEC_Decode(handle,m_FileStreamBuf,m_JPGFileSize,&outframe,&m_ComInfo);

		if(dec_result <= 0)
		{
			MessageBox(NULL,"Error:Decode Faild.","����",MB_OK);
			delete [] dec->sdram_buffer;
			dec->sdram_buffer =NULL;
			return FALSE;
		}

		if(m_ComInfo.com_len>0)
		{
			memset((void *)&m_JD_INFO,0,sizeof(m_JD_INFO));//
			//int a  = sizeof(m_JD_INFO);// = 5568;
			memcpy_s((void *)&m_JD_INFO,sizeof(m_JD_INFO),m_ComInfo.com_buffer,m_ComInfo.com_len);
		}
		else
		{
			MessageBox(NULL,"No Comment Infomation.","��ʾ",MB_OK);
			delete [] dec->sdram_buffer;
			dec->sdram_buffer =NULL;
			return FALSE;
		}
	 
		//420ת��ΪRGB
		YUV2RGB_FLOAT(m_YUVStream,m_RGBStream,m_JPGInfo.image_width,m_JPGInfo.image_height);
		//�����Ϣ��ͼ��ʾ
		//ͼƬ��ʽΪ���ϳɣ����������ŵ羯ͼ���
		if(m_JD_INFO.m_SnapInfo.m_MergMode == 1)
		{
			//��ʼ����Ϣ��ͼ�����ƾ�������
			for( int i =0; i<m_JD_INFO.m_ParamInit.m_LightNum;i++)
			{
				memset((void *)&m_JD_INFO,0,sizeof(m_JD_INFO));//
				int a  = sizeof(m_JD_INFO);// = 5568;
				memcpy_s((void *)&m_JD_INFO,sizeof(m_JD_INFO),m_ComInfo.com_buffer,m_ComInfo.com_len);
			}
			//ʵʱ��Ϣ��ͼ������λ����ʾ��
			for(int i =0;i<3;i++)
			{
				DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],100,100,100,0,imageWidth,imageHeight);
			}


			YUV2RGB_FLOAT(m_YUVStream,m_RGBStream,m_JPGInfo.image_width,m_JPGInfo.image_height);
			//�����Ϣ��ͼ��ʾ
			/*if(!m_JD_INFO.m_SnapInfo.m_MergMode)
			{*/
				//��ʼ����Ϣ��ͼ�����ƾ�������
				for( int i = 0; i < m_JD_INFO.m_ParamInit.m_LightNum; i++)
				{
					DrawRect(m_JD_INFO.m_ParamInit.m_LightRect[i],255,0,255,0,imageWidth,imageHeight);
				}
				//ʵʱ��Ϣ��ͼ������λ����ʾ��
				for(int i = 0;i < 3; i++)
				{
					DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],128,128,128,0,imageWidth,imageHeight);
				}
				//�����ߣ�ͣ���ߣ�������
				float k[LANELINENO] = {0};
				float b[LANELINENO] = {0};
				for(int i = 0; i<m_JD_INFO.m_ParamInit.m_LaneNum + 1; i++)
				{
					if(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x != 0)
					{
						//������1��б��
						k[i] = ((float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.y - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.y))/((float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x));
						//������2��б��
						b[i] = (float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.y - k[i]*m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x);
					}
					else
					{
						if(i>0)
						{
							//ֹͣ�߶�������
							m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.x = m_JD_INFO.m_ParamInit.m_LaneLine[i-1].Point1.x;
							m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point2.x = m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x;

							//�����߶�������
							m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.x = m_JD_INFO.m_ParamInit.m_LaneLine[i-1].Point1.x;
							m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point2.x = m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x;
						}
					}

					DrawLine(m_JD_INFO.m_ParamInit.m_LaneLine[i],255,0,0,0,imageWidth,imageHeight);
					if(i >0)
					{
						if(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x != 0)
						{
							m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.x = (m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i-1])/k[i-1]>0?(m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i-1])/k[i-1]:0;
							m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point2.x = (m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i])/k[i]>0?(m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i])/k[i]-3:0;

							m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.x = (m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i-1])/k[i-1]>0?(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i-1])/k[i-1]:0;
							m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point2.x = (m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i])/k[i]>0?(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i])/k[i]-3:0;
						}

						DrawLine(m_JD_INFO.m_ParamInit.m_StopLine[i-1],255,128,0,0,imageWidth,imageHeight);
						DrawLine(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1],0,255,0,0,imageWidth,imageHeight);
					}
				}

				//��ת����
				DrawLine(m_JD_INFO.m_ParamInit.m_LeftTurnLine,0,0,255,0,imageWidth,imageHeight);
				//��ת����
				DrawLine(m_JD_INFO.m_ParamInit.m_RightTurnLine,0,255,255,0,imageWidth,imageHeight);
				
			//}

			delete [] dec->sdram_buffer;
			dec->sdram_buffer =NULL;
			return TRUE;
		}

		//ͼƬ�Ǻϳɷ�ʽ
		else if(m_JD_INFO.m_SnapInfo.m_MergMode == 0)
		{
			//��ʼ����Ϣ��ͼ�����ƾ�������
			for( int i =0; i<m_JD_INFO.m_ParamInit.m_LightNum;i++)
			{
				memset((void *)&m_JD_INFO,0,sizeof(m_JD_INFO));//
				int a  = sizeof(m_JD_INFO);// = 5568;
				memcpy_s((void *)&m_JD_INFO,sizeof(m_JD_INFO),m_ComInfo.com_buffer,m_ComInfo.com_len);
			}
			//ʵʱ��Ϣ��ͼ������λ����ʾ��
			for(int i =0;i<3;i++)
			{
				DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],255,255,0,1,imageWidth,imageHeight);
			}
			/*for(int i =0;i<3;i++)
			{
				DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],255,255,0,2,imageWidth,imageHeight);
			}
			for(int i =0;i<3;i++)
			{
				DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],255,255,0,3,imageWidth,imageHeight);
			}*/


			YUV2RGB_FLOAT(m_YUVStream,m_RGBStream,m_JPGInfo.image_width,m_JPGInfo.image_height);
			//�����Ϣ��ͼ��ʾ
			//if(!m_JD_INFO.m_SnapInfo.m_MergMode)
			//{
			//	//��ʼ����Ϣ��ͼ�����ƾ�������
			//	for( int i = 0; i < m_JD_INFO.m_ParamInit.m_LightNum; i++)
			//	{
			//		DrawRect(m_JD_INFO.m_ParamInit.m_LightRect[i],255,0,255,1);
			//	}
			//	//ʵʱ��Ϣ��ͼ������λ����ʾ��
			//	for(int i = 0;i < 3; i++)
			//	{
			//		//DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],128,128,128,1);
			//		DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],255,0,0,1);
			//	}
			//	//�����ߣ�ͣ���ߣ�������
			//	float k[LANELINENO] = {0};
			//	float b[LANELINENO] = {0};
			//	for(int i = 0; i<m_JD_INFO.m_ParamInit.m_LaneNum + 1; i++)
			//	{
			//		if(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x != 0)
			//		{
			//			//������1��б��
			//			k[i] = ((float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.y - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.y))/((float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x));
			//			//������2��б��
			//			b[i] = (float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.y - k[i]*m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x);
			//		}
			//		else
			//		{
			//			if(i>0)
			//			{
			//				//ֹͣ�߶�������
			//				m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.x = m_JD_INFO.m_ParamInit.m_LaneLine[i-1].Point1.x / 4 * 2;
			//				m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point2.x = m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x / 4 * 2;

			//				//�����߶�������
			//				m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.x = m_JD_INFO.m_ParamInit.m_LaneLine[i-1].Point1.x / 4 * 2;
			//				m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point2.x = m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x / 4 * 2;
			//			}
			//		}

			//		DrawLine(m_JD_INFO.m_ParamInit.m_LaneLine[i],255,0,0);
			//		if(i >0)
			//		{
			//			if(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x != 0)
			//			{
			//				m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.x = (m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i-1])/k[i-1]>0?(m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i-1])/k[i-1]:0;
			//				m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point2.x = (m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i])/k[i]>0?(m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i])/k[i]-3:0;

			//				m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.x = (m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i-1])/k[i-1]>0?(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i-1])/k[i-1]:0;
			//				m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point2.x = (m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i])/k[i]>0?(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i])/k[i]-3:0;
			//			}

			//			DrawLine(m_JD_INFO.m_ParamInit.m_StopLine[i-1],255,128,0);
			//			DrawLine(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1],0,255,0);
			//		}
			//	}

			//	//��ת����
			//	DrawLine(m_JD_INFO.m_ParamInit.m_LeftTurnLine,0,0,255);
			//	//��ת����
			//	DrawLine(m_JD_INFO.m_ParamInit.m_RightTurnLine,0,255,255);

			//}


			//Modify by SHJ
			//��ʼ����Ϣ��ͼ�����ƾ�������
			for( int i = 0; i < m_JD_INFO.m_ParamInit.m_LightNum; i++)
			{
				DrawRect(m_JD_INFO.m_ParamInit.m_LightRect[i],255,0,255,1,imageWidth,imageHeight);
				DrawRect(m_JD_INFO.m_ParamInit.m_LightRect[i],255,0,255,2,imageWidth,imageHeight);
				DrawRect(m_JD_INFO.m_ParamInit.m_LightRect[i],255,0,255,3,imageWidth,imageHeight);
			}
			//ʵʱ��Ϣ��ͼ������λ����ʾ��
			for(int i = 0;i < 3; i++)
			{
				//DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],128,128,128,1);
				DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],255,0,0,1,imageWidth,imageHeight);
				DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],255,0,0,2,imageWidth,imageHeight);
				DrawRect(m_JD_INFO.m_SnapInfo.m_PlateRect[i],255,0,0,3,imageWidth,imageHeight);
			}
			//�����ߣ�ͣ���ߣ�������
			float k[LANELINENO] = {0};
			float b[LANELINENO] = {0};
			for(int i = 0; i<m_JD_INFO.m_ParamInit.m_LaneNum + 1; i++)
			{
				if(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x != 0)
				{
					//������1��б��
					k[i] = ((float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.y - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.y))/((float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x));
					//������2��б��
					b[i] = (float)(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.y - k[i]*m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x);
				}
				else
				{
					if(i>0)
					{
						//ֹͣ�߶�������
						m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.x = m_JD_INFO.m_ParamInit.m_LaneLine[i-1].Point1.x / 4 * 2;
						m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point2.x = m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x / 4 * 2;

						//�����߶�������
						m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.x = m_JD_INFO.m_ParamInit.m_LaneLine[i-1].Point1.x / 4 * 2;
						m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point2.x = m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x / 4 * 2;
					}
				}

				DrawLine(m_JD_INFO.m_ParamInit.m_LaneLine[i],255,0,0,1,imageWidth,imageHeight);
				DrawLine(m_JD_INFO.m_ParamInit.m_LaneLine[i],255,0,0,2,imageWidth,imageHeight);
				DrawLine(m_JD_INFO.m_ParamInit.m_LaneLine[i],255,0,0,3,imageWidth,imageHeight);
				if(i >0)
				{
					if(m_JD_INFO.m_ParamInit.m_LaneLine[i].Point1.x - m_JD_INFO.m_ParamInit.m_LaneLine[i].Point2.x != 0)
					{
						m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.x = (m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i-1])/k[i-1]>0?(m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i-1])/k[i-1]:0;
						m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point2.x = (m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i])/k[i]>0?(m_JD_INFO.m_ParamInit.m_StopLine[i-1].Point1.y - (short)b[i])/k[i]-3:0;

						m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.x = (m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i-1])/k[i-1]>0?(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i-1])/k[i-1]:0;
						m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point2.x = (m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i])/k[i]>0?(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1].Point1.y - (short)b[i])/k[i]-3:0;
					}

					DrawLine(m_JD_INFO.m_ParamInit.m_StopLine[i-1],255,128,0,1,imageWidth,imageHeight);
					DrawLine(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1],0,255,0,1,imageWidth,imageHeight);
					DrawLine(m_JD_INFO.m_ParamInit.m_StopLine[i-1],255,128,0,2,imageWidth,imageHeight);
					DrawLine(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1],0,255,0,2,imageWidth,imageHeight);
					DrawLine(m_JD_INFO.m_ParamInit.m_StopLine[i-1],255,128,0,3,imageWidth,imageHeight);
					DrawLine(m_JD_INFO.m_ParamInit.m_TrigleLine[i-1],0,255,0,3,imageWidth,imageHeight);
				}
			}

			//��ת����
			DrawLine(m_JD_INFO.m_ParamInit.m_LeftTurnLine,0,0,255,1,imageWidth,imageHeight);
			DrawLine(m_JD_INFO.m_ParamInit.m_LeftTurnLine,0,0,255,2,imageWidth,imageHeight);
			DrawLine(m_JD_INFO.m_ParamInit.m_LeftTurnLine,0,0,255,3,imageWidth,imageHeight);
			//��ת����
			DrawLine(m_JD_INFO.m_ParamInit.m_RightTurnLine,0,255,255,1,imageWidth,imageHeight);
			DrawLine(m_JD_INFO.m_ParamInit.m_RightTurnLine,0,255,255,2,imageWidth,imageHeight);
			DrawLine(m_JD_INFO.m_ParamInit.m_RightTurnLine,0,255,255,3,imageWidth,imageHeight);

			delete [] dec->sdram_buffer;
			dec->sdram_buffer =NULL;
			return TRUE;
		}
	}
	catch(...)
	{
		MessageBox(NULL,"����ͼƬ��Ϣʱ���ִ���.","����",MB_OK);
		return FALSE;
	}
}
/*****************************************************************
������: DrawLine
����: ���ߺ�������RGBͼ����ֱ�ӻ�ֱ��
����:
line��ֱ������
r,g,bΪֱ�ߵ���ɫ����
����ֵ:BOOL��true�ɹ���falseʧ��
��ע:
******************************************************************/
BOOL DecProcess::DrawLine(JD_LINE line,unsigned char r,unsigned char g,unsigned char b, UINT SynType,int imgWidth,int imgHeigth)
{
	switch(SynType)
	{
	case 0:
	default:
			break;
	case 1:
		line.Point1.x = line.Point1.x / 4 * 2;
		line.Point1.y = line.Point1.y / 4 * 2;
		line.Point2.x = line.Point2.x / 4 * 2;
		line.Point2.y = line.Point2.y / 4 * 2;
		break;
	case 2:
		line.Point1.x = line.Point1.x / 4 * 2 + imgWidth / 4 * 2;
		line.Point1.y = line.Point1.y / 4 * 2;
		line.Point2.x = line.Point2.x / 4 * 2 + imgWidth / 4 * 2;
		line.Point2.y = line.Point2.y / 4 * 2;
		break;
	case 3:
		line.Point1.x = line.Point1.x / 4 * 2;
		line.Point1.y = line.Point1.y / 4 * 2 + imgHeigth / 4 * 2;
		line.Point2.x = line.Point2.x / 4 * 2;
		line.Point2.y = line.Point2.y / 4 * 2 + imgHeigth / 4 * 2;
		break;
	}
	if(!m_RGBStream || (line.Point1.x - line.Point2.x)*(line.Point1.x - line.Point2.x) + (line.Point1.y - line.Point2.y)*(line.Point1.y - line.Point2.y) == 0)
	{
		return FALSE;
	}
	if(line.Point1.x - line.Point2.x == 0)
	{
		for(unsigned int i = 0;i<m_JPGInfo.image_height;i++)
		{
			for(unsigned int j = 0;j<m_JPGInfo.image_width;j++)
			{
				if(i >= (unsigned int)line.Point1.y && i <= (unsigned int)line.Point2.y && j == line.Point1.x)
				{
					m_RGBStream[i*m_JPGInfo.image_width*3+(j-1)*3] = r;
					m_RGBStream[i*m_JPGInfo.image_width*3+(j-1)*3+1] = g;
					m_RGBStream[i*m_JPGInfo.image_width*3+(j-1)*3+2] = b;

					m_RGBStream[i*m_JPGInfo.image_width*3+j*3] = r;
					m_RGBStream[i*m_JPGInfo.image_width*3+j*3+1] = g;
					m_RGBStream[i*m_JPGInfo.image_width*3+j*3+2] = b;

					m_RGBStream[i*m_JPGInfo.image_width*3+(j+1)*3] = r;
					m_RGBStream[i*m_JPGInfo.image_width*3+(j+1)*3+1] = g;
					m_RGBStream[i*m_JPGInfo.image_width*3+(j+1)*3+2] = b;
				}
			}
		}
	}
	else if(line.Point1.y - line.Point2.y == 0)
	{
		for(unsigned int i = 0;i<m_JPGInfo.image_height;i++)
		{
			for(unsigned int j = 0;j<m_JPGInfo.image_width;j++)
			{
				if(j >= (unsigned int)line.Point1.x && j <= (unsigned int)line.Point2.x && i == line.Point1.y)
				{
					if(i>0)
					{
						m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3] = r;
						m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3+1] = g;
						m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3+2] = b;
					}
					m_RGBStream[i*m_JPGInfo.image_width*3+j*3] = r;
					m_RGBStream[i*m_JPGInfo.image_width*3+j*3+1] = g;
					m_RGBStream[i*m_JPGInfo.image_width*3+j*3+2] = b;

					m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3] = r;
					m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3+1] = g;
					m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3+2] = b;
				}
			}
		}
	}
	else
	{
		float k = ((float)(line.Point1.y - line.Point2.y))/((float)(line.Point1.x - line.Point2.x));
		static float k1 = 0;
		static short tmpX,tmpY;
		if(k > 0)
		{
			tmpX = line.Point1.x;
			tmpY = line.Point1.y;
			for(unsigned int i = 0;i<m_JPGInfo.image_height;i++)
			{
				for(unsigned int j = 0;j<m_JPGInfo.image_width;j++)
				{
					if(j == tmpX && i == tmpY && tmpX <=line.Point2.x)
					{
						if(i>0)
						{
							m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3] = r;
							m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3+1] = g;
							m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3+2] = b;
						}

						m_RGBStream[i*m_JPGInfo.image_width*3+j*3] = r;
						m_RGBStream[i*m_JPGInfo.image_width*3+j*3+1] = g;
						m_RGBStream[i*m_JPGInfo.image_width*3+j*3+2] = b;

						m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3] = r;
						m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3+1] = g;
						m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3+2] = b;

						if(k1 == 0)
						{
							tmpY ++;
							tmpX ++;
							k1 = ((float)(tmpY-line.Point1.y))/((float)(tmpX-line.Point1.x));
						}
						else
						{
							if(k1>k)
							{
								tmpX ++;
							}
							else
							{
								tmpY ++;
							}
							k1 = ((float)(tmpY-line.Point1.y))/((float)(tmpX-line.Point1.x));
						}
					}
				}
			}
		}

		if(k <0)
		{
			if (line.Point1.y < line.Point2.y)
			{
				short tempX = line.Point2.x;
				short tempY = line.Point2.y;
				line.Point2.x = line.Point1.x;
				line.Point2.y = line.Point1.y;
				line.Point1.x = tempX;
				line.Point1.y = tempY;
			}
			tmpX = line.Point2.x;
			tmpY = line.Point2.y;
			for(unsigned int i = 0;i<m_JPGInfo.image_height;i++)
			{
				for(unsigned int j = 0;j<m_JPGInfo.image_width;j++)
				{
					if(j == tmpX && i == tmpY && tmpX >= line.Point1.x)
					{
						if(i>0)
						{
							m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3] = r;
							m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3+1] = g;
							m_RGBStream[(i-1)*m_JPGInfo.image_width*3+j*3+2] = b;
						}

						m_RGBStream[i*m_JPGInfo.image_width*3+j*3] = r;
						m_RGBStream[i*m_JPGInfo.image_width*3+j*3+1] = g;
						m_RGBStream[i*m_JPGInfo.image_width*3+j*3+2] = b;

						m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3] = r;
						m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3+1] = g;
						m_RGBStream[(i+1)*m_JPGInfo.image_width*3+j*3+2] = b;
		
						if(k1 == 0)
						{
							tmpY ++;
							tmpX --;
							k1 = ((float)(line.Point2.y-tmpY))/((float)(line.Point2.x-tmpX));
						}
						else
						{
							if(k1<k)
							{
								tmpX --;
								i -- ;
							}
							else
							{
								tmpY ++;
							}
							k1 = ((float)(line.Point2.y-tmpY))/((float)(line.Point2.x-tmpX));
						}
					}
				}
			}
		}
	}
	return TRUE;
}

/************************************************************************/
/*
������:DrawRect
����:�����ο�
����:
	JD_RECT	��������
	r g b ��ɫ����
*/

/************************************************************************/
BOOL DecProcess::DrawRect(JD_RECT rect,unsigned char r,unsigned char g,unsigned char b,UINT SynType,int imgWidth, int imgHeigth)
{
	JD_LINE rectLine1,rectLine2,rectLine3,rectLine4;
	//�ж�ͼƬ�ϳ����ͣ�0�����ϳɣ����Ŷ���ͼƬ	1��4��1�������ͺϳ�
	/*switch(SynType)
	{
	case 0:
		rectLine1.Point1.x = rect.left;
		rectLine1.Point1.y = rect.top;
		rectLine1.Point2.x = rect.left;
		rectLine1.Point2.y = rect.bottom;

		rectLine2.Point1.x = rect.left;
		rectLine2.Point1.y = rect.top;
		rectLine2.Point2.x = rect.right;
		rectLine2.Point2.y = rect.top;

		rectLine3.Point1.x = rect.right;
		rectLine3.Point1.y = rect.top;
		rectLine3.Point2.x = rect.right;
		rectLine3.Point2.y = rect.bottom;

		rectLine4.Point1.x = rect.left;
		rectLine4.Point1.y = rect.bottom;
		rectLine4.Point2.x = rect.right;
		rectLine4.Point2.y = rect.bottom;
		
		break;
	case 1:
		rectLine1.Point1.x = rect.left / 4 * 2;
		rectLine1.Point1.y = rect.top / 4 * 2;
		rectLine1.Point2.x = rect.left / 4 * 2;
		rectLine1.Point2.y = rect.bottom / 4 * 2;

		rectLine2.Point1.x = rect.left / 4 * 2;
		rectLine2.Point1.y = rect.top / 4 * 2;
		rectLine2.Point2.x = rect.right / 4 * 2;
		rectLine2.Point2.y = rect.top / 4 * 2;

		rectLine3.Point1.x = rect.right / 4 * 2;
		rectLine3.Point1.y = rect.top / 4 * 2;
		rectLine3.Point2.x = rect.right / 4 * 2;
		rectLine3.Point2.y = rect.bottom / 4 * 2;

		rectLine4.Point1.x = rect.left / 4 * 2;
		rectLine4.Point1.y = rect.bottom / 4 * 2;
		rectLine4.Point2.x = rect.right / 4 * 2;
		rectLine4.Point2.y = rect.bottom / 4 * 2;

		break;
	}*/
	
	rectLine1.Point1.x = rect.left;
	rectLine1.Point1.y = rect.top;
	rectLine1.Point2.x = rect.left;
	rectLine1.Point2.y = rect.bottom;

	rectLine2.Point1.x = rect.left;
	rectLine2.Point1.y = rect.top;
	rectLine2.Point2.x = rect.right;
	rectLine2.Point2.y = rect.top;

	rectLine3.Point1.x = rect.right;
	rectLine3.Point1.y = rect.top;
	rectLine3.Point2.x = rect.right;
	rectLine3.Point2.y = rect.bottom;

	rectLine4.Point1.x = rect.left;
	rectLine4.Point1.y = rect.bottom;
	rectLine4.Point2.x = rect.right;
	rectLine4.Point2.y = rect.bottom;

	DrawLine(rectLine1,r,g,b,SynType,imgWidth,imgHeigth);
	DrawLine(rectLine2,r,g,b,SynType,imgWidth,imgHeigth);
	DrawLine(rectLine3,r,g,b,SynType,imgWidth,imgHeigth);
	DrawLine(rectLine4,r,g,b,SynType,imgWidth,imgHeigth);

	return TRUE;
}