#include "Framework.h"

IronBow::IronBow() : Model("IronBow")
{
	SetTag("IronBow");
	Pos().x += -0;
	Pos().y += 0;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += -5.3f;
	collider->Pos().y += 0.0;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 20.1f;
	collider->Scale().y *= 116.0f;
	collider->Scale().z *= 1.0f;


	collider->SetTag("IronBowCollider");
	collider->SetParent(this);
	collider->Load();
}

IronBow::~IronBow()
{
	delete collider;
}

void IronBow::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronBow::Render()
{
	Model::Render();
	collider->Render();
}

void IronBow::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronBow::ColliderManager(bool isWeaponColl)
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
