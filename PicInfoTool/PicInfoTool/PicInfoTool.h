
// PicInfoTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPicInfoToolApp:
// �йش����ʵ�֣������ PicInfoTool.cpp
//

class CPicInfoToolApp : public CWinAppEx
{
public:
	CPicInfoToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPicInfoToolApp theApp;