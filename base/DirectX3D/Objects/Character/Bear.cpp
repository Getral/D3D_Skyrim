#include "Framework.h"

Bear::Bear(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos)
	: Enemy(name, index, modelAnimatorInstancing, transform, spawnPos)
{
	colliders.push_back(new CapsuleCollider(35.0f)); // HIP

	colliders.push_back(new CapsuleCollider(20.0f)); // LEFT LEG
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));

	colliders.push_back(new CapsuleCollider(20.0f)); // RIGHT LEG
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));

	colliders.push_back(new CapsuleCollider(35.0f)); // BELLY
	colliders.push_back(new CapsuleCollider(35.0f)); // TORSO
	colliders.push_back(new CapsuleCollider(35.0f)); // CHEST
	colliders.push_back(new CapsuleCollider(35.0f)); // NECK

	colliders.push_back(new CapsuleCollider(20.0f)); // LEFT ARM
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));

	colliders.push_back(new CapsuleCollider(20.0f)); // RIGHT ARM
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));
	colliders.push_back(new CapsuleCollider(20.0f));

	colliders.push_back(new CapsuleCollider(25.0f)); // HEAD

	trackRange = 75000.f;
	attackRange = trackRange * 0.15f;

	SetEvent(STARTSLEEP, bind(&Bear::StartStartSleep, this), 0.0f);
	SetEvent(STARTSLEEP, bind(&Bear::EndStartSleep, this), 0.95f);

	SetEvent(WAKEUP, bind(&Bear::StartWakeUp, this), 0.0f);
	SetEvent(WAKEUP, bind(&Bear::EndWakeUp, this), 0.95f);

	SetEvent(RUN, bind(&Bear::StartRun, this), 0.0f);
	SetEvent(RUN, bind(&Bear::EndRun, this), 0.9f);

	SetEvent(ATTACK, bind(&Bear::StartAttack, this), 0.0f);
	SetEvent(ATTACK, bind(&Bear::StartAttackTrigger, this), 0.4f);
	SetEvent(ATTACK, bind(&Bear::EndAttackTrigger, this), 0.6f);
	SetEvent(ATTACK, bind(&Bear::EndAttack, this), 0.95f);

	SetEvent(ATTACK2, bind(&Bear::StartAttack, this), 0.0f);
	SetEvent(ATTACK2, bind(&Bear::StartAttackTrigger, this), 0.4f);
	SetEvent(ATTACK2, bind(&Bear::EndAttackTrigger, this), 0.6f);
	SetEvent(ATTACK2, bind(&Bear::EndAttack, this), 0.95f);

	SetEvent(ATTACK3, bind(&Bear::StartAttack, this), 0.0f);
	SetEvent(ATTACK3, bind(&Bear::StartAttackTrigger, this), 0.4f);
	SetEvent(ATTACK3, bind(&Bear::EndAttackTrigger, this), 0.6f);
	SetEvent(ATTACK3, bind(&Bear::EndAttack, this), 0.95f);

	SetEvent(HIT, bind(&Bear::StartHit, this), 0.0f);
	SetEvent(HIT, bind(&Bear::EndHit, this), 0.95f);

	SetEvent(HEADSHAKE, bind(&Bear::EndHeadShake, this), 0.95f);

	SetEvent(DEATH, bind(&Bear::Death, this), 0.9f);

	FOR(totalEvent.size())
		eventIters[i] = totalEvent[i].begin();

	rigidbody->Scale().x *= trackRange * 0.2f;
	rigidbody->Scale().y *= trackRange * 0.25f;
	rigidbody->Scale().z *= trackRange * 0.38f;

	rigidbody->Pos().y = rigidbody->Scale().y * 0.5f;

	SetState(SLEEP);

	Init();
}

Bear::~Bear()
{
}

void Bear::Update()
{
	if (transform->Active())
	{
		Enemy::Update();

		Behavior();
		ExecuteEvent();
	}
}

void Bear::Render()
{
	if (transform->Active())
		Enemy::Render();
}

void Bear::GUIRender()
{
}

void Bear::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	instancing->PlayClip(index, (int)state, 0.5f);
	eventIters[state] = totalEvent[state].begin();
}

void Bear::Track()
{
	if (target)
	{
		velocity = target->GlobalPos() - transform->GlobalPos();
		transform->Pos() += velocity.GetNormalized() * this->status.speed * DELTA;
		//transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;

		Vector3 forward = transform->Forward(); //�� �������� �� ������
		Vector3 cross = Cross(forward, velocity);

		if (cross.y < 0) // ������ ���̴� = ���� ���� ���⺸�� �������� ���� ���̴�
		{
			transform->Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0) //�ݴ��� ���
		{
			transform->Rot().y -= rotSpeed * DELTA;
		}
	}
}

void Bear::StartStartSleep()
{
	SetTarget(nullptr);
}

void Bear::EndStartSleep()
{
	isSleep = true;
	isWakeUp = false;
	isBattle = false;
}

void Bear::StartWakeUp()
{
	isWakeUp = true;
	isBattle = true;
}

void Bear::EndWakeUp()
{
	isSleep = false;
	SetState(RUN);
}

void Bear::StartRun()
{
	SetTarget(playerData);
}

void Bear::EndRun()
{
}

void Bear::StartAttack()
{
	attackCollider->SetActive(false);
	SetTarget(nullptr);
	attackDelay = 3.0f;
}

