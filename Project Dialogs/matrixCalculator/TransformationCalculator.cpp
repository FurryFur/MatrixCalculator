//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: TransformationCalculator.cpp
// Description	: Handles all the maths during the transformation matrix window
// Author		: Jack Mair : Lance Chaney
// Mail			: jack.mair@mediadesign.school.nz : lance.chaney@mediadesign.school.nz
//

#include <math.h>

#include "TransformationCalculator.h"
#include "utils.h"
#include "resource.h"
#include "Matrix.h"

CTransformationCalculator::CTransformationCalculator()
{
	m_aColMatrixBoxes[0][0] = IDC_EDITC11;
	m_aColMatrixBoxes[0][1] = IDC_EDITC12;
	m_aColMatrixBoxes[0][2] = IDC_EDITC13;
	m_aColMatrixBoxes[0][3] = IDC_EDITC14;
	m_aColMatrixBoxes[1][0] = IDC_EDITC21;
	m_aColMatrixBoxes[1][1] = IDC_EDITC22;
	m_aColMatrixBoxes[1][2] = IDC_EDITC23;
	m_aColMatrixBoxes[1][3] = IDC_EDITC24;
	m_aColMatrixBoxes[2][0] = IDC_EDITC31;
	m_aColMatrixBoxes[2][1] = IDC_EDITC32;
	m_aColMatrixBoxes[2][2] = IDC_EDITC33;
	m_aColMatrixBoxes[2][3] = IDC_EDITC34;
	m_aColMatrixBoxes[3][0] = IDC_EDITC41;
	m_aColMatrixBoxes[3][1] = IDC_EDITC42;
	m_aColMatrixBoxes[3][2] = IDC_EDITC43;
	m_aColMatrixBoxes[3][3] = IDC_EDITC44;

	m_aRowMatrixBoxes[0][0] = IDC_EDITR11;
	m_aRowMatrixBoxes[0][1] = IDC_EDITR12;
	m_aRowMatrixBoxes[0][2] = IDC_EDITR13;
	m_aRowMatrixBoxes[0][3] = IDC_EDITR14;
	m_aRowMatrixBoxes[1][0] = IDC_EDITR21;
	m_aRowMatrixBoxes[1][1] = IDC_ED1TR22;
	m_aRowMatrixBoxes[1][2] = IDC_EDITR23;
	m_aRowMatrixBoxes[1][3] = IDC_EDITR24;
	m_aRowMatrixBoxes[2][0] = IDC_EDITR31;
	m_aRowMatrixBoxes[2][1] = IDC_EDITR32;
	m_aRowMatrixBoxes[2][2] = IDC_EDITR33;
	m_aRowMatrixBoxes[2][3] = IDC_EDITR34;
	m_aRowMatrixBoxes[3][0] = IDC_EDITR41;
	m_aRowMatrixBoxes[3][1] = IDC_EDITR42;
	m_aRowMatrixBoxes[3][2] = IDC_EDITR43;
	m_aRowMatrixBoxes[3][3] = IDC_EDITR44;

}


CTransformationCalculator::~CTransformationCalculator()
{
}

size_t CTransformationCalculator::GetColMatrixBox(const size_t& _szRows, const size_t& _szColumns)
{
	return m_aColMatrixBoxes[_szRows][_szColumns];
}

size_t CTransformationCalculator::GetRowMatrixBox(const size_t& _szRows, const size_t& _szColumns)
{
	return m_aRowMatrixBoxes[_szRows][_szColumns];
}

void CTransformationCalculator::SetMatrixBox(HWND _hDlg, const float& _fValue, const size_t& _szRows, const size_t& _szColumns)
{
	WriteToEditBox(_hDlg, GetColMatrixBox(_szRows, _szColumns), _fValue);

	WriteToEditBox(_hDlg, GetRowMatrixBox(_szColumns, _szRows), _fValue);
}

void CTransformationCalculator::HandleSetI(HWND _hDlg) {
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				SetMatrixBox(_hDlg, 1, i, j);
			}
			else {
				SetMatrixBox(_hDlg, 0, i, j);
			}
		}
	}
}

