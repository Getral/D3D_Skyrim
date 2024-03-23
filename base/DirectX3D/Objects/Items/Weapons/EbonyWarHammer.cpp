#include "Framework.h"

EbonyWarHammer::EbonyWarHammer(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)

{
	SetTag("EbonyWarHammer");
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
	collider->Pos().x += 0.0f;
	collider->Pos().y += 51.6;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 33.0f;
	collider->Scale().y *= 20.0f;
	collider->Scale().z *= 7.0f;


	collider->SetTag("EbonyWarHammerCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyWarHammer::~EbonyWarHammer()
{
	delete collider;
}

void EbonyWarHammer::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyWarHammer::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyWarHammer::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyWarHammer::ColliderManager(bool isWeaponColl)
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
