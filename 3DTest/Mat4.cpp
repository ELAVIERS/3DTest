#include "Mat4.h"

#include <cmath>

#define DOT(A,B,R,C) (A[R][0] * B[0][C]) + (A[R][1] * B[1][C]) + (A[R][2] * B[2][C]) + (A[R][3] * B[3][C])

const Mat4 Mat4::operator*(const Mat4& other) const {
	Mat4 result(
		Vector4F(DOT(_data, other, 0, 0), DOT(_data, other, 0, 1), DOT(_data, other, 0, 2), DOT(_data, other, 0, 3)),
		Vector4F(DOT(_data, other, 1, 0), DOT(_data, other, 1, 1), DOT(_data, other, 1, 2), DOT(_data, other, 1, 3)),
		Vector4F(DOT(_data, other, 2, 0), DOT(_data, other, 2, 1), DOT(_data, other, 2, 2), DOT(_data, other, 2, 3)),
		Vector4F(DOT(_data, other, 3, 0), DOT(_data, other, 3, 1), DOT(_data, other, 3, 2), DOT(_data, other, 3, 3))
	);

	return result;
}
