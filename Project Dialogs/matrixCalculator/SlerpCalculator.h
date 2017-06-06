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
	CSlerpCalculator(HWND _hDlg);
	~CSlerpCalculator();

	void  HandleBtnASlerpB();

	std::array<size_t, 4> GetAQuaternion();
	std::array<size_t, 4> GetBQuaternion();
	std::array<size_t, 4> GetRQuaternion();

	void ConvertToMatrix(const std::array<size_t, 4> _karrQuatBoxes);

private:
	CQuaternion GetQuaternionA();
	CQuaternion GetQuaternionB();

	void SetAnswerBox(const CQuaternion& _krqAnswer);

	const std::array<size_t, 4> m_karrQuatABoxes;
	const std::array<size_t, 4> m_karrQuatBBoxes;
	const std::array<size_t, 4> m_karrQuatAnsBoxes;
	const size_t                m_kszScalarTBox;

	HWND m_hDlg;

	size_t m_aRMatrixBoxes[4][4];
};

#endif // SLERP_CALCULATOR_H
