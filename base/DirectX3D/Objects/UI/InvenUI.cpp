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
	framebar2->Pos() = { CENTER_X - 400 ,CENTER_Y };
	framebar2->Scale().x *= 2.5f;
	framebar2->Scale().y *= 1000.0f;
	framebar2->UpdateWorld();

	framebar3 = new Quad(L"Textures/UI/frameColor.png");
	framebar3->Pos() = { CENTER_X - 228 ,CENTER_Y + 275 };
	framebar3->Scale().x *= 340.0f;
	framebar3->Scale().y *= 2.5f;
	framebar3->UpdateWorld();

	detailedframebar = new Quad(L"Textures/UI/frameColor.png");
	detailedframebar->Pos() = { CENTER_X - 228 ,CENTER_Y + 275 };
	detailedframebar->Scale().x *= 340.0f;
	detailedframebar->Scale().y *= 2.5f;
	

	title_all = new Quad(L"Textures/UI/icon_all.png");
	title_all->Pos() = {70, 610};
	title_all->Scale() *= 0.3f;

	title_armor = new Quad(L"Textures/UI/icon_armor.png");
	title_armor->Pos().x = title_all->Pos().x;
	title_armor->Pos().y = title_all->Pos().y - 40.0f;
	title_armor->Scale() *= 0.3f;

	title_weapon = new Quad(L"Textures/UI/icon_weapon.png");
	title_weapon->Pos().x = title_all->Pos().x;
	title_weapon->Pos().y = title_all->Pos().y - 160.0f;
	title_weapon->Scale() *= 0.3f;

	title_arrow = new Quad(L"Textures/UI/icon_arrow.png");
	title_arrow->Pos().x = title_all->Pos().x;
	title_arrow->Pos().y = title_all->Pos().y - 280.0f;
	title_arrow->Scale() *= 0.05f;

	title_potion = new Quad(L"Textures/UI/icon_potion.png");
	title_potion->Pos().x = title_all->Pos().x;
	title_potion->Pos().y = title_all->Pos().y - 320.0f;
	title_potion->Scale() *= 0.05f;

	title_misc = new Quad(L"Textures/UI/icon_misc.png");
	title_misc->Pos().x = title_all->Pos().x;
	title_misc->Pos().y = title_all->Pos().y - 360.0f;
	title_misc->Scale() *= 0.3f;

	selected_bar = new Quad(Vector2(180, 40));
	selected_bar->Pos() = { CENTER_X - 495,CENTER_Y + 250};
	selected_bar->GetMaterial()->SetShader(L"UI/EditAlpha2.hlsl");

	FOR(5)
	{
		equiped_icon_armor.push_back(new Quad(L"Textures/UI/Equiped_Icon.png"));
		equiped_icon_armor.back()->Scale() *= 0.9f;
		equiped_icon_armor.back()->SetActive(false);
	}

	equiped_icon_weapon = new Quad(L"Textures/UI/Equiped_Icon.png");
	equiped_icon_weapon->Scale() *= 0.9f;
	equiped_icon_weapon->Pos() = { CENTER_X ,CENTER_Y };
	

	itemstatus = new ItemStatus();

	item_detail_frame = new Quad(L"Textures/UI/Item_detail_frame.png");
	item_detail_frame->GetMaterial()->SetShader(L"UI/EditAlpha.hlsl");
	item_detail_frame->Pos() = { CENTER_X + 300 ,CENTER_Y - 200 };

	player_helmet = new Armor("none", -1, -1, -1, -1, -1, 0);
	player_cuirass = new Armor("none", -1, -1, -1, -1, -1, 0);
	player_gauntlet = new Armor("none", -1, -1, -1, -1, -1, 0);
	player_boots = new Armor("none", -1, -1, -1, -1, -1, 0);
	player_shield = new Armor("none", -1, -1, -1, -1, -1, 0);
}

InvenUI::~InvenUI()
{
}

