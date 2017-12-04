#pragma once
#include "MatrixTransform.h"
#include "Vector.h"

class Camera
{
	Vector<unsigned short, 2>	_viewport_size;
	float						_fov;

	Mat4						_m_projection;

	void _CalculateProjection();
public:
	Camera();
	~Camera();

	inline const Vector<unsigned short, 2> GetSize() { return _viewport_size; }

	Vector3F position;
	Vector2F rotation;

	inline const Mat4& GetProjectionMatrix() { return _m_projection; };
	inline const Mat4 GetViewMatrix() {
		return
			Matrix::Translation(position * -1.f) *
			Matrix::YRotation(-rotation[1]) *
			Matrix::XRotation(-rotation[0]) *
			Matrix::Translation(Vector3F(0.f, 0.f, -1.f));
	}

	inline void SetFOV(float fov) {
		_fov = fov;
		_CalculateProjection();
	};

	inline void SetSize(unsigned short width, unsigned short height) {
		_viewport_size = Vector<unsigned short, 2>(width, height);
		_CalculateProjection();
	};
};
