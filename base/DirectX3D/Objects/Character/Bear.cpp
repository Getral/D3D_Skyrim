#include "Framework.h"

Bear::Bear(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos, float trackRange)
	: Enemy(name, index, modelAnimatorInstancing, transform, spawnPos, trackRange)
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

	SetCollidersParent();

	SetEvent(STARTSLEEP, bind(&Bear::StartStartSleep, this), 0.0f);
	SetEvent(STARTSLEEP, bind(&Bear::EndStartSleep, this), 0.9f);

	SetEvent(WAKEUP, bind(&Bear::StartWakeUp, this), 0.0f);
	SetEvent(WAKEUP, bind(&Bear::EndWakeUp, this), 0.9f);

	SetEvent(RUN, bind(&Bear::StartRun, this), 0.0f);
	SetEvent(RUN, bind(&Bear::EndRun, this), 0.9f);

	SetEvent(ATTACK, bind(&Bear::StartAttack, this), 0.0f);
	SetEvent(ATTACK, bind(&Bear::EndAttack, this), 0.9f);

	SetEvent(ATTACK2, bind(&Bear::StartAttack, this), 0.0f);
	SetEvent(ATTACK2, bind(&Bear::EndAttack, this), 0.9f);

	SetEvent(ATTACK3, bind(&Bear::StartAttack, this), 0.0f);
	SetEvent(ATTACK3, bind(&Bear::EndAttack, this), 0.9f);

	SetEvent(HIT, bind(&Bear::StartHit, this), 0.0f);
	SetEvent(HIT, bind(&Bear::EndHit, this), 0.7f);

	SetEvent(HEADSHAKE, bind(&Bear::EndHeadShake, this), 0.7f);

	FOR(totalEvent.size())
		eventIters[i] = totalEvent[i].begin();

	rigidbody->Scale().x *= trackRange * 0.2f;
	rigidbody->Scale().y *= trackRange * 0.25f;
	rigidbody->Scale().z *= trackRange * 0.38f;

	rigidbody->Pos().y = rigidbody->Scale().y * 0.5f;

	SetState(SLEEP);
}

Bear::~Bear()
{
}

void Bear::Update()
{
	Enemy::Update();

	Behavior();
	ExecuteEvent();
}

void Bear::Render()
{
	Enemy::Render();
	//for (CapsuleCollider* collider : colliders)
		//collider->Render();
	attackCollider->Render();
	trackCollider->Render();
}

void Bear::GUIRender()
{
	Enemy::GUIRender();
	ImGui::Text("Is Wake Up : %d", (int)isWakeUp);
	ImGui::Text("Is Sleep : %d", (int)isSleep);
	ImGui::Text("Is Hit : %d", (int)isHit);
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
}

void Bear::StartStartSleep()
{
	SetTarget(nullptr);
}

void Bear::EndStartSleep()
{
	isSleep = true;
	isWakeUp = false;
}

void Bear::StartWakeUp()
{
	isWakeUp = true;
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
	isHit = false;
}

void Bear::Behavior()
{
	for (CapsuleCollider* collider : colliders)
	{
		if (collider->IsCollision(playerData->GetSword()->GetCollider()))
		{
			if (!isHit)
			{
				SetState(HIT);
				break;
			}
		}
	}
	for (CapsuleCollider* collider : colliders)
	{
		if (collider->IsCollision(playerData->GetCollier()) && 
			(curState == ATTACK || curState == ATTACK2 || curState == ATTACK3))
		{
			playerData->SetAction(Player::HIT_MEDIUM);
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
			SetState(ATTACK4);
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
	if (totalEvent[clip].count(timeRatio) > 0) return; // 선행 예약된 이벤트가 있으면 종료
	totalEvent[clip][timeRatio] = event;
}

void Bear::ExecuteEvent()
{
	int index = curState; //현재 상태 받아오기
	if (totalEvent[index].empty()) return;
	if (eventIters[index] == totalEvent[index].end()) return;

	float ratio = motion->runningTime / motion->duration; //진행된 시간 나누기 전체 진행시간

	if (eventIters[index]->first > ratio) return; // 진행 시간이 정해진 기준에 못 미치면 종료(재시작)

	eventIters[index]->second(); //등록된 이벤트 수행
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
