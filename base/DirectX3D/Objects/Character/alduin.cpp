#include "Framework.h"
#include "alduin.h"

alduin::alduin() : ModelAnimator("alduin")
{
	transform = new Transform();
	alduinCollider2 = new CapsuleCollider(50.0f,25.0f);
	alduinCollider2->SetParent(this->transform);

	HeadCollider = new CapsuleCollider(90.0f,0.1f);
	LWingCollider = new CapsuleCollider(100.0f, 30.0f);
	RWingCollider = new CapsuleCollider(100.0f, 30.0f);
	BodyCollider = new CapsuleCollider(70.0f, 260.0f);
	LLegCollider = new CapsuleCollider(80.0f,0.5f);
	RLegCollider = new CapsuleCollider(30.0f, 20.0f);
	TailCollider = new CapsuleCollider(70.0f, 1.0f);

	//alduinCollider3 = new CapsuleCollider();

	collider_F = new CapsuleCollider(90.0f, 0.1f);
	collider_F->Pos().SetZ(-30);
	collider_F->SetParent(transform);
	collider_F->Scale() *= 0.2;

	collider_R = new CapsuleCollider(90.0f, 0.1f);
	collider_R->Pos().SetX(-30);
	collider_R->SetParent(transform);
	collider_R->Scale() *= 0.2;

	collider_L = new CapsuleCollider(90.0f, 0.1f);
	collider_L->Pos().SetX(30);
	collider_L->SetParent(transform);
	collider_L->Scale() *= 0.2;

	collider_B = new CapsuleCollider(90.0f, 0.1f);
	collider_B->Pos().SetZ(30);
	collider_B->SetParent(transform);
	collider_B->Scale() *= 0.2;

	this->ReadClip("alduin_idle");
	this->ReadClip("alduin_takeoff");
	this->ReadClip("alduin_hover");
	this->ReadClip("alduin_flight_hit");
	this->ReadClip("alduin_backward");
	this->ReadClip("alduin_bleedidle");
	this->ReadClip("alduin_fly");
	this->ReadClip("alduin_flight_forward");
	this->ReadClip("alduin_bite");
	this->ReadClip("alduin_wingswip_left");
	this->ReadClip("alduin_wingswip_right");
	this->ReadClip("alduin_tailwhip");
	this->ReadClip("alduin_climb");
	this->ReadClip("alduin_aproach");
	this->ReadClip("alduin_descend");
	this->ReadClip("alduin_injured");
	this->ReadClip("alduin_ascend");
	this->ReadClip("alduin_inhale");
	this->ReadClip("alduin_exhale_breath");
	this->ReadClip("alduin_exhale_fireball");
	this->ReadClip("alduin_pain");
	this->ReadClip("alduin_pain2");
	this->ReadClip("alduin_timetravel");
	Scale() *= 0.001;

	moveSpeed = 15.0f;

	//SetEvent(TAKEOFF, bind(&alduin::EndTakeoff, this), 0.7f);
	//SetEvent(PAIN, bind(&alduin::EndHit, this), 0.9f);

	for (int clipIndex = ATTACK_F; clipIndex <= ATTACK_B; clipIndex++)
	{
		GetClip(clipIndex)->SetEvent(bind(&alduin::beginAttack, this), 0.0f);
		GetClip(clipIndex)->SetEvent(bind(&alduin::EndAttack, this), 0.9f);
	}

	//GetClip(BREATH)->SetEvent(bind(&alduin::BreathAttack, this), 0.3f);
	GetClip(FIREBALL)->SetEvent(bind(&alduin::FireBallAttack, this), 0.2f);

	GetClip(BREATH)->SetEvent(bind(&alduin::EndAttack, this), 0.9f);
	GetClip(FIREBALL)->SetEvent(bind(&alduin::EndAttack, this), 0.9f);


	
}

alduin::~alduin()
{
	delete collider_B;
	delete collider_L;
	delete collider_R;
	delete collider_F;
	delete transform;

	delete	HeadCollider;
	delete	LWingCollider;
	delete	RWingCollider;
	delete	BodyCollider;
	delete	LLegCollider;
	delete	RLegCollider;
	delete	TailCollider;

}

void alduin::Update()
{
	
	ModelAnimator::Update(); 

	collider_F->UpdateWorld();
	collider_R->UpdateWorld();
	collider_L->UpdateWorld();
	collider_B->UpdateWorld();
	transform->UpdateWorld();

	
	if (target)
	{
		velocity = this->target->GlobalPos() - transform->GlobalPos();
		Move();
	}

	alduinCollider2->SetWorld(GetTransformByNode(nodeIndex));
	HeadCollider->SetWorld(GetTransformByNode(45));
	LWingCollider->SetWorld(GetTransformByNode(81));
	RWingCollider->SetWorld(GetTransformByNode(103));
	BodyCollider->SetWorld(GetTransformByNode(84));
	RLegCollider->SetWorld(GetTransformByNode(119));
	LLegCollider->SetWorld(GetTransformByNode(23));
	TailCollider->SetWorld(GetTransformByNode(110));

	Patterns();
	//SetAnimation();
	
}

void alduin::Render()
{
	ModelAnimator::Render();
	alduinCollider2->Render();
	HeadCollider->Render();
	LWingCollider->Render();
	RWingCollider->Render();
	BodyCollider->Render();
	RLegCollider->Render();
	LLegCollider->Render();
	TailCollider->Render();

	collider_F->Render();
	collider_R->Render();
	collider_L->Render();
	collider_B->Render();
}

void alduin::GUIRender()
{
	Model::GUIRender();

	ImGui::SliderInt("nodeIndex", (int*)&nodeIndex, 0, 500);
}

void alduin::SetTarget(Player* target)
{
	this->target = target;
}



void alduin::Move()
{
	if (velocity.Length() < 100) return;

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);
	Pos() += velocity.GetNormalized() * moveSpeed * DELTA;
	Rot().y = atan2(velocity.x, velocity.z) + XM_PI;

	transform->Pos() += velocity.GetNormalized() * moveSpeed * DELTA;
	transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;

	
}


void alduin::beginAttack()
{
	collider_F->SetActive(false);
	collider_R->SetActive(false);
	collider_L->SetActive(false);
	collider_B->SetActive(false);

}

void alduin::Inhale()
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


void alduin::FireBallAttack()
{
	//파이어볼이 나가는 시점일 때 실행할 내용들 ( 파티클, 투사체 생성...)


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
	SetState(IDLE);
}

void alduin::EndAttack()
{
	collider_F->SetActive(true);
	collider_R->SetActive(true);
	collider_L->SetActive(true);
	collider_B->SetActive(true);

	SetState(IDLE);
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
	if (curState == state) return;

	curState = state;
	this->PlayClip((int)state);
}

void alduin::Patterns()
{

	if (curState == ATTACK_F || curState == ATTACK_R || curState == ATTACK_L || curState == ATTACK_B) return;

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
