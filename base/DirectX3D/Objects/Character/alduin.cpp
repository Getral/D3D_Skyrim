#include "Framework.h"
#include "alduin.h"

alduin::alduin() :  ModelAnimator("alduin")
{
	transform = new Transform();
	//transform->SetParent(this);

	//transform->Rot().SetY(this->Rot().y);
	FireAttackTransform = new Transform();

	alduinCollider2 = new CapsuleCollider(50.0f,25.0f);
	alduinCollider2->SetParent(this->transform);

	HeadCollider = new CapsuleCollider(90.0f,0.1f);
	HeadCollider->SetParent(transform);
	BodyCollider = new CapsuleCollider(110.0f, 350.0f);
	BodyCollider->SetParent(transform);
	TailCollider = new CapsuleCollider(90.0f, 10.0f);
	TailCollider->SetParent(transform);

	breathCollider = new BoxCollider({ 150,50,300 });

	ApproachCollider = new BoxCollider({ 150,100,300 });


	DeathParticle = new ParticleSystem("Textures/alduin_death.fx");
	BreathParticle = new ParticleSystem("Textures/alduin_breath.fx");

	//alduinCollider3 = new CapsuleCollider();


	//공격 인식
	collider_F = new CapsuleCollider(60.0f, 0.1f);
	collider_F->Pos().SetZ(-22);
	collider_F->SetParent(transform);
	collider_F->Scale() *= 0.2;

	collider_R = new CapsuleCollider(70.0f, 0.1f);
	collider_R->Pos().SetX(-25);
	collider_R->SetParent(transform);
	collider_R->Scale() *= 0.2;

	collider_L = new CapsuleCollider(70.0f, 0.1f);
	collider_L->Pos().SetX(25);
	collider_L->SetParent(transform);
	collider_L->Scale() *= 0.2;

	collider_B = new CapsuleCollider(110.0f, 0.1f);
	collider_B->Pos().SetZ(30);
	collider_B->SetParent(transform);
	collider_B->Scale() *= 0.2;

	//공격 범위
	Acollider_F = new CapsuleCollider(60.0f, 0.1f);
	Acollider_F->Pos().SetZ(-22);
	Acollider_F->SetParent(transform);
	Acollider_F->Scale() *= 0.2;
	Acollider_F->SetActive(false);

	Acollider_R = new CapsuleCollider(70.0f, 0.1f);
	Acollider_R->Pos().SetX(-25);
	Acollider_R->SetParent(transform);
	Acollider_R->Scale() *= 0.2;
	Acollider_R->SetActive(false);

	Acollider_L = new CapsuleCollider(70.0f, 0.1f);
	Acollider_L->Pos().SetX(25);
	Acollider_L->SetParent(transform);
	Acollider_L->Scale() *= 0.2;
	Acollider_L->SetActive(false);

	Acollider_B = new CapsuleCollider(120.0f, 0.1f);
	Acollider_B->Pos().SetZ(30);
	Acollider_B->SetParent(transform);
	Acollider_B->Scale() *= 0.2;
	Acollider_B->SetActive(false);
	
	breathCollider->Pos().SetZ(-50);
	breathCollider->SetParent(transform);
	breathCollider->Scale() *= 0.2;
	breathCollider->SetActive(false);

	ApproachCollider->SetParent(transform);
	ApproachCollider->Scale() *= 0.2;
	ApproachCollider->SetActive(false);

	WakeUpCollider = new SphereCollider(2500.0f);
	WakeUpCollider->SetParent(this);
	WakeUpCollider->Scale() *= 50.0f;
	WakeUpCollider->SetActive(true);

	//fBallCollider->SetParent(transform);
	//fBallCollider->SetActive(false);

	this->ReadClip("alduin_idle");
	this->ReadClip("alduin_takeoff");
	this->ReadClip("alduin_hover");
	this->ReadClip("alduin_flight_hit");
	this->ReadClip("alduin_forward");
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
	this->ReadClip("alduin_land_vertical");
	this->ReadClip("alduin_dive");
	this->ReadClip("alduin_hit");
	this->ReadClip("alduin_death");
	this->ReadClip("alduin_turn_left");
	this->ReadClip("alduin_turn_right");
	this->ReadClip("alduin_sleep");
	this->ReadClip("alduin_wakeUp");
	Scale() *= 0.0003f;
	transform->Scale() *= 0.5f;

	moveSpeed = 5.5f;


	GetClip(WAKEUP)->SetEvent(bind(&alduin::WakeUp, this), 0.9f);

	//일반 공격

	for (int clipIndex = ATTACK_F; clipIndex <= ATTACK_B; clipIndex++)
	{
		GetClip(clipIndex)->SetEvent(bind(&alduin::Attacking, this), 0.0f);
		GetClip(clipIndex)->SetEvent(bind(&alduin::EndAction, this), 0.9f);
	}

	GetClip(ATTACK_F)->SetEvent(bind(&alduin::Attacking2, this), 0.5f);
	GetClip(ATTACK_R)->SetEvent(bind(&alduin::Attacking2, this), 0.15f);
	GetClip(ATTACK_L)->SetEvent(bind(&alduin::Attacking2, this), 0.15f);
	GetClip(ATTACK_B)->SetEvent(bind(&alduin::Attacking2, this), 0.5f);


	
	//화염 공격

	GetClip(INHALE)->SetEvent(bind(&alduin::InhaleStart, this), 0.0f);
	GetClip(INHALE)->SetEvent(bind(&alduin::Inhale, this), 0.9f);

	GetClip(BREATH)->SetEvent(bind(&alduin::BreathAttack, this), 0.2f);
	GetClip(BREATH)->SetEvent(bind(&alduin::EndAction, this), 0.9f);


	//공중
	GetClip(TAKEOFF)->SetEvent(bind(&alduin::beginTakeoff, this), 0.2f);
	GetClip(TAKEOFF)->SetEvent(bind(&alduin::EndTakeoff, this), 0.9f);

	GetClip(APROACH)->SetEvent(bind(&alduin::beginAproach, this), 0.9f);

	GetClip(LANDING_HARD)->SetEvent(bind(&alduin::EndLanding, this), 0.0f);
	GetClip(LANDING_HARD)->SetEvent(bind(&alduin::EndAction, this), 0.9f);

	GetClip(DEATH)->SetEvent(bind(&alduin::Dying, this), 0.5f);
	GetClip(DEATH)->SetEvent(bind(&alduin::Dead, this), 0.9f);

	GetClip(HIT)->SetEvent(bind(&alduin::hit, this), 0.0f);
	GetClip(HIT)->SetEvent(bind(&alduin::HitDelayEnd, this), 0.9f);

	SetState(SLEEP);

}

