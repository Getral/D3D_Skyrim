#include "Framework.h"

InvenUI::InvenUI()
{
	frame = new Quad(L"Textures/UI/9.png");
	frame->GetMaterial()->SetShader(L"UI/EditAlpha2.hlsl");
	frame->Pos() = { CENTER_X - 300 ,CENTER_Y };
	frame->Scale().x *= 0.9f;

	framebar = new Quad(L"Textures/UI/87.png");
	framebar->SetParent(frame);
	framebar->Pos().x -= 24.0f;
	framebar->Pos().y += 300.0f;
	framebar->Scale().x *= 5.5f;

	title_all = new Quad(L"Textures/UI/icon_all.png");
	title_all->SetParent(frame);
	title_all->Pos().x -= 300.0f;
	title_all->Pos().y += 250.0f;
	title_all->Scale() *= 0.3f;


	title_weapon = new Quad(L"Textures/UI/icon_weapon.png");
	title_weapon->SetParent(title_all);
	//title_weapon->Pos().x -= 300.0f;
	title_weapon->Pos().y -= 150.0f;
	//title_weapon->Scale() *= 0.3f;

	title_armor = new Quad(L"Textures/UI/icon_armor.png");
	title_clothing = new Quad(L"Textures/UI/icon_clothing.png");
	title_misc = new Quad(L"Textures/UI/icon_misc.png");
}

InvenUI::~InvenUI()
{
}

void InvenUI::Update()
{
	frame->UpdateWorld();
	framebar->UpdateWorld();

	title_all->UpdateWorld();
	title_weapon->UpdateWorld();
}

void InvenUI::Render()
{
	frame->Render();
	framebar->Render();

	title_all->Render();
	title_weapon->Render();


	//Font::Get()->RenderText("ALL",		{ CENTER_X,CENTER_Y });
	//Font::Get()->RenderText("Weapons",	{ CENTER_X,CENTER_Y - 10 });
	//Font::Get()->RenderText("Armor",	{ CENTER_X,CENTER_Y - 20 });
	//Font::Get()->RenderText("Clothing", { CENTER_X,CENTER_Y - 30 });
}

void InvenUI::GUIRender()
{
}
