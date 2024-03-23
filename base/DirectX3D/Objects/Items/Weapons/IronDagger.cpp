#include "Framework.h"

IronDagger::IronDagger(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("IronDagger");

	Pos().x += 0;
	Pos().y += -4.9f;
	Pos().z += 0;
			
	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.2f;
	Scale().y *= 1.2f;
	Scale().z *= 1.2f;

	collider = new BoxCollider();
	collider->Pos().x += 0;
	collider->Pos().y += 16.3f;
	collider->Pos().z += 0;

	collider->Rot().x += 0;
	collider->Rot().y += 0;
	collider->Rot().z += 0;

	collider->Scale().x *= 2.5f;
	collider->Scale().y *= 19.4f;
	collider->Scale().z *= 2.0f;



	collider->SetTag("IronDaggerCollider");
	collider->SetParent(this);
	collider->Load();
}

IronDagger::~IronDagger()
{
	delete collider;
}

void IronDagger::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronDagger::Render()
{
	Model::Render();
	collider->Render();
}

void IronDagger::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronDagger::ColliderManager(bool isWeaponColl)
{
	if (isWeaponColl)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}