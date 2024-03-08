#include "Framework.h"

InvenUI::InvenUI()
{
	frame = new Quad(L"Textures/UI/InvenAsset/97.png");
	frame->Pos() = { CENTER_X,CENTER_Y };
}

InvenUI::~InvenUI()
{
}

void InvenUI::Update()
{
	frame->UpdateWorld();
}

void InvenUI::Render()
{
	//frame->Render();
	Font::Get()->RenderText("ALL",		{ CENTER_X,CENTER_Y });
	Font::Get()->RenderText("Weapons",	{ CENTER_X,CENTER_Y - 10 });
	Font::Get()->RenderText("Armor",	{ CENTER_X,CENTER_Y - 20 });
	Font::Get()->RenderText("Clothing", { CENTER_X,CENTER_Y - 30 });
}

void InvenUI::GUIRender()
{
}
