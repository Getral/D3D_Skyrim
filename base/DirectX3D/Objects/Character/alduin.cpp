#include "Framework.h"
#include "alduin.h"

alduin::alduin() :  ModelAnimator("alduin")
{
	transform = new Transform();
	alduinCollider2 = new CapsuleCollider(50.0f,25.0f);
	alduinCollider2->SetParent(this->transform);

	tempRot = new Vector3();

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
	this->ReadClip("alduin_aproach");
	this->ReadClip("alduin_flight_forward");
	this->ReadClip("alduin_bite");
	this->ReadClip("alduin_wingswip_left");
	this->ReadClip("alduin_wingswip_right");
	this->ReadClip("alduin_tailwhip");
	this->ReadClip("alduin_inhale");
	this->ReadClip("alduin_exhale_breath");
	this->ReadClip("alduin_exhale_fireball");
	this->ReadClip("alduin_pain");
	this->ReadClip("alduin_pain2");
	this->ReadClip("alduin_landing");
	this->ReadClip("alduin_landing_soft");
	this->ReadClip("alduin_landing_hard");
	this->ReadClip("alduin_land_ground");
	this->ReadClip("alduin_dive");
	this->ReadClip("alduin_death");
	this->ReadClip("alduin_turn_left");
	this->ReadClip("alduin_turn_right");
	Scale() *= 0.001;

	moveSpeed = 15.0f;


	//일반 공격

	for (int clipIndex = ATTACK_F; clipIndex <= ATTACK_B; clipIndex++)
	{
		GetClip(clipIndex)->SetEvent(bind(&alduin::attacking, this), 0.0f);
		GetClip(clipIndex)->SetEvent(bind(&alduin::EndAction, this), 0.9f);
	}

	
	//화염 공격
	GetClip(INHALE)->SetEvent(bind(&alduin::Inhale, this), 0.9f);

	GetClip(BREATH)->SetEvent(bind(&alduin::BreathAttack, this), 0.3f);
	GetClip(FIREBALL)->SetEvent(bind(&alduin::FireBallAttack, this), 0.9f);

	GetClip(BREATH)->SetEvent(bind(&alduin::EndAction, this), 0.9f);
	GetClip(FIREBALL)->SetEvent(bind(&alduin::EndAction, this), 0.9f);


	//공중
	GetClip(TAKEOFF)->SetEvent(bind(&alduin::beginTakeoff, this), 0.2f);
	GetClip(TAKEOFF)->SetEvent(bind(&alduin::EndTakeoff, this), 0.9f);

	GetClip(APROACH)->SetEvent(bind(&alduin::beginAproach, this), 0.9f);
	//GetClip(FLIGHT_FOR)->SetEvent(bind(&alduin::aproaching, this), 0.0f);
	GetClip(LANDING_HARD)->SetEvent(bind(&alduin::EndAction, this), 0.9f);


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

	if(isAscending) 
		altitude += 35 * DELTA;

	if (isDescending)
	{
		altitude -= 70 * DELTA;

		if (Pos().y < 0.0f)
		{
			isDescending = false;
			SetState(LANDING_HARD);
			moveSpeed = 15.0f;
		}
		
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
	PatternsAir();



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
	if (velocity.Length() > 120 && curState == IDLE)
	{
		SetState(TAKEOFF);

	}

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);
	Pos().y = altitude;
	transform->Pos().y = altitude;
	Pos() += velocity.GetNormalized() * moveSpeed * DELTA;

	Vector3 forward = this->Forward(); //모델 기준으로 앞 따오기
	Vector3 cross = Cross(forward, velocity); //방향차이에서 나온 법선

	transform->Pos() += velocity.GetNormalized() * moveSpeed * DELTA;

	if (cross.y < -30 && !isAttacking) // 법선이 밑이다 = 내가 목적 방향보다 오른쪽을 보는 중이다
	{
		Rot().y += rotSpeed * DELTA;
		transform->Rot().y += rotSpeed * DELTA;
		if(Pos().y < 1)
			SetState(TURN_R);
	}
	else if (cross.y > 30 && !isAttacking) //반대의 경우
	{
		Rot().y -= rotSpeed * DELTA;
		transform->Rot().y -= rotSpeed * DELTA;
		if(Pos().y < 1)
			SetState(TURN_L);
	}
	else if (cross.y >= -30 && cross.y <= 30 && Pos().y < 1 && !isAttacking) //반대의 경우
	{
		if(velocity.Length() <= 120)
			SetState(IDLE);
	}
	

	
}

void alduin::attacking()
{
	isAttacking = true;
	//moveSpeed = 0;
	//rotSpeed = 0;

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


}

void alduin::BreathAttack()
{
	//브레스 공격이 나가야 되는 시점에서 실행할 내용들

}


void alduin::beginTakeoff()
{
	isAscending = true;
	
}

void alduin::EndTakeoff()
{
	isAscending = false;
	SetState(HOVER);

}

void alduin::beginAproach()
{
	isDescending = true;
	SetState(DIVE);
	moveSpeed = 300;
}

//void alduin::aproaching()
//{
//	if (Pos().y > 0) //땅에 안 닿은 상태
//	{
//		SetState(FLIGHT_FOR);
//	}
//	else return;
//
//}


void alduin::EndAction()
{
	isAttacking = false;
	moveSpeed = 15.0f;
	SetState(IDLE);
	Pos().y = 0;
	
}




//void alduin::SetAnimation()
//{
//	if (curState == BREATH) return;
//
//	if (velocity.z > 0.1f) // 속력 기준이 현재 앞으로 +면
//		SetState(RUN);
//	else if (velocity.x > 0.1f) // 좌우 기준 +면
//		SetState(RUN_R);
//	else if (velocity.x < -0.1f) //좌우 기준 -면
//		SetState(RUN_L);
//	else SetState(IDLE); // 가만히 있으면
//}

void alduin::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	this->PlayClip((int)state);
}

void alduin::Patterns() //지상패턴
{

	if (curState == ATTACK_F || curState == ATTACK_R || curState == ATTACK_L || curState == ATTACK_B || curState == LANDING_HARD) return;

	
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

void alduin::PatternsAir()
{
	if (curState != HOVER) return;

	SetState(APROACH);
	//switch (Random(0,3))
	//{
	//case 0:
	//	SetState(APROACH);
	//	break;
	//case 1:
	//	SetState(LANDING);
	//	break;
	//default:
	//	break;
	//}



}
