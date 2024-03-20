#include "Framework.h"

EbonyBattleAxe::EbonyBattleAxe(string name, int type, int weight, int value,
	int weapon_class, int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class, weapon_type, atk) 
{
	ebonybattleaxe = new Model("EbonyBattleAxe");
	SetTag("EbonyBattleAxe");

	Pos().x *= 0;
	Pos().y *= 0;
	Pos().z *= 0;

	Rot().x *= 0;
	Rot().y *= 0;
	Rot().z *= 0;
	
	Scale().x *= 1;
	Scale().y *= 1;
	Scale().z *= 1;


	collider = new BoxCollider();
	collider->Pos().x = -12.3f;
	collider->Pos().y += 44.5f;
	collider->Pos().z = 0;

	collider->Rot().x *= 0.0f;
	collider->Rot().y *= 0.0f;
	collider->Rot().z *= 0.0f;

	collider->Scale().x *= 17.0f;
	collider->Scale().y *= 66.8f;
	collider->Scale().z *= 1;

	collider->SetTag("EbonyBattleAxeCollider");
	collider->SetParent(this);
	collider->Load();


}

EbonyBattleAxe::~EbonyBattleAxe()
{
	delete collider;
}

void EbonyBattleAxe::Update()
{
	UpdateWorld(); // �ڱ� ������Ʈ
	ColliderManager(isWeapon);
	collider->UpdateWorld(); //�浹ü�� ������Ʈ
}

void EbonyBattleAxe::Render()
{
	Model::Render(); // �ڱ� ����
	collider->Render(); // �浹ü ����
}

void EbonyBattleAxe::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyBattleAxe::ColliderManager(bool isWeaponColl)
{
	if (isWeaponColl)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}