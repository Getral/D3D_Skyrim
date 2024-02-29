#include "Framework.h"

Enemy::Enemy(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos, float trackRange)
	: Character(transform, name, spawnPos), index(index), instancing(modelAnimatorInstancing), trackRange(trackRange)
{
	trackCollider = new SphereCollider();
	trackCollider->Scale() *= trackRange;
	trackCollider->SetParent(transform);
}

Enemy::~Enemy()
{
	delete trackCollider;
}

void Enemy::Update()
{
	Character::Update();
	trackCollider->UpdateWorld();

	if (target)
	{
		SetState(RUN);
		velocity = target->GlobalPos() - transform->GlobalPos();
	}

	Track();
}

void Enemy::Render()
{
	Character::Render();
	trackCollider->Render();
}

void Enemy::GUIRender()
{
	Character::GUIRender();
}

void Enemy::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	instancing->PlayClip(index, (int)state);
}

void Enemy::Track()
{
	transform->Pos() += velocity.GetNormalized() * speed * DELTA;
	transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
}
