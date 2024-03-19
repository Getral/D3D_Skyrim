#include "Framework.h"

EbonyLongSword::EbonyLongSword() : Model("EbonyLongSword")
{
	SetTag("EbonyLongSword");
	Pos().x *= 0;
	Pos().y *= 23.8;
	Pos().z *= 0;

	Rot().x += 90;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 2;
	Scale().y *= 2;
	Scale().z *= 3;

	collider = new BoxCollider();
	collider->Pos().x *= -0.3f;
	collider->Pos().y *= 0;
	collider->Pos().z *= -9.2f;

	collider->Rot().x *= 90;
	collider->Rot().y *= 0.0f;
	collider->Rot().z *= 0.0f;

	collider->Scale().x *= 1.2f;
	collider->Scale().y *= 21.3f;
	collider->Scale().z *= 1;


	collider->SetTag("EbonyLongSwordCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyLongSword::~EbonyLongSword()
{
	delete collider;
}

void EbonyLongSword::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyLongSword::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyLongSword::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyLongSword::ColliderManager(bool isWeaponColl)
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
