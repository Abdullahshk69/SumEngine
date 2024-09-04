#include "GameState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;

const char* gDrawTypeNames[] =
{
	"None",
	"Cone",
	"Line",
	"Sphere",
	"AABB",
	"AABBFilled",
	"Sonic",
	"Oval",
	"OvalFilled"
};

struct SonicCone
{
	// positions
	Vector3 circleCenter;
	Vector3 coneTip;

	// circle
	int slices;
	float radius;

	SonicCone()
	{
		circleCenter = Vector3::Zero;
		coneTip = Vector3::YAxis;

		slices = 30;
		radius = 2.0f;
	}
};

struct Sphere
{
	int slices;
	int rings;
	float radius;
	Vector3 sphereCenter;
	Color color;

	Sphere()
	{
		slices = 30;
		rings = 30;
		radius = 2.0f;
		sphereCenter = Vector3::Zero;

		color = Colors::Blue;
	}
};

struct Oval
{
	int slices;
	int rings;
	float rx, ry, rz;

	Vector3 center;
	Color color;

	Oval()
	{
		slices = 30;
		rings = 30;
		rx = ry = rz = 2.0f;

		center = Vector3::Zero;
		color = Colors::Blue;
	}
};

struct Sonic
{
	// Face
	Sphere face;
	Oval leftEye, rightEye;
	Oval leftPupil, rightPupil;


	// body
	Oval body;

	// Arms
	Oval leftArm, rightArm;
	Sphere leftHand, rightHand;
	Oval lf1, lf2, lf3, lf4, lf5,
		rf1, rf2, rf3, rf4, rf5;

	// Legs
	Oval leftLeg, rightLeg;
	Oval leftBoot, rightBoot;

	// Spikes
	std::vector<SonicCone> cones;
	Color coneColor;

	Sonic()
	{
		coneColor = Colors::DarkBlue;
	}
};

Sonic sonic;
void CreateSonic(Sonic& sonic)
{
	// Eyes
		// Left Eye
	sonic.leftEye.center = { 0.6f, 0.7f, -1.5f };
	sonic.leftEye.rx = 0.2f;
	sonic.leftEye.ry = 0.6f;
	sonic.leftEye.rz = 0.1f;
	sonic.leftEye.color = { 129, 129, 138, 255 };
		// Right Eye
	sonic.rightEye.center = { -0.6f, 0.7f, -1.5f };
	sonic.rightEye.rx = 0.2f;
	sonic.rightEye.ry = 0.6f;
	sonic.rightEye.rz = 0.1f;
	sonic.rightEye.color = { 129, 129, 138, 255 };

	// Pupils
		// Left Pupil
	sonic.leftPupil.center = { 0.6f, 0.4f, -1.6f };
	sonic.leftPupil.rx = 0.1f;
	sonic.leftPupil.ry = 0.2f;
	sonic.leftPupil.rz = 0.1f;
	sonic.leftPupil.color = { 0, 0, 0, 255 };
		// Right Pupil
	sonic.rightPupil.center = { -0.6f, 0.4f, -1.6f };
	sonic.rightPupil.rx = 0.1f;
	sonic.rightPupil.ry = 0.2f;
	sonic.rightPupil.rz = 0.1f;
	sonic.rightPupil.color = { 0, 0, 0, 255 };
}

void DrawSonic(const Sonic& sonic)
{
	// Face
	SimpleDraw::AddFilledSphere(sonic.face.slices, sonic.face.rings, sonic.face.radius, sonic.face.sphereCenter, sonic.face.color);

	// Eyes
	SimpleDraw::AddFilledOval(sonic.leftEye.slices, sonic.leftEye.rings, sonic.leftEye.rx, sonic.leftEye.ry, sonic.leftEye.rz, sonic.leftEye.center, sonic.leftEye.color);
	SimpleDraw::AddFilledOval(sonic.rightEye.slices, sonic.rightEye.rings, sonic.rightEye.rx, sonic.rightEye.ry, sonic.rightEye.rz, sonic.rightEye.center, sonic.rightEye.color);

	// Pupils
	SimpleDraw::AddFilledOval(sonic.leftPupil.slices, sonic.leftPupil.rings, sonic.leftPupil.rx, sonic.leftPupil.ry, sonic.leftPupil.rz, sonic.leftPupil.center, sonic.leftPupil.color);
	SimpleDraw::AddFilledOval(sonic.rightPupil.slices, sonic.rightPupil.rings, sonic.rightPupil.rx, sonic.rightPupil.ry, sonic.rightPupil.rz, sonic.rightPupil.center, sonic.rightPupil.color);
}

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	CreateSonic(sonic);
}

