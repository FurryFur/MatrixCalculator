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
	m_vecMatrixABoxes.push_back(IDC_EDIT_A11);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A12);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A13);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A14);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A21);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A22);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A23);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A24);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A31);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A32);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A33);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A34);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A41);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A42);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A43);
	m_vecMatrixABoxes.push_back(IDC_EDIT_A44);

	m_vecMatrixBBoxes.push_back(IDC_EDIT_B11);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B12);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B13);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B14);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B21);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B22);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B23);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B24);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B31);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B32);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B33);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B34);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B41);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B42);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B43);
	m_vecMatrixBBoxes.push_back(IDC_EDIT_B44);
}

CMatrixCalculator::~CMatrixCalculator()
{
}

size_t CMatrixCalculator::GetMatrixBoxA(size_t _szRows, size_t _szColumns)
{
	return m_vecMatrixABoxes.at(_szRows * 4 + _szColumns);
}

size_t CMatrixCalculator::GetMatrixBoxB(size_t _szRows, size_t _szColumns)
{
	return m_vecMatrixBBoxes.at(_szRows * 4 + _szColumns);
}

void CMatrixCalculator::SetMatrixBoxA(HWND _hDlg, float _fValue, size_t _szRows, size_t _szColumns)
{
	WriteToEditBox(_hDlg, GetMatrixBoxA(_szRows, _szColumns), _fValue);
}

void CMatrixCalculator::SetMatrixBoxB(HWND _hDlg, float _fValue, size_t _szRows, size_t _szColumns)
{
	WriteToEditBox(_hDlg, GetMatrixBoxB(_szRows, _szColumns), _fValue);
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