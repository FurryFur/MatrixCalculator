#pragma once

#ifndef QUATERNION_CALCULATOR_H
#define QUATERNION_CALCULATOR_H

#include <Windows.h>
#include <array>

#include "Quaternion.h"

class CQuaternionCalculator
{
public:
	CQuaternionCalculator();
	~CQuaternionCalculator();

	void HandleBtnAPlusB(HWND _hDlg);
	void HandleBtnAMinusB(HWND _hDlg);
	void HandleBtnBMinusA(HWND _hDlg);
	void HandleBtnATimesB(HWND _hDlg);
	void HandleBtnBTimesA(HWND _hDlg);
	void HandleBtnADotB(HWND _hDlg);
	void HandleBtnAConjugate(HWND _hDlg);
	void HandleBtnBConjugate(HWND _hDlg);
	void HandleBtnMagnitudeOfA(HWND _hDlg);
	void HandleBtnMagnitudeOfB(HWND _hDlg);
	void HandleBtnAInverse(HWND _hDlg);
	void HandleBtnBInverse(HWND _hDlg);
	void HandleBtnTTimesA(HWND _hDlg);
	void HandleBtnTTimesB(HWND _hDlg);

private:
	CQuaternion GetQuaternionA(HWND _hDlg);
	CQuaternion GetQuaternionB(HWND _hDlg);

	void SetAnswerBox(HWND _hDlg, const CQuaternion& _krqAnswer);

	const std::array<size_t, 4> m_karrQuatABoxes;
	const std::array<size_t, 4> m_karrQuatBBoxes;
	const std::array<size_t, 4> m_karrQuatAnsBoxes;
	const size_t                m_kszScalarTBox;
};

#endif // QUATERNION_CALCULATOR_H