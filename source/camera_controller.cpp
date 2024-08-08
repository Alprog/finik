#include "camera_controller.h"

#include "camera.h"
#include <cmath>
#include "utils.h"

CameraController::CameraController(Camera& camera)
    : camera{ camera }
{
	RefreshCameraPosition();
}

float CameraController::GetVisibleAreaLength() const
{
	return lerp(MaxCellCount, MinCellCount, std::sqrt(ZoomK));
}

float CameraController::GetFieldOfView() const
{
	return lerp(MinFov, MaxFov, FovK);
}

float CameraController::GetAngle() const
{
	return lerp(MinAngle, MaxAngle, AngleK);
}

void CameraController::RefreshCameraPosition()
{
	auto angle = GetAngle();
	auto x = std::cos(angle) * std::sin(Rotation);
	auto y = std::sin(angle);
	auto z = std::cos(angle) * std::cos(Rotation);
	auto OffsetDirection = Vector3(x, y, z);

	//camera.Projection = IsOrthogonal ? Camera3D.ProjectionType.Orthogonal : Camera3D.ProjectionType.Perspective;
	//camera.Size = VisibleAreaLength * Mathf.Sin(Angle);
	
	auto Distance = IsOrthogonal ? 80.0f : CalculateDistance();
	camera.position = FocusPosition + OffsetDirection * Distance;
	camera.lookAt = FocusPosition;
	camera.FieldOfView = GetFieldOfView();

	camera.calcViewMatrix();
	camera.calcProjectionMatrix();
}

float CameraController::CalculateDistance()
{
	auto viewAngle = GetAngle();

	auto fieldOfView = GetFieldOfView();
	auto nearAngle = viewAngle + fieldOfView / 2;
	auto farAngle = viewAngle - fieldOfView / 2;

	auto nearXperY = std::cos(nearAngle) / std::sin(nearAngle);
	auto farXperY = std::cos(farAngle) / std::sin(farAngle);

	// (farXperY - nearXperY) * Y = VisibleAreaLength
	auto y = GetVisibleAreaLength() / (farXperY - nearXperY);
	return y / std::sin(viewAngle);
}