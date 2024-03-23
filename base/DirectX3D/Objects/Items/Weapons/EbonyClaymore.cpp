#include "Framework.h"


EbonyClaymore::EbonyClaymore(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk) 
{
	SetTag("EbonyClaymore");

	Pos().x *= 0;
	Pos().y *= -11;
	Pos().z *= 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;


	collider = new BoxCollider();
	collider->Pos().x = 1.0f;
	collider->Pos().y += 58.0f;
	collider->Pos().z = 0;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 7.0;
	collider->Scale().y *= 60.0f;
	collider->Scale().z *= 3.0f;



	collider->SetTag("EbonyClaymoreCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyClaymore::~EbonyClaymore()
{
	delete collider;
}

void EbonyClaymore::Update()
{
	UpdateWorld(); // 자기 업데이트
	ColliderManager(isWeapon);
	collider->UpdateWorld(); //충돌체도 업데이트
}

void EbonyClaymore::Render()
{
	Model::Render(); // 자기 렌더
	collider->Render(); // 충돌체 렌더
}

void EbonyClaymore::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyClaymore::ColliderManager(bool isWeaponColl)
{
	if (isWeaponColl)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}