void Bear::StartAttackTrigger()
{
	attackTrigger = true;
}

void Bear::EndAttackTrigger()
{
	attackTrigger = false;
}

void Bear::EndAttack()
{
	SetState(COMBATIDLE);
}

void Bear::StartHit()
{
	isHit = true;
}

void Bear::EndHit()
{
	SetState(HEADSHAKE);
	isHit = false;
}

void Bear::EndHeadShake()
{
	SetState(COMBATIDLE);
	attackDelay = 1.0f;
	isHit = false;
}

void Bear::Death()
{
	Enemy::Death();
}

void Bear::Behavior()
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
			if (hitDelay == 0.0f)
			{
				this->status.curHp -= playerData->GetStatus().atk;
				hitDelay = 1.0f;
				if (!isHit && playerData->GetAction() == Player::OHM_ATK_P)
					SetState(HIT);
				break;
			}
		}
	}
	if (isHit) return;

	for (CapsuleCollider* collider : colliders)
	{
		if (collider->IsCollision(playerData->GetCollier()) && attackTrigger)
		{
			playerData->SetHit();
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
			SetState(RUN);
		}
		return;
	}

	if (curState == ATTACK || curState == ATTACK2 || curState == ATTACK3 || curState == HIT) return;
	if (playerData->GetCollier()->IsSphereCollision(attackCollider) && attackDelay <= 0.0f)
	{
		switch (attackState)
		{
		case 0:
			SetState(ATTACK);
			attackState++;
			break;
		case 1:
			SetState(ATTACK2);
			attackState++;
			break;
		case 2:
			SetState(ATTACK3);
			attackState = 0;
			break;
		}
	}
	else if (playerData->GetCollier()->IsCollision(trackCollider))
	{
		if (isSleep)
			SetState(WAKEUP);
	}
	else if (isSleep)
	{
		SetState(SLEEP);
	}
	else if (!isSleep)
	{
		SetState(STARTSLEEP);
	}
	Track();
}

void Bear::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvent[clip].count(timeRatio) > 0) return; // ���� ����� �̺�Ʈ�� ������ ����
	totalEvent[clip][timeRatio] = event;
}

void Bear::ExecuteEvent()
{
	int index = curState; //���� ���� �޾ƿ���
	if (totalEvent[index].empty()) return;
	if (eventIters[index] == totalEvent[index].end()) return;

	float ratio = motion->runningTime / motion->duration; //����� �ð� ������ ��ü ����ð�

	if (eventIters[index]->first > ratio) return; // ���� �ð��� ������ ���ؿ� �� ��ġ�� ����(�����)

	eventIters[index]->second(); //��ϵ� �̺�Ʈ ����
	eventIters[index]++;
}

void Bear::SetColliderByNode()
{
	colliderTransforms[HIP]->SetWorld(instancing->GetTransformByNode(index, 8));

	colliderTransforms[KNEE_L]->SetWorld(instancing->GetTransformByNode(index, 10));
	colliderTransforms[HEEL_L]->SetWorld(instancing->GetTransformByNode(index, 11));
	colliderTransforms[SOLE_L]->SetWorld(instancing->GetTransformByNode(index, 12));
	colliderTransforms[TOES_L]->SetWorld(instancing->GetTransformByNode(index, 13));
	colliderTransforms[THIGH_L]->SetWorld(instancing->GetTransformByNode(index, 15));

	colliderTransforms[KNEE_R]->SetWorld(instancing->GetTransformByNode(index, 18));
	colliderTransforms[HEEL_R]->SetWorld(instancing->GetTransformByNode(index, 19));
	colliderTransforms[SOLE_R]->SetWorld(instancing->GetTransformByNode(index, 20));
	colliderTransforms[TOES_R]->SetWorld(instancing->GetTransformByNode(index, 21));
	colliderTransforms[THIGH_R]->SetWorld(instancing->GetTransformByNode(index, 23));

	colliderTransforms[BELLY]->SetWorld(instancing->GetTransformByNode(index, 26));
	colliderTransforms[TORSO]->SetWorld(instancing->GetTransformByNode(index, 27));
	colliderTransforms[CHEST]->SetWorld(instancing->GetTransformByNode(index, 28));
	colliderTransforms[NECK]->SetWorld(instancing->GetTransformByNode(index, 29));

	colliderTransforms[SHOULDER_L]->SetWorld(instancing->GetTransformByNode(index, 31));
	colliderTransforms[ELBOW_L]->SetWorld(instancing->GetTransformByNode(index, 32));
	colliderTransforms[WRIST_L]->SetWorld(instancing->GetTransformByNode(index, 33));
	colliderTransforms[HAND_L]->SetWorld(instancing->GetTransformByNode(index, 34));
	colliderTransforms[FINGERS_L]->SetWorld(instancing->GetTransformByNode(index, 35));

	colliderTransforms[SHOULDER_R]->SetWorld(instancing->GetTransformByNode(index, 60));
	colliderTransforms[ELBOW_R]->SetWorld(instancing->GetTransformByNode(index, 61));
	colliderTransforms[WRIST_R]->SetWorld(instancing->GetTransformByNode(index, 62));
	colliderTransforms[HAND_R]->SetWorld(instancing->GetTransformByNode(index, 63));
	colliderTransforms[FINGERS_R]->SetWorld(instancing->GetTransformByNode(index, 64));

	colliderTransforms[HEAD]->SetWorld(instancing->GetTransformByNode(index, 91));
}
