#include "Framework.h"

Wolf::Wolf(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos)
	: Enemy(name, index, modelAnimatorInstancing, transform, spawnPos)
{
	//transform->Scale() *= 0.9f;

	colliders.push_back(new CapsuleCollider(20.0f)); // HIP
	colliders.push_back(new CapsuleCollider(20.0f)); // BELLY
	colliders.push_back(new CapsuleCollider(20.0f)); // TORSO

	colliders.push_back(new CapsuleCollider(12.5f)); // LEG FRONT LEFT
	colliders.push_back(new CapsuleCollider(7.5f));
	colliders.push_back(new CapsuleCollider(7.5f));

	colliders.push_back(new CapsuleCollider(12.5f)); // LEG FRONT RIGHT
	colliders.push_back(new CapsuleCollider(7.5f));
	colliders.push_back(new CapsuleCollider(7.5f));

	colliders.push_back(new CapsuleCollider(20.0f)); // CHEST
	colliders.push_back(new CapsuleCollider(20.0f)); // NECK

	colliders.push_back(new CapsuleCollider(25.0f)); // HEAD
	colliders.push_back(new CapsuleCollider(15.0)); // MOUTH

	colliders.push_back(new CapsuleCollider(12.5f)); // LEG BACK LEFT
	colliders.push_back(new CapsuleCollider(7.5f));
	colliders.push_back(new CapsuleCollider(7.5f));

	colliders.push_back(new CapsuleCollider(12.5f)); // LEG BACK RIGHT
	colliders.push_back(new CapsuleCollider(7.5f));
	colliders.push_back(new CapsuleCollider(7.5f));

	colliders.push_back(new CapsuleCollider(10.0)); // TAIL
	colliders.push_back(new CapsuleCollider(10.0));
	colliders.push_back(new CapsuleCollider(10.0));

	trackRange = 75000.f;
	attackRange = trackRange * 0.1f;

	SetEvent(IDLE, bind(&Wolf::StartIdle, this), 0.0f);

	SetEvent(HOWLING, bind(&Wolf::EndHowling, this), 0.99f);

	SetEvent(RUN, bind(&Wolf::StartRun, this), 0.0f);

	SetEvent(ATTACK, bind(&Wolf::StartAttack, this), 0.0f);
	SetEvent(ATTACK, bind(&Wolf::StartAttackTrigger, this), 0.4f);
	SetEvent(ATTACK, bind(&Wolf::EndAttackTrigger, this), 0.6f);
	SetEvent(ATTACK, bind(&Wolf::EndAttack, this), 0.9f);

	SetEvent(ATTACK2, bind(&Wolf::StartAttack, this), 0.0f);
	SetEvent(ATTACK2, bind(&Wolf::StartAttackTrigger, this), 0.4f);
	SetEvent(ATTACK2, bind(&Wolf::EndAttackTrigger, this), 0.6f);
	SetEvent(ATTACK2, bind(&Wolf::EndAttack, this), 0.9f);

	SetEvent(ATTACK3, bind(&Wolf::StartAttack, this), 0.0f);
	SetEvent(ATTACK3, bind(&Wolf::StartAttackTrigger, this), 0.4f);
	SetEvent(ATTACK3, bind(&Wolf::EndAttackTrigger, this), 0.6f);
	SetEvent(ATTACK3, bind(&Wolf::EndAttack, this), 0.9f);

	SetEvent(ATTACK4, bind(&Wolf::StartAttack, this), 0.0f);
	SetEvent(ATTACK4, bind(&Wolf::StartAttackTrigger, this), 0.4f);
	SetEvent(ATTACK4, bind(&Wolf::EndAttackTrigger, this), 0.6f);
	SetEvent(ATTACK4, bind(&Wolf::EndAttack, this), 0.9f);

	SetEvent(COMBATIDLE, bind(&Wolf::EndCombatIdle, this), 0.9f);

	SetEvent(HIT, bind(&Wolf::StartHit, this), 0.0f);
	SetEvent(HIT, bind(&Wolf::EndHit, this), 0.9f);

	SetEvent(DEATH, bind(&Wolf::Death, this), 0.9f);

	curState = IDLE;

	Init();
}

Wolf::~Wolf()
{

}