alduin::~alduin()
{
	delete WakeUpCollider;
	delete Acollider_F;
	delete Acollider_R;
	delete Acollider_L;
	delete Acollider_B;
	delete BreathParticle;
	delete DeathParticle;
	delete breathCollider;
	delete ApproachCollider;
	delete collider_B;
	delete collider_L;
	delete collider_R;
	delete collider_F;
	delete transform;

	delete	HeadCollider;
	delete	BodyCollider;
	delete	TailCollider;

}

void alduin::Update()
{
	
	SleepWake();

	ModelAnimator::Update(); 

	WakeUpCollider->UpdateWorld();

	if (isSleeping) return;

	collider_F->UpdateWorld();
	collider_R->UpdateWorld();
	collider_L->UpdateWorld();
	collider_B->UpdateWorld();

	Acollider_F->UpdateWorld();
	Acollider_R->UpdateWorld();
	Acollider_L->UpdateWorld();
	Acollider_B->UpdateWorld();

	breathCollider->UpdateWorld();
	ApproachCollider->UpdateWorld();
	transform->UpdateWorld();
	HeadCollider->UpdateWorld();
	BodyCollider->UpdateWorld();
	TailCollider->UpdateWorld();

	CoolingTime += DELTA;
	BreathParticle->Update();
	DeathParticle->Update();

	
	if (Acollider_F->Active() && Acollider_F->IsCapsuleCollision(target->GetCollier()))
	{
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
		target->GetStatus().curHp -= (150.0f - target->GetStatus().def);
	}

	else if (Acollider_R->Active() && Acollider_R->IsCapsuleCollision(target->GetCollier()))
	{
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
		target->GetStatus().curHp -= (142.0f - target->GetStatus().def);
	}

	else if (Acollider_L->Active() && Acollider_L->IsCapsuleCollision(target->GetCollier()))
	{
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
		target->GetStatus().curHp -= (142.0f - target->GetStatus().def);
	}

	else if (Acollider_B->Active() && Acollider_B->IsCapsuleCollision(target->GetCollier()))
	{
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
		target->GetStatus().curHp -= (170.0f - target->GetStatus().def);
	}


	if (breathCollider->Active() && breathCollider->IsCapsuleCollision(target->GetCollier()))
	{
		if (breathDelay <= 0.0f)
		{
			target->GetStatus().curHp -= (140.0f - target->GetStatus().def);
			breathDelay = 1.0f;
		}
		else breathDelay -= DELTA;

	}

	if (ApproachCollider->Active() && breathCollider->IsCapsuleCollision(target->GetCollier()))
	{
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);

		if (HitDelay <= 0.0f)
		{
			target->GetStatus().curHp -= (180.0f - target->GetStatus().def);
			HitDelay = 1.0f;
		}
		else HitDelay -= DELTA;


	}


	if (target)
	{
		velocity = this->target->GlobalPos() - transform->GlobalPos();
		Move();
		//SetAnimation();
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
			moveSpeed = 5.5f;
		}
		
	}

	if (isAttacking)
	{
		moveSpeed = 0.0f;
	}

	if (curHp <= 0.0f)
		SetState(DEATH);

	if (KEY_PRESS('K'))
		curHp = 0.0f;


	if (HitDelay2 > 0.0f)
	{
		HitDelay2 -= DELTA;
		if (HitDelay2 <= 0.0f)
			HitDelay2 = 0.0f;
	}

	if (HitDelay2 <= 0.1f)
	{
		if (HeadCollider->IsCollision(target->GetSword()->GetCollider())
			|| BodyCollider->IsCollision(target->GetSword()->GetCollider())
			|| TailCollider->IsCollision(target->GetSword()->GetCollider()))
		{

			if (curHp < 100)
				SetState(HIT);

			else if (curHp >= 100)
			{
				curHp -= target->GetStatus().atk * 2;
			}

			HitDelay2 = 0.7f;


		}

	}
	

	Patterns();
	PatternFire();
	PatternsAir();
		

	HeadCollider->SetWorld(GetTransformByNode(45));
	BodyCollider->SetWorld(GetTransformByNode(84));
	TailCollider->SetWorld(GetTransformByNode(110));
	
	
}

