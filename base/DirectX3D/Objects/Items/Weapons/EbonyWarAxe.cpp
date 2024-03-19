#include "Framework.h"

EbonyWarAxe::EbonyWarAxe() : Model("EbonyWarAxe")
{
	SetTag("EbonyWarAxe");
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
	collider->Pos().x += -9.0f;
	collider->Pos().y += 46.0f;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 20.0f;
	collider->Scale().y *= 63.0f;
	collider->Scale().z *= 1;


	collider->SetTag("EbonyWarAxeCollide");
	collider->SetParent(this);
	collider->Load();
}

EbonyWarAxe::~EbonyWarAxe()
{
	delete collider;
}

void EbonyWarAxe::Update()
{
	UpdateWorld();
	ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyWarAxe::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyWarAxe::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyWarAxe::ColliderManager(bool isWeaponColl)
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
