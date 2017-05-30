#pragma once

#ifndef GAUSSIAN_CALCULATOR_H
#define GAUSSIAN_CALCULATOR_H

#define NOMINMAX
#include <array>
#include <Windows.h>

#include "Matrix.h"

class CGaussianCalculator
{
public:
	CGaussianCalculator();
	~CGaussianCalculator();

	void HandleBtnApplyRowMultiply(HWND _hDlg);
	void HandleBtnApplyRowSwap(HWND _hDlg);
	void HandleBtnApplyAddMultipleOfRowToRow(HWND _hDlg);
	void HandleBtnRowEchelon(HWND _hDlg);

private:
	CMatrix<3, 4> GetMatrix(HWND _hDlg);
	void SetMatrixBoxes(HWND _hDlg, const CMatrix<3, 4>&);
	size_t m_szCurPivotRow;
	size_t m_szCurPivotCol;
	int m_iCurEliminationDir;

	const std::array<std::array<size_t, 4>, 3> m_k2darrMatrixBoxes;
	const std::array<size_t, 2> m_karrMultiplyRowBoxes;
	const std::array<size_t, 2> m_karrSwapRowBoxes;
	const std::array<size_t, 3> m_karrAddMultipleOfRowBoxes;
};

#endif // GUASSIAN_CALCULATOR_H