void alduin::Render()
{

	if(ModelAnimator::Active())
		ModelAnimator::Render();

	WakeUpCollider->Render();

	//collider_F->Render();
	//collider_R->Render();
	//collider_L->Render();
	//collider_B->Render();
	Acollider_F->Render();
	Acollider_R->Render();
	Acollider_L->Render();
	Acollider_B->Render();
	breathCollider->Render();
	ApproachCollider->Render();
	BreathParticle->Render();
	DeathParticle->Render();


	if (curState != DEATH)
	{
		HeadCollider->Render();
		BodyCollider->Render();
		TailCollider->Render();
	}
	

}

void alduin::GUIRender()
{
	Model::GUIRender();

	ImGui::SliderInt("nodeIndex", (int*)&nodeIndex, 0, 500);

	//ImGui::InputInt("FireBallCollider")

}

void alduin::SetTarget(Player* target)
{
	this->target = target;
}

void alduin::Move()
{
	if (curState == HIT)
	{
		isMoving = false;
		return;
	}

	if (curState == DEATH)
	{
		moveSpeed = 0.0f;
		isMoving = false;
		return;
	}

	if (velocity.Length() > MAX_GROUND_ATK && Pos().y < 1)
	{
		SetState(TAKEOFF);
		isMoving = false;

	}

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);
	Pos().y = altitude;
	transform->Pos().y = altitude;
	Pos() += velocity.GetNormalized() * moveSpeed * DELTA;

	Vector3 forward = this->Forward(); //모델 기준으로 앞 따오기
	Vector3 cross = Cross(forward, velocity); //방향차이에서 나온 법선

	transform->Pos() += velocity.GetNormalized() * moveSpeed * DELTA;

	if (cross.y < -10 && !isAttacking) // 법선이 밑이다 = 내가 목적 방향보다 오른쪽을 보는 중이다
	{
		Rot().y += rotSpeed * DELTA;
		transform->Rot().y += rotSpeed * DELTA;
		if (Pos().y < 1.0f && velocity.Length() < MAX_GROUND_ATK)
		{
			SetState(TURN_R);
			isMoving = true;
			moveSpeed = 0.0f;
		}
			
	}
	else if (cross.y > 10 && !isAttacking) //반대의 경우
	{
		Rot().y -= rotSpeed * DELTA;
		transform->Rot().y -= rotSpeed * DELTA;
		if (Pos().y < 1.0f && velocity.Length() < MAX_GROUND_ATK)
		{
			SetState(TURN_L);
			isMoving = true;
			moveSpeed = 0.0f;
		}
			
	}
	else if (cross.y >= -10 && cross.y <= 10 && !isAttacking) //반대의 경우
	{

		if (Pos().y < 1.0f && velocity.Length() < MAX_GROUND_ATK)
		{
			SetState(FORWARD);
			isMoving = true;
			moveSpeed = 5.5f;
		}
			
	}

}

