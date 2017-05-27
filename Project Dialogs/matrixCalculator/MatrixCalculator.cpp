//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Jack Mair : Lance Chaney
// Mail			: jack.mair@mediadesign.school.nz : lance.chaney@mediadesign.school.nz
//
#include "MatrixCalculator.h"
#include "utils.h"
#include "resource.h"

CMatrixCalculator::CMatrixCalculator()
{
	m_aMatrixABoxes[0][0] = IDC_EDIT_A11;
	m_aMatrixABoxes[0][1] = IDC_EDIT_A12;
	m_aMatrixABoxes[0][2] = IDC_EDIT_A13;
	m_aMatrixABoxes[0][3] = IDC_EDIT_A14;
	m_aMatrixABoxes[1][0] = IDC_EDIT_A21;
	m_aMatrixABoxes[1][1] = IDC_EDIT_A22;
	m_aMatrixABoxes[1][2] = IDC_EDIT_A23;
	m_aMatrixABoxes[1][3] = IDC_EDIT_A24;
	m_aMatrixABoxes[2][0] = IDC_EDIT_A31;
	m_aMatrixABoxes[2][1] = IDC_EDIT_A32;
	m_aMatrixABoxes[2][2] = IDC_EDIT_A33;
	m_aMatrixABoxes[2][3] = IDC_EDIT_A34;
	m_aMatrixABoxes[3][0] = IDC_EDIT_A41;
	m_aMatrixABoxes[3][1] = IDC_EDIT_A42;
	m_aMatrixABoxes[3][2] = IDC_EDIT_A43;
	m_aMatrixABoxes[3][3] = IDC_EDIT_A44;

	m_aMatrixBBoxes[0][0] = IDC_EDIT_B11;
	m_aMatrixBBoxes[0][1] = IDC_EDIT_B12;
	m_aMatrixBBoxes[0][2] = IDC_EDIT_B13;
	m_aMatrixBBoxes[0][3] = IDC_EDIT_B14;
	m_aMatrixBBoxes[1][0] = IDC_EDIT_B21;
	m_aMatrixBBoxes[1][1] = IDC_EDIT_B22;
	m_aMatrixBBoxes[1][2] = IDC_EDIT_B23;
	m_aMatrixBBoxes[1][3] = IDC_EDIT_B24;
	m_aMatrixBBoxes[2][0] = IDC_EDIT_B31;
	m_aMatrixBBoxes[2][1] = IDC_EDIT_B32;
	m_aMatrixBBoxes[2][2] = IDC_EDIT_B33;
	m_aMatrixBBoxes[2][3] = IDC_EDIT_B34;
	m_aMatrixBBoxes[3][0] = IDC_EDIT_B41;
	m_aMatrixBBoxes[3][1] = IDC_EDIT_B42;
	m_aMatrixBBoxes[3][2] = IDC_EDIT_B43;
	m_aMatrixBBoxes[3][3] = IDC_EDIT_B44;

	m_aMatrixRBoxes[0][0] = IDC_EDIT_R11;
	m_aMatrixRBoxes[0][1] = IDC_EDIT_R12;
	m_aMatrixRBoxes[0][2] = IDC_EDIT_R13;
	m_aMatrixRBoxes[0][3] = IDC_EDIT_R14;
	m_aMatrixRBoxes[1][0] = IDC_EDIT_R21;
	m_aMatrixRBoxes[1][1] = IDC_EDIT_R22;
	m_aMatrixRBoxes[1][2] = IDC_EDIT_R23;
	m_aMatrixRBoxes[1][3] = IDC_EDIT_R24;
	m_aMatrixRBoxes[2][0] = IDC_EDIT_R31;
	m_aMatrixRBoxes[2][1] = IDC_EDIT_R32;
	m_aMatrixRBoxes[2][2] = IDC_EDIT_R33;
	m_aMatrixRBoxes[2][3] = IDC_EDIT_R34;
	m_aMatrixRBoxes[3][0] = IDC_EDIT_R41;
	m_aMatrixRBoxes[3][1] = IDC_EDIT_R42;
	m_aMatrixRBoxes[3][2] = IDC_EDIT_R43;
	m_aMatrixRBoxes[3][3] = IDC_EDIT_R44;
}

CMatrixCalculator::~CMatrixCalculator()
{
}

size_t CMatrixCalculator::GetMatrixBoxA(size_t _szRows, size_t _szColumns)
{
	return m_aMatrixABoxes[_szRows][_szColumns];
}

size_t CMatrixCalculator::GetMatrixBoxB(size_t _szRows, size_t _szColumns)
{
	return m_aMatrixBBoxes[_szRows][_szColumns];
}

size_t CMatrixCalculator::GetMatrixBoxR(size_t _szRows, size_t _szColumns)
{
	return m_aMatrixRBoxes[_szRows][_szColumns];
}

void CMatrixCalculator::SetMatrixBoxA(HWND _hDlg, float _fValue, size_t _szRows, size_t _szColumns)
{
	WriteToEditBox(_hDlg, GetMatrixBoxA(_szRows, _szColumns), _fValue);
}

