#include "Framework.h"

IronBattleAxe::IronBattleAxe(string name, int type,
	int weight, int value, int weapon_class,
	int weapon_type, int atk)
	: Weapon(name, type, weight, value, weapon_class,
		weapon_type, atk)
{
	SetTag("IronBattleAxe");

	Pos().x += 0;
	Pos().y += 0;
	Pos().z += 0;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += 0;

	Scale().x *= 1;
	Scale().y *= 1;
	Scale().z *= 1;

	collider = new BoxCollider();
	collider->Pos().x += 0;
	collider->Pos().y += 47.6f;
	collider->Pos().z += 0;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 45.0f;
	collider->Scale().y *= 25.0f;
	collider->Scale().z *= 7.0f;


	collider->SetTag("IronBattleAxeCollider");
	collider->SetParent(this);
	collider->Load();
}

IronBattleAxe::~IronBattleAxe()
{
	delete collider;
}

void IronBattleAxe::Update()
{
	UpdateWorld(); // �ڱ� ������Ʈ
	ColliderManager(isWeapon);
	collider->UpdateWorld(); //�浹ü�� ������Ʈ
}

void IronBattleAxe::Render()
{
	Model::Render(); // �ڱ� ����
	collider->Render(); // �浹ü ����
}

void IronBattleAxe::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronBattleAxe::ColliderManager(bool isWeaponColl)
{
	if (isWeaponColl)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}