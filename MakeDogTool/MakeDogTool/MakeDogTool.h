// MakeDogTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMakeDogToolApp:
// �йش����ʵ�֣������ MakeDogTool.cpp
//

class CMakeDogToolApp : public CWinApp
{
public:
	CMakeDogToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMakeDogToolApp theApp;