
// GDIPractice.h : GDIPractice ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGDIPracticeApp:
// �� Ŭ������ ������ ���ؼ��� GDIPractice.cpp�� �����Ͻʽÿ�.
//

class CGDIPracticeApp : public CWinAppEx
{
public:
	CGDIPracticeApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDIPracticeApp theApp;
