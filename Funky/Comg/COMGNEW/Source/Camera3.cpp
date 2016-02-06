#include "Camera3.h"
#include "Assignment3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	translateChar = 0;
	rotateChar = 0;

	SetCursorPos(1920 / 2, 600 / 2);
}

void Camera3::Update(double dt)
{
	POINT mousecursor;

	GetCursorPos(&mousecursor);
	static const float CAMERA_SPEED = 60.f;
	static const float CAM_SPEED_MOV = 20.0f;
	if (EPressed == true)
	{
		if (Application::IsKeyPressed('D'))
		{
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			up = right.Cross(view).Normalized();
			if (position.x + (right.x * (float)(CAM_SPEED_MOV * dt)) > -35.7 && position.x + (right.x * (float)(CAM_SPEED_MOV * dt)) < 35.7)
			{
				position.x += right.x * (float)(CAM_SPEED_MOV * dt);
				target.x += right.x * (float)(CAM_SPEED_MOV * dt);
			}
			if (position.z + (right.z * (float)(CAM_SPEED_MOV * dt)) > 3 && position.z + (right.z * (float)(CAM_SPEED_MOV * dt)) < 80)
			{
				position.z += right.z * (float)(CAM_SPEED_MOV * dt);
				target.z += right.z * (float)(CAM_SPEED_MOV * dt);
			}
		}
		if (Application::IsKeyPressed('A'))
		{
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			up = right.Cross(view).Normalized();
			if (position.x - (right.x * (float)(CAM_SPEED_MOV * dt)) > -35.7 && position.x - (right.x * (float)(CAM_SPEED_MOV * dt)) < 35.7)
			{
				position.x -= right.x * (float)(CAM_SPEED_MOV * dt);
				target.x -= right.x * (float)(CAM_SPEED_MOV * dt);
			}
			if (position.z - (right.z * (float)(CAM_SPEED_MOV * dt)) > 3 && position.z - (right.z * (float)(CAM_SPEED_MOV * dt)) < 80)
			{
				position.z -= right.z * (float)(CAM_SPEED_MOV * dt);
				target.z -= right.z * (float)(CAM_SPEED_MOV * dt);
			}
		}
		if (Application::IsKeyPressed('W'))
		{
			Vector3 view = (target - position).Normalized();
			if (position.x + (view.x * (float)(CAM_SPEED_MOV * dt)) > -35.7 && position.x + (view.x * (float)(CAM_SPEED_MOV * dt)) < 35.7)
			{
				position.x += view.x * (float)(CAM_SPEED_MOV * dt);
				target.x += view.x * (float)(CAM_SPEED_MOV * dt);
			}
			if (position.z + (view.z * (float)(CAM_SPEED_MOV * dt)) > 3 && position.z + (view.z * (float)(CAM_SPEED_MOV * dt)) < 80)
			{
				position.z += view.z * (float)(CAM_SPEED_MOV * dt);
				target.z += view.z * (float)(CAM_SPEED_MOV * dt);
			}
		}
		if (Application::IsKeyPressed('S'))
		{
			Vector3 view = (target - position).Normalized();
			if (position.x - (view.x * (float)(CAM_SPEED_MOV * dt)) > -35.7 && position.x - (view.x * (float)(CAM_SPEED_MOV * dt)) < 35.7)
			{
				position.x -= view.x * (float)(CAM_SPEED_MOV * dt);
				target.x -= view.x * (float)(CAM_SPEED_MOV * dt);
			}
			if (position.z - (view.z * (float)(CAM_SPEED_MOV * dt)) > 3 && position.z - (view.z * (float)(CAM_SPEED_MOV * dt)) < 80)
			{
				position.z -= view.z * (float)(CAM_SPEED_MOV * dt);
				target.z -= view.z * (float)(CAM_SPEED_MOV * dt);
			}
		}
	}
	
	if (Application::IsKeyPressed(VK_UP) && target.y <= 5.75)
	{	
		float pitch = (float)(CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
		up = rotation * up;
	}
	if (mousecursor.y < 600 / 2)
	{
		float pitch = (float)(CAM_SPEED_MOV * 0.5 * dt * (600 / 2 - mousecursor.y));
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		if (target.y < 5.75)
		{
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = view + position;
		}
	}
	if (Application::IsKeyPressed(VK_DOWN) && target.y >= 4.45)
	{
		float pitch = (float)(-CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
		up = rotation * up;
	}
	if (mousecursor.y > 600 / 2)
	{
		if (target.y > 4.45)
		{
			float pitch = (float)(-CAM_SPEED_MOV * 0.5 * dt * (mousecursor.y - 600 / 2));
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = view + position;
		}
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = (float)(-CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = view + position;
		up = rotation * up;
	}
	if (mousecursor.x > 800 / 2)
	{
		float yaw = (float)(-CAM_SPEED_MOV * 0.5 * dt *(mousecursor.x - 800 / 2));
		rotateChar += yaw;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;

	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		float yaw = (float)(CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = view + position;
		up = rotation * up;
	}
	if (mousecursor.x < 800 / 2)
	{
		float yaw = (float)(CAM_SPEED_MOV * 0.5 * dt *(800 / 2 - mousecursor.x));
		rotateChar += yaw;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	//if (Application::IsKeyPressed('N'))
	//{
	//	Vector3 direction = target - position;
	//	if (direction.Length() > 5)
	//	{
	//		Vector3 view = (target - position).Normalized();
	//		position += view * (float)(10.f * dt);
	//	}
	//}
	//if (Application::IsKeyPressed('M'))
	//{
	//	Vector3 view = (target - position).Normalized();
	//	position -= view * (float)(10.f * dt);
	//}
	//if (Application::IsKeyPressed('F'))
	//{
	//	drunkL = true;
	//}
	//if (drunkL == true)
	//{
	//	up += 0.5 * dt;
	//}
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
	if (Application::IsKeyPressed('E'))
		EPressed = true;
	SetCursorPos(800 / 2, 600 / 2);
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}