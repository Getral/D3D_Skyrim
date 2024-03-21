#include "Framework.h"

IronQuiver::IronQuiver() : Model("IronQuiver")
{
	SetTag("IronQuiver");
	Pos().x += 26.0f;
	Pos().y += 0;
	Pos().z += 1.5f;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 179.0f;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 21.0f;
	collider->Pos().y += 0.0;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 22.7f;
	collider->Scale().y *= 116.0f;
	collider->Scale().z *= 1.0f;


	collider->SetTag("IronQuiverCollider");
	collider->SetParent(this);
	collider->Load();
}

IronQuiver::~IronQuiver()
{
	delete collider;
}

void IronQuiver::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronQuiver::Render()
{
	Model::Render();
	collider->Render();
}

void IronQuiver::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronQuiver::ColliderManager(bool isWeaponColl)
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
