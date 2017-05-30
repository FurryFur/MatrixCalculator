//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: SlerpCalculator.cpp
// Description	: Handles all code on the slerp calculator window
// Author		: Jack Mair : Lance Chaney
// Mail			: jack.mair@mediadesign.school.nz : lance.chaney@mediadesign.school.nz
//

#include <math.h>

#include "SlerpCalculator.h"
#include "utils.h"
#include "resource.h"


CSlerpCalculator::CSlerpCalculator() :
	m_karrQuatABoxes{
		IDC_EDIT1,     // The real component is placed in the last edit box
		IDC_EDIT2,
		IDC_EDIT3,
		IDC_EDIT4,
	},
	m_karrQuatBBoxes{
		IDC_EDIT5,     // The real component is placed in the last edit box
		IDC_EDIT6,
		IDC_EDIT7,
		IDC_EDIT8,
	},
	m_karrQuatAnsBoxes{
	IDC_EDIT10,    // The real component is placed in the last edit box
	IDC_EDIT11,
	IDC_EDIT12,
	IDC_EDIT13,
	},
	m_kszScalarTBox(IDC_EDIT9)
{
}


CSlerpCalculator::~CSlerpCalculator()
{
}

void CSlerpCalculator::HandleBtnASlerpB(HWND _hDlg) {
	CQuaternion qA = GetQuaternionA(_hDlg);
	CQuaternion qB = GetQuaternionB(_hDlg);
	float _fAngle = acosf((qA.Dot(qB)) / (qA.Magnitude() * qB.Magnitude()));
	SetAnswerBox(_hDlg, ((((sinf((1 - m_kszScalarTBox) * _fAngle)) / (sinf(_fAngle))) * qA) + (((sinf(m_kszScalarTBox * _fAngle)) / (sinf(_fAngle))) * qB)));
}

CQuaternion CSlerpCalculator::GetQuaternionA(HWND _hDlg)
{
	float fW = ReadFromEditBox(_hDlg, m_karrQuatABoxes[0]);
	float fI = ReadFromEditBox(_hDlg, m_karrQuatABoxes[1]);
	float fJ = ReadFromEditBox(_hDlg, m_karrQuatABoxes[2]);
	float fK = ReadFromEditBox(_hDlg, m_karrQuatABoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

CQuaternion CSlerpCalculator::GetQuaternionB(HWND _hDlg)
{
	float fW = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[0]);
	float fI = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[1]);
	float fJ = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[2]);
	float fK = ReadFromEditBox(_hDlg, m_karrQuatBBoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

void CSlerpCalculator::SetAnswerBox(HWND _hDlg, const CQuaternion& _krqAnswer)
{
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		float fElement = _krqAnswer.GetElement(szIdx);
		WriteToEditBox(_hDlg, m_karrQuatAnsBoxes.at(szIdx), fElement);
	}
}