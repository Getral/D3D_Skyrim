#include "Framework.h"

IronLongSword::IronLongSword(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("IronLongSword");
	Pos().x += 0;
	Pos().y += 0;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 0;
	collider->Pos().y += 35.2f;
	collider->Pos().z += 0;
					  
	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 8.0f;
	collider->Scale().y *= 62.2f;
	collider->Scale().z *= 2.0f;


	collider->SetTag("IronLongSwordCollider");
	collider->SetParent(this);
	collider->Load();
}

IronLongSword::~IronLongSword()
{
	delete collider;
}

void IronLongSword::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronLongSword::Render()
{
	Model::Render();
	collider->Render();
}

void IronLongSword::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronLongSword::ColliderManager(bool isWeaponColl)
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
