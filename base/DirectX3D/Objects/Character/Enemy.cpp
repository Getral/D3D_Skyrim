#include "Framework.h"

Enemy::Enemy(string name, UINT index, ModelAnimatorInstancing * modelAnimatorInstancing, Transform* transform, Vector3 spawnPos)
	: Character(transform, name, spawnPos), index(index), instancing(modelAnimatorInstancing)
{
	this->transform->SetTag("Enemy");

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

	if(!TerrainManager::Get()->GetTerrain()->ComputePicking(transform->Pos(), transform))
		transform->Pos().y -= gravity * DELTA;
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

	isBattle = false;

	ObjectManager::Get()->Create({ transform->GlobalPos().x, 0.5f, transform->GlobalPos().z }, 0, "coin");
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
