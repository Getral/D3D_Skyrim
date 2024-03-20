#include "Framework.h"
#include "alduin.h"

alduin::alduin() :  ModelAnimator("alduin")
{
	transform = new Transform();
	FireAttackTransform = new Transform();

	alduinCollider2 = new CapsuleCollider(50.0f,25.0f);
	alduinCollider2->SetParent(this->transform);


	HeadCollider = new CapsuleCollider(90.0f,0.1f);
	BodyCollider = new CapsuleCollider(110.0f, 350.0f);

	TailCollider = new CapsuleCollider(90.0f, 10.0f);



	breathCollider = new BoxCollider({ 300,200,400 });

	DeathParticle = new ParticleSystem("Textures/alduin_death.fx");
	BreathParticle = new ParticleSystem("Textures/alduin_breath.fx");
	

	//alduinCollider3 = new CapsuleCollider();


	//���� �ν�
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

	//���� ����
	Acollider_F = new CapsuleCollider(90.0f, 0.1f);
	Acollider_F->Pos().SetZ(-32);
	Acollider_F->SetParent(transform);
	Acollider_F->Scale() *= 0.1;
	Acollider_F->SetActive(false);

	Acollider_R = new CapsuleCollider(90.0f, 0.1f);
	Acollider_R->Pos().SetX(-25);
	Acollider_R->SetParent(transform);
	Acollider_R->Scale() *= 0.1;
	Acollider_R->SetActive(false);

	Acollider_L = new CapsuleCollider(90.0f, 0.1f);
	Acollider_L->Pos().SetX(25);
	Acollider_L->SetParent(transform);
	Acollider_L->Scale() *= 0.1;
	Acollider_L->SetActive(false);

	Acollider_B = new CapsuleCollider(90.0f, 0.1f);
	Acollider_B->Pos().SetZ(25);
	Acollider_B->SetParent(transform);
	Acollider_B->Scale() *= 0.1;
	Acollider_B->SetActive(false);

	
	breathCollider->Pos().SetZ(-70);
	breathCollider->SetParent(transform);
	breathCollider->Scale() *= 0.2;
	breathCollider->SetActive(false);



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
	Scale() *= 0.001f;

	moveSpeed = 15.0f;


	//�Ϲ� ����

	for (int clipIndex = ATTACK_F; clipIndex <= ATTACK_B; clipIndex++)
	{
		GetClip(clipIndex)->SetEvent(bind(&alduin::Attacking, this), 0.0f);
		GetClip(clipIndex)->SetEvent(bind(&alduin::EndAction, this), 0.9f);
	}

	GetClip(ATTACK_F)->SetEvent(bind(&alduin::Attacking2, this), 0.5f);
	GetClip(ATTACK_R)->SetEvent(bind(&alduin::Attacking2, this), 0.3f);
	GetClip(ATTACK_L)->SetEvent(bind(&alduin::Attacking2, this), 0.3f);
	GetClip(ATTACK_B)->SetEvent(bind(&alduin::Attacking2, this), 0.5f);


	
	//ȭ�� ����

	GetClip(INHALE)->SetEvent(bind(&alduin::InhaleStart, this), 0.0f);
	GetClip(INHALE)->SetEvent(bind(&alduin::Inhale, this), 0.9f);

	GetClip(BREATH)->SetEvent(bind(&alduin::BreathAttack, this), 0.0f);

	GetClip(BREATH)->SetEvent(bind(&alduin::EndAction, this), 0.9f);


	//����
	GetClip(TAKEOFF)->SetEvent(bind(&alduin::beginTakeoff, this), 0.2f);
	GetClip(TAKEOFF)->SetEvent(bind(&alduin::EndTakeoff, this), 0.9f);

	GetClip(APROACH)->SetEvent(bind(&alduin::beginAproach, this), 0.9f);
	//GetClip(FLIGHT_FOR)->SetEvent(bind(&alduin::aproaching, this), 0.0f);
	GetClip(LANDING_HARD)->SetEvent(bind(&alduin::EndAction, this), 0.9f);

	GetClip(DEATH)->SetEvent(bind(&alduin::Dying, this), 0.5f);
	GetClip(DEATH)->SetEvent(bind(&alduin::Dead, this), 0.9f);

	GetClip(HIT)->SetEvent(bind(&alduin::hit, this), 0.0f);
	GetClip(HIT)->SetEvent(bind(&alduin::HitDelayEnd, this), 0.9f);

}

