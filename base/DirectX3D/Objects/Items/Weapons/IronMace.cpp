#include "Framework.h"
#include "IronMace.h"

IronMace::IronMace(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("IronMace");
	Pos().x += 0;
	Pos().y += -6.6f;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 0.0f;
	collider->Pos().y += 29.7f;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 17.0f;
	collider->Scale().y *= 17.0f;
	collider->Scale().z *= 17.0f;


	collider->SetTag("IronMaceCollider");
	collider->SetParent(this);
	collider->Load();
}

IronMace::~IronMace()
{
	delete collider;
}

void IronMace::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronMace::Render()
{
	Model::Render();
	collider->Render();
}

void IronMace::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronMace::ColliderManager(bool isWeaponColl)
{
	if (isWeaponColl)
	{
		collider->SetActive(true);
	}
	else
	{
		collider->SetActive(false);
	}

}
