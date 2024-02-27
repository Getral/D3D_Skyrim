#include "Framework.h"

Enemy::Enemy(string name, Transform* transform, Vector3 spawnPos, float trackRange)
	: Character(transform, name, spawnPos), trackRange(trackRange)
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
}

void Enemy::Render()
{
	Character::Render();
}

void Enemy::GUIRender()
{
	Character::GUIRender();
}
