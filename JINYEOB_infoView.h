
// JINYEOB_infoView.h : CJINYEOB_infoView Ŭ������ �������̽�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CJINYEOB_infoSet;

class CJINYEOB_infoView : public CRecordView
{
protected: // serialization������ ��������ϴ�.
	CJINYEOB_infoView();
	DECLARE_DYNCREATE(CJINYEOB_infoView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_JINYEOB_INFO_FORM };
#endif
	CJINYEOB_infoSet* m_pSet;

// Ư���Դϴ�.
public:
	CJINYEOB_infoDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CJINYEOB_infoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CButton m_ButtonTotal;
	CButton m_ButtonAdd;
	CButton m_ButtonMod;
	CButton m_ButtonDelete;
	void Addcolumn();
	void AddAllRecord();
	void GetTotalRecordCount();
	int record_count;
	afx_msg void OnBnClickedButtonTotal();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdate();
	int current_pos;
	BOOL bUpdate;
	BOOL bAdd;
	BOOL bSearch;

	afx_msg void OnLvnItemchangedListAddr(NMHDR *pNMHDR, LRESULT *pResult);
	void Select();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordPrev();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordLast();
	void SetImageList();

	CImageList m_LargeImageList;
	CImageList m_SmallImageList;
	afx_msg void OnIcon();
	afx_msg void OnSmallicon();
	afx_msg void OnList();
	afx_msg void OnReport();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedButtonSearch();
	CString m_Search;
	afx_msg void OnLbnSelchangeListSearch();
	CListBox m_Box;
	afx_msg void OnBnClickedButtonAsset();
};

#ifndef _DEBUG  // JINYEOB_infoView.cpp�� ����� ����
inline CJINYEOB_infoDoc* CJINYEOB_infoView::GetDocument() const
   { return reinterpret_cast<CJINYEOB_infoDoc*>(m_pDocument); }
#endif

