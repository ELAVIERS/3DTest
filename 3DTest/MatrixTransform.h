#pragma once
#include "Mat4.h"
#include "Math.h"

namespace Matrix {
	inline const Mat4 Scale(const Vector3F& scale) {
		return Mat4(
			Vector4F(scale[0], 0.f, 0.f, 0.f),
			Vector4F(0.f, scale[1], 0.f, 0.f),
			Vector4F(0.f, 0.f, scale[2], 0.f),
			Vector4F(0.f, 0.f, 0.f,		 1.f)
		);
	}

	inline const Mat4 Perspective(float fov, float near, float far, float aspect) {
		float half_h = tanf(fov / 2.f);
		float half_w = half_h * aspect;

		return Mat4(
			Vector4F(1.f / half_w, 0.f, 0.f,								0.f),
			Vector4F(0.f, 1.f / half_h, 0.f,								0.f),
			Vector4F(0.f, 0.f,			(far + near) / (far - near),		1.f),
			Vector4F(0.f, 0.f,			(-2.f * far * near) / (far - near),	1.f)
		);
	}

	inline const Mat4 XRotation(float angle) {
		float cosine =	cosdeg(angle);
		float sine =	sindeg(angle);

		return Mat4(
			Vector4F(1.f, 0.f, 0.f, 0.f),
			Vector4F(0.f, cosine, sine, 0.f),
			Vector4F(0.f, -sine, cosine,  0.f),
			Vector4F(0.f, 0.f, 0.f, 1.f)
		);
	}

	inline const Mat4 YRotation(float angle) {
		float cosine =	cosdeg(angle);
		float sine =	sindeg(angle);

		return Mat4(
			Vector4F(cosine, 0.f, -sine,	  0.f),
			Vector4F(0.f,	 1.f, 0.f,	  0.f),
			Vector4F(sine,  0.f, cosine, 0.f),
			Vector4F(0.f, 0.f, 0.f, 1.f)
		);
	}

	inline const Mat4 ZRotation(float angle) {
		float cosine =	cosdeg(angle);
		float sine =	sindeg(angle);

		return Mat4(
			Vector4F(cosine, sine, 0.f, 0.f),
			Vector4F(-sine, cosine,  0.f, 0.f),
			Vector4F(0.f, 0.f, 1.f, 0.f),
			Vector4F(0.f, 0.f, 0.f, 1.f)
		);
	}

	inline const Mat4 Translation(const Vector3F& translation) {
		return Mat4(
			Vector4F(1.f, 0.f, 0.f, 0.f),
			Vector4F(0.f, 1.f, 0.f, 0.f),
			Vector4F(0.f, 0.f, 1.f, 0.f),
			Vector4F(translation[0], translation[1], translation[2], 1.f)
		);
	}
}
