#pragma once

#ifndef GAUSSIAN_CALCULATOR_H
#define GAUSSIAN_CALCULATOR_H

#include <Windows.h>

#include "Matrix.h"

class CGaussianCalculator
{
public:
	CGaussianCalculator();
	~CGaussianCalculator();

private:
	CMatrix<3, 4> GetMatrix(HWND _hDlg);

	/*const std::array<size_t, 4> m_karrMatrixBoxes;
	const std::array<size_t, 4> m_karrQuatBBoxes;
	const std::array<size_t, 4> m_karrQuatAnsBoxes;
	const size_t                m_kszScalarTBox;*/
};

#endif // GUASSIAN_CALCULATOR_H