void InvenUI::Update(Player* player)
{
	frame->UpdateWorld();
	framebar->UpdateWorld();

	title_all->UpdateWorld();
	title_weapon->UpdateWorld();
	title_armor->UpdateWorld();
	title_arrow->UpdateWorld();
	title_potion->UpdateWorld();
	title_misc->UpdateWorld();

	selected_bar->UpdateWorld();

	for(Quad* icon : equiped_icon_armor)
		icon->UpdateWorld();
	equiped_icon_weapon->UpdateWorld();

	item_detail_frame->UpdateWorld();
	detailedframebar->UpdateWorld();

	SelectedBarPosing();
	
	if (KEY_DOWN('1'))
		AddItem("ironhelmet");
	if (KEY_DOWN('2'))
		AddItem("ironcuirass");
	if (KEY_DOWN('3'))
		AddItem("irongauntlet");
	if (KEY_DOWN('4'))
		AddItem("ironboots");
	if (KEY_DOWN('5'))
		AddItem("ironshield");

	if (KEY_DOWN('6'))
		UseItem(player, "ironhelmet");
	if (KEY_DOWN('7'))
		UseItem(player, "ironcuirass");
	if (KEY_DOWN('8'))
		UseItem(player, "irongauntlet");
	if (KEY_DOWN('9'))
		UseItem(player, "ironboots");
	if (KEY_DOWN('0'))
		UseItem(player, "ironshield");
	
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
	title_arrow->Render();
	title_potion->Render();
	title_misc->Render();

	selected_bar->Render();

	for (Quad* icon : equiped_icon_armor)
		icon->Render();
	equiped_icon_weapon->Render();

	{
		item_detail_frame->Render();

		Font::Get()->RenderText("Deffense", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30});
		Font::Get()->RenderText("Weight",   { item_detail_frame->Pos().x - 40, item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText("Value",    { item_detail_frame->Pos().x + 60, item_detail_frame->Pos().y - 30 });
	}
	
	RenderTitle();

	ListingItem();

	ListingDetailed("ironhelmet");
}

void InvenUI::GUIRender()
{
	ImGui::Text(player_helmet->GetStatus().name.c_str());
	ImGui::Text(player_cuirass->GetStatus().name.c_str());
	ImGui::Text(player_gauntlet->GetStatus().name.c_str());
	ImGui::Text(player_boots->GetStatus().name.c_str());
	ImGui::Text(player_shield->GetStatus().name.c_str());
	ImGui::Text("player_helmet equip state : %d", player_helmet->GetEquip());

	if (inven_armors.size() > 1)
	{
		ImGui::Text("inven[0] equip state : %d", inven_armors[0]->GetEquip());
		ImGui::Text("inven[1] equip state : %d", inven_armors[1]->GetEquip());
	}

	
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
		selected_bar->Pos().y = title_all->GlobalPos().y;
		break;
	case InvenUI::WEAPON:
		selected_bar->Pos().y = title_weapon->GlobalPos().y;
		break;
	case InvenUI::WEAPON_IRON:
		selected_bar->Pos().y = title_weapon->GlobalPos().y - 40;
		break;
	case InvenUI::WEAPON_EBONY:
		selected_bar->Pos().y = title_weapon->GlobalPos().y - 80;
		break;
	case InvenUI::ARMOR:
		selected_bar->Pos().y = title_armor->GlobalPos().y;
		break;
	case InvenUI::ARMOR_IRON:
		selected_bar->Pos().y = title_armor->GlobalPos().y - 40;
		break;
	case InvenUI::ARMOR_DRAGONBONE:
		selected_bar->Pos().y = title_armor->GlobalPos().y - 80;
		break;
	case InvenUI::ARROW:
		selected_bar->Pos().y = title_arrow->GlobalPos().y;
		break;
	case InvenUI::POTION:
		selected_bar->Pos().y = title_potion->GlobalPos().y;
		break;
	case InvenUI::MISC:
		selected_bar->Pos().y = title_misc->GlobalPos().y;
		break;
	default:
		break;
	}


}

