#include "Framework.h"

EbonyMace::EbonyMace(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("EbonyMace");
	Pos().x += 0;
	Pos().y += 12.0f;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 0.0f;
	collider->Pos().y += 0.0f;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 15.0f;
	collider->Scale().y *= 15.0f;
	collider->Scale().z *= 15.0f;


	collider->SetTag("EbonyMaceCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyMace::~EbonyMace()
{
	delete collider;
}

void EbonyMace::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyMace::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyMace::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyMace::ColliderManager(bool isWeaponColl)
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
