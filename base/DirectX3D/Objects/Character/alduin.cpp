#include "Framework.h"
#include "alduin.h"

alduin::alduin() : ModelAnimator("alduin")
{
	alduinCollider = new CapsuleCollider();
	ReadClip("alduin_idle");
	ReadClip("alduin_bleedidle");
	ReadClip("alduin_takeoff");
	ReadClip("alduin_fly");
	ReadClip("alduin_hover");
	ReadClip("alduin_flight_forward");
	ReadClip("alduin_flight_hit");
	ReadClip("alduin_ascend");
	ReadClip("alduin_climb");
	ReadClip("alduin_aproach");
	ReadClip("alduin_descend");
	ReadClip("alduin_backward");
	ReadClip("alduin_injured");
	ReadClip("alduin_inhale");
	ReadClip("alduin_exhale_breath");
	ReadClip("alduin_exhale_fireball");
	ReadClip("alduin_wingswip_left");
	ReadClip("alduin_wingswip_right");
	ReadClip("alduin_bite");
	ReadClip("alduin_pain");
	ReadClip("alduin_pain2");
	ReadClip("alduin_tailwhip");
	ReadClip("alduin_timetravel");
	Scale() *= 0.001;

	moveSpeed = 150.0f;

}

alduin::~alduin()
{
}

void alduin::Update()
{
	ModelAnimator::Update(); 

	alduinCollider->UpdateWorld();

	SetAnimation();
}

void alduin::Render()
{
	ModelAnimator::Render();
	alduinCollider->Render();
}

void alduin::GUIRender()
{
	Model::GUIRender();
}

void alduin::SetTarget(Transform* target)
{
	this->target = target;
}


void alduin::SetAnimation()
{
	if (curState == BREATH) return;

	if (velocity.z > 0.1f) // 속력 기준이 현재 앞으로 +면
		SetState(RUN);
	//else if (velocity.z < -0.1f) // 앞 기준 -면
	//	SetState(RUN_B);
	else if (velocity.x > 0.1f) // 좌우 기준 +면
		SetState(RUN_R);
	else if (velocity.x < -0.1f) //좌우 기준 -면
		SetState(RUN_L);
	else SetState(IDLE); // 가만히 있으면
}

void alduin::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	PlayClip((int)state);
}

void alduin::Pattern1()
{
}

void alduin::Pattern2()
{
}
