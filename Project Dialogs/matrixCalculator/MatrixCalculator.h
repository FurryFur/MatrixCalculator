//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: MatrixCalculator.h
// Description	: Header file for MatrixCalculator.cpp. Handles all the maths during the Matrix calculator window
// Author		: Jack Mair : Lance Chaney
// Mail			: jack.mair@mediadesign.school.nz : lance.chaney@mediadesign.school.nz
//

#pragma once

#if !defined(__MATRIXCALCULATOR_H__)
#define __MATRIXCALCULATOR_H__

#include <Windows.h>

class CMatrixCalculator
{
public:
	CMatrixCalculator();
	~CMatrixCalculator();

	void HandleSetAtoI(HWND _hDlg);
	void HandleSetBtoI(HWND _hDlg);

	void DeterminantofA(HWND _hDlg);
	void DeterminantofB(HWND _hDlg);

	void InverseofA(HWND _hDlg);
	void InverseofB(HWND _hDlg);

	void TransposeA(HWND _hDlg);
	void TransposeB(HWND _hDlg);

	void ScalarMultiplyA(HWND _hDlg, const float& _fScalar);
	void ScalarMultiplyB(HWND _hDlg, const float& _fScalar);

	void AddMatrices(HWND _hDlg);
	void SubtractMatrices(HWND _hDlg);

	void MultiplyAB(HWND _hDlg);
	void MultiplyBA(HWND _hDlg);

private:
	void SetMatrixBoxA(HWND _hDlg, const float& _fValue, const size_t& _szRows, const size_t& _szColumns);
	void SetMatrixBoxB(HWND _hDlg, const float& _fValue, const size_t& _szRows, const size_t& _szColumns);
	void SetMatrixBoxR(HWND _hDlg, const float& _fValue, const size_t& _szRows, const size_t& _szColumns);
	size_t GetMatrixBoxA(const size_t& _szRows, const size_t& _szColumns);
	size_t GetMatrixBoxB(const size_t& _szRows, const size_t& _szColumns);
	size_t GetMatrixBoxR(const size_t& _szRows, const size_t& _szColumns);

	size_t m_aMatrixABoxes[4][4];
	size_t m_aMatrixBBoxes[4][4];
	size_t m_aMatrixRBoxes[4][4];
};

#endif  //__MATRIXCALCULATOR_H__