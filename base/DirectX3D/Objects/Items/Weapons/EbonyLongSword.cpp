#include "Framework.h"

EbonyLongSword::EbonyLongSword(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("EbonyLongSword");
	Pos().x += 1.5f;
	Pos().y += 12.0f;
	Pos().z += 0;

	Rot().x += 90;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 2.5f;
	Scale().y *= 2.5f;
	Scale().z *= 3.0f;

	collider = new BoxCollider();
	collider->Pos().x += 0;
	collider->Pos().y += 0;
	collider->Pos().z += -9.2f;

	collider->Rot().x += 90;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 2.0f;
	collider->Scale().y *= 23.0f;
	collider->Scale().z *= 2.0f;


	collider->SetTag("EbonyLongSwordCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyLongSword::~EbonyLongSword()
{
	delete collider;
}

void EbonyLongSword::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyLongSword::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyLongSword::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyLongSword::ColliderManager(bool isWeaponColl)
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
