
// BarClientDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBarClientDemoApp: 
// �йش����ʵ�֣������ BarClientDemo.cpp
//

class CBarClientDemoApp : public CWinApp
{
public:
	CBarClientDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBarClientDemoApp theApp;