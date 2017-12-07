#pragma once

template <typename T, size_t N>
class Vector {
protected:
	T _data[N];

public:
	Vector() {};

	template <typename ...Args>
	Vector(Args... args) : _data{ (T)args... } { static_assert(sizeof...(args) == N, "Invalid argument count"); }
	~Vector() {}

	inline		 T& operator[](int element)		  { return _data[element]; }
	inline const T& operator[](int element) const { return _data[element]; }

	inline Vector operator*(T scalar) const {
		Vector result(*this);
		for (int i = 0; i < N; ++i)
			result[i] *= scalar;

		return result;
	}

	inline Vector& operator+=(const Vector& other) {
		for (int i = 0; i < N; ++i)
			_data[i] += other[i];

		return *this;
	}
};

#include "Math.h"

template <typename T>
class Vector3 : public Vector<T, 3> {
public:
	Vector3() {};
	Vector3(T x, T y, T z) : Vector(x, y, z) {};
	~Vector3() {};

	inline Vector3 operator*(T scalar) const { return Vector3(_data[0] * scalar, _data[1] * scalar, _data[2] * scalar); }

	inline const T Dot(const Vector3& other) {
		return _data[0] * other[0] + _data[1] * other[1] + _data[2] + other[2];
	}

	inline const Vector3 Cross(const Vector3& other) {
		return Vector3(
			_data[1] * other[2] - _data[2] * other[1],
			_data[2] * other[0] - _data[0] * other[2],
			_data[0] * other[1] - _data[1] * other[0]
		);
	}

	inline const T LengthSquared() { return Dot(*this); }
	inline const float Length() { return sqrtf(LengthSquared()); }

	inline const Vector3 Normal() { 
		float length = Length();
		return Vector(_data[0] / length, _data[1] / length, _data[2] / length);
	}
};

typedef Vector<float, 2> Vector2F;
typedef Vector3<float> Vector3F;
typedef Vector<float, 4> Vector4F;
