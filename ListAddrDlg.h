#pragma once
#include "afxwin.h"

// CListAddrDlg ��ȭ �����Դϴ�.

class CListAddrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListAddrDlg)

public:
	CListAddrDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CListAddrDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_phone;
	CString m_group;
	CString m_email;
	CString m_relation;
	CComboBox m_comboRelation;
};