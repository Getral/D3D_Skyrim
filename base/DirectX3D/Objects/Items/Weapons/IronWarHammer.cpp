#include "Framework.h"

IronWarHammer::IronWarHammer(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("IronWarHammer");
	Pos().x += 0;
	Pos().y += 0;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += XM_PI;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 0;
	collider->Pos().y += 55.2;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 30.8f;
	collider->Scale().y *= 18.3f;
	collider->Scale().z *= 9.4f;


	collider->SetTag("IronWarHammerCollider");
	collider->SetParent(this);
	collider->Load();
}

IronWarHammer::~IronWarHammer()
{
	delete collider;
}

void IronWarHammer::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronWarHammer::Render()
{
	Model::Render();
	collider->Render();
}

void IronWarHammer::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronWarHammer::ColliderManager(bool isWeaponColl)
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
