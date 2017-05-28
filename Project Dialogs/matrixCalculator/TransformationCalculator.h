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
#pragma once

#ifndef TRANSFORMATION_CALCULATOR_H
#define TRANSFORMATION_CALCULATOR_H

#include <Windows.h>

class CTransformationCalculator
{
public:
	CTransformationCalculator();
	~CTransformationCalculator();

	void HandleSetI(HWND _hDlg);

	void ScaleTransformation(HWND _hDlg, float _fX, float _fY, float _fZ);
	void TranslationTransformation(HWND _hDlg, float _fX, float _fY, float _fZ);
	void RotationTransformation(HWND _hDlg, float _fX, float _fY, float _fZ, float _fAngle);
	void ReflectionTransformation(HWND _hDlg, float _fX, float _fY, float _fZ);
	void ProjectionTransformation(HWND _hDlg, float _fX, float _fY, float _fZ, float _fDistance);

private:
	void SetMatrixBox(HWND _hDlg, float _fValue, size_t _szRow, size_t _szColumn);
	size_t GetColMatrixBox(size_t _szRow, size_t _szColumn);
	size_t GetRowMatrixBox(size_t _szRow, size_t _szColumn);

	size_t m_aColMatrixBoxes[4][4];
	size_t m_aRowMatrixBoxes[4][4];
};

#endif // TRANSFORMATION_CALCULATOR_H