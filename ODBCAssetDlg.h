#pragma once
#include "afxcmn.h"


// CODBCAssetDlg ��ȭ �����Դϴ�.

class CODBCAssetDlg : public CDialog
{
	DECLARE_DYNAMIC(CODBCAssetDlg)

public:
	CODBCAssetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CODBCAssetDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ODBCDIALOG_ASSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListAsset;
	CImageList m_LargeImageList2;
	CImageList m_SmallImageList2;
};
