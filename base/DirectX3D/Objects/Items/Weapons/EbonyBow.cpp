#include "Framework.h"

EbonyBow::EbonyBow() : Model("EbonyBow")
{
	SetTag("EbonyBow");
	Pos().x += -27.0f;
	Pos().y += 0;
	Pos().z += 1.6f;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

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


	collider->SetTag("EbonyBowCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyBow::~EbonyBow()
{
	delete collider;
}

void EbonyBow::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyBow::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyBow::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyBow::ColliderManager(bool isWeaponColl)
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
