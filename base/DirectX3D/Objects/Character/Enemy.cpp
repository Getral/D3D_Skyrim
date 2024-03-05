#include "Framework.h"

Enemy::Enemy(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos, float trackRange)
	: Character(transform, name, spawnPos), index(index), instancing(modelAnimatorInstancing), trackRange(trackRange)
{
	trackCollider = new SphereCollider();
	trackCollider->Scale() *= trackRange;
	trackCollider->SetParent(transform);

	attackRange = trackRange * 0.3f;
	attackCollider = new SphereCollider();
	attackCollider->Scale() *= attackRange;
	attackCollider->Pos().SetY(attackRange * 0.5f);
	attackCollider->SetParent(transform);


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
}

Enemy::~Enemy()
{
	delete trackCollider;
	delete attackCollider;
	for (CapsuleCollider* collider : colliders)
		delete collider;
}

void Enemy::Update()
{
	Character::Update();
	trackCollider->UpdateWorld();
	attackCollider->UpdateWorld();
	for (CapsuleCollider* collider : colliders)
		collider->UpdateWorld();

	//for (CapsuleCollider* collider : colliders)
	//{
	//	if (playerData->GetCollier()->IsCollision(collider))
	//	{
	//		playerData->SetAction(Player::HIT_MEDIUM);
	//		playerData->SetIsHit(true);
	//	}
	//	else
	//	{
	//		playerData->SetIsHit(false);
	//	}
	//}
	if (playerData->GetCollier()->IsCollision(attackCollider))
	{
		SetState(ATTACK);
	}
	else if (playerData->GetCollier()->IsCollision(trackCollider))
	{
		SetState(RUN);
		SetTarget(playerData);
	}
	else
	{
		SetState(IDLE);
		SetTarget(nullptr);
	}
	

	SetColliderByNode();

	Track();
	Attack();
}

void Enemy::Render()
{
	Character::Render();
	//trackCollider->Render();
	//attackCollider->Render();
	for (CapsuleCollider* collider : colliders)
		collider->Render();
}

void Enemy::GUIRender()
{
	Character::GUIRender();
	ImGui::Text("Cur State : %d", test);
}

void Enemy::SetState(State state)
{
	if (state == curState) return;
	test = 0;
	curState = state;
	instancing->PlayClip(index, (int)state, 0.5f);
}

void Enemy::Track()
{
	if (curState == ATTACK) return;
	if (target)
	{
		velocity = target->GlobalPos() - transform->GlobalPos();
		transform->Pos() += velocity.GetNormalized() * this->status.speed * DELTA;
		transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
	}
}

void Enemy::Attack()
{
	if (curState == ATTACK)
	{

	}
}

void Enemy::SetColliderByNode()
{
	colliders[HIP]->SetWorld(instancing->GetTransformByNode(index, 8));

	colliders[KNEE_L]->SetWorld(instancing->GetTransformByNode(index, 10));
	colliders[HEEL_L]->SetWorld(instancing->GetTransformByNode(index, 11));
	colliders[SOLE_L]->SetWorld(instancing->GetTransformByNode(index, 12));
	colliders[TOES_L]->SetWorld(instancing->GetTransformByNode(index, 13));
	colliders[THIGH_L]->SetWorld(instancing->GetTransformByNode(index, 15));

	colliders[KNEE_R]->SetWorld(instancing->GetTransformByNode(index, 18));
	colliders[HEEL_R]->SetWorld(instancing->GetTransformByNode(index, 19));
	colliders[SOLE_R]->SetWorld(instancing->GetTransformByNode(index, 20));
	colliders[TOES_R]->SetWorld(instancing->GetTransformByNode(index, 21));
	colliders[THIGH_R]->SetWorld(instancing->GetTransformByNode(index, 23));

	colliders[BELLY]->SetWorld(instancing->GetTransformByNode(index, 26));
	colliders[TORSO]->SetWorld(instancing->GetTransformByNode(index, 27));
	colliders[CHEST]->SetWorld(instancing->GetTransformByNode(index, 28));
	colliders[NECK]->SetWorld(instancing->GetTransformByNode(index, 29));

	colliders[SHOULDER_L]->SetWorld(instancing->GetTransformByNode(index, 31));
	colliders[ELBOW_L]->SetWorld(instancing->GetTransformByNode(index, 32));
	colliders[WRIST_L]->SetWorld(instancing->GetTransformByNode(index, 33));
	colliders[HAND_L]->SetWorld(instancing->GetTransformByNode(index, 34));
	colliders[FINGERS_L]->SetWorld(instancing->GetTransformByNode(index, 35));

	colliders[SHOULDER_R]->SetWorld(instancing->GetTransformByNode(index, 60));
	colliders[ELBOW_R]->SetWorld(instancing->GetTransformByNode(index, 61));
	colliders[WRIST_R]->SetWorld(instancing->GetTransformByNode(index, 62));
	colliders[HAND_R]->SetWorld(instancing->GetTransformByNode(index, 63));
	colliders[FINGERS_R]->SetWorld(instancing->GetTransformByNode(index, 64));

	colliders[HEAD]->SetWorld(instancing->GetTransformByNode(index, 91));
}