void GameState::Terminate()
{
	
}


void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
	const float turnSpeed = 0.1f * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

Vector3 minExtents = -Vector3::One;
Vector3 maxExtents = Vector3::One;
float radius = 10.0f;
int slices = 10;
int rings = 10;
float rx = 5.0f;
float ry = 5.0f;
float rz = 5.0f;
Color lineColor = Colors::Green;

void GameState::Render()
{
	if (mDebugDrawType == DebugDrawType::Sphere)
	{
		SimpleDraw::AddSphere(30, 30, 2.0f, minExtents, lineColor);
	}

	else if (mDebugDrawType == DebugDrawType::Cone)
	{
		SimpleDraw::AddCone(slices, radius, minExtents, maxExtents, lineColor);
	}

	else if (mDebugDrawType == DebugDrawType::Line)
	{
		SimpleDraw::AddLine(minExtents, maxExtents, lineColor);
	}

	else if (mDebugDrawType == DebugDrawType::AABB)
	{
		SimpleDraw::AddAABB(minExtents, maxExtents, lineColor);
	}

	else if (mDebugDrawType == DebugDrawType::AABBFilled)
	{
		SimpleDraw::AddFilledAABB(minExtents, maxExtents, lineColor);
	}

	else if (mDebugDrawType == DebugDrawType::Sonic)
	{
		DrawSonic(sonic);
	}

	else if (mDebugDrawType == DebugDrawType::Oval)
	{
		SimpleDraw::AddOval(slices, rings, rx, ry, rz, minExtents, lineColor);
	}

	else if (mDebugDrawType == DebugDrawType::OvalFilled)
	{
		SimpleDraw::AddFilledOval(slices, rings, rx, ry, rz, minExtents, lineColor);
	}

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	int currentDrawType = static_cast<int>(mDebugDrawType);
	if (ImGui::Combo("DrawType", &currentDrawType, gDrawTypeNames, static_cast<int>(std::size(gDrawTypeNames))))
	{
		mDebugDrawType = (DebugDrawType)currentDrawType;
	}

	if (mDebugDrawType == DebugDrawType::Sphere)
	{
		// ImGui::DragFloat("SphereRadius", &radius, 0.1f, 0.01f, 1000000.0f);
		ImGui::DragFloat3("Pos", &minExtents.x);
	}
	
	else if (mDebugDrawType == DebugDrawType::Cone)
	{
		ImGui::DragFloat3("Circle Center", &minExtents.x);
		ImGui::DragFloat3("Cone Tip", &maxExtents.x);
		ImGui::DragFloat("Circle Radius", &radius);
		ImGui::DragInt("Slices", &slices);
	}

	else if (mDebugDrawType == DebugDrawType::Line)
	{
		ImGui::DragFloat3("LineStart", &minExtents.x);
		ImGui::DragFloat3("LineEnd", &maxExtents.x);
	}

	else if (mDebugDrawType == DebugDrawType::AABB)
	{
		ImGui::DragFloat3("minExtent", &minExtents.x);
		ImGui::DragFloat3("maxExtent", &maxExtents.x);
	}

	else if (mDebugDrawType == DebugDrawType::AABBFilled)
	{
		ImGui::DragFloat3("minExtent", &minExtents.x);
		ImGui::DragFloat3("maxExtent", &maxExtents.x);
	}

	else if (mDebugDrawType == DebugDrawType::Sonic)
	{
		// Head
		if (ImGui::CollapsingHeader("Head"))
		{



			// Face
			if (ImGui::CollapsingHeader("Face"))
			{
				//ImGui::Unindent();
				ImGui::DragFloat3("Face Pos", &sonic.face.sphereCenter.x, 0.1f);
				ImGui::Indent();
				ImGui::ColorEdit4("Face Color", &sonic.face.color.r);
				ImGui::Indent();
				ImGui::DragFloat("Face Radius", &sonic.face.radius, 0.1f);
			}


			// Eyes
			if (ImGui::CollapsingHeader("Eyes"))
			{
				if (ImGui::CollapsingHeader("Left Eye"))
				{
					ImGui::DragFloat3("Left Eye", &sonic.leftEye.center.x, 0.1f);
					ImGui::DragFloat("Left Eye Rx", &sonic.leftEye.rx, 0.1f);
					ImGui::DragFloat("Left Eye Ry", &sonic.leftEye.ry, 0.1f);
					ImGui::DragFloat("Left Eye Rz", &sonic.leftEye.rz, 0.1f);
					ImGui::ColorEdit4("Left Eye Color", &sonic.leftEye.color.r);
				}

				if (ImGui::CollapsingHeader("Right Eye"))
				{
					ImGui::DragFloat3("Right Eye", &sonic.rightEye.center.x, 0.1f);
					ImGui::DragFloat("Right Eye Rx", &sonic.rightEye.rx, 0.1f);
					ImGui::DragFloat("Right Eye Ry", &sonic.rightEye.ry, 0.1f);
					ImGui::DragFloat("Right Eye Rz", &sonic.rightEye.rz, 0.1f);
					ImGui::ColorEdit4("Right Eye Color", &sonic.rightEye.color.r);
				}
			}

			if (ImGui::CollapsingHeader("Pupils"))
			{
				if (ImGui::CollapsingHeader("Left Pupil"))
				{
					ImGui::DragFloat3("Left Pupil", &sonic.leftPupil.center.x, 0.1f);
					ImGui::DragFloat("Left Pupil Rx", &sonic.leftPupil.rx, 0.1f);
					ImGui::DragFloat("Left Pupil Ry", &sonic.leftPupil.ry, 0.1f);
					ImGui::DragFloat("Left Pupil Rz", &sonic.leftPupil.rz, 0.1f);
					ImGui::ColorEdit4("Left Pupil Color", &sonic.leftPupil.color.r);
				}

				if (ImGui::CollapsingHeader("Right Pupil"))
				{
					ImGui::DragFloat3("Right Pupil", &sonic.rightPupil.center.x, 0.1f);
					ImGui::DragFloat("Right Pupil Rx", &sonic.rightPupil.rx, 0.1f);
					ImGui::DragFloat("Right Pupil Ry", &sonic.rightPupil.ry, 0.1f);
					ImGui::DragFloat("Right Pupil Rz", &sonic.rightPupil.rz, 0.1f);
					ImGui::ColorEdit4("Right Pupil Color", &sonic.rightPupil.color.r);
				}
			}
		}


		// Body
		
	}

	else if (mDebugDrawType == DebugDrawType::Oval)
	{
		ImGui::DragFloat3("Circle Center", &minExtents.x);
		ImGui::DragFloat("Rx", &rx);
		ImGui::DragFloat("Ry", &ry);
		ImGui::DragFloat("Rz", &rz);
		ImGui::DragInt("Slices", &slices);
		ImGui::DragInt("Rings", &rings);
	}

	else if (mDebugDrawType == DebugDrawType::OvalFilled)
	{
		ImGui::DragFloat3("Circle Center", &minExtents.x);
		ImGui::DragFloat("Rx", &rx);
		ImGui::DragFloat("Ry", &ry);
		ImGui::DragFloat("Rz", &rz);
		ImGui::DragInt("Slices", &slices);
		ImGui::DragInt("Rings", &rings);
	}

	ImGui::ColorEdit4("Color", &lineColor.r);
	ImGui::End();
}