void CTransformationCalculator::ScaleTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ) {
	CVec3 scaleVector;
	
	scaleVector.SetElement(0, 0, _fX);
	scaleVector.SetElement(1, 0, _fY);
	scaleVector.SetElement(2, 0, _fZ);

	CMatrix4 scaleMatrix;
	CMatrix4 matrix;

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			matrix.SetElement(i, j, ReadFromEditBox(_hDlg, GetColMatrixBox(i, j)));
		}
	}

	CMatrix4 resultmatrix;
	CMatrix4::Scale(scaleVector, scaleMatrix);
	CMatrix4::Multiply(scaleMatrix, matrix, resultmatrix);

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBox(_hDlg, resultmatrix.GetElement(i, j), i, j);
		}
	}

}

void CTransformationCalculator::TranslationTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ) {
	CVec3 translationVector;

	translationVector.SetElement(0, 0, _fX);
	translationVector.SetElement(1, 0, _fY);
	translationVector.SetElement(2, 0, _fZ);

	CMatrix4 translationMatrix;
	CMatrix4 matrix;

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			matrix.SetElement(i, j, ReadFromEditBox(_hDlg, GetColMatrixBox(i, j)));
		}
	}

	CMatrix4 resultmatrix;
	CMatrix4::Translate(translationVector, translationMatrix);
	CMatrix4::Multiply(translationMatrix, matrix, resultmatrix);

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			SetMatrixBox(_hDlg, resultmatrix.GetElement(i, j), i, j);
		}
	}

}

void CTransformationCalculator::RotationTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ, const float& _fAngle) {
	//normalize the points
	if ((sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f) != 0)))
	{
		float _fnX = _fX / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));
		float _fnY = _fY / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));
		float _fnZ = _fZ / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));

		//create rotation matrix
		CMatrix4 rotationMatrix;

		rotationMatrix.SetElement(0, 0, (powf(_fnX, 2.0f) * (1 - cosf(_fAngle)) + cosf(_fAngle)));
		rotationMatrix.SetElement(0, 1, (_fnX * _fnY * (1 - cosf(_fAngle)) - _fnZ * sinf(_fAngle)));
		rotationMatrix.SetElement(0, 2, (_fnX * _fnZ * (1 - cosf(_fAngle)) + _fnY * sinf(_fAngle)));

		rotationMatrix.SetElement(1, 0, (_fnX * _fnY * (1 - cosf(_fAngle)) + _fnZ * sinf(_fAngle)));
		rotationMatrix.SetElement(1, 1, (powf(_fnY, 2.0f) * (1 - cosf(_fAngle)) + cosf(_fAngle)));
		rotationMatrix.SetElement(1, 2, (_fnY * _fnZ * (1 - cosf(_fAngle)) - _fnX * sinf(_fAngle)));

		rotationMatrix.SetElement(2, 0, (_fnX * _fnZ * (1 - cosf(_fAngle)) - _fnY * sinf(_fAngle)));
		rotationMatrix.SetElement(2, 1, (_fnY * _fnZ * (1 - cosf(_fAngle)) + _fnX * sinf(_fAngle)));
		rotationMatrix.SetElement(2, 2, (powf(_fnZ, 2.0f) * (1 - cos(_fAngle)) + cosf(_fAngle)));

		rotationMatrix.SetElement(0, 3, 0);
		rotationMatrix.SetElement(1, 3, 0);
		rotationMatrix.SetElement(2, 3, 0);
		rotationMatrix.SetElement(3, 0, 0);
		rotationMatrix.SetElement(3, 1, 0);
		rotationMatrix.SetElement(3, 2, 0);
		rotationMatrix.SetElement(3, 3, 1);

		//convert current matrix into one that can multiply
		CMatrix4 matrix;

		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				matrix.SetElement(i, j, ReadFromEditBox(_hDlg, GetColMatrixBox(i, j)));
			}
		}

		CMatrix4 resultmatrix;
		CMatrix4::Multiply(rotationMatrix, matrix, resultmatrix);

		//print new matrix
		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				SetMatrixBox(_hDlg, resultmatrix.GetElement(i, j), i, j);
			}
		}
	}
}

