
// JINYEOB_infoView.cpp : CJINYEOB_infoView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "JINYEOB_info.h"
#endif

#include "JINYEOB_infoSet.h"
#include "JINYEOB_infoDoc.h"
#include "JINYEOB_infoView.h"
#include "ListAddrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJINYEOB_infoView

IMPLEMENT_DYNCREATE(CJINYEOB_infoView, CRecordView)

BEGIN_MESSAGE_MAP(CJINYEOB_infoView, CRecordView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_TOTAL, &CJINYEOB_infoView::OnBnClickedButtonTotal)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CJINYEOB_infoView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CJINYEOB_infoView::OnBnClickedButtonUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ADDR, &CJINYEOB_infoView::OnLvnItemchangedListAddr)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CJINYEOB_infoView::OnBnClickedButtonDelete)
	ON_COMMAND(ID_RECORD_FIRST, &CJINYEOB_infoView::OnRecordFirst)
	ON_COMMAND(ID_RECORD_PREV, &CJINYEOB_infoView::OnRecordPrev)
	ON_COMMAND(ID_RECORD_NEXT, &CJINYEOB_infoView::OnRecordNext)
	ON_COMMAND(ID_RECORD_LAST, &CJINYEOB_infoView::OnRecordLast)
	ON_COMMAND(ID_ICON, &CJINYEOB_infoView::OnIcon)
	ON_COMMAND(ID_SMALLICON, &CJINYEOB_infoView::OnSmallicon)
	ON_COMMAND(ID_LIST, &CJINYEOB_infoView::OnList)
	ON_COMMAND(ID_REPORT, &CJINYEOB_infoView::OnReport)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CJINYEOB_infoView::OnBnClickedButtonSearch)
	ON_LBN_SELCHANGE(IDC_LIST_SEARCH, &CJINYEOB_infoView::OnLbnSelchangeListSearch)
	ON_BN_CLICKED(IDC_BUTTON_ASSET, &CJINYEOB_infoView::OnBnClickedButtonAsset)
END_MESSAGE_MAP()

// CJINYEOB_infoView ����/�Ҹ�

CJINYEOB_infoView::CJINYEOB_infoView()
	: CRecordView(IDD_JINYEOB_INFO_FORM)
{
	m_pSet = NULL;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	current_pos = 1;
	record_count = 0;
	bAdd = FALSE;
	bUpdate = FALSE;
	bSearch = FALSE;
}

CJINYEOB_infoView::~CJINYEOB_infoView()
{
}

CListAddrDlg dlg;

void CJINYEOB_infoView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// ��Ʈ���� �����ͺ��̽� �ʵ忡 '����'�ϱ� ���� ���⿡ DDX_Field* �Լ��� ������ �� �ֽ��ϴ�. ��:
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// �ڼ��� ������ MSDN �� ODBC ������ �����Ͻʽÿ�.

	DDX_Control(pDX, IDC_LIST_ADDR, m_List);
	DDX_Control(pDX, IDC_BUTTON_TOTAL, m_ButtonTotal);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_ButtonAdd);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_ButtonMod);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_ButtonDelete);

	DDX_Text(pDX, IDC_EDIT_SEARCH, m_Search);
	DDX_Control(pDX, IDC_LIST_SEARCH, m_Box);
}

BOOL CJINYEOB_infoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CRecordView::PreCreateWindow(cs);
}

void CJINYEOB_infoView::OnInitialUpdate()
{

	m_pSet = &GetDocument()->m_JINYEOB_infoSet;
	CRecordView::OnInitialUpdate();
	m_Box.AddString(_T("��ü"));
	m_Box.AddString(_T("����"));
	m_Box.AddString(_T("����"));
	m_Box.AddString(_T("�б�"));
	m_Box.AddString(_T("ģ��"));
	m_Box.AddString(_T("��Ÿ"));
	Addcolumn();
	SetImageList();
	AddAllRecord(); 
	GetTotalRecordCount();

	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES);
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_List.SetSelectionMark(current_pos - 1);
	m_List.SetItemState(current_pos - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_List.SetFocus();
}


// CJINYEOB_infoView �μ�

BOOL CJINYEOB_infoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CJINYEOB_infoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CJINYEOB_infoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CJINYEOB_infoView ����

#ifdef _DEBUG
void CJINYEOB_infoView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CJINYEOB_infoView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CJINYEOB_infoDoc* CJINYEOB_infoView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJINYEOB_infoDoc)));
	return (CJINYEOB_infoDoc*)m_pDocument;
}
#endif //_DEBUG


// CJINYEOB_infoView �����ͺ��̽� ����
CRecordset* CJINYEOB_infoView::OnGetRecordset()
{
	return m_pSet;
}



