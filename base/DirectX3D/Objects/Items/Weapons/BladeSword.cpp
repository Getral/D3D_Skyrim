#include "Framework.h"

BladeSword::BladeSword() : Model("BladeSword")
{
	SetTag("BladeSword");

	collider = new BoxCollider();
	collider->Scale().x *= 2;
	collider->Scale().y *= 83;
	collider->Scale().z *= 2;
	collider->Pos().x = 0;
	collider->Pos().y += 40;
	collider->Pos().z = 0;

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
	UpdateWorld(); // �ڱ� ������Ʈ
	collider->UpdateWorld(); //�浹ü�� ������Ʈ
}

void BladeSword::Render()
{
	Model::Render(); // �ڱ� ����
	collider->Render(); // �浹ü ����
}

void BladeSword::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}
