#include "Framework.h"

InvenUI::InvenUI()
{
	frame = new Quad(L"Textures/UI/frame.png");
	frame->GetMaterial()->SetShader(L"UI/EditAlpha.hlsl");
	frame->Pos() = { CENTER_X - 300 ,CENTER_Y };
	frame->Scale().x *= 0.9f;

	framebar = new Quad(L"Textures/UI/framebar.png");
	framebar->SetParent(frame);

	framebar->Pos().x -= 24.0f;
	framebar->Pos().y += 300.0f;
	framebar->Scale().x *= 5.5f;

	framebar2 = new Quad(L"Textures/UI/frameColor.png");
	//framebar2->SetParent(frame);
	framebar2->Pos() = { CENTER_X - 400 ,CENTER_Y };
	framebar2->Scale().x *= 2.5f;
	framebar2->Scale().y *= 1000.0f;
	framebar2->UpdateWorld();

	framebar3 = new Quad(L"Textures/UI/frameColor.png");
	//framebar2->SetParent(frame);
	framebar3->Pos() = { CENTER_X - 200 ,CENTER_Y + 275 };
	framebar3->Scale().x *= 500.0f;
	framebar3->Scale().y *= 2.5f;
	framebar3->UpdateWorld();

	title_all = new Quad(L"Textures/UI/icon_all.png");
	title_all->SetParent(frame);
	title_all->Pos().x -= 300.0f;
	title_all->Pos().y += 250.0f;
	title_all->Scale() *= 0.3f;


	title_weapon = new Quad(L"Textures/UI/icon_weapon.png");
	title_weapon->SetParent(title_all);
	title_weapon->Pos().y -= 150.0f;

	title_armor = new Quad(L"Textures/UI/icon_armor.png");
	title_clothing = new Quad(L"Textures/UI/icon_clothing.png");
	title_misc = new Quad(L"Textures/UI/icon_misc.png");

	selectedBar = new Quad(Vector2(180, 40));
	selectedBar->Pos() = { CENTER_X - 495,CENTER_Y + 250};
	selectedBar->GetMaterial()->SetShader(L"UI/EditAlpha2.hlsl");

	itemstatus = new ItemStatus();
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
	selectedBar->UpdateWorld();

	if (selectedTitleNum < InvenUI::ALL)
		selectedTitleNum = InvenUI::ALL;
	if (selectedTitleNum > InvenUI::WEAPON)
		selectedTitleNum = InvenUI::WEAPON;

	if (KEY_DOWN(VK_DOWN))
		selectedTitleNum++;
	if (KEY_DOWN(VK_UP))
		selectedTitleNum--;

	switch (selectedTitleNum)
	{
	case InvenUI::ALL:
		selectedBar->Pos().y = title_all->GlobalPos().y;
		break;
	case InvenUI::WEAPON:
		selectedBar->Pos().y = title_weapon->GlobalPos().y;
		break;
	case InvenUI::ARMOR:
		break;
	case InvenUI::CLOTHING:
		break;
	case InvenUI::MISC:
		break;
	default:
		break;
	}
}

void InvenUI::Render()
{
	frame->Render();
	framebar->Render();
	framebar2->Render();
	framebar3->Render();
	title_all->Render();
	title_weapon->Render();

	selectedBar->Render();

	Font::Get()->RenderText("NAME", { 275, CENTER_Y + 290 });
	Font::Get()->RenderText("TYPE", { 480, CENTER_Y + 290 });
	Font::Get()->RenderText("WGT", { 515, CENTER_Y + 290 });
	Font::Get()->RenderText("VAL", { 550, CENTER_Y + 290 });

	listingItem("dragonboneboots");

	

	//Font::Get()->RenderText("dragonbonecuirassplate", { 300, WIN_HEIGHT - 30 });
	//Font::Get()->RenderText("dragonbonegauntlets", { 300, WIN_HEIGHT - 50 });
	//Font::Get()->RenderText("dragonbonehelmet", { 300, WIN_HEIGHT - 70 });
	//Font::Get()->RenderText("dragonboneshield", { 300, WIN_HEIGHT - 90 });
}

void InvenUI::GUIRender()
{
	

}

void InvenUI::AddItem(string inname)
{
	inven_armors.push_back(itemstatus->GetArmor(inname));

	
}

void InvenUI::listingItem(string inname)
{
	Font::Get()->RenderText(itemstatus->GetArmor(inname)->GetStatus().name, { 275, WIN_HEIGHT - 100 });
	Font::Get()->RenderText(to_string(itemstatus->GetArmor(inname)->GetStatus().gold), { 515, WIN_HEIGHT - 100 });
	Font::Get()->RenderText(to_string(itemstatus->GetArmor(inname)->GetStatus().weight), { 550, WIN_HEIGHT - 100 });
	//Font::Get()->RenderText(to_string(itemstatus->GetArmor(inname)->GetStatus().count), { 540, WIN_HEIGHT - 10 });
}