// CJINYEOB_infoView �޽��� ó����



void CJINYEOB_infoView::Addcolumn()
{
	CRect rect;
	m_List.GetClientRect(&rect);
	m_List.InsertColumn(0, _T("�̸�"), LVCFMT_RIGHT, 100);
	m_List.InsertColumn(1, _T("�̸���"), LVCFMT_LEFT, rect.Width() - 430);
	m_List.InsertColumn(2, _T("��ȭ��ȣ"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, _T("����"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, _T("����"), LVCFMT_LEFT, 60);

}


void CJINYEOB_infoView::AddAllRecord()
{
		m_pSet->Requery();
		int i = 0;
		m_List.DeleteAllItems();
		while (m_pSet->IsEOF() == FALSE) {
			m_List.InsertItem(i, m_pSet->m_fname, 0);
			m_List.SetItemText(i, 1, m_pSet->m_femail);
			m_List.SetItemText(i, 2, m_pSet->m_fphone);
			m_List.SetItemText(i, 3, m_pSet->m_fgroup);
			m_List.SetItemText(i, 4, m_pSet->m_frelation);
			m_pSet->MoveNext();
			i++;
		}
		current_pos = record_count = i;
		m_pSet->SetAbsolutePosition(current_pos);
}

void CJINYEOB_infoView::GetTotalRecordCount()
{
	CRecordset cntSet(m_pSet->m_pDatabase);
	cntSet.Open(CRecordset::dynaset, _T("select count(*) from addressbook")); // ��ü ���ڵ��� ������ ����
		CString strCount;
	cntSet.GetFieldValue((short)0, strCount);
	record_count = atoi((char *)(const wchar_t *)strCount);
	cntSet.Close();
}


void CJINYEOB_infoView::OnBnClickedButtonTotal()
{
	AddAllRecord();
	Select();
}


void CJINYEOB_infoView::OnBnClickedButtonAdd()
{
	int res = dlg.DoModal();

	if (res == IDOK) {
		m_pSet->AddNew();
		m_pSet->SetFieldNull(NULL);

		m_pSet->m_fname = dlg.m_name;
		m_pSet->m_fphone = dlg.m_phone;
		m_pSet->m_femail = dlg.m_email;
		m_pSet->m_fgroup = dlg.m_group;
		m_pSet->m_frelation = dlg.m_relation;

		m_pSet->Update();
		m_pSet->Requery();
		m_pSet->MoveLast();
		GetTotalRecordCount();
		AddAllRecord();
	}
	Select();
}

void CJINYEOB_infoView::OnLvnItemchangedListAddr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nItem = pNMLV->iItem; //���õ� �׸��� ���� ��ġ ���� ���ɴϴ�.
	current_pos = nItem + 1;
	m_pSet->SetAbsolutePosition(current_pos);

	*pResult = 0;
}

void CJINYEOB_infoView::OnBnClickedButtonUpdate()
{

		CListAddrDlg dlg;

		dlg.m_name= m_pSet->m_fname;
		dlg.m_phone = m_pSet->m_fphone;
		dlg.m_email=m_pSet->m_femail;
		dlg.m_group=m_pSet->m_fgroup;
		dlg.m_relation=m_pSet->m_frelation;

		int res = dlg.DoModal();

		if (res == IDOK) {
			m_pSet->SetAbsolutePosition(current_pos);
			m_pSet->Edit();
			UpdateData(TRUE);
			m_pSet->m_fname = dlg.m_name;
			m_pSet->m_fphone = dlg.m_phone;
			m_pSet->m_femail = dlg.m_email;
			m_pSet->m_fgroup = dlg.m_group;
			m_pSet->m_frelation = dlg.m_relation;

			m_pSet->Update();
			m_pSet->Requery();
			m_pSet->SetAbsolutePosition(current_pos);
			UpdateData(FALSE);
			AddAllRecord();
	}
		Select();
}




void CJINYEOB_infoView::Select()
{
	CListCtrl* list;

	list = (CListCtrl*)GetDlgItem(IDC_LIST_ADDR);

	list->SetItemState(current_pos - 1, LVIS_SELECTED, LVIS_SELECTED);
	list->EnsureVisible(current_pos - 1, FALSE);
	list->SetFocus();
}


void CJINYEOB_infoView::OnBnClickedButtonDelete()
{
	if (record_count == 0) {
		MessageBox(_T("������ �����Ͱ� �����ϴ�!"));
		return;
	}
	m_pSet->Delete(); // ����
	m_pSet->Requery(); // ����
	GetTotalRecordCount();
	if (record_count == 0) // �����Ͱ� �������� ������..
	{
		m_pSet->SetFieldNull(NULL);
		UpdateData(FALSE);
		current_pos = 0;
		return;
	}
	if (record_count < current_pos) // ������ ������ ������
		current_pos--;// current_pos = record_count;
	m_pSet->SetAbsolutePosition(current_pos);
	UpdateData(FALSE);
	AddAllRecord();
	Select();
}


void CJINYEOB_infoView::OnRecordFirst()
{
	if (record_count == 0)return;
	current_pos = 1;
	m_pSet->MoveFirst();
	UpdateData(FALSE);
	Select();
}


void CJINYEOB_infoView::OnRecordPrev()
{
	if (record_count == 0) return;
	current_pos--; // ���� ��ġ ���� 1���ҽ�Ŵ
	m_pSet->MovePrev(); // ���� ���ڵ� ��ġ�� �̵�
	if (m_pSet->IsBOF()) {
		m_pSet->MoveFirst();
		current_pos = 1;
	}
	UpdateData(FALSE); // Recordset ���� ���� ��Ʈ�ѿ� ���
	Select();
}


void CJINYEOB_infoView::OnRecordNext()
{
	if (record_count == 0)return;
	current_pos++;
	m_pSet->MoveNext();
	if (m_pSet->IsEOF())
	{
		m_pSet->MoveLast();
		current_pos--;
	}
	UpdateData(FALSE);
	Select();
}


void CJINYEOB_infoView::OnRecordLast()
{
	if (record_count == 0)return;
	current_pos = record_count;
	m_pSet->MoveLast();
	UpdateData(FALSE);
	Select();
}


void CJINYEOB_infoView::SetImageList(void) {
	m_LargeImageList.Create(IDB_BITMAP2, 48, 1, RGB(0, 0, 0));
	m_SmallImageList.Create(IDB_BITMAP1, 16, 1, RGB(0, 0, 0));
	m_List.SetImageList(&m_LargeImageList, LVSIL_NORMAL);
	m_List.SetImageList(&m_SmallImageList, LVSIL_SMALL);;
}

void CJINYEOB_infoView::OnIcon()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_ICON);
}


