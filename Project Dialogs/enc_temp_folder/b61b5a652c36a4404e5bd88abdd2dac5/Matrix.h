#pragma once

#include <math.h>
#include <array>

//#include "Vec.h"

// Magic.....
template<bool...> struct bool_pack;
template<bool... bs>
using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

template <size_t szRows, size_t szCols>
class CMatrix
{
public:
	CMatrix();
	~CMatrix();

	template <typename... Floats,
		typename = std::enable_if_t< 
			all_true<std::is_convertible<Floats, float>::value...>::value &&
			sizeof...(Floats) == (szRows * szCols)
		>
	>
	CMatrix(Floats...);

	// 0 based index.
	void SetElement(int _iR, int _iC, float _fValue);
	float GetElement(int _iR, int _iC) const;
	static CMatrix& Zero(CMatrix& _rResult);
	static bool Equals(const CMatrix& _rA, const CMatrix& _rB);
	static CMatrix& Add(const CMatrix& _rA, const CMatrix& _rB, CMatrix& _rResult);
	static CMatrix& Subtract(const CMatrix& _rA, const CMatrix& _rB, CMatrix& _rResult);
	static CMatrix& Multiply(float _fScalar, const CMatrix& _rA, CMatrix& _rResult);
	static CMatrix& Multiply(const CMatrix& _rA, const CMatrix& _rB, CMatrix& _rResult);

	static CMatrix<szCols, szRows>& Transpose(const CMatrix& _rA, CMatrix<szCols, szRows>& _rResult);

	template <size_t _szRows = szRows, size_t _szCols = szCols,
		typename = std::enable_if_t<(_szRows == _szCols)> >
	static CMatrix& Identity(CMatrix& _rResult);

	template <size_t _szRows = szRows, size_t _szCols = szCols,
		typename = std::enable_if_t<(_szRows == _szCols)> >
	static float Determinant(const CMatrix& _rA);

	template <size_t _szRows = szRows, size_t _szCols = szCols,
		typename = std::enable_if_t<(_szRows == _szCols)> >
	static bool Inverse(const CMatrix& _rA, CMatrix& _rResult);

	template <size_t _szRows = szRows, size_t _szCols = szCols,
		typename = std::enable_if_t<(_szRows == _szCols)> >
	static CMatrix<szRows, szCols>& Scale(const CMatrix<szRows, 1>& vec, CMatrix<szRows, szCols>& _rResult);

	// For scaling an Affine matrix
	template <size_t _szRows = szRows, size_t _szCols = szCols,
		typename = std::enable_if_t<(_szRows == _szCols)> >
	static CMatrix<szRows, szCols>& Scale(const CMatrix<szRows - 1, 1>& vec, CMatrix<szRows, szCols>& _rResult);

	template <size_t szRows2 = szRows, size_t szCols2 = szCols,
		typename = std::enable_if_t<(szRows2 == szCols2 && szRows2 <= 4)> >
		static CMatrix<szRows, szCols>& Translate(const CMatrix<szRows, 1>& vec, CMatrix<szRows, szCols>& _rResult);

	template <size_t szRows2 = szRows, size_t szCols2 = szCols,
		typename = std::enable_if_t<(szRows2 == szCols2 && szRows2 <= 4)> >
		static CMatrix<szRows, szCols>& Translate(const CMatrix<szRows - 1, 1>& vec, CMatrix<szRows, szCols>& _rResult);

	// Methods for Gaussian Elimination
	void MultiplyRow(size_t _szRow, float _fScalar);
	void SwapRow(size_t _szRow1, size_t _szRow2);
	void AddMultipleOfRowToRow(float _fScalar, size_t _szRowSrc, size_t _szRowDst);
	static int GaussianElimStep(CMatrix<szRows, szCols> & _rmat);
	// Notes: May result in row swap,
	// Returns: Whether an unprocessed pivot was found
	static bool GetPivot(CMatrix<szRows, szCols> & _rmat, size_t & _rszPivotRow, size_t & _rszPivotCol, int & _riEliminationDir, bool & _rbWasRowSwap);
	static bool IsInReducedRowEchelonForm(const CMatrix<szRows, szCols> &_rmat);
	static bool IsInEchelonForm(const CMatrix<szRows, szCols> &_rmat);

private:
	std::array<std::array<float, szCols>, szRows> m_arrfMatrix;

