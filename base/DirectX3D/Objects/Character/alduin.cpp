#include "Framework.h"
#include "alduin.h"

alduin::alduin() :  ModelAnimator("alduin")
{
	transform = new Transform();
	alduinCollider = new CapsuleCollider();

	collider_F = new SphereCollider();
	collider_F->Pos().SetZ(-30);
	collider_F->SetParent(transform);
	collider_F->Scale() *= 30;

	collider_R = new SphereCollider();
	collider_R->Pos().SetX(-30);
	collider_R->SetParent(transform);
	collider_R->Scale() *= 30;

	collider_L = new SphereCollider();
	collider_L->Pos().SetX(30);
	collider_L->SetParent(transform);
	collider_L->Scale() *= 30;

	collider_B = new SphereCollider();
	collider_B->Pos().SetZ(30);
	collider_B->SetParent(transform);
	collider_B->Scale() *= 30;

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

	//SetEvent(TAKEOFF, bind(&alduin::EndTakeoff, this), 0.7f);
	//SetEvent(PAIN, bind(&alduin::EndHit, this), 0.9f);
	//SetEvent(INHALE, bind(&alduin::FireAttack, this), 0.9f);

	//for (int clipIndex = ATTACK_F; clipIndex <= ATTACK_B; clipIndex++)
	//{
	//	SetEvent(clipIndex, bind(&alduin::EndAttack, this), 0.9f);
	//}
	
}

alduin::~alduin()
{
}

void alduin::Update()
{
	ModelAnimator::Update(); 

	alduinCollider->UpdateWorld();
	collider_F->UpdateWorld();
	collider_R->UpdateWorld();
	collider_L->UpdateWorld();
	collider_B->UpdateWorld();
	transform->UpdateWorld();

	transform->Pos() = this->Pos();


	//velocity = target->GlobalPos() - transform->GlobalPos();

	SetAnimation();
	Move();
}

void alduin::Render()
{
	ModelAnimator::Render();
	alduinCollider->Render();
	collider_F->Render();
	collider_R->Render();
	collider_L->Render();
	collider_B->Render();
}

void alduin::GUIRender()
{
	Model::GUIRender();
}

void alduin::SetTarget(Player* target)
{
	this->target = target;
}

void alduin::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvent[clip].count(timeRatio) > 0) return; // 선행 예약된 이벤트가 있으면 종료
	totalEvent[clip][timeRatio] = event;
}

void alduin::Move()
{

	if (KEY_PRESS('I'))
	{
		velocity.z += DELTA; //속력 기준에 시간 경과만큼 누적값 주기
		SetState(RUN);
		//isMoveZ = true; //전후 이동 중임
	}

	if (KEY_PRESS('J'))
	{
		velocity.z -= DELTA;
		SetState(WALK);
		//isMoveZ = true;
	}

	if (KEY_PRESS('K'))
	{
		velocity.x -= DELTA;
		SetState(RUN_L);
		//isMoveX = true;
	}

	if (KEY_PRESS('L'))
	{
		velocity.x += DELTA;
		SetState(RUN_R);
		//isMoveX = true;
	}

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);
	Pos() += direction * moveSpeed * DELTA * -1;

	//for (int i = ATTACK_F; i <= ATTACK_B; i++)
	//{
	//	if (curState == i) return;
	//}
	//if (curState == PAIN) return; 
	//if (curState == DEATH) return; 
	//if (velocity.Length() < 10) return; 


	//if (velocity.Length() < 1000) // 표적과 거리가 가까울 때는
	//{
	//	moveSpeed = 100; //두 배로 빨라진다
	//	SetState(RUN);
	//}
	//else
	//{
	//	moveSpeed = 50;
	//	SetState(WALK);
	//}

	//transform->Pos() += velocity.GetNormalized() * moveSpeed * DELTA;
	//transform->Rot().y = atan2(velocity.x, velocity.z) * rotSpeed + XM_PI; // XY좌표 방향 + 전후반전(문워크 방지)
}


void alduin::FireAttack()
{


	if (velocity.Length() < 1000)
	{
		SetState(BREATH);
	}

	else if (velocity.Length() > 1000)
	{
		SetState(FIREBALL);
	}


}

void alduin::EndTakeoff()
{
	SetState(HOVER);

}

void alduin::EndHit()
{
	SetState(WALK);
}

void alduin::EndAttack()
{
	SetState(WALK);
}

void alduin::EndBreath()
{


}

void alduin::SetAnimation()
{
	if (curState == BREATH) return;

	if (velocity.z > 0.1f) // 속력 기준이 현재 앞으로 +면
		SetState(RUN);
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

void alduin::Patterns()
{

	if (collider_F->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_F);

	}
	else if (collider_R->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_R);

	}
	else if (collider_L->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_L);

	}
	else if (collider_B->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_B);

	}

	

}
