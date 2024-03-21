#include "Framework.h"
#include "IronArrow.h"

IronArrow::IronArrow(string name, int type, int weight,
	int value, int arrow_type, int atk)
	: Arrow(name, type, weight, value, arrow_type, atk)
{
	SetTag("EbonyArrow");

	Pos().x += 0.0f;
	Pos().y += 38.0f;
	Pos().z += 0.0f;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += XM_PI;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	collider = new BoxCollider();
	collider->Pos().x += 0.0f;
	collider->Pos().y += 0.0;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 5.0f;
	collider->Scale().y *= 5.0f;
	collider->Scale().z *= 5.0f;


	collider->SetTag("EbonyArrowCollider");
	collider->SetParent(this);
	collider->Load();
}

IronArrow::~IronArrow()
{
	delete collider;
}

void IronArrow::Update()
{
	UpdateWorld();
	collider->UpdateWorld();
}

void IronArrow::Render()
{
	Model::Render();
	collider->Render();
}

void IronArrow::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void IronArrow::ColliderManager(bool isBowCollider)
{
	if (isBowCollider)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}
