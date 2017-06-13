#include "GaussianCalculator.h"
#include "resource.h"
#include "utils.h"

CGaussianCalculator::CGaussianCalculator() :
	m_k2darrMatrixBoxes{ {
		{ IDC_EDIT1, IDC_EDIT2, IDC_EDIT3, IDC_EDIT4 },
		{ IDC_EDIT5, IDC_EDIT6, IDC_EDIT7, IDC_EDIT8 },
		{ IDC_EDIT9, IDC_EDIT10, IDC_EDIT11, IDC_EDIT12 },
	} },
	m_karrMultiplyRowBoxes{ IDC_EDIT13, IDC_EDIT14 },
	m_karrSwapRowBoxes{ IDC_EDIT16, IDC_EDIT17 },
	m_karrAddMultipleOfRowBoxes{ IDC_EDIT19, IDC_EDIT20, IDC_EDIT22 },
	m_szCurPivotRow(0),
	m_szCurPivotCol(0),
	m_iCurEliminationDir(1)
{
}


CGaussianCalculator::~CGaussianCalculator()
{
}

void CGaussianCalculator::HandleBtnApplyRowMultiply(HWND _hDlg)
{
	CMatrix<3, 4> matResult = GetMatrix(_hDlg);
	size_t szRow = static_cast<size_t>(ReadFromEditBox(_hDlg, m_karrMultiplyRowBoxes[0]));
	float fScalar = ReadFromEditBox(_hDlg, m_karrMultiplyRowBoxes[1]);

	if (szRow < 3)
	{
		matResult.MultiplyRow(szRow, fScalar);

		SetMatrixBoxes(_hDlg, matResult);

		// TODO: Check if in Row Echelon Form
		// TODO: Check if in Reduced Row Echelon Form
	}
}

void CGaussianCalculator::HandleBtnApplyRowSwap(HWND _hDlg)
{
	CMatrix<3, 4> matResult = GetMatrix(_hDlg);
	size_t szRow1 = static_cast<size_t>(ReadFromEditBox(_hDlg, m_karrSwapRowBoxes[0]));
	size_t szRow2 = static_cast<size_t>(ReadFromEditBox(_hDlg, m_karrSwapRowBoxes[1]));

	if (szRow1 < 3 && szRow2 < 3)
	{
		matResult.SwapRow(szRow1, szRow2);

		SetMatrixBoxes(_hDlg, matResult);

		// TODO: Check if in Row Echelon Form
		// TODO: Check if in Reduced Row Echelon Form
	}
}

void CGaussianCalculator::HandleBtnApplyAddMultipleOfRowToRow(HWND _hDlg)
{
	CMatrix<3, 4> matResult = GetMatrix(_hDlg);
	float fScalar = ReadFromEditBox(_hDlg, m_karrAddMultipleOfRowBoxes[0]);
	size_t szRowSrc = static_cast<size_t>(ReadFromEditBox(_hDlg, m_karrAddMultipleOfRowBoxes[1]));
	size_t szRowDst = static_cast<size_t>(ReadFromEditBox(_hDlg, m_karrAddMultipleOfRowBoxes[2]));

	if (szRowSrc < 3 && szRowDst < 3)
	{
		matResult.AddMultipleOfRowToRow(fScalar, szRowSrc, szRowDst);

		SetMatrixBoxes(_hDlg, matResult);

		// TODO: Check if in Row Echelon Form
		// TODO: Check if in Reduced Row Echelon Form
	}
}

void CGaussianCalculator::HandleBtnGaussianElimStep(HWND _hDlg)
{
 	CMatrix<3, 4> matResult = GetMatrix(_hDlg);
	int iEliminationDirection = CMatrix<3, 4>::GaussianElimStep(matResult);

	SetMatrixBoxes(_hDlg, matResult);

	if (CMatrix<3, 4>::IsInReducedRowEchelonForm(matResult))
	{
		MessageBoxA(_hDlg, "The matrix is now in reduced row echelon form", "Matrix Form", MB_OK | MB_ICONINFORMATION);
	}
	else if (CMatrix<3, 4>::IsInEchelonForm(matResult) && iEliminationDirection == 1)
	{
		MessageBoxA(_hDlg, "The matrix is now in echelon form", "Matrix Form", MB_OK | MB_ICONINFORMATION);
	}
}

CMatrix<3, 4> CGaussianCalculator::GetMatrix(HWND _hDlg)
{
	CMatrix<3, 4> matResult;
	for (size_t r = 0; r < 3; ++r)
	{
		for (size_t c = 0; c < 4; ++c)
		{
			float val = ReadFromEditBox(_hDlg, m_k2darrMatrixBoxes[r][c]);
			matResult.SetElement(r, c, val);
		}
	}
	return matResult;
}

void CGaussianCalculator::SetMatrixBoxes(HWND _hDlg, const CMatrix<3, 4>& _rkmat)
{
	for (size_t r = 0; r < 3; ++r)
	{
		for (size_t c = 0; c < 4; ++c)
		{
			WriteToEditBox(_hDlg, m_k2darrMatrixBoxes[r][c], _rkmat.GetElement(r, c));
		}
	}
}
