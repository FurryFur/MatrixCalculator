#include <assert.h>

#include "Quaternion.h"

CQuaternion::CQuaternion(float _fW, float _fI, float _fJ, float _fK) :
	m_arrfElements{_fW, _fI, _fJ, _fK}
{
}

CQuaternion::~CQuaternion()
{
}

float CQuaternion::GetElement(size_t _szIdx) const
{
	return m_arrfElements.at(_szIdx);
}

float CQuaternion::GetW() const
{
	return GetElement(0);
}

float CQuaternion::GetI() const
{
	return GetElement(1);
}

float CQuaternion::GetJ() const
{
	return GetElement(2);
}

float CQuaternion::GetK() const
{
	return GetElement(3);
}

void CQuaternion::SetElement(size_t _szIdx, float _fValue)
{
	m_arrfElements.at(_szIdx) = _fValue;
}

void CQuaternion::SetW(float _fValue)
{
	m_arrfElements.at(0) = _fValue;
}

void CQuaternion::SetI(float _fValue)
{
	m_arrfElements.at(1) = _fValue;
}

void CQuaternion::SetJ(float _fValue)
{
	m_arrfElements.at(2) = _fValue;
}

void CQuaternion::SetK(float _fValue)
{
	m_arrfElements.at(3) = _fValue;
}

CQuaternion CQuaternion::operator*(const CQuaternion & _kqRHS) const
{
	CQuaternion qResult;
	float qA0 = GetW(), qB0 = _kqRHS.GetW();
	float qA1 = GetI(), qB1 = _kqRHS.GetI();
	float qA2 = GetJ(), qB2 = _kqRHS.GetJ();
	float qA3 = GetK(), qB3 = _kqRHS.GetK();
	qResult.SetW(qA0*qB0 - qA1*qB1 - qA2*qB2 - qA3*qB3);
	qResult.SetI(qA0*qB1 + qA1*qB0 + qA2*qB3 - qA3*qB2);
	qResult.SetJ(qA0*qB2 - qA1*qB3 + qA2*qB0 + qA3*qB1);
	qResult.SetK(qA0*qB3 + qA1*qB2 - qA2*qB1 + qA3*qB0);
	return qResult;
}

CQuaternion CQuaternion::operator*(float _fScaler) const
{
	return CQuaternion(_fScaler * GetW(), _fScaler * GetI(), _fScaler * GetJ(), _fScaler * GetK());
}

CQuaternion CQuaternion::operator+(const CQuaternion & _kqRHS) const
{
	CQuaternion qResult;
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		qResult.SetElement(szIdx, this->GetElement(szIdx) + _kqRHS.GetElement(szIdx));
	}
	return qResult;
}

CQuaternion CQuaternion::operator-(const CQuaternion & _kqRHS) const
{
	CQuaternion qResult;
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		qResult.SetElement(szIdx, this->GetElement(szIdx) - _kqRHS.GetElement(szIdx));
	}
	return qResult;
}

CQuaternion  CQuaternion::operator-() const
{
	CQuaternion qResult;
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		qResult.SetElement(szIdx, -(this->GetElement(szIdx)));
	}
	return qResult;
}

float CQuaternion::Dot(const CQuaternion & _kqRHS) const
{
	float fResult = 0;
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		fResult += this->GetElement(szIdx) * _kqRHS.GetElement(szIdx);
	}
	return fResult;
}

CQuaternion CQuaternion::Conjugate() const
{
	return CQuaternion(GetW(), -GetI(), -GetJ(), -GetK());
}

float CQuaternion::Magnitude() const
{
	float fResult = 0;
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		fResult += GetElement(szIdx) * GetElement(szIdx);
	}
	return std::sqrt(fResult);
}

// TODO: Test inverse is correct (gives weird results with long decimals)
CQuaternion CQuaternion::Inverse() const
{
	float fMagnitudeSquared = (Conjugate() * (*this)).GetW();
	CQuaternion qResult = Conjugate() * (1.0f / fMagnitudeSquared);

	return qResult;
}
