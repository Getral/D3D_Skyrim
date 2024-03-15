#include "Framework.h"

IronDagger::IronDagger() : Model("IronDagger")
{
	SetTag("IronDagger");

	Pos().x *= 0;
	Pos().y *= 0;
	Pos().z *= 0;

	Rot().x *= 0;
	Rot().y *= 0;
	Rot().z *= 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x = 0;
	collider->Pos().y += 14.6f;
	collider->Pos().z = 0;

	collider->Rot().x = 0;
	collider->Rot().y = 0;
	collider->Rot().z = 0;

	collider->Scale().x *= 2.0f;
	collider->Scale().y *= 16.0f;
	collider->Scale().z *= 1;



	collider->SetTag("IronDaggerCollider");
	collider->SetParent(this);
	collider->Load();
}

IronDagger::~IronDagger()
{
	delete collider;
}

void IronDagger::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronDagger::Render()
{
	Model::Render();
	collider->Render();
}

void IronDagger::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronDagger::ColliderManager(bool isWeaponColl)
{
	if (isWeaponColl)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}