void CTransformationCalculator::ReflectionTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ) {
	//normalize the points
	if ((sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f) != 0)))
	{
		float _fnX = _fX / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));
		float _fnY = _fY / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));
		float _fnZ = _fZ / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));
											 
		//create rotation matrix
		CMatrix4 reflectionMatrix;

		reflectionMatrix.SetElement(0, 0, (1 - (2 * powf(_fnX, 2.0f))));
		reflectionMatrix.SetElement(0, 1, (-2 * _fnX * _fnY));
		reflectionMatrix.SetElement(0, 2, (-2 * _fnX * _fnZ));

		reflectionMatrix.SetElement(1, 0, (-2 * _fnX * _fnY));
		reflectionMatrix.SetElement(1, 1, (1 - (2 * powf(_fnY, 2.0f))));
		reflectionMatrix.SetElement(1, 2, (-2 * _fnY * _fnZ));

		reflectionMatrix.SetElement(2, 0, (-2 * _fnX * _fnZ));
		reflectionMatrix.SetElement(2, 1, (-2 * _fnY * _fnZ));
		reflectionMatrix.SetElement(2, 2, (1 - (2 * powf(_fnZ, 2.0f))));

		reflectionMatrix.SetElement(0, 3, 0);
		reflectionMatrix.SetElement(1, 3, 0);
		reflectionMatrix.SetElement(2, 3, 0);
		reflectionMatrix.SetElement(3, 0, 0);
		reflectionMatrix.SetElement(3, 1, 0);
		reflectionMatrix.SetElement(3, 2, 0);
		reflectionMatrix.SetElement(3, 3, 1);

		//convert current matrix into one that can multiply
		CMatrix4 matrix;

		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				matrix.SetElement(i, j, ReadFromEditBox(_hDlg, GetColMatrixBox(i, j)));
			}
		}

		CMatrix4 resultmatrix;
		CMatrix4::Multiply(reflectionMatrix, matrix, resultmatrix);

		//print the new matrix
		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				//if really close to zero make zero. 
				if (resultmatrix.GetElement(i, j) <= 0.0005f && resultmatrix.GetElement(i, j) >= -0.0005f)
				{
					resultmatrix.SetElement(i, j, 0);
				}
				SetMatrixBox(_hDlg, resultmatrix.GetElement(i, j), i, j);
			}
		}
	}
}

void CTransformationCalculator::ProjectionTransformation(HWND _hDlg, const float& _fX, const float& _fY, const float& _fZ, const float& _fDistance) {
	if ((sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f) != 0)))
	{
		CMatrix4 projectionMatrix;

		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				projectionMatrix.SetElement(i, j, 0);
			}
		}

		projectionMatrix.SetElement(0, 0, 1);
		projectionMatrix.SetElement(1, 1, 1);
		projectionMatrix.SetElement(2, 2, 1);
		projectionMatrix.SetElement(3, 2, 1 / _fDistance);

		CMatrix4 rotationMatrix;
		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				rotationMatrix.SetElement(i, j, 0);
			}
		}

		float _fnX = _fX / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));
		float _fnY = _fY / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));
		float _fnZ = _fZ / (sqrtf(powf(_fX, 2.0f) + powf(_fY, 2.0f) + powf(_fZ, 2.0f)));

		rotationMatrix.SetElement(2, 0, _fnX);
		rotationMatrix.SetElement(2, 1, _fnY);
		rotationMatrix.SetElement(2, 2, _fnZ);
		rotationMatrix.SetElement(3, 3, 1);

		//convert current matrix into one that can multiply
		CMatrix4 matrix;

		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				matrix.SetElement(i, j, ReadFromEditBox(_hDlg, GetColMatrixBox(i, j)));
			}
		}

		CMatrix4 PRmatrix;
		CMatrix4::Multiply(projectionMatrix, rotationMatrix, PRmatrix);
		CMatrix4 resultmatrix;
		CMatrix4::Multiply(PRmatrix, matrix, resultmatrix);

		//print new matrix
		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				SetMatrixBox(_hDlg, resultmatrix.GetElement(i, j), i, j);
			}
		}
	}
}