void Wolf::Update()
{
	if (transform->Active())
	{
		Enemy::Update();

		Behavior();
		ExecuteEvent();
	}
}

void Wolf::Render()
{
	if (transform->Active())
		Enemy::Render();
	//for (CapsuleCollider* collider : colliders)
	//	collider->Render();
	//trackCollider->Render();
	//attackCollider->Render();
}

void Wolf::GUIRender()
{
}

void Wolf::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	instancing->PlayClip(index, (int)state, 0.5f);
	eventIters[state] = totalEvent[state].begin();
}

void Wolf::Track()
{
	if (target)
	{
		velocity = target->GlobalPos() - transform->GlobalPos();
		transform->Pos() += velocity.GetNormalized() * this->status.speed * DELTA;

		Vector3 forward = transform->Forward();
		Vector3 cross = Cross(forward, velocity);

		if (cross.y < 0)
		{
			transform->Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			transform->Rot().y -= rotSpeed * DELTA;
		}
	}
}

void Wolf::SetRandIdleRot()
{
	while (true)
	{
		randPos = { transform->GlobalPos().x + Random(-100, 100), 0,
			transform->GlobalPos().z + Random(-100, 100) };
		if ((randPos - transform->GlobalPos()).Length() >= 40.0f) break;
	}
}

void Wolf::Death()
{
	Enemy::Death();
}

void Wolf::Behavior()
{
	if (this->status.curHp <= 0)
	{
		this->status.curHp = 0;
		SetState(DEATH);
	}

	if (hitDelay > 0.0f)
	{
		hitDelay -= DELTA;
		if (hitDelay <= 0.0f)
			hitDelay = 0.0f;
	}

	for (CapsuleCollider* collider : colliders)
	{
		if (collider->IsCollision(playerData->GetSword()->GetCollider()))
		{
			this->status.curHp -= playerData->GetStatus().atk;
			hitDelay = 1.0f;
			if (!isHit && playerData->GetAction() == Player::OHM_ATK_P)
				SetState(HIT);
			break;
		}
	}
	if (isHit) return;

	for (CapsuleCollider* collider : colliders)
	{
		if (collider->IsCollision(playerData->GetCollier()) && attackTrigger)
		{
			playerData->SetAction(Player::OHM_HIT_MEDIUM);
			playerData->SetIsHit(true);
			break;
		}
	}

	if (attackDelay > 0.0f)
	{
		attackDelay -= DELTA;
		if (attackDelay <= 0.0f)
		{
			attackCollider->SetActive(true);
			attackDelay = 0.0f;
			SetState(RUN);
		}
		return;
	}
	
	if (curState == ATTACK || curState == ATTACK2 || curState == ATTACK3 || curState == ATTACK4
		|| curState == HIT) return;
	if (playerData->GetCollier()->IsCollision(attackCollider))
	{
		while (true)
		{
			int tmp = Random(0, 4);
			if (atkType != tmp)
			{
				atkType = tmp;
				break;
			}
		}
		switch (atkType)
		{
		case 0:
			SetState(ATTACK);
			break;
		case 1:
			SetState(ATTACK2);
			break;
		case 2:
			SetState(ATTACK3);
			break;
		case 3:
			SetState(ATTACK4);
			break;
		}
	}
	else if (playerData->GetCollier()->IsCollision(trackCollider))
	{
		if (!isTracking)
			SetState(HOWLING);
		else
		{
			SetState(RUN);
			Track();
		}
	}
	else if (idleTime > 0.0f)
	{
		idleTime -= DELTA;
		if (idleTime <= 0.0f)
		{
			idleTime = 0.0f;
			tmpPos = transform->GlobalPos();
			SetRandIdleRot();
			SetState(WALK);
		}
	}
	else
	{
		Walk();
	}
}

void Wolf::Walk()
{
	if ((transform->GlobalPos() - tmpPos).Length() < 40.0f)
	{
		velocity = randPos - transform->GlobalPos();
		transform->Pos() += velocity.GetNormalized() * this->status.speed * DELTA;
		Vector3 forward = transform->Forward(); //모델 기준으로 앞 따오기
		Vector3 cross = Cross(forward, velocity);

		if (cross.y < 0) // 법선이 밑이다 = 내가 목적 방향보다 오른쪽을 보는 중이다
		{
			transform->Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0) //반대의 경우
		{
			transform->Rot().y -= rotSpeed * DELTA;
		}
	}
	else
	{
		SetState(IDLE);
	}
}