void alduin::WakeUp()
{
	SetState(FORWARD);
	isSleeping = false;

}


void alduin::Inhale()
{

	SetState(BREATH);
	

}

void alduin::InhaleStart()
{
	tempPos = Pos() + Back() * 10;
	tempRot = Rot();

	BreathParticle->Play(tempPos, tempRot);
}


void alduin::BreathAttack()
{
	//브레스 공격이 나가야 되는 시점에서 실행할 내용들

		breathCollider->SetActive(true);


}



void alduin::Attacking()
{
	isAttacking = true;

	isMoving = false;
}

void alduin::Attacking2()
{
	if (curState == ATTACK_F) Acollider_F->SetActive(true);

	else if (curState == ATTACK_R) Acollider_R->SetActive(true);

	else if (curState == ATTACK_L) Acollider_L->SetActive(true);

	else if (curState == ATTACK_B) Acollider_B->SetActive(true);


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
	moveSpeed = 250.0f;
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
	isMoving = true;
	moveSpeed = 5.5f;
	SetState(FORWARD);
	Pos().y = 0;
	CoolingTime = 0.0f;
	breathDelay = 1.0f;

	breathCollider->SetActive(false);
	ApproachCollider->SetActive(false);

	Acollider_F->SetActive(false);
	Acollider_R->SetActive(false);
	Acollider_L->SetActive(false);
	Acollider_B->SetActive(false);

	if (target->GetAction() == Player::ACTION::OHM_HIT_MEDIUM)
	{
		target->SetAction(Player::ACTION::OHM_IDLE);
	}
	
	
}

void alduin::EndLanding()
{
	ApproachCollider->SetActive(true);

}

void alduin::hit()
{
	//if (HitDelay > 0) return;

	curHp -= target->GetStatus().atk;
	//HitDelay += DELTA;

}

void alduin::HitDelayEnd()
{
	//HitDelay = 0.0f;
	SetState(FORWARD);
}

void alduin::SleepWake()
{
	if (curState != SLEEP) return;

	if (WakeUpCollider->IsCapsuleCollision(target->GetCollier()))
	{
		WakeUpCollider->SetActive(false);
		SetState(WAKEUP);

	}

}

void alduin::Dying()
{
	tempPos = Pos();
	tempPos += {0, 10, 0};
	DeathParticle->Play(tempPos);
	
	//파티클 재생

}

void alduin::Dead()
{
	ModelAnimator::SetActive(false);
	transform->SetActive(false);

}




void alduin::SetState(State state,float Scale)
{
	if (curState == state) return;

	curState = state;
	this->PlayClip((int)state,Scale);
}

void alduin::Patterns() //지상패턴
{

	if (!isMoving || curState == DEATH || curState == HIT) return;

	
	if (collider_F->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_F, 1.5f);
	}
	else if (collider_R->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_R, 0.7f);
	}
	else if (collider_L->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_L, 0.7f);
	}
	else if (collider_B->IsCapsuleCollision(this->target->GetCollier()))
	{
		SetState(ATTACK_B);
	}

	


}

void alduin::PatternFire()
{

	if (CoolingTime < 8 || curState != FORWARD || Pos().y > 1 || curState == DEATH || curState == HIT) return;

	isMoving = false;

	if (Pos().y < 1) //지상에 있을 때
	{
		SetState(INHALE);
		isAttacking = true;

	}

	


}

void alduin::PatternsAir()
{
	if (curState != HOVER) return;

	SetState(APROACH);


}
