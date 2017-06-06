#pragma once

#include <array>
#include <math.h>

class CQuaternion
{
public:
	CQuaternion(float _fW = 0.0f, float _fI = 0.0f, float _fJ = 0.0f, float _fK = 0.0f);
	~CQuaternion();

	float GetElement(size_t _szIdx) const;
	float GetW() const;
	float GetI() const;
	float GetJ() const;
	float GetK() const;
	void SetElement(size_t _szIdx, float _fValue);
	void SetW(float _fValue);
	void SetI(float _fValue);
	void SetJ(float _fValue);
	void SetK(float _fValue);

	CQuaternion operator*(const CQuaternion& _kqRHS) const;
	CQuaternion operator*(float  _fScaler) const;
	CQuaternion operator+(const CQuaternion& _kqRHS) const;
	CQuaternion operator-(const CQuaternion& _kqRHS) const;
	CQuaternion operator-() const;
	float Dot(const CQuaternion& _kqRHS) const;
	CQuaternion Conjugate() const;
	float Magnitude() const;
	CQuaternion Inverse() const;

private:
	std::array<float, 4> m_arrfElements;
};

inline CQuaternion operator*(float _fScalar, const CQuaternion& _kq)
{
	return _kq * _fScalar;
}