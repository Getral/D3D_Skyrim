#include "Framework.h"

EbonyDagger::EbonyDagger(string name, int type, int weight, int value,
	int weapon_class, int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class, weapon_type, atk)
{
	SetTag("EbonyDagger");

	Pos().x += 0;
	Pos().y += 5.0f;
	Pos().z += 0;

	Rot().x += 90;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.3f;
	Scale().y *= 1.3f;
	Scale().z *= 1.3f;

	collider = new BoxCollider();
	collider->Pos().x += 0;
	collider->Pos().y += -1.0f;
	collider->Pos().z += -4.0f;

	collider->Rot().x += 90;
	collider->Rot().y += 0;
	collider->Rot().z += 0;

	collider->Scale().x *= 3.0f;
	collider->Scale().y *= 20.0f;
	collider->Scale().z *= 2;



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