#include "Framework.h"

BladeSword::BladeSword() : Model("BladeSword")
{
	SetTag("BladeSword");

	collider = new BoxCollider();
	collider->Pos().x = 0;
	collider->Pos().y += 40;
	collider->Pos().z = 0;

	collider->Rot().x *= 0.0f;
	collider->Rot().y *= 0.0f;
	collider->Rot().z *= 0.0f;

	collider->Scale().x *= 2;
	collider->Scale().y *= 83;
	collider->Scale().z *= 2;

	collider->SetTag("BladeSwordCollider");
	collider->SetParent(this);
	collider->Load();
}

BladeSword::~BladeSword()
{
	delete collider;
}

void BladeSword::Update()
{
	UpdateWorld(); // 자기 업데이트
	ColliderManager(isWeapon);
	collider->UpdateWorld(); //충돌체도 업데이트
}

void BladeSword::Render()
{
	Model::Render(); // 자기 렌더
	collider->Render(); // 충돌체 렌더
}

void BladeSword::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void BladeSword::ColliderManager(bool isWeaponColl)
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
