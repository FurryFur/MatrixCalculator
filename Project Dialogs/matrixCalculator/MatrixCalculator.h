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
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__MATRIXCALCULATOR_H__)
#define __MATRIXCALCULATOR_H__

#include <Windows.h>
#include <vector>

class CMatrixCalculator
{
public:
	CMatrixCalculator();
	~CMatrixCalculator();

	void HandleSetAtoI(HWND _hDlg);
	void HandleSetBtoI(HWND _hDlg);

private:
	void SetMatrixBoxA(HWND _hDlg, float _fValue, size_t _szRows, size_t _szColumns);
	void SetMatrixBoxB(HWND _hDlg, float _fValue, size_t _szRows, size_t _szColumns);
	size_t GetMatrixBoxA(size_t _szRows, size_t _szColumns);
	size_t GetMatrixBoxB(size_t _szRows, size_t _szColumns);
	std::vector<size_t> m_vecMatrixABoxes;
	std::vector<size_t> m_vecMatrixBBoxes;

};

#endif  //__MATRIXCALCULATOR_H__