#include "QuaternionCalculator.h"
#include "resource.h"
#include "utils.h"


CQuaternionCalculator::CQuaternionCalculator() :
	m_karrQuatABoxes{
		IDC_EDIT4,     // The real component is placed in the last edit box
		IDC_EDIT1,
		IDC_EDIT2,
		IDC_EDIT3,
	},
	m_karrQuatBBoxes {
		IDC_EDIT8,     // The real component is placed in the last edit box
		IDC_EDIT5,
		IDC_EDIT6,
		IDC_EDIT7,
	},
	m_karrQuatAnsBoxes {
		IDC_EDIT13,    // The real component is placed in the last edit box
		IDC_EDIT10,
		IDC_EDIT11,
		IDC_EDIT12,
}
{
}


CQuaternionCalculator::~CQuaternionCalculator()
{
}

void CQuaternionCalculator::HandleBtnAPlusB(HWND _hDlg)
{
	CQuaternion qA = GetQuaternionA(_hDlg);
	CQuaternion qB = GetQuaternionB(_hDlg);
	SetAnswerBox(_hDlg, qA + qB);
}

CQuaternion CQuaternionCalculator::GetQuaternionA(HWND _hDlg)
{
	float fW = ReadFromEditBox(_hDlg, m_karrQuatABoxes[0]);
	float fI = ReadFromEditBox(_hDlg, m_karrQuatABoxes[1]);
	float fJ = ReadFromEditBox(_hDlg, m_karrQuatABoxes[2]);
	float fK = ReadFromEditBox(_hDlg, m_karrQuatABoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

CQuaternion CQuaternionCalculator::GetQuaternionB(HWND _hDlg)
{
	float fW = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[0]);
	float fI = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[1]);
	float fJ = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[2]);
	float fK = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

void CQuaternionCalculator::SetAnswerBox(HWND _hDlg, const CQuaternion& _krqAnswer)
{
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		float fElement = _krqAnswer.GetElement(szIdx);
		WriteToEditBox(_hDlg, m_karrQuatAnsBoxes.at(szIdx), fElement);
	}
}

