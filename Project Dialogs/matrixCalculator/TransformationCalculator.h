//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: TransformationCalculator.h
// Description	: Header file for Transformation.cpp. Handles all the maths during the transformation matrix window
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

	void ScaleTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ);
	void TranslationTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ);
	void RotationTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ, const float& _fAngle);
	void ReflectionTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ);
	void ProjectionTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ, const float& _fDistance);

private:
	void SetMatrixBox(HWND _hDlg, const float& _fValue, const size_t& _szRow, const size_t& _szColumn);
	size_t GetColMatrixBox(const size_t& _szRow, const size_t& _szColumn);
	size_t GetRowMatrixBox(const size_t& _szRow, const size_t& _szColumn);

	size_t m_aColMatrixBoxes[4][4];
	size_t m_aRowMatrixBoxes[4][4];
};

#endif // TRANSFORMATION_CALCULATOR_H