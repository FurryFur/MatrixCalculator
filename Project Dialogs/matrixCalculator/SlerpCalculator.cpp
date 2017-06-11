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
		IDC_EDIT4,     // The real component is placed in the last edit box
		IDC_EDIT1,
		IDC_EDIT2,
		IDC_EDIT3,
	},
	m_karrQuatBBoxes{
		IDC_EDIT8,     // The real component is placed in the last edit box
		IDC_EDIT5,
		IDC_EDIT6,
		IDC_EDIT7,
	},
	m_karrQuatAnsBoxes{
	IDC_EDIT13,    // The real component is placed in the last edit box
	IDC_EDIT10,
	IDC_EDIT11,
	IDC_EDIT12,
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

CQuaternion Normalize(CQuaternion qA)
{
	float qAMag = sqrt(pow(qA.GetW(), 2) + pow(qA.GetI(), 2) + pow(qA.GetJ(), 2) + pow(qA.GetK(), 2));
	//Normalize the quaternions first
	qA.SetW(qA.GetW() / qAMag);
	qA.SetI(qA.GetI() / qAMag);
	qA.SetJ(qA.GetJ() / qAMag);
	qA.SetK(qA.GetK() / qAMag);
	return qA;
}

void CSlerpCalculator::HandleBtnASlerpB() {
	CQuaternion qA = GetQuaternionA();
	qA = Normalize(qA);
	float qAMag = sqrt(pow(qA.GetW(), 2) + pow(qA.GetI(), 2) + pow(qA.GetJ(), 2) + pow(qA.GetK(), 2));
	CQuaternion qB = GetQuaternionB();
	qB = Normalize(qB);
	float qBMag = sqrt(pow(qB.GetW(), 2) + pow(qB.GetI(), 2) + pow(qB.GetJ(), 2) + pow(qB.GetK(), 2));

	float _fAngle = acosf((qA.Dot(qB)) / (qAMag * qBMag));
	//checks to see if the angle is negative. if so makes it positive.
	if (_fAngle < 0)
	{
		_fAngle = acosf((qA.Dot((-qB))) / (qAMag * qBMag));
	}
	//will perform a SLERP if the angle is not tiny
	if(_fAngle > 0.01)
	{
		CQuaternion qSr = ((((sinf((1 - ReadFromEditBox(m_hDlg, m_kszScalarTBox)) * _fAngle)) / (sinf(_fAngle))) * qA) + (((sinf(ReadFromEditBox(m_hDlg, m_kszScalarTBox) * _fAngle)) / (sinf(_fAngle))) * qB));
		qSr = Normalize(qSr);
		SetAnswerBox(qSr);
	}
	//otherwise it will perform a LERP
	else
	{
		CQuaternion qLr = ((1 - ReadFromEditBox(m_hDlg, m_kszScalarTBox)) * qA) + (ReadFromEditBox(m_hDlg, m_kszScalarTBox) * qB);
		qLr = Normalize(qLr);
		SetAnswerBox(qLr);
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

CQuaternion CSlerpCalculator::GetQuaternionR()
{
	float fW = ReadFromEditBox(m_hDlg, m_karrQuatAnsBoxes[0]);
	float fI = ReadFromEditBox(m_hDlg, m_karrQuatAnsBoxes[1]);
	float fJ = ReadFromEditBox(m_hDlg, m_karrQuatAnsBoxes[2]);
	float fK = ReadFromEditBox(m_hDlg, m_karrQuatAnsBoxes[3]);
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

void CSlerpCalculator::ConvertAToMatrix()
{
	ConvertToMatrix(GetQuaternionA());
}

void CSlerpCalculator::ConvertBToMatrix()
{
	ConvertToMatrix(GetQuaternionB());
}

void CSlerpCalculator::ConvertRToMatrix()
{
	ConvertToMatrix(GetQuaternionR());
}


void CSlerpCalculator::ConvertToMatrix(const CQuaternion& _krqQuat)
{
	//normalize the quaternion
	CQuaternion kN = _krqQuat;
	kN = Normalize(kN);

	float qw = kN.GetW();
	float qx = kN.GetI();
	float qy = kN.GetJ();
	float qz = kN.GetK();


	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][0], 1 - 2 * qy * qy - 2 * qz * qz);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][1], 2 * qx*qy - 2 * qz*qw);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][2], 2 * qx*qz + 2 * qy*qw);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[0][3], 0);
				   
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][0], 2 * qx*qy + 2 * qz*qw);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][1], 1 - 2 * pow(qx, 2.0f) - 2 * pow(qz, 2.0f));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][2], 2 * qy*qz - 2 * qx*qw);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[1][3], 0);
				   
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][0], 2 * qx*qz - 2 * qy*qw);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][1], 2 * qy*qz + 2 * qx*qw);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][2], 1 - 2 * pow(qx, 2) - 2 * pow(qy, 2.0f));
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[2][3], 0);
				   
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][0], 0);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][1], 0);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][2], 0);
	WriteToEditBox(m_hDlg, m_aRMatrixBoxes[3][3], 1);
}