
// QuotePub.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQuotePubApp: 
// �йش����ʵ�֣������ QuotePub.cpp
//

class CQuotePubApp : public CWinApp
{
public:
	CQuotePubApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQuotePubApp theApp;