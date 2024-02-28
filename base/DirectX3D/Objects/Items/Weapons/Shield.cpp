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
	UpdateWorld(); // 자기 업데이트
	collider->UpdateWorld(); //충돌체도 업데이트
}

void Shield::Render()
{
	Model::Render(); // 자기 렌더
	collider->Render(); // 충돌체 렌더
}

void Shield::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}
