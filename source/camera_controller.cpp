#include "camera_controller.h"

#include "camera.h"
#include "utils.h"

import std;
import imgui;

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
	return IsOrthogonal ? 0 : lerp(MinFov, MaxFov, FovK);
}

float CameraController::GetAngle() const
{
	return lerp(MinAngle, MaxAngle, AngleK);
}

void CameraController::HandleInput(float deltaTime)
{
	auto Direction = Vector3::Zero;

	if (ImGui::IsKeyDown(ImGuiKey_W))
	{
		Direction += Vector3::Forward;
	}
	if (ImGui::IsKeyDown(ImGuiKey_S))
	{
		Direction += Vector3::Backward;
	}
	if (ImGui::IsKeyDown(ImGuiKey_A))
	{
		Direction += Vector3::Left;
	}
	if (ImGui::IsKeyDown(ImGuiKey_D))
	{
		Direction += Vector3::Right;
	}

	Direction = Matrix::RotationZ(Rotation).MultiplyDirection(Direction);

	ZoomK += ImGui::GetIO().MouseWheel / ZoomStepCount;
	if (ImGui::IsKeyDown(ImGuiKey_Q))
	{
		ZoomK -= deltaTime / 2;
	}
	if (ImGui::IsKeyDown(ImGuiKey_E))
	{
		ZoomK += deltaTime / 2;
	}
	ZoomK = std::clamp(ZoomK, 0.0f, 1.0f);

	float PanningScreenPerSecond = 1.0f;
	if (ImGui::IsKeyDown(ImGuiKey_LeftShift))
	{
		PanningScreenPerSecond *= 3;
	}
	FocusPosition += Direction * GetVisibleAreaLength() * PanningScreenPerSecond * deltaTime;

	if (ImGui::IsKeyDown(ImGuiKey_Z))
	{
		AngleK -= deltaTime / 2;
	}
	if (ImGui::IsKeyDown(ImGuiKey_X))
	{
		AngleK += deltaTime / 2;
	}
	AngleK = std::clamp(AngleK, 0.0f, 1.0f);

	if (ImGui::IsKeyDown(ImGuiKey_1))
	{
		IsOrthogonal = false;
	}
	if (ImGui::IsKeyDown(ImGuiKey_2))
	{
		IsOrthogonal = true;
	}

	if (ImGui::IsKeyDown(ImGuiKey_O))
	{
		FovK -= deltaTime / 2;
		IsOrthogonal = FovK <= 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_P))
	{
		IsOrthogonal = false;
		FovK += deltaTime / 2;
	}
	FovK = std::clamp(FovK, 0.0f, 1.0f);

	if (ImGui::IsKeyDown(ImGuiKey_Y))
	{
		Rotation -= std::numbers::pi * deltaTime / 4;
	}
	if (ImGui::IsKeyDown(ImGuiKey_U))
	{
		Rotation += std::numbers::pi * deltaTime / 4;
	}
}

void CameraController::RefreshCameraPosition()
{
	auto angle = GetAngle();
	auto x = std::cos(angle) * -std::sin(Rotation);
	auto y = std::cos(angle) * std::cos(Rotation);
	auto z = std::sin(angle);	
	auto OffsetDirection = Vector3(x, y, z);

	
	auto Distance = CalculateDistance();
	camera.position = FocusPosition + OffsetDirection * Distance;
	camera.lookAt = FocusPosition;
	
	camera.FieldOfView = GetFieldOfView();
	camera.OrthoSize = GetVisibleAreaLength() * std::sin(angle);

	camera.calcViewMatrix();
	camera.calcProjectionMatrix();
}

float CameraController::CalculateDistance()
{
	auto fieldOfView = GetFieldOfView();
	if (fieldOfView == 0)
	{
		return 80.0f;
	}

	auto viewAngle = GetAngle();

	auto nearAngle = viewAngle + fieldOfView / 2;
	auto farAngle = viewAngle - fieldOfView / 2;

	auto nearXperY = std::cos(nearAngle) / std::sin(nearAngle);
	auto farXperY = std::cos(farAngle) / std::sin(farAngle);

	// (farXperY - nearXperY) * Y = VisibleAreaLength
	auto y = GetVisibleAreaLength() / (farXperY - nearXperY);
	return y / std::sin(viewAngle);
}