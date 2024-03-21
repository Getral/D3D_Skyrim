#include "Framework.h"

IronShield::IronShield(string name, int type, int weight,
	int value, int armor_class, int armor_type, int def)
	: Armor(name, type, weight, value, armor_class, armor_type, def)
{
	ironshield = new Model("IronShield");
	SetTag("IronShield");

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
	collider->Pos().x += 0;
	collider->Pos().y += 0;
	collider->Pos().z += 7.0f;

	collider->Rot().x *= 0.0f;
	collider->Rot().y *= 0.0f;
	collider->Rot().z *= 0.0f;

	collider->Scale().x *= 60.0f;
	collider->Scale().y *= 60.0f;
	collider->Scale().z *= 10.0f;



	collider->SetTag("IronShieldCollider");
	collider->SetParent(this);
	collider->Load();
}

IronShield::~IronShield()
{
	delete collider;
}

void IronShield::Update()
{
	UpdateWorld(); // �ڱ� ������Ʈ
	collider->UpdateWorld(); //�浹ü�� ������Ʈ
}

void IronShield::Render()
{
	Model::Render(); // �ڱ� ����
	collider->Render(); // �浹ü ����
}

void IronShield::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}
