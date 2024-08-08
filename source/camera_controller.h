#pragma once

#include <numbers>
#include "math/vector3.h"

class Camera;

class CameraController
{
public:
    CameraController(Camera& camera);

	float GetVisibleAreaLength() const;
	float GetFieldOfView() const;
	float GetAngle() const;

	void RefreshCameraPosition();
	float CalculateDistance();

	Vector3 FocusPosition = Vector3::Zero;

	bool IsOrthogonal = false;
	float Rotation = 0;

	static constexpr float MinCellCount = 10.0f;
	static constexpr float MaxCellCount = 160.0f;
	float ZoomK = 0.0f;
	
	int ZoomStepCount = 20;

	static constexpr float MinFov = std::numbers::pi / 30.0f;
	static constexpr float MaxFov = std::numbers::pi / 3.0f;
	float FovK = 0.5f;

	static constexpr float MinAngle = std::numbers::pi * 0.20f;
	static constexpr float MaxAngle = std::numbers::pi * 0.49f;
	float AngleK = 0.5f;
	
	Camera& camera;
};