void InvenUI::RenderTitle()
{
	Font::Get()->RenderText("ALL", { 100, title_all->GlobalPos().y });

	Font::Get()->RenderText("ARMOR", { 100,title_armor->GlobalPos().y });
	Font::Get()->RenderText("Iron", { 110,title_armor->GlobalPos().y - 40 });
	Font::Get()->RenderText("Dragonbone", { 110,title_armor->GlobalPos().y - 40 * 2 });

	Font::Get()->RenderText("WEAPON", { 100,title_weapon->GlobalPos().y });
	Font::Get()->RenderText("Iron", { 110,title_weapon->GlobalPos().y - 40 });
	Font::Get()->RenderText("Ebony", { 110,title_weapon->GlobalPos().y - 40 * 2 });

	Font::Get()->RenderText("ARROW", { 100,title_arrow->GlobalPos().y });

	Font::Get()->RenderText("POTION", { 100,title_potion->GlobalPos().y });

	Font::Get()->RenderText("MISC", { 100,title_misc->GlobalPos().y });

	Font::Get()->RenderText("NAME", { 275, CENTER_Y + 290 });
	Font::Get()->RenderText("TYPE", { 480, CENTER_Y + 290 });
	Font::Get()->RenderText("WGT", { 515, CENTER_Y + 290 });
	Font::Get()->RenderText("VAL", { 550, CENTER_Y + 290 });

	Font::Get()->SetStyle("Futura_big");
	switch (selectedTitleNum)
	{
	case InvenUI::ALL:
		Font::Get()->RenderText("ALL", { 70, CENTER_Y + 330 });
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
	case InvenUI::WEAPON:
		Font::Get()->RenderText("WEAPON", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::WEAPON_IRON:
		Font::Get()->RenderText("IRON", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::WEAPON_EBONY:
		Font::Get()->RenderText("EBONY", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::ARROW:
		Font::Get()->RenderText("ARROW", { 70, CENTER_Y + 330 });
		break;
	case InvenUI::POTION:
		Font::Get()->RenderText("POTION", { 70, CENTER_Y + 330 });
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
	if(itemstatus->GetItem(inname).type == Item::ARMOR)
		inven_armors.push_back(itemstatus->GetArmor(inname));
	if (itemstatus->GetItem(inname).type == Item::WEAPON)
		inven_weapons.push_back(itemstatus->GetWeapon(inname));
	if (itemstatus->GetItem(inname).type == Item::ARROW)
		inven_arrows.push_back(itemstatus->GetArrow(inname));
	if (itemstatus->GetItem(inname).type == Item::POTION)
		inven_potions.push_back(itemstatus->GetPotion(inname));
	if (itemstatus->GetItem(inname).type == Item::MISC)
		inven_misces.push_back(itemstatus->GetMisc(inname));
}

void InvenUI::UseItem(Player* player, string inname)
{
	if (itemstatus->GetItem(inname).type == Item::ARMOR)
	{
		FOR(inven_armors.size())
		{
			if (inven_armors[i]->GetStatus().name == inname)
			{
				switch (inven_armors[i]->GetArmorType())
				{
				case Armor::helmet:
					player_helmet->ChangeEquipState();
					inven_armors[i]->ChangeEquipState();

					player->GetStatus().def -= player_helmet->GetDef();
					player->GetStatus().def += inven_armors[i]->GetDef();

					player_helmet = inven_armors[i];
					break;
				case Armor::cuirass:
					player_cuirass->ChangeEquipState();
					inven_armors[i]->ChangeEquipState();

					player->GetStatus().def -= player_cuirass->GetDef();
					player->GetStatus().def += inven_armors[i]->GetDef();

					player_cuirass = inven_armors[i];
					break;
				case Armor::gauntlet:
					player_gauntlet->ChangeEquipState();
					inven_armors[i]->ChangeEquipState();

					player->GetStatus().def -= player_gauntlet->GetDef();
					player->GetStatus().def += inven_armors[i]->GetDef();

					player_gauntlet = inven_armors[i];
					break;
				case Armor::boots:
					player_boots->ChangeEquipState();
					inven_armors[i]->ChangeEquipState();

					player->GetStatus().def -= player_boots->GetDef();
					player->GetStatus().def += inven_armors[i]->GetDef();

					player_boots = inven_armors[i];
					break;
				case Armor::shield:
					player_shield->ChangeEquipState();
					inven_armors[i]->ChangeEquipState();

					player->GetStatus().def -= player_shield->GetDef();
					player->GetStatus().def += inven_armors[i]->GetDef();

					player_shield = inven_armors[i];
					break;
				default:
					break;
				}
				
			}
		}
	}
	//if (itemstatus->GetItem(inname).type == Item::WEAPON)
	//	
	//if (itemstatus->GetItem(inname).type == Item::ARROW)
	//	
	//if (itemstatus->GetItem(inname).type == Item::POTION)
	//	
	//if (itemstatus->GetItem(inname).type == Item::MISC)
	else return;
}

void InvenUI::ListingItem()
{
	if (inven_armors.size() > 0 || inven_weapons.size() > 0)
	{
		if (selectedTitleNum == InvenUI::ALL)
		{
			for (int i = 0; i < inven_armors.size(); i++)
			{
				if (inven_armors[i]->GetEquip() == true)
				{
					for (int j = 0; j < equiped_icon_armor.size(); j++)
					{
						/// <summary>
						/// 수정해야함
						/// </summary>
						if (equiped_icon_armor[j]->GetActive() == false)
						{
							equiped_icon_armor[j]->SetActive(true);
							equiped_icon_armor[j]->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)i) };
							break;
						}
					}
				}
					
				Font::Get()->RenderText(inven_armors[i]->GetStatus().name,              { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().value),  { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}

			for (int i = 0; i < inven_weapons.size(); i++)
			{
				Font::Get()->RenderText(inven_weapons[i]->GetStatus().name,              { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size())) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().value),  { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size())) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size())) });
			}

			for (int i = 0; i < inven_arrows.size(); i++)
			{
				Font::Get()->RenderText(inven_arrows[i]->GetStatus().name,              { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
				Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().value),  { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
				Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
			}

			for (int i = 0; i < inven_potions.size(); i++)
			{
				Font::Get()->RenderText(inven_potions[i]->GetStatus().name,              { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
				Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().value),  { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
				Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
			}

			for (int i = 0; i < inven_misces.size(); i++)
			{
				Font::Get()->RenderText(inven_misces[i]->GetStatus().name,              { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().value),  { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())) });
			}
		}

		if (selectedTitleNum == InvenUI::ARMOR)
		{
			for (int i = 0; i < inven_armors.size(); i++)
			{
				Font::Get()->RenderText(inven_armors[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}

		if (selectedTitleNum == InvenUI::ARMOR_IRON)
		{
			int tmp = 0;
			for (Armor* armor : inven_armors)
			{
				if (armor->GetArmorClass() == Armor::IRON)
				{
					Font::Get()->RenderText(armor->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::ARMOR_DRAGONBONE)
		{
			int tmp = 0;
			for (Armor* armor : inven_armors)
			{
				if (armor->GetArmorClass() == Armor::DRAGONBONE)
				{
					Font::Get()->RenderText(armor->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::WEAPON)
		{
			for (int i = 0; i < inven_weapons.size(); i++)
			{
				Font::Get()->RenderText(inven_weapons[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}

		if (selectedTitleNum == InvenUI::WEAPON_IRON)
		{
			int tmp = 0;
			for (Weapon* weapon : inven_weapons)
			{
				if (weapon->GetWeaponClass() == Weapon::IRON)
				{
					Font::Get()->RenderText(weapon->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::WEAPON_EBONY)
		{
			int tmp = 0;
			for (Weapon* weapon : inven_weapons)
			{
				if (weapon->GetWeaponClass() == Weapon::EBONY)
				{
					Font::Get()->RenderText(weapon->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::ARROW)
		{
			for (int i = 0; i < inven_arrows.size(); i++)
			{
				Font::Get()->RenderText(inven_arrows[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}

		if (selectedTitleNum == InvenUI::POTION)
		{
			for (int i = 0; i < inven_potions.size(); i++)
			{
				Font::Get()->RenderText(inven_potions[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}

		if (selectedTitleNum == InvenUI::MISC)
		{
			for (int i = 0; i < inven_misces.size(); i++)
			{
				Font::Get()->RenderText(inven_misces[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}
	}
}

void InvenUI::ListingDetailed(string inname)
{
	if (itemstatus->GetItem(inname).type == Item::ARMOR)
	{
		FOR(inven_armors.size())
		{
			if (inven_armors[i]->GetStatus().name == inname)
			{
				Font::Get()->SetStyle("Futura_big");
				Font::Get()->RenderText(inven_armors[i]->GetStatus().name, { item_detail_frame->Pos().x - inname.size() * 15 ,item_detail_frame->Pos().y + 40 });				
				Font::Get()->RenderText(to_string(inven_armors[i]->GetDef()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });				
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30});
				Font::Get()->SetStyle("Futura");
			}
		}
	}
		
	//if (itemstatus->GetItem(inname).type == Item::WEAPON)
	//	
	//if (itemstatus->GetItem(inname).type == Item::ARROW)
	//	
	//if (itemstatus->GetItem(inname).type == Item::POTION)
	//	
	//if (itemstatus->GetItem(inname).type == Item::MISC)
		
}