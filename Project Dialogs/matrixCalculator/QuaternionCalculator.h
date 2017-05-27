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

private:
	CQuaternion GetQuaternionA(HWND _hDlg);
	CQuaternion GetQuaternionB(HWND _hDlg);

	void SetAnswerBox(HWND _hDlg, const CQuaternion& _krqAnswer);

	const std::array<size_t, 4> m_karrQuatABoxes;
	const std::array<size_t, 4> m_karrQuatBBoxes;
	const std::array<size_t, 4> m_karrQuatAnsBoxes;
};

#endif // QUATERNION_CALCULATOR_H