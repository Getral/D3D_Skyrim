#include "Framework.h"
#include "DragonShield.h"

DragonShield::DragonShield(string name, int type, int weight, 
	int value, int armor_class, int armor_type, int def)
	: Armor(name, type, weight, value, armor_class, armor_type, def)
{
	dragonshield = new Model("dragonshield");
	SetTag("DragonShield");

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
	collider->Pos().y += -8.0f;
	collider->Pos().z += 7.0f;

	collider->Rot().x *= 0.0f;
	collider->Rot().y *= 0.0f;
	collider->Rot().z *= 0.0f;

	collider->Scale().x *= 50.0f;
	collider->Scale().y *= 70.0f;
	collider->Scale().z *= 10.0f;



	collider->SetTag("DragonShieldCollider");
	collider->SetParent(this);
	collider->Load();
}

DragonShield::~DragonShield()
{
	delete collider;
}

void DragonShield::Update()
{
	UpdateWorld();
	collider->UpdateWorld();
}

void DragonShield::Render()
{
	Model::Render();
	collider->Render();
}

void DragonShield::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}
