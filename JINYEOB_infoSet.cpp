
// JINYEOB_infoSet.cpp : CJINYEOB_infoSet Ŭ������ ����
//

#include "stdafx.h"
#include "JINYEOB_info.h"
#include "JINYEOB_infoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJINYEOB_infoSet ����

// �ڵ� ���� ��ġ 2018�� 11�� 20�� ȭ����, ���� 4:59

IMPLEMENT_DYNAMIC(CJINYEOB_infoSet, CRecordset)

CJINYEOB_infoSet::CJINYEOB_infoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_fname = L"";
	m_femail = L"";
	m_fphone = L"";
	m_fgroup = L"";
	m_frelation = L"";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
CString CJINYEOB_infoSet::GetDefaultConnect()
{
	return _T("DSN=informationDSN;DBQ=C:\\db\\my_information.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CJINYEOB_infoSet::GetDefaultSQL()
{
	return _T("[addressbook]");
}

void CJINYEOB_infoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[fname]"), m_fname);
	RFX_Text(pFX, _T("[femail]"), m_femail);
	RFX_Text(pFX, _T("[fphone]"), m_fphone);
	RFX_Text(pFX, _T("[fgroup]"), m_fgroup);
	RFX_Text(pFX, _T("[frelation]"), m_frelation);

}
/////////////////////////////////////////////////////////////////////////////
// CJINYEOB_infoSet ����

#ifdef _DEBUG
void CJINYEOB_infoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CJINYEOB_infoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

