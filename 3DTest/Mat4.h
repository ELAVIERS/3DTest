#pragma once
#include "Vector.h"

class Mat4 {
	Vector4F _data[4];

public:
	Mat4() : _data{ Vector4F(1.f, 0.f, 0.f, 0.f),
					Vector4F(0.f, 1.f, 0.f, 0.f),
					Vector4F(0.f, 0.f, 1.f, 0.f),
					Vector4F(0.f, 0.f, 0.f, 1.f) } {};
	Mat4(const Vector4F& row0, const Vector4F& row1, const Vector4F& row2, const Vector4F& row3)
		: _data{ row0, row1, row2, row3 } {}

		  Vector4F& operator[](int index)		{ return _data[index]; };
	const Vector4F& operator[](int index) const { return _data[index]; };

	const Mat4 operator*(const Mat4& other) const;
	inline Mat4& operator*=(const Mat4& other) {
		*this = other * *this;
		return *this;
	}
};
