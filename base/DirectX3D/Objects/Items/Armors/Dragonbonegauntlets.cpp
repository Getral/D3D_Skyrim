#include "Framework.h"

Dragonbonegauntlets::Dragonbonegauntlets() : Model("dragonbonegauntlets")
{
	SetTag("dragonbonegauntlets");
}

Dragonbonegauntlets::~Dragonbonegauntlets()
{
}

void Dragonbonegauntlets::Update()
{
	UpdateWorld();
}

void Dragonbonegauntlets::Render()
{
	Model::Render();
}

void Dragonbonegauntlets::GUIRender()
{
	Model::GUIRender();
}
