#include "Framework.h"

EbonyQuiver::EbonyQuiver() : Model("EbonyQuiver")
{
	SetTag("EbonyQuiver");
	Pos().x += 0;
	Pos().y += -6.0;
	Pos().z += 1.5f;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += XM_PI;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

	//collider = new CapsuleCollider();
	//collider->Pos().x += 1.0f;
	//collider->Pos().y += -2.7f;
	//collider->Pos().z += 1.0f;

	//collider->Rot().x += 0.0f;
	//collider->Rot().y += 0.0f;
	//collider->Rot().z += 0.0f;

	//collider->Scale().x *= 13.1f;
	//collider->Scale().y *= 12.6;
	//collider->Scale().z *= -7.7f;


	/*collider->SetTag("EbonyQuiverCollider");
	collider->SetParent(this);
	collider->Load();*/
}

EbonyQuiver::~EbonyQuiver()
{
	//delete collider;
}

void EbonyQuiver::Update()
{
	UpdateWorld();
	//collider->UpdateWorld();
}

void EbonyQuiver::Render()
{
	Model::Render();
	//collider->Render();
}

void EbonyQuiver::GUIRender()
{
	Model::GUIRender();
	//collider->GUIRender();
}

