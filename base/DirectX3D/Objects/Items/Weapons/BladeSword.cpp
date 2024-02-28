#include "Framework.h"

BladeSword::BladeSword() : Model("BladeSword")
{
	SetTag("BladeSword");

	collider = new BoxCollider();
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
