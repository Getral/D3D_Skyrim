#include "Framework.h"

IronWarHammer::IronWarHammer() : Model("IronWarHammer")
{
	SetTag("IronWarHammer");
	Pos().x += 0;
	Pos().y += 0;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 180;
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

	collider->Scale().x *= 24.9f;
	collider->Scale().y *= 15.1f;
	collider->Scale().z *= 5;


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
