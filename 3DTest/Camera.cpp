#include "Camera.h"

#include "Math.h"

Camera::Camera() : _fov(90)
{
	_CalculateProjection();
}


Camera::~Camera()
{
}

void Camera::_CalculateProjection() {
	_m_projection = Matrix::Perspective(
		_fov * Math::pi_over_180,
		.001f, 1000.f,
		(float)_viewport_size[0] / (float)_viewport_size[1]
	);
}
