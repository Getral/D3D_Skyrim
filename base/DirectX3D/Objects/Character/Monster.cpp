#include "Framework.h"

Monster::Monster(Transform* transform, Status status, float trackRange)
	: Character(transform, status), trackRange(trackRange)
{
	trackCollider = new SphereCollider();
	trackCollider->Scale() *= trackRange;
	trackCollider->SetParent(transform);
}

Monster::~Monster()
{
	delete trackCollider;
}

void Monster::Update()
{
	Character::Update();
	trackCollider->UpdateWorld();
}

void Monster::Render()
{
	Character::Render();
	trackCollider->Render();
}

void Monster::GUIRender()
{
}

void Monster::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);
	trackCollider->SetActive(true);

	status.curHp = status.maxHp;

	transform->Pos() = pos;
}
