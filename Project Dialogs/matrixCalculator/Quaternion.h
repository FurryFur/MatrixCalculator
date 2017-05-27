#pragma once

#include <array>

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

	CQuaternion operator+(const CQuaternion& _kqRHS);

private:
	std::array<float, 4> m_arrfElements;
};

