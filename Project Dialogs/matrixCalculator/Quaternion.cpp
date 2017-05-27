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

CQuaternion CQuaternion::operator+(const CQuaternion & _kqRHS)
{
	CQuaternion qResult;
	for (size_t szIdx = 0; szIdx < 4; ++szIdx)
	{
		qResult.m_arrfElements.at(szIdx) = m_arrfElements.at(szIdx) + _kqRHS.m_arrfElements.at(szIdx);
	}
	return qResult;
}
