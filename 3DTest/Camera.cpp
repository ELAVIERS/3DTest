#include "Camera.h"

#include "Math.h"

Camera::Camera() : _fov(90), _near(0.001f), _far(1000.f)
{
	_CalculateProjection();
}


Camera::~Camera()
{
}

void Camera::_CalculateProjection() {
	_m_perspective = Matrix::Perspective(
		_fov * Math::pi_over_180,
		_near, _far,
		(float)_viewport_size[0] / (float)_viewport_size[1]
	);

	_m_orthographic = Matrix::Orthographic(
		(float)_viewport_size[0], (float)_viewport_size[1], -1000.f, 1000.f);
}
