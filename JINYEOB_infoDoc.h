
// JINYEOB_infoDoc.h : CJINYEOB_infoDoc Ŭ������ �������̽�
//


#pragma once
#include "JINYEOB_infoSet.h"


class CJINYEOB_infoDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CJINYEOB_infoDoc();
	DECLARE_DYNCREATE(CJINYEOB_infoDoc)

// Ư���Դϴ�.
public:
	CJINYEOB_infoSet m_JINYEOB_infoSet;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CJINYEOB_infoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
