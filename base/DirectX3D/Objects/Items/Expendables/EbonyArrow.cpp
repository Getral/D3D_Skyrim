#include "Framework.h"
#include "EbonyArrow.h"

EbonyArrow::EbonyArrow(string name, int type, int weight,
	int value, int arrow_type, int atk)
	: Arrow(name, type, weight, value, arrow_type, atk)
{
	SetTag("EbonyArrow");

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += XM_PI;


	collider = new BoxCollider();
	collider->Pos().x += 1.0f;
	collider->Pos().y += 1.0f;
	collider->Pos().z += 1.0f;
	
	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 1.0f;
	collider->Scale().y *= 1.0f;
	collider->Scale().z *= 1.0f;


	collider->SetTag("EbonyArrowCollider");
	collider->SetParent(this);
	collider->Load();
}

EbonyArrow::~EbonyArrow()
{
	delete collider;
}

void EbonyArrow::Update()
{
	UpdateWorld();
	collider->UpdateWorld();
}

void EbonyArrow::Render()
{
	Model::Render();
	collider->Render();
}

void EbonyArrow::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}

void EbonyArrow::ColliderManager(bool isBowCollider)
{
	if (isBowCollider)
		collider->SetActive(true);

	else
		collider->SetActive(false);
}
