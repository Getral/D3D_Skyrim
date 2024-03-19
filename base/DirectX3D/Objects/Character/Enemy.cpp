#include "Framework.h"

Enemy::Enemy(string name, UINT index, ModelAnimatorInstancing * modelAnimatorInstancing, Transform* transform, Vector3 spawnPos)
	: Character(transform, name, spawnPos), index(index), instancing(modelAnimatorInstancing)
{
	rigidbody = new BoxCollider();
	rigidbody->SetParent(transform);

	trackCollider = new SphereCollider();
	trackCollider->SetParent(transform);

	attackCollider = new SphereCollider();

	attackCollider->SetParent(transform);

	motion = modelAnimatorInstancing->GetMotion(index);
	totalEvent.resize(modelAnimatorInstancing->GetClipSize());
	eventIters.resize(modelAnimatorInstancing->GetClipSize());

	//instancing->GetClip(ATTACK)->SetEvent(bind(&Enemy::Attack, this), 0.0f);
}

Enemy::~Enemy()
{
	delete trackCollider;
	delete attackCollider;
	for (Transform* colliderTransform : colliderTransforms)
		delete colliderTransform;
	for (CapsuleCollider* collider : colliders)
		delete collider;
}

void Enemy::Update()
{
	Character::Update();
	rigidbody->UpdateWorld();
	trackCollider->UpdateWorld();
	attackCollider->UpdateWorld();
	for (Transform* t : colliderTransforms)
		t->UpdateWorld();

	SetColliderByNode();

	for (CapsuleCollider* collider : colliders)
		collider->UpdateWorld();

	transform->Pos().y -= gravity * DELTA;
	if (TerrainManager::Get()->GetTerrain()->ComputePicking(transform->Pos(), transform))
		transform->Pos().y += (gravity + 2) * DELTA;
}

void Enemy::Render()
{
	Character::Render();
}

void Enemy::GUIRender()
{
	Character::GUIRender();
}

void Enemy::Init()
{
	trackCollider->Scale() *= trackRange;
	attackCollider->Scale() *= attackRange;
	attackCollider->Pos().SetY(attackRange * 0.5f);
	SetCollidersParent();

	FOR(totalEvent.size())
		eventIters[i] = totalEvent[i].begin();
}

void Enemy::Death()
{
	transform->SetActive(false);
	trackCollider->SetActive(false);
	attackCollider->SetActive(false);
	for (Transform* colliderTransform : colliderTransforms)
		colliderTransform->SetActive(false);
	for (CapsuleCollider* collider : colliders)
		collider->SetActive(false);
}

void Enemy::Track()
{
}

void Enemy::SetCollidersParent()
{
	FOR(colliders.size())
	{
		colliderTransforms.push_back(new Transform());
		colliderTransforms[i]->SetParent(transform);
		colliders[i]->SetParent(colliderTransforms[i]);
	}
}

void Enemy::SetColliderByNode()
{
}
