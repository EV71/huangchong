
// VoiceTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVoiceTestApp:
// �йش����ʵ�֣������ VoiceTest.cpp
//

class CVoiceTestApp : public CWinAppEx
{
public:
	CVoiceTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVoiceTestApp theApp;