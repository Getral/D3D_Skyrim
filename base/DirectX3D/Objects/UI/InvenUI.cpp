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
	framebar3->Pos() = { CENTER_X - 228 ,CENTER_Y + 275 };
	framebar3->Scale().x *= 340.0f;
	framebar3->Scale().y *= 2.5f;
	framebar3->UpdateWorld();

	title_all = new Quad(L"Textures/UI/icon_all.png");
	title_all->Pos() = {70, 610};
	title_all->Scale() *= 0.3f;


	title_weapon = new Quad(L"Textures/UI/icon_weapon.png");
	title_weapon->Pos().x = title_all->Pos().x;
	title_weapon->Pos().y = title_all->Pos().y - 40.0f;
	title_weapon->Scale() *= 0.3f;

	title_armor = new Quad(L"Textures/UI/icon_armor.png");
	title_armor->Pos().x = title_all->Pos().x;
	title_armor->Pos().y = title_all->Pos().y - 160.0f;
	title_armor->Scale() *= 0.3f;

	title_clothing = new Quad(L"Textures/UI/icon_clothing.png");
	title_clothing->Pos().x = title_all->Pos().x;
	title_clothing->Pos().y = title_all->Pos().y - 280.0f;
	title_clothing->Scale() *= 0.3f;

	title_expendable = new Quad(L"Textures/UI/icon_expendable.png");
	title_expendable->Pos().x = title_all->Pos().x;
	title_expendable->Pos().y = title_all->Pos().y - 320.0f;
	title_expendable->Scale() *= 0.05f;

	title_misc = new Quad(L"Textures/UI/icon_misc.png");
	title_misc->Pos().x = title_all->Pos().x;
	title_misc->Pos().y = title_all->Pos().y - 360.0f;
	title_misc->Scale() *= 0.3f;


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
	title_armor->UpdateWorld();
	title_clothing->UpdateWorld();
	title_expendable->UpdateWorld();
	title_misc->UpdateWorld();

	selectedBar->UpdateWorld();

	SelectedBarPosing();
	
}

void InvenUI::Render()
{
	frame->Render();
	framebar->Render();
	framebar2->Render();
	framebar3->Render();

	title_all->Render();
	title_weapon->Render();
	title_armor->Render();
	title_clothing->Render();
	title_expendable->Render();
	title_misc->Render();

	selectedBar->Render();

	RenderTitle();

	listingItem("dragonboneboots");

	

	//Font::Get()->RenderText("dragonbonecuirassplate", { 300, WIN_HEIGHT - 30 });
	//Font::Get()->RenderText("dragonbonegauntlets", { 300, WIN_HEIGHT - 50 });
	//Font::Get()->RenderText("dragonbonehelmet", { 300, WIN_HEIGHT - 70 });
	//Font::Get()->RenderText("dragonboneshield", { 300, WIN_HEIGHT - 90 });
}

void InvenUI::GUIRender()
{
	ImGui::Text("pos : %f", title_all->GlobalPos().x);
	ImGui::Text("pos : %f", title_all->GlobalPos().y);
}

void InvenUI::SelectedBarPosing()
{
	if (selectedTitleNum < InvenUI::ALL)
		selectedTitleNum = InvenUI::ALL;
	if (selectedTitleNum > InvenUI::MISC)
		selectedTitleNum = InvenUI::MISC;

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
	case InvenUI::WEAPON_IRON:
		selectedBar->Pos().y = title_weapon->GlobalPos().y - 40;
		break;
	case InvenUI::WEAPON_EBONY:
		selectedBar->Pos().y = title_weapon->GlobalPos().y - 80;
		break;
	case InvenUI::ARMOR:
		selectedBar->Pos().y = title_armor->GlobalPos().y;
		break;
	case InvenUI::ARMOR_IRON:
		selectedBar->Pos().y = title_armor->GlobalPos().y - 40;
		break;
	case InvenUI::ARMOR_DRAGONBONE:
		selectedBar->Pos().y = title_armor->GlobalPos().y - 80;
		break;
	case InvenUI::CLOTHING:
		selectedBar->Pos().y = title_clothing->GlobalPos().y;
		break;
	case InvenUI::EXPENDABLE:
		selectedBar->Pos().y = title_expendable->GlobalPos().y;
		break;
	case InvenUI::MISC:
		selectedBar->Pos().y = title_misc->GlobalPos().y;
		break;
	default:
		break;
	}


}

void InvenUI::RenderTitle()
{
	Font::Get()->RenderText("ALL", { 100, title_all->GlobalPos().y });

	Font::Get()->RenderText("WEAPON", { 100,title_weapon->GlobalPos().y });
	Font::Get()->RenderText("Iron", { 110,title_weapon->GlobalPos().y - 40 });
	Font::Get()->RenderText("Ebony", { 110,title_weapon->GlobalPos().y - 40 * 2 });

	Font::Get()->RenderText("ARMOR", { 100,title_armor->GlobalPos().y });
	Font::Get()->RenderText("Iron", { 110,title_armor->GlobalPos().y - 40 });
	Font::Get()->RenderText("Dragonbone", { 110,title_armor->GlobalPos().y - 40 * 2 });

	Font::Get()->RenderText("CLOTHING", { 100,title_clothing->GlobalPos().y });

	Font::Get()->RenderText("EXPENDABLE", { 100,title_expendable->GlobalPos().y });

	Font::Get()->RenderText("MISC", { 100,title_misc->GlobalPos().y });

	Font::Get()->RenderText("NAME", { 275, CENTER_Y + 290 });
	Font::Get()->RenderText("TYPE", { 480, CENTER_Y + 290 });
	Font::Get()->RenderText("WGT", { 515, CENTER_Y + 290 });
	Font::Get()->RenderText("VAL", { 550, CENTER_Y + 290 });

	Font::Get()->AddStyle("Futura_big", L"Futura", 30.0f);
	Font::Get()->SetStyle("Futura_big");
	switch (selectedTitleNum)
	{
	case InvenUI::ALL:
		Font::Get()->RenderText("ALL", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::WEAPON:
		Font::Get()->RenderText("WEAPON", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::WEAPON_IRON:
		Font::Get()->RenderText("IRON", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::WEAPON_EBONY:
		Font::Get()->RenderText("EBONY", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::ARMOR:
		Font::Get()->RenderText("ARMOR", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::ARMOR_IRON:
		Font::Get()->RenderText("IRON", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::ARMOR_DRAGONBONE:
		Font::Get()->RenderText("DRAGONBONE", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::CLOTHING:
		Font::Get()->RenderText("CLOTHING", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::EXPENDABLE:
		Font::Get()->RenderText("EXPENDABLE", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::MISC:
		Font::Get()->RenderText("MISC", { 70, CENTER_Y + 330 });
		break;
	default:
		break;
	}
	Font::Get()->SetStyle("Futura");
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
