#include "Framework.h"

IronWarAxe::IronWarAxe() : Model("IronWarAxe")
{
	SetTag("IronWarAxe");
	Pos().x += 0;
	Pos().y += 25;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 180;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 7.4f;
	collider->Pos().y += -5.1f;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 8.9f;
	collider->Scale().y *= 17.2f;
	collider->Scale().z *= 2;


	collider->SetTag("IronWarAxeCollider");
	collider->SetParent(this);
	collider->Load();
}

IronWarAxe::~IronWarAxe()
{
	delete collider;
}

void IronWarAxe::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronWarAxe::Render()
{
	Model::Render();
	collider->Render();
}

void IronWarAxe::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronWarAxe::ColliderManager(bool isWeaponColl)
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
