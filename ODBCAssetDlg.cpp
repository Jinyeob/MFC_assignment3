// ODBCAssetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JINYEOB_info.h"
#include "ODBCAssetDlg.h"
#include "afxdialogex.h"
#include <string>

// CODBCAssetDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CODBCAssetDlg, CDialog)

CODBCAssetDlg::CODBCAssetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ODBCDIALOG_ASSET, pParent)
{

}

CODBCAssetDlg::~CODBCAssetDlg()
{
}

void CODBCAssetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ASSET, m_ListAsset);
}


BEGIN_MESSAGE_MAP(CODBCAssetDlg, CDialog)
END_MESSAGE_MAP()


// CODBCAssetDlg �޽��� ó�����Դϴ�.


BOOL CODBCAssetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CDatabase db;
	db.OpenEx(_T("DSN=informationDSN"), 0);
	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, _T("SELECT * FROM asset"));

	m_LargeImageList2.Create(IDB_BITMAP2, 48, 1, RGB(0, 0, 0));
	m_SmallImageList2.Create(IDB_BITMAP1, 16, 1, RGB(0, 0, 0));
	m_ListAsset.SetImageList(&m_LargeImageList2, LVSIL_NORMAL);
	m_ListAsset.SetImageList(&m_SmallImageList2, LVSIL_SMALL);

	m_ListAsset.SetExtendedStyle(m_ListAsset.GetExtendedStyle() | LVS_EX_GRIDLINES);
	m_ListAsset.SetExtendedStyle(m_ListAsset.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_ListAsset.InsertColumn(0, _T("��ȣ"), LVCFMT_RIGHT, 60);
	m_ListAsset.InsertColumn(1, _T("��ǰ"), LVCFMT_LEFT, 100);
	m_ListAsset.InsertColumn(2, _T("�ݾ�"), LVCFMT_LEFT, 150);
	m_ListAsset.InsertColumn(3, _T("���ų⵵"), LVCFMT_LEFT, 100);
	m_ListAsset.InsertColumn(4, _T("�з�"), LVCFMT_LEFT, 100);

	CString str;
	int i = 0;
	while (!rs.IsEOF()) {
		rs.GetFieldValue(short(0), str);
		m_ListAsset.InsertItem(i, str, 0);
		rs.GetFieldValue(short(1), str);
		m_ListAsset.SetItemText(i, 1, str);
		rs.GetFieldValue(short(2), str);
		m_ListAsset.SetItemText(i, 2, str);
		rs.GetFieldValue(short(3), str);
		m_ListAsset.SetItemText(i, 3, str);
		rs.GetFieldValue(short(4), str);
		m_ListAsset.SetItemText(i, 4, str);

		rs.MoveNext();
		i++;
	}

	rs.Close(); 
	db.Close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
