#include "Framework.h"

Shield::Shield() : Model("Shield")
{
	SetTag("Shield");

	collider = new BoxCollider();
	collider->SetTag("ShieldCollider");
	collider->SetParent(this);
	collider->Load();
}

Shield::~Shield()
{
	delete collider;
}

void Shield::Update()
{
	UpdateWorld(); // �ڱ� ������Ʈ
	collider->UpdateWorld(); //�浹ü�� ������Ʈ
}

void Shield::Render()
{
	Model::Render(); // �ڱ� ����
	collider->Render(); // �浹ü ����
}

void Shield::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}
