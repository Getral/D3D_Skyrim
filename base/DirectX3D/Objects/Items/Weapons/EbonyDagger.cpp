#include "Framework.h"

EbonyDagger::EbonyDagger(string name, int type, int weight, int value,
	int weapon_class, int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class, weapon_type, atk)
{
	ebonydagger = new Model("EbonyDagger");
	SetTag("EbonyDagger");

	Pos().x *= 0;
	Pos().y *= 0;
	Pos().z *= 0;

	Rot().x *= 90;
	Rot().y *= 0;
	Rot().z *= 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x = 0;
	collider->Pos().y += -1.0f;
	collider->Pos().z = -9.0f;

	collider->Rot().x = 90;
	collider->Rot().y = 0;
	collider->Rot().z = 0;

	collider->Scale().x *= 2.0f;
	collider->Scale().y *= 16.0f;
	collider->Scale().z *= 1;



	collider->SetTag("EbonyDaggerCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyDagger::~EbonyDagger()
{
	delete collider;
}

void EbonyDagger::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyDagger::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyDagger::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyDagger::ColliderManager(bool isWeaponColl)
{
	if (isWeaponColl)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}