void CJINYEOB_infoView::OnSmallicon()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_SMALLICON);
}


void CJINYEOB_infoView::OnList()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_LIST);
}


void CJINYEOB_infoView::OnReport()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
}


void CJINYEOB_infoView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu *subMenu = menu.GetSubMenu(5);
	subMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}


void CJINYEOB_infoView::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);

	if (m_pSet->m_fname.IsEmpty() == false) {
		m_pSet->m_strFilter.Format(_T("fname like '%%%s%%'"), m_Search);
		int i = 0;
		m_pSet->Requery();
		m_pSet->m_strFilter.Empty();
		m_List.DeleteAllItems();

		while (m_pSet->IsEOF() == FALSE) {
			m_List.InsertItem(i, m_pSet->m_fname, 0);
			m_List.SetItemText(i, 1, m_pSet->m_femail);
			m_List.SetItemText(i, 2, m_pSet->m_fphone);
			m_List.SetItemText(i, 3, m_pSet->m_fgroup);
			m_List.SetItemText(i, 4, m_pSet->m_frelation);
			m_pSet->MoveNext();
			i++;
		}
		current_pos = record_count = i;
		m_pSet->SetAbsolutePosition(current_pos);
	}
	Select();
}



void CJINYEOB_infoView::OnLbnSelchangeListSearch()
{
	int Index = m_Box.GetCurSel();
	CString seldata;

	m_Box.GetText(Index, seldata);
	if (seldata == "��ü") {
		AddAllRecord();
	}
	else {
		if (m_pSet->m_fname.IsEmpty() == false)
		{
			m_pSet->m_strFilter.Format(_T(" frelation like '%%%s%%'"), seldata);
			int i = 0;
			m_pSet->Requery(); m_pSet->m_strFilter.Empty();
			m_List.DeleteAllItems();
			CString strTemp;
			while (m_pSet->IsEOF() == FALSE) {
				m_List.InsertItem(i, m_pSet->m_fname, 0);
				m_List.SetItemText(i, 1, m_pSet->m_femail);
				m_List.SetItemText(i, 2, m_pSet->m_fphone);
				m_List.SetItemText(i, 3, m_pSet->m_fgroup);
				m_List.SetItemText(i, 4, m_pSet->m_frelation);
				m_pSet->MoveNext();
				i++;
			}
			current_pos = record_count = i;
			m_pSet->SetAbsolutePosition(current_pos);
		}
	}
	Select();
}
#include "ODBCAssetDlg.h"
void CJINYEOB_infoView::OnBnClickedButtonAsset()
{
	CODBCAssetDlg dlgg;
	int res = dlgg.DoModal();
}