//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: SlerpCalculator.h
// Description	: The header file for the SlerpCalculator.cpp handles all code on the slerp calculator window
// Author		: Jack Mair : Lance Chaney
// Mail			: jack.mair@mediadesign.school.nz : lance.chaney@mediadesign.school.nz
//

#pragma once

#ifndef SLERP_CALCULATOR_H
#define SLERP_CALCULATOR_H

#include <Windows.h>

class CSlerpCalculator
{
public:
	CSlerpCalculator();
	~CSlerpCalculator();

	void SlerpAB(HWND _hDlg);
};

#endif // SLERP_CALCULATOR_H