void Wolf::StartIdle()
{
	idleTime = Random(3, 6);
	isTracking = false;
}

void Wolf::EndHowling()
{
	SetState(RUN);
	SetTarget(nullptr);
	isTracking = true;
	idleTime = 0.0f;
}

void Wolf::StartRun()
{
	SetTarget(playerData);
}

void Wolf::StartAttack()
{
	attackCollider->SetActive(false);
	attackDelay = 2.5f;
}

void Wolf::StartAttackTrigger()
{
	attackTrigger = true;
}

void Wolf::EndAttackTrigger()
{
	attackTrigger = false;
}

void Wolf::EndAttack()
{
	SetState(COMBATIDLE);
}

void Wolf::EndCombatIdle()
{
	isHit = false;
}

void Wolf::StartHit()
{
	isHit = true;
}

void Wolf::EndHit()
{
	SetState(COMBATIDLE);
	isHit = false;
}

void Wolf::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvent[clip].count(timeRatio) > 0) return; // 선행 예약된 이벤트가 있으면 종료
	totalEvent[clip][timeRatio] = event;
}

void Wolf::ExecuteEvent()
{
	int index = curState; //현재 상태 받아오기
	if (totalEvent[index].empty()) return;
	if (eventIters[index] == totalEvent[index].end()) return;

	float ratio = motion->runningTime / motion->duration; //진행된 시간 나누기 전체 진행시간

	if (eventIters[index]->first > ratio) return; // 진행 시간이 정해진 기준에 못 미치면 종료(재시작)

	eventIters[index]->second(); //등록된 이벤트 수행
	eventIters[index]++;
}

void Wolf::SetColliderByNode()
{
	colliderTransforms[HIP]->SetWorld(instancing->GetTransformByNode(index, 10));
	colliderTransforms[BELLY]->SetWorld(instancing->GetTransformByNode(index, 11));
	colliderTransforms[TORSO]->SetWorld(instancing->GetTransformByNode(index, 12));

	colliderTransforms[THIGH_FL]->SetWorld(instancing->GetTransformByNode(index, 15));
	colliderTransforms[LEG_FL]->SetWorld(instancing->GetTransformByNode(index, 16));
	colliderTransforms[FOOT_FL]->SetWorld(instancing->GetTransformByNode(index, 18));

	colliderTransforms[THIGH_FR]->SetWorld(instancing->GetTransformByNode(index, 21));
	colliderTransforms[LEG_FR]->SetWorld(instancing->GetTransformByNode(index, 22));
	colliderTransforms[FOOT_FR]->SetWorld(instancing->GetTransformByNode(index, 24));

	colliderTransforms[CHEST]->SetWorld(instancing->GetTransformByNode(index, 26));
	colliderTransforms[CHEST]->SetWorld(instancing->GetTransformByNode(index, 27));

	colliderTransforms[HEAD]->SetWorld(instancing->GetTransformByNode(index, 29));
	colliderTransforms[MOUTH]->SetWorld(instancing->GetTransformByNode(index, 32));

	colliderTransforms[THIGH_BL]->SetWorld(instancing->GetTransformByNode(index, 66));
	colliderTransforms[LEG_BL]->SetWorld(instancing->GetTransformByNode(index, 67));
	colliderTransforms[FOOT_BL]->SetWorld(instancing->GetTransformByNode(index, 69));

	colliderTransforms[THIGH_BR]->SetWorld(instancing->GetTransformByNode(index, 71));
	colliderTransforms[LEG_BR]->SetWorld(instancing->GetTransformByNode(index, 72));
	colliderTransforms[FOOT_BR]->SetWorld(instancing->GetTransformByNode(index, 74));

	colliderTransforms[TAIL1]->SetWorld(instancing->GetTransformByNode(index, 75));
	colliderTransforms[TAIL2]->SetWorld(instancing->GetTransformByNode(index, 76));
	colliderTransforms[TAIL3]->SetWorld(instancing->GetTransformByNode(index, 77));
}
