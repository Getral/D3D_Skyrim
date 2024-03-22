#include "Framework.h"

EbonyWarAxe::EbonyWarAxe(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("EbonyWarAxe");
	Pos().x += 0;
	Pos().y += 0.0f;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += -5.0f;
	collider->Pos().y += 30.0f;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 30.0f;
	collider->Scale().y *= 16.0f;
	collider->Scale().z *= 9.0f;


	collider->SetTag("EbonyWarAxeCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyWarAxe::~EbonyWarAxe()
{
	delete collider;
}

void EbonyWarAxe::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyWarAxe::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyWarAxe::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyWarAxe::ColliderManager(bool isWeaponColl)
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
