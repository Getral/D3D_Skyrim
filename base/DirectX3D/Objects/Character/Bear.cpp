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
}

Bear::~Bear()
{
}

void Bear::Update()
{
	Enemy::Update();

	if (isAttacked)
	{
		hitDelay += DELTA;
		if (hitDelay > 0.6f)
		{
			hitDelay = 0.0f;
			isAttacked = false;
		}
	}

	for (CapsuleCollider* collider : colliders)
	{
		if (collider->IsCollision(playerData->GetSword()->GetCollider()))
		{
			if (!isAttacked && (playerData->GetAction() == Player::ATTACK_HEAVY || playerData->GetAction() == Player::ATTACK_LEFT ||
				playerData->GetAction() == Player::ATTACK_RIGHT))
			{
				SetState(ATTACK);
				isAttacked = true;
				break;
			}
		}
	}

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

	Attack();
}

void Bear::Render()
{
	Enemy::Render();
}

void Bear::GUIRender()
{
	Enemy::GUIRender();
}

void Bear::SetState(State state)
{
	if (isAttacked) return;
	if (state == curState) return;

	curState = state;
	instancing->PlayClip(index, (int)state, 0.5f);
}

void Bear::Track()
{
	if (curState == ATTACK) return;
	if (curState == HIT) return;
	if (target)
	{
		velocity = target->GlobalPos() - transform->GlobalPos();
		transform->Pos() += velocity.GetNormalized() * this->status.speed * DELTA;
		transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
	}
}

void Bear::Attack()
{
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
