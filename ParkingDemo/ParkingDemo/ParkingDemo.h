
// ParkingDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CParkingDemoApp:
// �йش����ʵ�֣������ ParkingDemo.cpp
//

class CParkingDemoApp : public CWinAppEx
{
public:
	CParkingDemoApp();
	ULONG_PTR m_gdiplusToken; 

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CParkingDemoApp theApp;