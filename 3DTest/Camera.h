#pragma once
#include "MatrixTransform.h"
#include "Vector.h"

class Camera
{
	Vector<unsigned short, 2>	_viewport_size;
	float						_fov;
	float						_near;
	float						_far;

	Mat4						_m_perspective;
	Mat4						_m_orthographic;

	void _CalculateProjection();
public:
	Camera();
	~Camera();

	inline const Vector<unsigned short, 2> GetSize() { return _viewport_size; }

	Vector3F position;
	Vector2F rotation;

	inline const Mat4& GetPerspective() { return _m_perspective; }
	inline const Mat4& GetOrthographic() { return _m_orthographic; }

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
