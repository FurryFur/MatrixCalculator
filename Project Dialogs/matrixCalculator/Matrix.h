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

	static CMatrix& Transpose(const CMatrix& _rA, CMatrix& _rResult);

	static CMatrix& Identity(CMatrix& _rResult);
	static float Determinant(const CMatrix& _rA);
	static bool Inverse(const CMatrix& _rA, CMatrix& _rResult);

	template <size_t szRows2 = szRows, size_t szCols2 = szCols,
		typename = std::enable_if_t<(szRows2 == szCols2 && szRows2 <= 4)> >
	static CMatrix<szRows, szCols>& Scale(const CMatrix<szRows, 1>& vec, CMatrix<szRows, szCols>& _rResult);

	template <size_t szRows2 = szRows, size_t szCols2 = szCols,
		typename = std::enable_if_t<(szRows2 == szCols2 && szRows2 <= 4)> >
	static CMatrix<szRows, szCols>& Scale(const CMatrix<szRows - 1, 1>& vec, CMatrix<szRows, szCols>& _rResult);

private:
	float m_fMatrix[szRows][szRows];

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
	m_fMatrix[_iR][_iC] = _fValue;
}

template <size_t szRows, size_t szCols>
float CMatrix<szRows, szCols>::GetElement(int _iR, int _iC) const
{
	return m_fMatrix[_iR][_iC];
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Identity(CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szRows; ++c)
		{
			if (r == c)
			{
				_rResult.m_fMatrix[r][c] = 1;
			}
			else
			{
				_rResult.m_fMatrix[r][c] = 0;
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
			_rResult.m_fMatrix[r][c] = 0;
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
			if (abs(_rA.m_fMatrix[r][c] - _rB.m_fMatrix[r][c]) > 0.0001)
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
			_rResult.m_fMatrix[r][c] = _rA.m_fMatrix[r][c] + _rB.m_fMatrix[r][c];
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
			_rResult.m_fMatrix[r][c] = _rA.m_fMatrix[r][c] - _rB.m_fMatrix[r][c];
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
			_rResult.m_fMatrix[r][c] = _fScalar * _rA.m_fMatrix[r][c];
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
			_rResult.m_fMatrix[r][c] = 0;
			for (int i = 0; i < szRows; ++i)
			{
				_rResult.m_fMatrix[r][c] += _rA.m_fMatrix[r][i] * _rB.m_fMatrix[i][c];
			}
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
CMatrix<szRows, szCols> & CMatrix<szRows, szCols>::Transpose(const CMatrix<szRows, szCols> & _rA, CMatrix<szRows, szCols> & _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			_rResult.m_fMatrix[r][c] = _rA.m_fMatrix[c][r];
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
float CMatrix<szRows, szCols>::Determinant(const CMatrix<szRows, szCols> & _rA)
{
	float fDeterminant = 0;
	for (int c = 0; c < szCols; ++c)
	{
		CMatrix<szRows - 1, szCols - 1> matView;
		_rA.ConstructView(0, c, matView);

		float fA = _rA.m_fMatrix[0][c];
		fDeterminant += pow(-1.0f, c) * fA * CMatrix<szRows - 1, szCols - 1>::Determinant(matView);
	}

	return fDeterminant;
}

template <>
inline float CMatrix<2, 2>::Determinant(const CMatrix<2, 2> & _rA)
{
	float fA = _rA.m_fMatrix[0][0];
	float fB = _rA.m_fMatrix[0][1];
	float fC = _rA.m_fMatrix[1][0];
	float fD = _rA.m_fMatrix[1][1];
	return fA * fD - fB * fC;
}

template <>
inline float CMatrix<1, 1>::Determinant(const CMatrix<1, 1> & _rA)
{
	return _rA.m_fMatrix[0][0];
}

template <size_t szRows, size_t szCols>
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

			_matView.SetElement(viewR, viewC, m_fMatrix[srcR][srcC]);

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
			m_fMatrix[r][c] = arrfValues[c + r * szCols];
		}
	}
}

template <size_t szRows, size_t szCols>
template <size_t szRows2, size_t szCols2, typename>
inline CMatrix<szRows, szCols>& CMatrix<szRows, szCols>::Scale(const CMatrix<szRows, 1>& vec, CMatrix<szRows, szCols>& _rResult)
{
	for (int r = 0; r < szRows; ++r)
	{
		for (int c = 0; c < szCols; ++c)
		{
			if (r == c)
			{
				_rResult.m_fMatrix[r][c] = vec.GetElement(r, 0);
			}
			else
			{
				_rResult.m_fMatrix[r][c] = 0;
			}
		}
	}

	return _rResult;
}

template <size_t szRows, size_t szCols>
template <size_t szRows2, size_t szCols2, typename>
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
					_rResult.m_fMatrix[r][c] = 1;
					break;
				}

				_rResult.m_fMatrix[r][c] = vec3.GetElement(r, 0);
			}
			else
			{
				_rResult.m_fMatrix[r][c] = 0;
			}
		}
	}

	return _rResult;
}

typedef CMatrix<2, 2> CMatrix2;
typedef CMatrix<3, 3> CMatrix3;
typedef CMatrix<4, 4> CMatrix4;
typedef CMatrix<3, 1> CVec3;
typedef CMatrix<4, 1> CVec4;
typedef CMatrix<2, 1> CVec2;