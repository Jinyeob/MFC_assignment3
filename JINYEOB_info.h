
// JINYEOB_info.h : JINYEOB_info ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CJINYEOB_infoApp:
// �� Ŭ������ ������ ���ؼ��� JINYEOB_info.cpp�� �����Ͻʽÿ�.
//

class CJINYEOB_infoApp : public CWinApp
{
public:
	CJINYEOB_infoApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CJINYEOB_infoApp theApp;