alduin::~alduin()
{
	delete BreathParticle;
	delete DeathParticle;
	delete breathCollider;
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
	
	
	ModelAnimator::Update(); 

	collider_F->UpdateWorld();
	collider_R->UpdateWorld();
	collider_L->UpdateWorld();
	collider_B->UpdateWorld();

	Acollider_F->UpdateWorld();
	Acollider_R->UpdateWorld();
	Acollider_L->UpdateWorld();
	Acollider_B->UpdateWorld();


	breathCollider->UpdateWorld();
	transform->UpdateWorld();
	HeadCollider->UpdateWorld();
	BodyCollider->UpdateWorld();
	TailCollider->UpdateWorld();




	CoolingTime += DELTA;
	BreathParticle->Update();
	DeathParticle->Update();

	
	if (Acollider_F->Active() && Acollider_F->IsCapsuleCollision(target->GetCollier()))
	{
		//3 : OHM_HIT_MEDIUM
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
	}

	else if (Acollider_R->Active() && Acollider_R->IsCapsuleCollision(target->GetCollier()))
	{
		//3 : OHM_HIT_MEDIUM
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
	}

	else if (Acollider_L->Active() && Acollider_L->IsCapsuleCollision(target->GetCollier()))
	{
		//3 : OHM_HIT_MEDIUM
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
	}

	else if (Acollider_B->Active() && Acollider_B->IsCapsuleCollision(target->GetCollier()))
	{
		//3 : OHM_HIT_MEDIUM
		target->SetAction(Player::ACTION::OHM_HIT_MEDIUM);
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
			moveSpeed = 15.0f;
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


	if (HeadCollider->IsCollision(target->GetSword()->GetCollider()) 
		|| BodyCollider->IsCollision(target->GetSword()->GetCollider()) 
		|| TailCollider->IsCollision(target->GetSword()->GetCollider()))
	{

		SetState(HIT);


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

	collider_F->Render();
	collider_R->Render();
	collider_L->Render();
	collider_B->Render();
	Acollider_F->Render();
	Acollider_R->Render();
	Acollider_L->Render();
	Acollider_B->Render();
	breathCollider->Render();
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

	if (velocity.Length() > 250 && Pos().y < 1)
	{
		SetState(TAKEOFF);
		isMoving = false;

	}

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);
	Pos().y = altitude;
	transform->Pos().y = altitude;
	Pos() += velocity.GetNormalized() * moveSpeed * DELTA;

	Vector3 forward = this->Forward(); //�� �������� �� ������
	Vector3 cross = Cross(forward, velocity); //�������̿��� ���� ����

	transform->Pos() += velocity.GetNormalized() * moveSpeed * DELTA;

	if (cross.y < -20 && !isAttacking) // ������ ���̴� = ���� ���� ���⺸�� �������� ���� ���̴�
	{
		Rot().y += rotSpeed * DELTA;
		transform->Rot().y += rotSpeed * DELTA;
		if (Pos().y < 1.0f && velocity.Length() < 250)
		{
			SetState(TURN_R);
			isMoving = true;
			moveSpeed = 0.0f;
		}
			
	}
	else if (cross.y > 20 && !isAttacking) //�ݴ��� ���
	{
		Rot().y -= rotSpeed * DELTA;
		transform->Rot().y -= rotSpeed * DELTA;
		if (Pos().y < 1.0f && velocity.Length() < 250)
		{
			SetState(TURN_L);
			isMoving = true;
			moveSpeed = 0.0f;
		}
			
	}
	else if (cross.y >= -0 && cross.y <= 20 && !isAttacking) //�ݴ��� ���
	{

		if (Pos().y < 1.0f && velocity.Length() < 250)
		{
			SetState(FORWARD);
			isMoving = true;
			moveSpeed = 15.0f;
		}
			
	}

	
}


void alduin::Inhale()
{

	SetState(BREATH);
	

}

void alduin::InhaleStart()
{
	tempPos = Pos();
	tempPos += {0, 0, -30};
	tempRot = Rot();

	BreathParticle->Play(tempPos, tempRot);
}




void alduin::BreathAttack()
{
	//�극�� ������ ������ �Ǵ� �������� ������ �����

	

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
	moveSpeed = 300.0f;
}

//void alduin::aproaching()
//{
//	if (Pos().y > 0) //���� �� ���� ����
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
	moveSpeed = 15.0f;
	SetState(FORWARD);
	Pos().y = 0;
	CoolingTime = 0.0f;

	breathCollider->SetActive(false);

	Acollider_F->SetActive(false);
	Acollider_R->SetActive(false);
	Acollider_L->SetActive(false);
	Acollider_B->SetActive(false);

	if (target->GetAction() == Player::ACTION::OHM_HIT_MEDIUM)
	{
		target->SetAction(Player::ACTION::OHM_IDLE);
	}
	
	
}

void alduin::hit()
{
	if (HitDelay > 0) return;

	curHp -= 50;
	HitDelay += DELTA;

}
void alduin::HitDelayEnd()
{
	HitDelay = 0.0f;
	SetState(FORWARD);
}

void alduin::Dying()
{
	tempPos = Pos();
	tempPos += {0, 30, 0};
	DeathParticle->Play(tempPos);
	
	//��ƼŬ ���

}

void alduin::Dead()
{
	ModelAnimator::SetActive(false);
	transform->SetActive(false);

}




void alduin::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	this->PlayClip((int)state);
}

void alduin::Patterns() //��������
{
	

	if (!isMoving || curState == DEATH || curState == HIT) return;

	
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

void alduin::PatternFire()
{

	if (CoolingTime < 8 || curState != FORWARD || Pos().y > 1 || curState == DEATH || curState == HIT) return;

	isMoving = false;

	if (Pos().y < 1) //���� ���� ��
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
