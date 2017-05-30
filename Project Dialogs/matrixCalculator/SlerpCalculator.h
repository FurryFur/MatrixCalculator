//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: SlerpCalculator.h
// Description	: The header file for the SlerpCalculator.cpp handles all code on the slerp calculator window
// Author		: Jack Mair : Lance Chaney
// Mail			: jack.mair@mediadesign.school.nz : lance.chaney@mediadesign.school.nz
//

#pragma once

#ifndef SLERP_CALCULATOR_H
#define SLERP_CALCULATOR_H

#include <Windows.h>
#include <array>

#include "Quaternion.h"

class CSlerpCalculator
{
public:
	CSlerpCalculator();
	~CSlerpCalculator();

	void  HandleBtnASlerpB(HWND _hDlg);

private:
	CQuaternion GetQuaternionA(HWND _hDlg);
	CQuaternion GetQuaternionB(HWND _hDlg);

	void SetAnswerBox(HWND _hDlg, const CQuaternion& _krqAnswer);

	const std::array<size_t, 4> m_karrQuatABoxes;
	const std::array<size_t, 4> m_karrQuatBBoxes;
	const std::array<size_t, 4> m_karrQuatAnsBoxes;
	const size_t                m_kszScalarTBox;
};

#endif // SLERP_CALCULATOR_H
