#include "Framework.h"

EbonyWarHammer::EbonyWarHammer() : Model("EbonyWarHammer")
{
	SetTag("EbonyWarHammer");
	Pos().x += 0;
	Pos().y += 0;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 2.5f;
	collider->Pos().y += 51.0;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 29.5f;
	collider->Scale().y *= 14.5f;
	collider->Scale().z *= 5.1f;


	collider->SetTag("EbonyWarHammerCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyWarHammer::~EbonyWarHammer()
{
	delete collider;
}

void EbonyWarHammer::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyWarHammer::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyWarHammer::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyWarHammer::ColliderManager(bool isWeaponColl)
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
