
// mfc_opengl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_openglApp: 
// �йش����ʵ�֣������ mfc_opengl.cpp
//

class Cmfc_openglApp : public CWinApp
{
public:
	Cmfc_openglApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_openglApp theApp;