#include "Framework.h"

EbonyMace1::EbonyMace1() : Model("EbonyMace1")
{
	SetTag("EbonyMace1");
	Pos().x += 0;
	Pos().y += 1;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 0.0f;
	collider->Pos().y += 40;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 15.0f;
	collider->Scale().y *= 15.0f;
	collider->Scale().z *= 15.0f;


	collider->SetTag("EbonyMace1collider");
	collider->SetParent(this);
	collider->Load();
}

EbonyMace1::~EbonyMace1()
{
	delete collider;
}

void EbonyMace1::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyMace1::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyMace1::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyMace1::ColliderManager(bool isWeaponColl)
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
