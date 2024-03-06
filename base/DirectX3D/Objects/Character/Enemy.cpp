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

	FOR(colliders.size())
	{
		colliderTransforms.push_back(new Transform());
		colliderTransforms[i]->SetParent(transform);
		colliders[i]->SetParent(colliderTransforms[i]);
	}
}

Enemy::~Enemy()
{
	delete trackCollider;
	delete attackCollider;
	for (Transform* t : colliderTransforms)
		delete t;
	for (CapsuleCollider* collider : colliders)
		delete collider;
}

void Enemy::Update()
{
	Character::Update();
	trackCollider->UpdateWorld();
	attackCollider->UpdateWorld();
	for (Transform* t : colliderTransforms)
		t->UpdateWorld();

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
		if(collider->IsCollision(playerData->GetSword()->GetCollider()))
		{
			if (!isAttacked && (playerData->GetAction() == Player::ATTACK_HEAVY || playerData->GetAction() == Player::ATTACK_LEFT ||
				playerData->GetAction() == Player::ATTACK_RIGHT))
			{
				SetState(HIT);
				test = 1;
				isAttacked = true;
				break;
			}
		}
		test = 0;
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

	Track();
	Attack();

	for (CapsuleCollider* collider : colliders)
		collider->UpdateWorld();
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
	if (isAttacked) return;
	if (state == curState) return;
	
	curState = state;
	instancing->PlayClip(index, (int)state, 0.5f);
}

void Enemy::Track()
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

void Enemy::Attack()
{
	if (curState == ATTACK)
	{

	}
}

void Enemy::SetColliderByNode()
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
