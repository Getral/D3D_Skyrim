#include "Framework.h"

Dragonboneboots::Dragonboneboots() : Model("dragonboneboots")
{
	SetTag("dragonboneboots");

}

Dragonboneboots::~Dragonboneboots()
{
}

void Dragonboneboots::Update()
{
	UpdateWorld();
}

void Dragonboneboots::Render()
{
	Model::Render();
}

void Dragonboneboots::GUIRender()
{
	Model::GUIRender();
}
