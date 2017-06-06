#include "QuaternionCalculator.h"
#include "resource.h"
#include "utils.h"


CQuaternionCalculator::CQuaternionCalculator(HWND _hDlg) :
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
	},
	m_kszScalarTBox(IDC_EDIT9)
{
	m_hDlg = _hDlg;
}


CQuaternionCalculator::~CQuaternionCalculator()
{
}

void CQuaternionCalculator::HandleBtnAPlusB()
{
	CQuaternion qA = GetQuaternionA();
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qA + qB);
}

void CQuaternionCalculator::HandleBtnAMinusB()
{
	CQuaternion qA = GetQuaternionA();
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qA - qB);
}

void CQuaternionCalculator::HandleBtnBMinusA()
{
	CQuaternion qA = GetQuaternionA();
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qB - qA);
}

void CQuaternionCalculator::HandleBtnATimesB()
{
	CQuaternion qA = GetQuaternionA();
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qA * qB);
}

void CQuaternionCalculator::HandleBtnBTimesA()
{
	CQuaternion qA = GetQuaternionA();
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qB * qA);
}

void CQuaternionCalculator::HandleBtnADotB()
{
	CQuaternion qA = GetQuaternionA();
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qA.Dot(qB));
}

void CQuaternionCalculator::HandleBtnAConjugate()
{
	CQuaternion qA = GetQuaternionA();
	SetAnswerBox(qA.Conjugate());
}

void CQuaternionCalculator::HandleBtnBConjugate()
{
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qB.Conjugate());
}

void CQuaternionCalculator::HandleBtnMagnitudeOfA()
{
	CQuaternion qA = GetQuaternionA();
	SetAnswerBox(qA.Magnitude());
}

void CQuaternionCalculator::HandleBtnMagnitudeOfB()
{
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qB.Magnitude());
}

void CQuaternionCalculator::HandleBtnAInverse()
{
	CQuaternion qA = GetQuaternionA();
	SetAnswerBox(qA.Inverse());
}

void CQuaternionCalculator::HandleBtnBInverse()
{
	CQuaternion qB = GetQuaternionB();
	SetAnswerBox(qB.Inverse());
}

void CQuaternionCalculator::HandleBtnTTimesA()
{
	CQuaternion qA = GetQuaternionA();
	float fT = ReadFromEditBox(m_hDlg, m_kszScalarTBox);
	SetAnswerBox(fT * qA);
}

void CQuaternionCalculator::HandleBtnTTimesB()
{
	CQuaternion qB = GetQuaternionB();
	float fT = ReadFromEditBox(m_hDlg, m_kszScalarTBox);
	SetAnswerBox(fT * qB);
}

CQuaternion CQuaternionCalculator::GetQuaternionA()
{
	float fW = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[0]);
	float fI = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[1]);
	float fJ = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[2]);
	float fK = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

CQuaternion CQuaternionCalculator::GetQuaternionB()
{
	float fW = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[0]);
	float fI = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[1]);
	float fJ = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[2]);
	float fK = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

void CQuaternionCalculator::SetAnswerBox(const CQuaternion& _krqAnswer)
{
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		float fElement = _krqAnswer.GetElement(szIdx);
		WriteToEditBox(m_hDlg, m_karrQuatAnsBoxes.at(szIdx), fElement);
	}
}

