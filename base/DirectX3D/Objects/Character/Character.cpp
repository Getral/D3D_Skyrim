#include "Framework.h"

Character::Character(Transform* transform, string name, Vector3 spawnPos)
	: transform(transform), name(name), spawnPos(spawnPos)
{
	collider = new CapsuleCollider();
	collider->SetParent(transform);
}

Character::~Character()
{
	delete transform;
	delete collider;
}

void Character::Update()
{
	collider->UpdateWorld();
}

void Character::Render()
{
	collider->Render();
}

void Character::SetStatus(int level, float hp, float stam, float atk, float speed)
{
	status.level = level;
	status.curHp = hp;
	status.maxHp = hp;
	status.curStam = stam;
	status.maxStam = stam;
	status.atk = atk;
	status.speed = speed;
}

void Character::Spawn()
{
	transform->SetActive(true);
	collider->SetActive(true);

	status.curHp = status.maxHp;

	transform->Pos() = { spawnPos.x, spawnPos.y, spawnPos.z };
}
