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


CSlerpCalculator::CSlerpCalculator(HWND _hDlg) :
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
	m_hDlg = _hDlg;
	m_aRMatrixBoxes[0][0] = IDC_EDIT34;
	m_aRMatrixBoxes[0][1] = IDC_EDIT35;
	m_aRMatrixBoxes[0][2] = IDC_EDIT36;
	m_aRMatrixBoxes[0][3] = IDC_EDIT37;
	m_aRMatrixBoxes[1][0] = IDC_EDIT38;
	m_aRMatrixBoxes[1][1] = IDC_EDIT39;
	m_aRMatrixBoxes[1][2] = IDC_EDIT40;
	m_aRMatrixBoxes[1][3] = IDC_EDIT41;
	m_aRMatrixBoxes[2][0] = IDC_EDIT42;
	m_aRMatrixBoxes[2][1] = IDC_EDIT43;
	m_aRMatrixBoxes[2][2] = IDC_EDIT44;
	m_aRMatrixBoxes[2][3] = IDC_EDIT45;
	m_aRMatrixBoxes[3][0] = IDC_EDIT46;
	m_aRMatrixBoxes[3][1] = IDC_EDIT47;
	m_aRMatrixBoxes[3][2] = IDC_EDIT48;
	m_aRMatrixBoxes[3][3] = IDC_EDIT49;
}


CSlerpCalculator::~CSlerpCalculator()
{
}

void CSlerpCalculator::HandleBtnASlerpB() {
	CQuaternion qA = GetQuaternionA();
	CQuaternion qB = GetQuaternionB();
	float _fAngle = acosf((qA.Dot(qB)) / (qA.Magnitude() * qB.Magnitude()));
	//checks to see if the angle is negative. if so makes it positive.
	if (_fAngle < 0)
	{
		_fAngle = acosf((qA.Dot((-qB))) / (qA.Magnitude() * (-qB).Magnitude()));
	}
	//will perform a SLERP if the angle is not tiny
	if(_fAngle > 0.01)
	{
		SetAnswerBox(((((sinf((1 - m_kszScalarTBox) * _fAngle)) / (sinf(_fAngle))) * qA) + (((sinf(m_kszScalarTBox * _fAngle)) / (sinf(_fAngle))) * qB)));
	}
	//otherwise it will perform a LERP
	else
	{
		SetAnswerBox(((1 - m_kszScalarTBox) * qA) + (m_kszScalarTBox * qB));
	}
}

CQuaternion CSlerpCalculator::GetQuaternionA()
{
	float fW = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[0]);
	float fI = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[1]);
	float fJ = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[2]);
	float fK = ReadFromEditBox(m_hDlg, m_karrQuatABoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

CQuaternion CSlerpCalculator::GetQuaternionB()
{
	float fW = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[0]);
	float fI = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[1]);
	float fJ = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[2]);
	float fK = ReadFromEditBox(m_hDlg, m_karrQuatBBoxes[3]);
	return CQuaternion(fW, fI, fJ, fK);
}

void CSlerpCalculator::SetAnswerBox(const CQuaternion& _krqAnswer)
{
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		float fElement = _krqAnswer.GetElement(szIdx);
		WriteToEditBox(m_hDlg, m_karrQuatAnsBoxes.at(szIdx), fElement);
	}
}

std::array<size_t, 4> CSlerpCalculator::GetAQuaternion()
{
	return m_karrQuatABoxes;
}

std::array<size_t, 4> CSlerpCalculator::GetBQuaternion()
{
	return m_karrQuatBBoxes;
}

std::array<size_t, 4> CSlerpCalculator::GetRQuaternion()
{
	return m_karrQuatAnsBoxes;
}


void CSlerpCalculator::ConvertToMatrix(const std::array<size_t, 4> _karrQuatBoxes)
{
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][0], ReadFromEditBox(m_hDlg, _karrQuatBoxes[0]));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][1], ReadFromEditBox(m_hDlg, _karrQuatBoxes[1]));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][2], ReadFromEditBox(m_hDlg, _karrQuatBoxes[2]));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][3], ReadFromEditBox(m_hDlg, _karrQuatBoxes[3]));
				   
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][0], -(ReadFromEditBox(m_hDlg, _karrQuatBoxes[1])));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][1], ReadFromEditBox(m_hDlg, _karrQuatBoxes[0]));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][2], -(ReadFromEditBox(m_hDlg, _karrQuatBoxes[3])));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][3], ReadFromEditBox(m_hDlg, _karrQuatBoxes[2]));
				   
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][0], -(ReadFromEditBox(m_hDlg, _karrQuatBoxes[2])));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][1], ReadFromEditBox(m_hDlg, _karrQuatBoxes[3]));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][2], ReadFromEditBox(m_hDlg, _karrQuatBoxes[0]));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][3], -(ReadFromEditBox(m_hDlg, _karrQuatBoxes[1])));
				   
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][0], -(ReadFromEditBox(m_hDlg, _karrQuatBoxes[3])));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][1], -(ReadFromEditBox(m_hDlg, _karrQuatBoxes[2])));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][2], ReadFromEditBox(m_hDlg, _karrQuatBoxes[1]));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][3], ReadFromEditBox(m_hDlg, _karrQuatBoxes[0]));
}