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
	"OvalFilled",
	"GroundCircle",
	"GroundPlane"
};

struct Cone
{
	// positions
	Vector3 circleCenter;
	Vector3 coneTip;

	// circle
	int slices;
	float radius;

	Cone()
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
	Oval leftFingers[5];
	Oval rightFingers[5];

	// Legs
	Oval leftLeg, rightLeg;
	Oval leftBoot, rightBoot;

	// Spikes
	std::vector<Cone> cones;
	Color coneColor;

	Sonic()
	{
		coneColor = Colors::DarkBlue;
	}
};

Sonic sonic;
void CreateSonic(Sonic& sonic)
{
	// Face
	sonic.face.sphereCenter = { 0.0f, 0.7f, -1.0f };
	sonic.face.radius = 1.0f;
	sonic.face.color = Colors::Blue;

	// Eyes
	// Left Eye
	sonic.leftEye.center = { 0.4f, 0.7f, -1.5f };
	sonic.leftEye.rx = 0.2f;
	sonic.leftEye.ry = 0.6f;
	sonic.leftEye.rz = 0.1f;
	sonic.leftEye.color = { 129, 129, 138, 255 };
	// Right Eye
	sonic.rightEye.center = { -0.4f, 0.7f, -1.5f };
	sonic.rightEye.rx = 0.2f;
	sonic.rightEye.ry = 0.6f;
	sonic.rightEye.rz = 0.1f;
	sonic.rightEye.color = { 129, 129, 138, 255 };

	// Pupils
	// Left Pupil
	sonic.leftPupil.center = { 0.4f, 0.4f, -1.6f };
	sonic.leftPupil.rx = 0.1f;
	sonic.leftPupil.ry = 0.2f;
	sonic.leftPupil.rz = 0.1f;
	sonic.leftPupil.color = { 0, 0, 0, 255 };
	// Right Pupil
	sonic.rightPupil.center = { -0.4f, 0.4f, -1.6f };
	sonic.rightPupil.rx = 0.1f;
	sonic.rightPupil.ry = 0.2f;
	sonic.rightPupil.rz = 0.1f;
	sonic.rightPupil.color = { 0, 0, 0, 255 };

	// Body
	sonic.body.center = { 0.0f, -0.3f, -1.0f };
	sonic.body.rx = 0.5f;
	sonic.body.ry = 0.8f;
	sonic.body.rz = 0.3f;
	sonic.body.color = Colors::Blue;

	// Arms
	// Left Arm
	sonic.leftArm.center = { 0.9f, -0.3f, -1.0f };
	sonic.leftArm.rx = 0.5f;
	sonic.leftArm.ry = 0.1f;
	sonic.leftArm.rz = 0.2f;
	sonic.leftArm.color = Colors::Blue;
	// Right Arm
	sonic.rightArm.center = { -0.9f, -0.3f, -1.0f };
	sonic.rightArm.rx = 0.5f;
	sonic.rightArm.ry = 0.1f;
	sonic.rightArm.rz = 0.2f;
	sonic.rightArm.color = Colors::Blue;

	// Hands
	// Left Hand
	sonic.leftHand.sphereCenter = { 1.5f, -0.3f, -1.0f };
	sonic.leftHand.radius = 0.3f;
	sonic.leftHand.color = Colors::White;
	// Right Hand
	sonic.rightHand.sphereCenter = { -1.5f, -0.3f, -1.0f };
	sonic.rightHand.radius = 0.3f;
	sonic.rightHand.color = Colors::White;

	// Fingers
	// Left Fingers
	for (int i = 0; i < 5; ++i)
	{
		sonic.leftFingers[i].center = { 1.8f, -0.3f, -0.15f * i - 0.8f }; // Adjust spacing for each finger
		sonic.leftFingers[i].rx = 0.2f;
		sonic.leftFingers[i].ry = 0.1f;
		sonic.leftFingers[i].rz = 0.1f;
		sonic.leftFingers[i].color = Colors::Gray;
	}

	// Right Fingers
	for (int i = 0; i < 5; ++i)
	{
		sonic.rightFingers[i].center = { -1.8f, -0.3f, -0.15f * i - 0.8f }; // Adjust spacing for each finger
		sonic.rightFingers[i].rx = 0.2f;
		sonic.rightFingers[i].ry = 0.1f;
		sonic.rightFingers[i].rz = 0.1f;
		sonic.rightFingers[i].color = Colors::Gray;
	}

	// Legs
	// Left Leg
	sonic.leftLeg.center = { 0.4f, -1.4f, -1.0f };
	sonic.leftLeg.rx = 0.1f;
	sonic.leftLeg.ry = 0.7f;
	sonic.leftLeg.rz = 0.1f;
	sonic.leftLeg.color = Colors::Blue;
	// Right Leg
	sonic.rightLeg.center = { -0.4f, -1.4f, -1.0f };
	sonic.rightLeg.rx = 0.1f;
	sonic.rightLeg.ry = 0.7f;
	sonic.rightLeg.rz = 0.1f;
	sonic.rightLeg.color = Colors::Blue;

	// Boots
	// Left Boot
	sonic.leftBoot.center = { 0.4f, -2.0f, -1.3f };
	sonic.leftBoot.rx = 0.2f;
	sonic.leftBoot.ry = 0.2f;
	sonic.leftBoot.rz = 0.5f;
	sonic.leftBoot.color = Colors::Red;
	// Right Boot
	sonic.rightBoot.center = { -0.4f, -2.0f, -1.3f };
	sonic.rightBoot.rx = 0.2f;
	sonic.rightBoot.ry = 0.2f;
	sonic.rightBoot.rz = 0.5f;
	sonic.rightBoot.color = Colors::Red;

	// Spikes (Cones)
	sonic.cones.resize(3);

	// Top Spike
	sonic.cones[0].circleCenter = { 0.0f, 0.9f, 0.2f };
	sonic.cones[0].coneTip = { 0.0f, 1.4f, -0.3f };
	sonic.cones[0].radius = 0.3f;
	sonic.cones[0].slices = 20;

	// Middle Spike
	sonic.cones[1].circleCenter = { 0.0f, 0.7f, 0.0f };
	sonic.cones[1].coneTip = { 0.0f, 1.1f, -0.5f };
	sonic.cones[1].radius = 0.35f;
	sonic.cones[1].slices = 20;

	// Bottom Spike
	sonic.cones[2].circleCenter = { 0.0f, 0.5f, -0.2f };
	sonic.cones[2].coneTip = { 0.0f, 0.8f, -0.7f };
	sonic.cones[2].radius = 0.4f;
	sonic.cones[2].slices = 20;
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

	// Body
	SimpleDraw::AddFilledOval(sonic.body.slices, sonic.body.rings, sonic.body.rx, sonic.body.ry, sonic.body.rz, sonic.body.center, sonic.body.color);

	// Arms
	SimpleDraw::AddFilledOval(sonic.leftArm.slices, sonic.leftArm.rings, sonic.leftArm.rx, sonic.leftArm.ry, sonic.leftArm.rz, sonic.leftArm.center, sonic.leftArm.color);
	SimpleDraw::AddFilledOval(sonic.rightArm.slices, sonic.rightArm.rings, sonic.rightArm.rx, sonic.rightArm.ry, sonic.rightArm.rz, sonic.rightArm.center, sonic.rightArm.color);

	// Hands
	SimpleDraw::AddFilledSphere(sonic.leftHand.slices, sonic.leftHand.rings, sonic.leftHand.radius, sonic.leftHand.sphereCenter, sonic.leftHand.color);
	SimpleDraw::AddFilledSphere(sonic.rightHand.slices, sonic.rightHand.rings, sonic.rightHand.radius, sonic.rightHand.sphereCenter, sonic.rightHand.color);

	// Legs
	SimpleDraw::AddFilledOval(sonic.leftLeg.slices, sonic.leftLeg.rings, sonic.leftLeg.rx, sonic.leftLeg.ry, sonic.leftLeg.rz, sonic.leftLeg.center, sonic.leftLeg.color);
	SimpleDraw::AddFilledOval(sonic.rightLeg.slices, sonic.rightLeg.rings, sonic.rightLeg.rx, sonic.rightLeg.ry, sonic.rightLeg.rz, sonic.rightLeg.center, sonic.rightLeg.color);

	// Boots
	SimpleDraw::AddFilledOval(sonic.leftBoot.slices, sonic.leftBoot.rings, sonic.leftBoot.rx, sonic.leftBoot.ry, sonic.leftBoot.rz, sonic.leftBoot.center, sonic.leftBoot.color);
	SimpleDraw::AddFilledOval(sonic.rightBoot.slices, sonic.rightBoot.rings, sonic.rightBoot.rx, sonic.rightBoot.ry, sonic.rightBoot.rz, sonic.rightBoot.center, sonic.rightBoot.color);

	// Spikes (Cones)
	for (const auto& cone : sonic.cones)
	{
		SimpleDraw::AddCone(cone.slices, cone.radius, cone.circleCenter, cone.coneTip, sonic.coneColor);
	}

	// Fingers
	for (const auto& finger : sonic.leftFingers)
	{
		SimpleDraw::AddFilledOval(finger.slices, finger.rings, finger.rx, finger.ry, finger.rz, finger.center, finger.color);
	}
	for (const auto& finger : sonic.rightFingers)
	{
		SimpleDraw::AddFilledOval(finger.slices, finger.rings, finger.rx, finger.ry, finger.rz, finger.center, finger.color);
	}
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

	else if (mDebugDrawType == DebugDrawType::GroundCircle)
	{
		SimpleDraw::AddGroundCircle(slices, radius, minExtents, lineColor);
	}

	else if (mDebugDrawType == DebugDrawType::GroundPlane)
	{
		SimpleDraw::AddGroundPlane(radius, lineColor);
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
				ImGui::DragFloat3("Face Pos", &sonic.face.sphereCenter.x, 0.1f);
				ImGui::DragFloat("Face Radius", &sonic.face.radius, 0.1f);
				ImGui::ColorEdit4("Face Color", &sonic.face.color.r);
			}

			// Eyes
			if (ImGui::CollapsingHeader("Eyes"))
			{
				if (ImGui::CollapsingHeader("Left Eye"))
				{
					ImGui::DragFloat3("Left Eye Pos", &sonic.leftEye.center.x, 0.1f);
					ImGui::DragFloat("Left Eye Rx", &sonic.leftEye.rx, 0.1f);
					ImGui::DragFloat("Left Eye Ry", &sonic.leftEye.ry, 0.1f);
					ImGui::DragFloat("Left Eye Rz", &sonic.leftEye.rz, 0.1f);
					ImGui::ColorEdit4("Left Eye Color", &sonic.leftEye.color.r);
				}

				if (ImGui::CollapsingHeader("Right Eye"))
				{
					ImGui::DragFloat3("Right Eye Pos", &sonic.rightEye.center.x, 0.1f);
					ImGui::DragFloat("Right Eye Rx", &sonic.rightEye.rx, 0.1f);
					ImGui::DragFloat("Right Eye Ry", &sonic.rightEye.ry, 0.1f);
					ImGui::DragFloat("Right Eye Rz", &sonic.rightEye.rz, 0.1f);
					ImGui::ColorEdit4("Right Eye Color", &sonic.rightEye.color.r);
				}
			}

			// Pupils
			if (ImGui::CollapsingHeader("Pupils"))
			{
				if (ImGui::CollapsingHeader("Left Pupil"))
				{
					ImGui::DragFloat3("Left Pupil Pos", &sonic.leftPupil.center.x, 0.1f);
					ImGui::DragFloat("Left Pupil Rx", &sonic.leftPupil.rx, 0.1f);
					ImGui::DragFloat("Left Pupil Ry", &sonic.leftPupil.ry, 0.1f);
					ImGui::DragFloat("Left Pupil Rz", &sonic.leftPupil.rz, 0.1f);
					ImGui::ColorEdit4("Left Pupil Color", &sonic.leftPupil.color.r);
				}

				if (ImGui::CollapsingHeader("Right Pupil"))
				{
					ImGui::DragFloat3("Right Pupil Pos", &sonic.rightPupil.center.x, 0.1f);
					ImGui::DragFloat("Right Pupil Rx", &sonic.rightPupil.rx, 0.1f);
					ImGui::DragFloat("Right Pupil Ry", &sonic.rightPupil.ry, 0.1f);
					ImGui::DragFloat("Right Pupil Rz", &sonic.rightPupil.rz, 0.1f);
					ImGui::ColorEdit4("Right Pupil Color", &sonic.rightPupil.color.r);
				}
			}
		}

		// Body
		if (ImGui::CollapsingHeader("Body"))
		{
			ImGui::DragFloat3("Body Pos", &sonic.body.center.x, 0.1f);
			ImGui::DragFloat("Body Rx", &sonic.body.rx, 0.1f);
			ImGui::DragFloat("Body Ry", &sonic.body.ry, 0.1f);
			ImGui::DragFloat("Body Rz", &sonic.body.rz, 0.1f);
			ImGui::ColorEdit4("Body Color", &sonic.body.color.r);
		}

		// Arms
		if (ImGui::CollapsingHeader("Arms"))
		{
			if (ImGui::CollapsingHeader("Left Arm"))
			{
				ImGui::DragFloat3("Left Arm Pos", &sonic.leftArm.center.x, 0.1f);
				ImGui::DragFloat("Left Arm Rx", &sonic.leftArm.rx, 0.1f);
				ImGui::DragFloat("Left Arm Ry", &sonic.leftArm.ry, 0.1f);
				ImGui::DragFloat("Left Arm Rz", &sonic.leftArm.rz, 0.1f);
				ImGui::ColorEdit4("Left Arm Color", &sonic.leftArm.color.r);
			}

			if (ImGui::CollapsingHeader("Right Arm"))
			{
				ImGui::DragFloat3("Right Arm Pos", &sonic.rightArm.center.x, 0.1f);
				ImGui::DragFloat("Right Arm Rx", &sonic.rightArm.rx, 0.1f);
				ImGui::DragFloat("Right Arm Ry", &sonic.rightArm.ry, 0.1f);
				ImGui::DragFloat("Right Arm Rz", &sonic.rightArm.rz, 0.1f);
				ImGui::ColorEdit4("Right Arm Color", &sonic.rightArm.color.r);
			}
		}

		// Hands
		if (ImGui::CollapsingHeader("Hands"))
		{
			if (ImGui::CollapsingHeader("Left Hand"))
			{
				ImGui::DragFloat3("Left Hand Pos", &sonic.leftHand.sphereCenter.x, 0.1f);
				ImGui::DragFloat("Left Hand Radius", &sonic.leftHand.radius, 0.1f);
				ImGui::ColorEdit4("Left Hand Color", &sonic.leftHand.color.r);
			}

			if (ImGui::CollapsingHeader("Right Hand"))
			{
				ImGui::DragFloat3("Right Hand Pos", &sonic.rightHand.sphereCenter.x, 0.1f);
				ImGui::DragFloat("Right Hand Radius", &sonic.rightHand.radius, 0.1f);
				ImGui::ColorEdit4("Right Hand Color", &sonic.rightHand.color.r);
			}
		}

		// Fingers
		if (ImGui::CollapsingHeader("Fingers"))
		{
			// Left Fingers
			if (ImGui::CollapsingHeader("Left Fingers"))
			{
				ImGui::DragFloat3("Left Finger 1 Pos", &sonic.leftFingers[0].center.x, 0.1f);
				ImGui::DragFloat("Left Finger 1 Rx", &sonic.leftFingers[0].rx, 0.1f);
				ImGui::DragFloat("Left Finger 1 Ry", &sonic.leftFingers[0].ry, 0.1f);
				ImGui::DragFloat("Left Finger 1 Rz", &sonic.leftFingers[0].rz, 0.1f);
				ImGui::ColorEdit4("Left Finger 1 Color", &sonic.leftFingers[0].color.r);

				ImGui::DragFloat3("Left Finger 2 Pos", &sonic.leftFingers[1].center.x, 0.1f);
				ImGui::DragFloat("Left Finger 2 Rx", &sonic.leftFingers[1].rx, 0.1f);
				ImGui::DragFloat("Left Finger 2 Ry", &sonic.leftFingers[1].ry, 0.1f);
				ImGui::DragFloat("Left Finger 2 Rz", &sonic.leftFingers[1].rz, 0.1f);
				ImGui::ColorEdit4("Left Finger 2 Color", &sonic.leftFingers[1].color.r);

				ImGui::DragFloat3("Left Finger 3 Pos", &sonic.leftFingers[2].center.x, 0.1f);
				ImGui::DragFloat("Left Finger 3 Rx", &sonic.leftFingers[2].rx, 0.1f);
				ImGui::DragFloat("Left Finger 3 Ry", &sonic.leftFingers[2].ry, 0.1f);
				ImGui::DragFloat("Left Finger 3 Rz", &sonic.leftFingers[2].rz, 0.1f);
				ImGui::ColorEdit4("Left Finger 3 Color", &sonic.leftFingers[2].color.r);

				ImGui::DragFloat3("Left Finger 4 Pos", &sonic.leftFingers[3].center.x, 0.1f);
				ImGui::DragFloat("Left Finger 4 Rx", &sonic.leftFingers[3].rx, 0.1f);
				ImGui::DragFloat("Left Finger 4 Ry", &sonic.leftFingers[3].ry, 0.1f);
				ImGui::DragFloat("Left Finger 4 Rz", &sonic.leftFingers[3].rz, 0.1f);
				ImGui::ColorEdit4("Left Finger 4 Color", &sonic.leftFingers[3].color.r);

				ImGui::DragFloat3("Left Finger 5 Pos", &sonic.leftFingers[4].center.x, 0.1f);
				ImGui::DragFloat("Left Finger 5 Rx", &sonic.leftFingers[4].rx, 0.1f);
				ImGui::DragFloat("Left Finger 5 Ry", &sonic.leftFingers[4].ry, 0.1f);
				ImGui::DragFloat("Left Finger 5 Rz", &sonic.leftFingers[4].rz, 0.1f);
				ImGui::ColorEdit4("Left Finger 5 Color", &sonic.leftFingers[4].color.r);
			}

			// Right Fingers
			if (ImGui::CollapsingHeader("Right Fingers"))
			{
				ImGui::DragFloat3("Right Finger 1 Pos", &sonic.rightFingers[0].center.x, 0.1f);
				ImGui::DragFloat("Right Finger 1 Rx", &sonic.rightFingers[0].rx, 0.1f);
				ImGui::DragFloat("Right Finger 1 Ry", &sonic.rightFingers[0].ry, 0.1f);
				ImGui::DragFloat("Right Finger 1 Rz", &sonic.rightFingers[0].rz, 0.1f);
				ImGui::ColorEdit4("Right Finger 1 Color", &sonic.rightFingers[0].color.r);

				ImGui::DragFloat3("Right Finger 2 Pos", &sonic.rightFingers[1].center.x, 0.1f);
				ImGui::DragFloat("Right Finger 2 Rx", &sonic.rightFingers[1].rx, 0.1f);
				ImGui::DragFloat("Right Finger 2 Ry", &sonic.rightFingers[1].ry, 0.1f);
				ImGui::DragFloat("Right Finger 2 Rz", &sonic.rightFingers[1].rz, 0.1f);
				ImGui::ColorEdit4("Right Finger 2 Color", &sonic.rightFingers[1].color.r);

				ImGui::DragFloat3("Right Finger 3 Pos", &sonic.rightFingers[2].center.x, 0.1f);
				ImGui::DragFloat("Right Finger 3 Rx", &sonic.rightFingers[2].rx, 0.1f);
				ImGui::DragFloat("Right Finger 3 Ry", &sonic.rightFingers[2].ry, 0.1f);
				ImGui::DragFloat("Right Finger 3 Rz", &sonic.rightFingers[2].rz, 0.1f);
				ImGui::ColorEdit4("Right Finger 3 Color", &sonic.rightFingers[2].color.r);

				ImGui::DragFloat3("Right Finger 4 Pos", &sonic.rightFingers[3].center.x, 0.1f);
				ImGui::DragFloat("Right Finger 4 Rx", &sonic.rightFingers[3].rx, 0.1f);
				ImGui::DragFloat("Right Finger 4 Ry", &sonic.rightFingers[3].ry, 0.1f);
				ImGui::DragFloat("Right Finger 4 Rz", &sonic.rightFingers[3].rz, 0.1f);
				ImGui::ColorEdit4("Right Finger 4 Color", &sonic.rightFingers[3].color.r);

				ImGui::DragFloat3("Right Finger 5 Pos", &sonic.rightFingers[4].center.x, 0.1f);
				ImGui::DragFloat("Right Finger 5 Rx", &sonic.rightFingers[4].rx, 0.1f);
				ImGui::DragFloat("Right Finger 5 Ry", &sonic.rightFingers[4].ry, 0.1f);
				ImGui::DragFloat("Right Finger 5 Rz", &sonic.rightFingers[4].rz, 0.1f);
				ImGui::ColorEdit4("Right Finger 5 Color", &sonic.rightFingers[4].color.r);
			}
		}

		// Legs
		if (ImGui::CollapsingHeader("Legs"))
		{
			if (ImGui::CollapsingHeader("Left Leg"))
			{
				ImGui::DragFloat3("Left Leg Pos", &sonic.leftLeg.center.x, 0.1f);
				ImGui::DragFloat("Left Leg Rx", &sonic.leftLeg.rx, 0.1f);
				ImGui::DragFloat("Left Leg Ry", &sonic.leftLeg.ry, 0.1f);
				ImGui::DragFloat("Left Leg Rz", &sonic.leftLeg.rz, 0.1f);
				ImGui::ColorEdit4("Left Leg Color", &sonic.leftLeg.color.r);
			}

			if (ImGui::CollapsingHeader("Right Leg"))
			{
				ImGui::DragFloat3("Right Leg Pos", &sonic.rightLeg.center.x, 0.1f);
				ImGui::DragFloat("Right Leg Rx", &sonic.rightLeg.rx, 0.1f);
				ImGui::DragFloat("Right Leg Ry", &sonic.rightLeg.ry, 0.1f);
				ImGui::DragFloat("Right Leg Rz", &sonic.rightLeg.rz, 0.1f);
				ImGui::ColorEdit4("Right Leg Color", &sonic.rightLeg.color.r);
			}
		}

		// Boots
		if (ImGui::CollapsingHeader("Boots"))
		{
			if (ImGui::CollapsingHeader("Left Boot"))
			{
				ImGui::DragFloat3("Left Boot Pos", &sonic.leftBoot.center.x, 0.1f);
				ImGui::DragFloat("Left Boot Rx", &sonic.leftBoot.rx, 0.1f);
				ImGui::DragFloat("Left Boot Ry", &sonic.leftBoot.ry, 0.1f);
				ImGui::DragFloat("Left Boot Rz", &sonic.leftBoot.rz, 0.1f);
				ImGui::ColorEdit4("Left Boot Color", &sonic.leftBoot.color.r);
			}

			if (ImGui::CollapsingHeader("Right Boot"))
			{
				ImGui::DragFloat3("Right Boot Pos", &sonic.rightBoot.center.x, 0.1f);
				ImGui::DragFloat("Right Boot Rx", &sonic.rightBoot.rx, 0.1f);
				ImGui::DragFloat("Right Boot Ry", &sonic.rightBoot.ry, 0.1f);
				ImGui::DragFloat("Right Boot Rz", &sonic.rightBoot.rz, 0.1f);
				ImGui::ColorEdit4("Right Boot Color", &sonic.rightBoot.color.r);
			}
		}

		// Spikes (Cones)
		if (ImGui::CollapsingHeader("Spikes"))
		{
			for (int i = 0; i < sonic.cones.size(); ++i)
			{
				if (ImGui::CollapsingHeader(("Spike " + std::to_string(i + 1)).c_str()))
				{
					ImGui::DragFloat3(("Spike " + std::to_string(i + 1) + " Base Pos").c_str(), &sonic.cones[i].circleCenter.x, 0.1f);
					ImGui::DragFloat3(("Spike " + std::to_string(i + 1) + " Tip Pos").c_str(), &sonic.cones[i].coneTip.x, 0.1f);
					ImGui::DragFloat(("Spike " + std::to_string(i + 1) + " Radius").c_str(), &sonic.cones[i].radius, 0.1f);
					ImGui::ColorEdit4(("Spike " + std::to_string(i + 1) + " Color").c_str(), &sonic.coneColor.r);
				}
			}
		}
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

	else if (mDebugDrawType == DebugDrawType::GroundCircle)
	{
		ImGui::DragInt("Slices", &slices);
		ImGui::DragFloat("Radius", &radius);
		ImGui::DragFloat3("Pos", &minExtents.x);
	}

	else if (mDebugDrawType == DebugDrawType::GroundPlane)
	{
		ImGui::DragFloat("Size", &radius);
	}

	ImGui::ColorEdit4("Color", &lineColor.r);
	ImGui::End();
}

