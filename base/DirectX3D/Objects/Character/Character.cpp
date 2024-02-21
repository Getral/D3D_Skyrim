#include "Framework.h"

Character::Character(Transform* transform, Status status)
	: transform(transform), status(status)
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