	CMatrix<szRows - 1, szCols - 1>& ConstructView(int _iBlankedOutR, int _iBlankedOutC, CMatrix<szRows - 1, szCols - 1>& matView) const;
};

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols>::CMatrix()
{
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols>::~CMatrix()
{
}

template <size_t szRows, size_t szCols>
void CMatrix<szRows, szCols>::SetElement(int _iR, int _iC, float _fValue)
{
	m_arrfMatrix[_iR][_iC] = _fValue;
}

template <size_t szRows, size_t szCols>
float CMatrix<szRows, szCols>::GetElement(int _iR, int _iC) const
{
	return m_arrfMatrix[_iR][_iC];
}

template <size_t szRows, size_t szCols>
template <size_t _szRows, size_t _szCols, typename>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Identity(CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szRows; ++c)
		{
			if (r == c)
			{
				_rResult.m_arrfMatrix[r][c] = 1;
			}
			else
			{
				_rResult.m_arrfMatrix[r][c] = 0;
			}
		}
	}
	return _rResult;
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Zero(CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szRows; ++c)
		{
			_rResult.m_arrfMatrix[r][c] = 0;
		}
	}
	return _rResult;
}

template <size_t szRows, size_t szCols>
bool CMatrix<szRows, szCols>::Equals(const CMatrix<szRows, szCols> & _rA, const CMatrix<szRows, szCols> & _rB)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			// Return false immediately, if we find an unequal element
			if (abs(_rA.m_arrfMatrix[r][c] - _rB.m_arrfMatrix[r][c]) > 0.0001)
			{
				return false;
			}
		}
	}

	// True if no unequal elements were found
	return true;
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Add(const CMatrix<szRows, szCols> & _rA, const CMatrix<szRows, szCols> & _rB, CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szRows; ++c)
		{
			_rResult.m_arrfMatrix[r][c] = _rA.m_arrfMatrix[r][c] + _rB.m_arrfMatrix[r][c];
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Subtract(const CMatrix<szRows, szCols> & _rA, const CMatrix<szRows, szCols> & _rB, CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			_rResult.m_arrfMatrix[r][c] = _rA.m_arrfMatrix[r][c] - _rB.m_arrfMatrix[r][c];
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Multiply(float _fScalar, const CMatrix<szRows, szCols> & _rA, CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			_rResult.m_arrfMatrix[r][c] = _fScalar * _rA.m_arrfMatrix[r][c];
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Multiply(const CMatrix<szRows, szCols> & _rA, const CMatrix<szRows, szCols> & _rB, CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szRows; ++c)
		{
			_rResult.m_arrfMatrix[r][c] = 0;
			for (int i = 0; i < szRows; ++i)
			{
				_rResult.m_arrfMatrix[r][c] += _rA.m_arrfMatrix[r][i] * _rB.m_arrfMatrix[i][c];
			}
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
CMatrix<szCols, szRows> & CMatrix<szRows, szCols>::Transpose(const CMatrix<szRows, szCols> & _rA, CMatrix<szCols, szRows> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			_rResult.m_arrfMatrix[r][c] = _rA.m_arrfMatrix[c][r];
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
template <size_t _szRows, size_t _szCols, typename>
float CMatrix<szRows, szCols>::Determinant(const CMatrix<szRows, szCols> & _rA)
{
	float fDeterminant = 0;
	for (int c = 0; c < szCols; ++c)
	{
		CMatrix<szRows - 1, szCols - 1> matView;
		_rA.ConstructView(0, c, matView);

		float fA = _rA.m_arrfMatrix[0][c];
		fDeterminant += pow(-1.0f, c) * fA * CMatrix<szRows - 1, szCols - 1>::Determinant(matView);
	}

	return fDeterminant;
}

template <>
template <>
inline float CMatrix<2, 2>::Determinant(const CMatrix<2, 2> & _rA)
{
	float fA = _rA.m_arrfMatrix[0][0];
	float fB = _rA.m_arrfMatrix[0][1];
	float fC = _rA.m_arrfMatrix[1][0];
	float fD = _rA.m_arrfMatrix[1][1];
	return fA * fD - fB * fC;
}

template <>
template <>
inline float CMatrix<1, 1>::Determinant(const CMatrix<1, 1> & _rA)
{
	return _rA.m_arrfMatrix[0][0];
}

template <size_t szRows, size_t szCols>
template <size_t _szRows, size_t _szCols, typename>
bool CMatrix<szRows, szCols>::Inverse(const CMatrix<szRows, szCols> & _rA, CMatrix<szRows, szCols> & _rResult)
{
	float fDeterminant = CMatrix::Determinant(_rA);
	if (fDeterminant != 0)
	{
		// Get cofactor matrix
		CMatrix<szRows, szCols> matCofactor;
		for (int r = 0; r < szRows; ++r)
		{
			for (int c = 0; c < szCols; ++c)
			{
				CMatrix<szRows - 1, szCols - 1> matView;
				_rA.ConstructView(r, c, matView);

				matCofactor.SetElement(r, c, pow(-1.0f, r + c) * CMatrix<szRows - 1, szCols - 1>::Determinant(matView));
			}
		}

		// Get Adjunct matrix
		CMatrix<szRows, szCols> matAdj;
		CMatrix::Transpose(matCofactor, matAdj);

		// Compute inverse using adjunct matrix and determinant
		CMatrix::Multiply(1.0f / fDeterminant, matAdj, _rResult);

		return true;
	}
	else
	{
		return false;
	}
}

// Construct size - 1 matrix with specified row and col blanked out
template <size_t szRows, size_t szCols>
CMatrix<szRows - 1, szCols - 1>& CMatrix<szRows, szCols>::ConstructView(int _iBlankedOutR, int _iBlankedOutC, CMatrix<szRows - 1, szCols - 1>& _matView) const
{
	size_t srcR = 0;
	for (size_t viewR = 0; viewR < szRows - 1; ++viewR)
	{
		// Skip the blanked out row
		if (srcR == _iBlankedOutR)
			++srcR;

		size_t srcC = 0;
		for (size_t viewC = 0; viewC < szCols - 1; ++viewC)
		{
			// Skip the blanked out column
			if (srcC == _iBlankedOutC)
				++srcC;

			_matView.SetElement(viewR, viewC, m_arrfMatrix[srcR][srcC]);

			++srcC;
		}
		++srcR;
	}

	return _matView;
}

template<size_t szRows, size_t szCols>
template<typename ...Floats, typename>
inline CMatrix<szRows, szCols>::CMatrix(Floats... floats)
{
	// Extract floats to array
	float arrfValues[szRows * szCols] = { static_cast<float>(floats)... };

	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			m_arrfMatrix[r][c] = arrfValues[c + r * szCols];
		}
	}
}

template <size_t szRows, size_t szCols>
template <size_t _szRows, size_t _szCols, typename>
inline CMatrix<szRows, szCols>& CMatrix<szRows, szCols>::Scale(const CMatrix<szRows, 1>& vec, CMatrix<szRows, szCols>& _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			if (r == c)
			{
				_rResult.m_arrfMatrix[r][c] = vec.GetElement(r, 0);
			}
			else
			{
				_rResult.m_arrfMatrix[r][c] = 0;
			}
		}
	}

	return _rResult;
}

// For scaling an Affine matrix
template <size_t szRows, size_t szCols>
template <size_t _szRows, size_t _szCols, typename>
inline CMatrix<szRows, szCols>& CMatrix<szRows, szCols>::Scale(const CMatrix<szRows - 1, 1>& vec3, CMatrix<szRows, szCols>& _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			if (r == c)
			{
				if (r == (szRows - 1))
				{
					_rResult.m_arrfMatrix[r][c] = 1;
					break;
				}

				_rResult.m_arrfMatrix[r][c] = vec3.GetElement(r, 0);
			}
			else
			{
				_rResult.m_arrfMatrix[r][c] = 0;
			}
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
template <size_t szRows2, size_t szCols2, typename>
inline CMatrix<szRows, szCols>& CMatrix<szRows, szCols>::Translate(const CMatrix<szRows, 1>& vec, CMatrix<szRows, szCols>& _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			if (r == (szRows - 1))
			{
				_rResult.m_arrfMatrix[r][c] = vec.GetElement(r, 0);
			}
			else if (r == c)
			{
				_rResult.m_arrfMatrix[r][c] = 1;
			}
			else
			{
				_rResult.m_arrfMatrix[r][c] = 0;
			}
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
template <size_t szRows2, size_t szCols2, typename>
inline CMatrix<szRows, szCols>& CMatrix<szRows, szCols>::Translate(const CMatrix<szRows - 1, 1>& vec3, CMatrix<szRows, szCols>& _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			if (r == c)
			{
				_rResult.m_arrfMatrix[r][c] = 1;
			}
			else if (c == (szCols - 1))
			{
				_rResult.m_arrfMatrix[r][c] = vec3.GetElement(r, 0);
			}
			else
			{
				_rResult.m_arrfMatrix[r][c] = 0;
			}
		}
	}

	return _rResult;
}

template<size_t szRows, size_t szCols>
inline void CMatrix<szRows, szCols>::MultiplyRow(size_t _szRow, float _fScalar)
{
	for (size_t c = 0; c < szCols; ++c)
	{
		m_arrfMatrix[_szRow][c] *= _fScalar;
	}
}

template<size_t szRows, size_t szCols>
inline void CMatrix<szRows, szCols>::SwapRow(size_t _szRow1, size_t _szRow2)
{
	std::array<float, szCols> arrTmp = m_arrfMatrix[_szRow1];
	m_arrfMatrix[_szRow1] = m_arrfMatrix[_szRow2];
	m_arrfMatrix[_szRow2] = arrTmp;
}

template<size_t szRows, size_t szCols>
inline void CMatrix<szRows, szCols>::AddMultipleOfRowToRow(float _fScalar, size_t _szRowSrc, size_t _szRowDst)
{
	for (size_t c = 0; c < szCols; ++c)
	{
		m_arrfMatrix[_szRowDst][c] += _fScalar * m_arrfMatrix[_szRowSrc][c];
	}
}

template<size_t szRows, size_t szCols>
inline int CMatrix<szRows, szCols>::GaussianElimStep(CMatrix<szRows, szCols> & _rmat)
{
	// Find the next pivot (must have non-zero entries below it, otherwise it has already been processed)
	size_t szPivotRow;
	size_t szPivotCol;
	int iEliminationDir;
	bool bWasRowSwap;
	bool bPivotToProcess = GetPivot(_rmat, szPivotRow, szPivotCol, iEliminationDir, bWasRowSwap);

	if (bPivotToProcess && !bWasRowSwap)
	{
		// Normalise pivot first if doing row reduced part
		bool bNormalizedThisStep = false;
		if (iEliminationDir == -1 && abs(_rmat.m_arrfMatrix[szPivotRow][szPivotCol] - 1) >= 0.000001)
		{
			float fFactor = 1 / _rmat.m_arrfMatrix[szPivotRow][szPivotCol];
			for (size_t szCurCol = szPivotCol + 1; szCurCol < szCols; ++szCurCol)
			{
				_rmat.m_arrfMatrix[szPivotRow][szCurCol] *= fFactor;

				// Zero out entries that are basically zero already
				if (abs(_rmat.m_arrfMatrix[szPivotRow][szCurCol]) < 0.000001)
				{
					_rmat.m_arrfMatrix[szPivotRow][szCurCol] = 0;
				}
			}

			// Make the pivot exactly 1
			_rmat.m_arrfMatrix[szPivotRow][szPivotCol] = 1;

			bNormalizedThisStep = true;
		}

		// Do Gaussian Elimination steps
		if (!bNormalizedThisStep)
		{
			for (size_t szCurRow = szPivotRow + iEliminationDir; szCurRow < szRows && szCurRow >= 0; szCurRow += iEliminationDir)
			{
				float fFactor = -(_rmat.m_arrfMatrix[szCurRow][szPivotCol] / _rmat.m_arrfMatrix[szPivotRow][szPivotCol]);
				for (size_t szCurCol = szPivotCol + 1; szCurCol < szCols; ++szCurCol)
				{
					_rmat.m_arrfMatrix[szCurRow][szCurCol] += fFactor * _rmat.m_arrfMatrix[szPivotRow][szCurCol];

					// Zero out entries that are basically zero already
					if (abs(_rmat.m_arrfMatrix[szCurRow][szCurCol]) < 0.000001)
					{
						_rmat.m_arrfMatrix[szCurRow][szCurCol] = 0;
					}
				}

				// Fill triangular part of matrix with zeros
				_rmat.m_arrfMatrix[szCurRow][szPivotCol] = 0;
			}
		}
	}

	return iEliminationDir;
}

template<size_t szRows, size_t szCols>
inline bool CMatrix<szRows, szCols>::GetPivot(CMatrix<szRows, szCols>& _rmat, size_t & _rszPivotRow, size_t & _rszPivotCol, int & _riEliminationDir, bool & _rbWasRowSwap)
{
	_rszPivotRow = 0;
	_rszPivotCol = 0;
	_riEliminationDir = 1;
	_rbWasRowSwap = false;

	bool bFoundPivot = false;
	size_t szLastValidPivotRow = -1;
	size_t szLastValidPivotCol = -1;
	
	while (!bFoundPivot && (_rszPivotRow < szRows) && (_rszPivotCol < szCols) && (_rszPivotRow >= 0) && (_rszPivotCol >= 0))
	{
		// Find first non-zero pivot in column
		size_t szRowFirstNonZero = _rszPivotRow;
		for (size_t szCurRow = _rszPivotRow; szCurRow < szRows && szCurRow >= 0; szCurRow += _riEliminationDir)
		{
			if (_rmat.m_arrfMatrix[szCurRow][_rszPivotCol] != 0)
			{
				szRowFirstNonZero = szCurRow;
				break;
			}
		}

		// Move to next column if column contains no pivot
		if (_rmat.m_arrfMatrix[szRowFirstNonZero][_rszPivotCol] == 0)
		{
			// Swap elimination direction if we would go past the last column to find a pivot
			if (_rszPivotCol + _riEliminationDir == szCols)
			{
				_riEliminationDir *= -1;
				_rszPivotRow = szLastValidPivotRow;
				_rszPivotCol = szLastValidPivotCol;
			}
			else
			{
				_rszPivotCol += _riEliminationDir;
			}
			continue;
		}
		// Save valid pivots
		else
		{
			// We need this when changing elimination directions so we start at the last valid pivot
			szLastValidPivotRow = _rszPivotRow;
			szLastValidPivotCol = _rszPivotCol;
		}

		// If the pivot is in the wrong row, then swap the rows and break from the loop
		if (_rszPivotRow != szRowFirstNonZero)
		{
			_rmat.SwapRow(_rszPivotRow, szRowFirstNonZero);
			_rbWasRowSwap = true;
			bFoundPivot = true;
			break;
		}

		// Still need to process the column if doing row reduction steps and the pivot is not 1
		bool bColumnStillNeedsProcessing = false;
		if (_riEliminationDir == -1 && abs(_rmat.m_arrfMatrix[_rszPivotRow][_rszPivotCol] - 1) >= 0.000001)
		{
			bColumnStillNeedsProcessing = true;
		}
		else
		{
			// Move to next row and column if remainder of column contains only zeros
			for (size_t szCurRow = _rszPivotRow + _riEliminationDir; szCurRow < szRows && szCurRow >= 0; szCurRow += _riEliminationDir)
			{
				if (_rmat.m_arrfMatrix[szCurRow][_rszPivotCol] != 0)
				{
					bColumnStillNeedsProcessing = true;
					break;
				}
			}
		}
		if (!bColumnStillNeedsProcessing)
		{
			// Swap elimination direction if we would go past the last row or column to find a pivot
			if (_rszPivotRow + _riEliminationDir == szRows || _rszPivotCol + _riEliminationDir == szCols)
			{
				_riEliminationDir *= -1;
				_rszPivotRow = szLastValidPivotRow;
				_rszPivotCol = szLastValidPivotCol;
			}
			else 
			{
				_rszPivotRow += _riEliminationDir;
				_rszPivotCol += _riEliminationDir;
			}
			
			continue;
		}

		bFoundPivot = true;
	}

	return bFoundPivot;
}

template<size_t szRows, size_t szCols>
inline bool CMatrix<szRows, szCols>::IsInReducedRowEchelonForm(const CMatrix<szRows, szCols>& _rmat)
{
	size_t szPivotRow = 0;
	size_t szPivotCol = 0;

	while ((szPivotRow < szRows) && (szPivotCol < szCols))
	{
		// Find pivot row in this column
		for (size_t szCurRow = szPivotRow; szCurRow < szRows; ++szCurRow)
		{
			if (_rmat.m_arrfMatrix[szCurRow][szPivotCol] != 0)
			{
				szPivotRow = szCurRow;
				break;
			}
		}

		// Move to next column if column contains no pivot
		if (_rmat.m_arrfMatrix[szPivotRow][szPivotCol] == 0)
		{
			++szPivotCol;
			continue;
		}

		// Check that the pivots are 1
		bool bPivotsAreNormalized = abs(_rmat.m_arrfMatrix[szPivotRow][szPivotCol] - 1) < 0.000001f;

		// Check that there are no entries above pivot
		bool bEntriesAbove = false;
		for (size_t r = szPivotRow - 1; r >= 0 && r < szRows; --r)
		{
			if (abs(_rmat.m_arrfMatrix[r][szPivotCol]) >= 0.000001f)
			{
				bEntriesAbove = true;
				break;
			}
		}

		// Check that there are no entries below pivot
		bool bEntriesBelow = false;
		for (size_t r = szPivotRow + 1; r < szRows; ++r)
		{
			if (abs(_rmat.m_arrfMatrix[r][szPivotCol]) >= 0.000001f)
			{
				bEntriesBelow = true;
				break;
			}
		}

		if (!bPivotsAreNormalized || bEntriesAbove || bEntriesBelow)
		{
			return false;
		}

		++szPivotRow;
		++szPivotCol;
	}
}

template<size_t szRows, size_t szCols>
inline bool CMatrix<szRows, szCols>::IsInEchelonForm(const CMatrix<szRows, szCols>& _rmat)
{
	size_t szPivotRow = 0;
	size_t szPivotCol = 0;

	while ((szPivotRow < szRows) && (szPivotCol < szCols))
	{
		// Find pivot row in this column
		for (size_t szCurRow = szPivotRow; szCurRow < szRows; ++szCurRow)
		{
			if (_rmat.m_arrfMatrix[szCurRow][szPivotCol] != 0)
			{
				szPivotRow = szCurRow;
				break;
			}
		}

		// Move to next column if column contains no pivot
		if (_rmat.m_arrfMatrix[szPivotRow][szPivotCol] == 0)
		{
			++szPivotCol;
			continue;
		}

		// Check that there are no entries below pivot
		bool bEntriesBelow = false;
		for (size_t r = szPivotRow + 1; r < szRows; ++r)
		{
			if (abs(_rmat.m_arrfMatrix[r][szPivotCol]) >= 0.000001f)
			{
				bEntriesBelow = true;
				break;
			}
		}

		if (bEntriesBelow)
		{
			return false;
		}

		++szPivotRow;
		++szPivotCol;
	}
}

typedef CMatrix<2, 2> CMatrix2;
typedef CMatrix<3, 3> CMatrix3;
typedef CMatrix<4, 4> CMatrix4;
typedef CMatrix<3, 1> CVec3;
typedef CMatrix<4, 1> CVec4;
typedef CMatrix<2, 1> CVec2;