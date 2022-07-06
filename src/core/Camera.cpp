#include "Camera.h"

#include "Window.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::UpdateViewportTransform()
{
	//TODO: STORE PRECALCULATIONS FOR TRANSFORMATION
}

vec2 Camera::WorldToViewportPoint(vec2 point) const
{
	//To camera space
	point -= transform.position;

	/* Virtual Viewport size and Real Viewport size.
	* RV - Real Viewport
	* VV - Virtual Viewport
	*/
	float aspRatio = Window::GetAspectRatio();
	vec2 RVSize(Window::GetWidth(), Window::GetHeight());
	vec2 halfRVSize = RVSize * 0.5f;
	vec2 VVSize(aspRatio * 1000.0f, 1000.0f);
	vec2 halfVVSize = VVSize * 0.5f;

	//Scale from VV size to RV size
	point.x *= halfRVSize.x / halfVVSize.x;
	point.y *= halfRVSize.y / halfVVSize.y;

	//To Viewport Space (Origin to top-left, Y axis down)
	point.x = point.x + halfRVSize.x;
	point.y = point.y * -1.0f + halfRVSize.y;

	return point;
}