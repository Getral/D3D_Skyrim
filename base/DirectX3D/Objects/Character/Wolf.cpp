#include "Framework.h"

Wolf::Wolf(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos)
	: Enemy(name, index, modelAnimatorInstancing, transform, spawnPos)
{
	colliders.push_back(new CapsuleCollider(15.0f));

	trackRange = 75000.f;
	attackRange = trackRange * 0.1f;

	SetEvent(IDLE, bind(&Wolf::StartIdle, this), 0.0f);

	SetEvent(HOWLING, bind(&Wolf::EndHowling, this), 0.99f);

	SetEvent(RUN, bind(&Wolf::StartRun, this), 0.0f);

	SetEvent(ATTACK, bind(&Wolf::StartAttack, this), 0.0f);
	SetEvent(ATTACK, bind(&Wolf::EndAttack, this), 0.9f);

	curState = IDLE;

	Init();
}

Wolf::~Wolf()
{

}

void Wolf::Update()
{
	Enemy::Update();

	Behavior();
	ExecuteEvent();

	SetColliderByNode();
}

void Wolf::Render()
{
	Enemy::Render();
	//for (CapsuleCollider* collider : colliders)
	//	collider->Render();
	//trackCollider->Render();
	//attackCollider->Render();
}

void Wolf::GUIRender()
{
	Enemy::GUIRender();
	ImGui::SliderInt("Node", (int*)&node, 1, 100);
	ImGui::Text("Cur Idle Time : %f", idleTime);
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

void Wolf::Behavior()
{
	if (attackDelay > 0.0f)
	{
		attackDelay -= DELTA;
		if (attackDelay <= 0.0f)
		{
			attackCollider->SetActive(true);
			attackDelay = 0.0f;
			SetState(RUN);
		}
	}
	
	if (curState == ATTACK || curState == COMBATIDLE) return;
	if (playerData->GetCollier()->IsCollision(attackCollider))
	{
		SetState(ATTACK);
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
	attackDelay = 1.5f;
}

void Wolf::EndAttack()
{
	SetState(COMBATIDLE);
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
	colliderTransforms[HEAD]->SetWorld(instancing->GetTransformByNode(index, node));
}