void CMatrixCalculator::SetMatrixBoxB(HWND _hDlg, float _fValue, size_t _szRows, size_t _szColumns)
{
	WriteToEditBox(_hDlg, GetMatrixBoxB(_szRows, _szColumns), _fValue);
}

void CMatrixCalculator::SetMatrixBoxR(HWND _hDlg, float _fValue, size_t _szRows, size_t _szColumns)
{
	WriteToEditBox(_hDlg, GetMatrixBoxR(_szRows, _szColumns), _fValue);
}

void CMatrixCalculator:: HandleSetAtoI(HWND _hDlg) {
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			if (i == j)
			{		
				SetMatrixBoxA(_hDlg, 1, i, j);
			}
			else {
				SetMatrixBoxA(_hDlg, 0, i, j);
			}
		}
	}
}

void CMatrixCalculator::HandleSetBtoI(HWND _hDlg) {
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				SetMatrixBoxB(_hDlg, 1, i, j);
			}
			else {
				SetMatrixBoxB(_hDlg, 0, i, j);
			}
		}
	}
}

void CMatrixCalculator::DeterminantofA(HWND _hDlg) 
{
	//need code to determine the transpose of a 4x4 matrix
	//float _fDeterminant = ((GetMatrixBoxA(0, 0) * ((GetMatrixBoxA(1, 1) * GetMatrixBoxA(2, 2)) - (GetMatrixBoxA(1, 2) * GetMatrixBoxA(2, 1)))) 
	//					- (GetMatrixBoxA(0, 1) * ((GetMatrixBoxA(1, 0) * GetMatrixBoxA(2, 2)) - (GetMatrixBoxA(1, 2) *GetMatrixBoxA(2, 0)))) 
	//					+ (GetMatrixBoxA(0, 2) * ((GetMatrixBoxA(1, 0) * GetMatrixBoxA(2, 1)) - (GetMatrixBoxA(1, 1) * GetMatrixBoxA(2, 0)))));
	float _fDeterminant = 0;

	WriteToEditBox(_hDlg, IDC_EDIT_DetA, _fDeterminant);
}

void CMatrixCalculator::TransposeA(HWND _hDlg)
{
	float _tempArray[4][4];
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			_tempArray[i][j] = ReadFromEditBox(_hDlg, GetMatrixBoxA(j, i));
		}
	}

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBoxA(_hDlg, _tempArray[i][j], i, j);
		}
	}
}

void CMatrixCalculator::TransposeB(HWND _hDlg)
{
	float _tempArray[4][4];
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			_tempArray[i][j] = ReadFromEditBox(_hDlg, GetMatrixBoxB(j, i));
		}
	}

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBoxB(_hDlg, _tempArray[i][j], i, j);
		}
	}
}

void  CMatrixCalculator::ScalarMultiplyA(HWND _hDlg, float _fScalar) {
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			size_t _szScaledValue = (_fScalar * ReadFromEditBox(_hDlg, GetMatrixBoxA(i, j)));
			SetMatrixBoxA(_hDlg, _szScaledValue, i, j);
		}
	}
}

void  CMatrixCalculator::ScalarMultiplyB(HWND _hDlg, float _fScalar) {
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			size_t _szScaledValue = (_fScalar * ReadFromEditBox(_hDlg, GetMatrixBoxB(i, j)));
			SetMatrixBoxB(_hDlg, _szScaledValue, i, j);
		}
	}
}

void CMatrixCalculator::AddMatrices(HWND _hDlg) {
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBoxR(_hDlg, (ReadFromEditBox(_hDlg, GetMatrixBoxA(i, j))) + (ReadFromEditBox(_hDlg, GetMatrixBoxB(i, j))), i, j);
		}
	}
}

void CMatrixCalculator::SubtractMatrices(HWND _hDlg) {
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBoxR(_hDlg, (ReadFromEditBox(_hDlg, GetMatrixBoxA(i, j))) - (ReadFromEditBox(_hDlg, GetMatrixBoxB(i, j))), i, j);
		}
	}
}

void CMatrixCalculator::MultiplyAB(HWND _hDlg)
{
	float _ftempArray[4][4] = { 0 };
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k) {
				_ftempArray[i][j] += ReadFromEditBox(_hDlg, GetMatrixBoxA(i, k)) * ReadFromEditBox(_hDlg, GetMatrixBoxB(k, j));
			}
		}
	}

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBoxR(_hDlg, _ftempArray[i][j], i, j);
		}
	}
}

void CMatrixCalculator::MultiplyBA(HWND _hDlg)
{
	float _ftempArray[4][4] = { 0 };
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k) {
				_ftempArray[i][j] += ReadFromEditBox(_hDlg, GetMatrixBoxB(i, k)) * ReadFromEditBox(_hDlg, GetMatrixBoxA(k, j));
			}
		}
	}

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBoxR(_hDlg, _ftempArray[i][j], i, j);
		}
	}
}