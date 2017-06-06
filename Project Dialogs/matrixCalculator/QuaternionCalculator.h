#pragma once

#ifndef QUATERNION_CALCULATOR_H
#define QUATERNION_CALCULATOR_H

#include <Windows.h>
#include <array>

#include "Quaternion.h"

class CQuaternionCalculator
{
public:
	CQuaternionCalculator(HWND _hDlg);
	~CQuaternionCalculator();

	void HandleBtnAPlusB();
	void HandleBtnAMinusB();
	void HandleBtnBMinusA();
	void HandleBtnATimesB();
	void HandleBtnBTimesA();
	void HandleBtnADotB();
	void HandleBtnAConjugate();
	void HandleBtnBConjugate();
	void HandleBtnMagnitudeOfA();
	void HandleBtnMagnitudeOfB();
	void HandleBtnAInverse();
	void HandleBtnBInverse();
	void HandleBtnTTimesA();
	void HandleBtnTTimesB();

private:
	CQuaternion GetQuaternionA();
	CQuaternion GetQuaternionB();

	void SetAnswerBox(const CQuaternion& _krqAnswer);


	HWND m_hDlg;
	const std::array<size_t, 4> m_karrQuatABoxes;
	const std::array<size_t, 4> m_karrQuatBBoxes;
	const std::array<size_t, 4> m_karrQuatAnsBoxes;
	const size_t                m_kszScalarTBox;
};

#endif // QUATERNION_CALCULATOR_H