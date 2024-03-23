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
	title_all->Pos() = { 70, 610 };
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
	selected_bar->Pos() = { CENTER_X - 495,CENTER_Y + 250 };
	selected_bar->GetMaterial()->SetShader(L"UI/EditAlpha2.hlsl");

	selectedItem_bar = new Quad(L"Textures/UI/selectedItem_bar.png");
	selectedItem_bar->Pos() = { CENTER_X - 250,WIN_HEIGHT - 105 };
	selectedItem_bar->Scale() *= 0.725f;

	FOR(5)
	{
		equiped_icon_armor.push_back(new Quad(L"Textures/UI/Equiped_Icon.png"));
		equiped_icon_armor.back()->Scale() *= 0.9f;
		equiped_icon_armor.back()->SetActive(false);
	}

	equiped_icon_weapon = new Quad(L"Textures/UI/Equiped_Icon.png");
	equiped_icon_weapon->Scale() *= 0.9f;
	equiped_icon_weapon->SetActive(false);

	equiped_icon_arrow = new Quad(L"Textures/UI/Equiped_Icon.png");
	equiped_icon_arrow->Scale() *= 0.9f;
	equiped_icon_arrow->SetActive(false);



	itemstatus = new ItemStatus();

	item_detail_frame = new Quad(L"Textures/UI/Item_detail_frame.png");
	item_detail_frame->GetMaterial()->SetShader(L"UI/EditAlpha.hlsl");
	item_detail_frame->Pos() = { CENTER_X + 300 ,CENTER_Y - 200 };

	FOR(4)
	{
		player_armors.push_back(itemstatus->GetArmor("dragoncuirass"));
	}

	player_shield = new Armor(*itemstatus->GetArmor("dragonshield"));
	player_weapon = new Weapon(*itemstatus->GetWeapon("ebonydagger"));
	player_arrow = new Arrow(*itemstatus->GetArrow("ironarrow"));
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
	selectedItem_bar->UpdateWorld();

	if (selectedItemNum < 0)
		selectedItem_bar->SetActive(false);
	else
		selectedItem_bar->SetActive(true);

	for (Quad* icon : equiped_icon_armor)
		icon->UpdateWorld();
	equiped_icon_weapon->UpdateWorld();
	equiped_icon_arrow->UpdateWorld();

	item_detail_frame->UpdateWorld();
	detailedframebar->UpdateWorld();

	if (KEY_DOWN(VK_RIGHT))
		isSelectingItem = true;
	if (KEY_DOWN(VK_LEFT))
	{
		selectedItemNum = 0;
		isSelectingItem = false;
	}

	SelectedItemPosing();

	SelectedTitlePosing();

	if (isSelectingItem && KEY_DOWN(VK_RETURN))
		UseSelectedItem(player);

	if (KEY_DOWN('1'))
	{
		AddItem("ironcuirass");
		AddItem("irongauntlet");
		AddItem("dragonhelmet");
		AddItem("ironboots");
		AddItem("dragonshield");
	}
	if (KEY_DOWN('2'))
	{
		AddItem("ironhelmet");
		AddItem("ironshield");
		AddItem("dragoncuirass");
		AddItem("dragongauntlet");
		AddItem("dragonboots");
	}
	if (KEY_DOWN('3'))
		AddItem("irondagger");
	if (KEY_DOWN('4'))
		AddItem("ebonydagger");
	if (KEY_DOWN('5'))
		AddItem("ironarrow");
	if (KEY_DOWN('6'))
		AddItem("ebonyarrow");
	if (KEY_DOWN('7'))
		AddItem("hp_potion");
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
	if (isSelectingItem)
		selectedItem_bar->Render();

	for (Quad* icon : equiped_icon_armor)
		icon->Render();
	equiped_icon_weapon->Render();
	equiped_icon_arrow->Render();

	RenderTitle();

	ListingItem();

	if (selectedItemNum >= 0 && isSelectingItem)
		ListingDetailed();
}

void InvenUI::GUIRender()
{
	ImGui::Text("player helmet");
	ImGui::Text(player_armors[0]->GetStatus().name.c_str());
	ImGui::Text("player cuirass");
	ImGui::Text(player_armors[1]->GetStatus().name.c_str());
	ImGui::Text("player gauntlet");
	ImGui::Text(player_armors[2]->GetStatus().name.c_str());
	ImGui::Text("player boots");
	ImGui::Text(player_armors[3]->GetStatus().name.c_str());
	ImGui::Text("player shield");
	ImGui::Text(player_shield->GetStatus().name.c_str());
	ImGui::Text("player weapon");
	ImGui::Text(player_weapon->GetStatus().name.c_str());
	ImGui::Text("player arrow");
	ImGui::Text(player_arrow->GetStatus().name.c_str());

	if (inven_arrows.size() > 1)
	{
		ImGui::Text("arrow_equip render %d", inven_arrows[0]->GetEquip());
		ImGui::Text("arrow_icon render %d", equiped_icon_arrow->ActiveSelf());	
	}
	
	

	equiped_icon_arrow->GUIRender();
}

// 아이템 타입 선택
void InvenUI::SelectedTitlePosing()
{
	if (selectedTitleNum < InvenUI::ALL)
		selectedTitleNum = InvenUI::ALL;
	if (selectedTitleNum > InvenUI::MISC)
		selectedTitleNum = InvenUI::MISC;

	if (isSelectingItem == false)
	{
		if (KEY_DOWN(VK_DOWN))
			selectedTitleNum++;
		if (KEY_DOWN(VK_UP))
			selectedTitleNum--;
	}


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
// 아이템 선택
void InvenUI::SelectedItemPosing()
{
	if (selectedItemNum <= 0)
		selectedItemNum = 0;

	if (selectedItemNum >= title_inven_size - 1)
		selectedItemNum = title_inven_size - 1;

	if (isSelectingItem == true)
	{
		if (KEY_DOWN(VK_DOWN))
			selectedItemNum++;
		if (KEY_DOWN(VK_UP))
			selectedItemNum--;
	}

	int temp = 0;
	switch (selectedTitleNum)
	{
	case InvenUI::ALL:
		title_inven_size = inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size() + inven_misces.size();
		break;
	case InvenUI::ARMOR:
		title_inven_size = inven_armors.size();
		break;
	case InvenUI::ARMOR_IRON:
		FOR(inven_armors.size())
		{
			if (inven_armors[i]->GetArmorClass() == Armor::IRON)
				temp++;
		}
		title_inven_size = temp;
		break;
	case InvenUI::ARMOR_DRAGONBONE:
		FOR(inven_armors.size())
		{
			if (inven_armors[i]->GetArmorClass() == Armor::DRAGONBONE)
				temp++;
		}
		title_inven_size = temp;
		break;
	case InvenUI::WEAPON:
		title_inven_size = inven_weapons.size();
		break;
	case InvenUI::WEAPON_IRON:
		FOR(inven_weapons.size())
		{
			if (inven_weapons[i]->GetWeaponClass() == Weapon::IRON)
				temp++;
		}
		title_inven_size = temp;
		break;
	case InvenUI::WEAPON_EBONY:
		FOR(inven_weapons.size())
		{
			if (inven_weapons[i]->GetWeaponClass() == Weapon::EBONY)
				temp++;
		}
		title_inven_size = temp;
		break;
	case InvenUI::ARROW:
		title_inven_size = inven_arrows.size();
		break;
	case InvenUI::POTION:
		title_inven_size = inven_potions.size();
		break;
	case InvenUI::MISC:
		title_inven_size = inven_misces.size();
		break;
	default:
		break;
	}
	selectedItem_bar->Pos().y = WIN_HEIGHT - 105 - (20 * selectedItemNum);
}
// 아이템 선택후 사용
void InvenUI::UseSelectedItem(Player* player)
{
	switch (selectedTitleNum)
	{
	case InvenUI::ALL:
		if (selectedItemNum < inven_armors.size())
			UseItem(player, inven_armors[selectedItemNum]->GetStatus().name);

		if (selectedItemNum >= inven_armors.size() && selectedItemNum < inven_armors.size() + inven_weapons.size())
			UseItem(player, inven_weapons[selectedItemNum - inven_armors.size()]->GetStatus().name);

		if (selectedItemNum >= inven_armors.size() + inven_weapons.size() && selectedItemNum < inven_armors.size() + inven_weapons.size() + inven_arrows.size())
			UseItem(player, inven_arrows[selectedItemNum - (inven_armors.size() + inven_weapons.size())]->GetStatus().name);

		if (selectedItemNum >= inven_armors.size() + inven_weapons.size() + inven_arrows.size() && selectedItemNum < inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())
			UseItem(player, inven_potions[selectedItemNum - (inven_armors.size() + inven_weapons.size() + inven_arrows.size())]->GetStatus().name);
		break;
	case InvenUI::ARMOR:
		UseItem(player, inven_armors[selectedItemNum]->GetStatus().name);
		break;
	case InvenUI::ARMOR_IRON:
		UseItem(player, "ironhelmet");
		break;
	case InvenUI::ARMOR_DRAGONBONE:
		UseItem(player, "dragonhelmet");
		break;
	case InvenUI::WEAPON:
		UseItem(player, inven_weapons[selectedItemNum]->GetStatus().name);
		break;
	case InvenUI::WEAPON_IRON:
		FOR(inven_weapons.size())
		{
			if (inven_weapons[i]->GetWeaponClass() == Weapon::IRON)
			{
				temp_weapons.push_back(inven_weapons[i]);
			}
		}
		UseItem(player, temp_weapons[selectedItemNum]->GetStatus().name);
		temp_weapons.clear();
		break;
	case InvenUI::WEAPON_EBONY:
		FOR(inven_weapons.size())
		{
			if (inven_weapons[i]->GetWeaponClass() == Weapon::EBONY)
			{
				temp_weapons.push_back(inven_weapons[i]);
			}
		}
		UseItem(player, temp_weapons[selectedItemNum]->GetStatus().name);
		temp_weapons.clear();
		break;
	case InvenUI::ARROW:
		UseItem(player, inven_arrows[selectedItemNum]->GetStatus().name);
		break;
	case InvenUI::POTION:
		UseItem(player, inven_potions[selectedItemNum]->GetStatus().name);
		break;
	default:
		break;
	}

}
// 아이템 타입 글씨 렌더
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
	Font::Get()->RenderText("TYPE", { 400, CENTER_Y + 290 });
	Font::Get()->RenderText("WGT", { 515, CENTER_Y + 290 });
	Font::Get()->RenderText("VAL", { 550, CENTER_Y + 290 });
	if (selectedTitleNum == ARROW || selectedTitleNum == POTION || selectedTitleNum == MISC)
		Font::Get()->RenderText("COUNT", { 350, CENTER_Y + 290 });

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
// 방어구 벡터 재배열
bool armorComparator(Armor* armor1, Armor* armor2) {
	if (armor1->GetArmorClass() != armor2->GetArmorClass()) {
		return armor1->GetArmorClass() < armor2->GetArmorClass();
	}

	return armor1->GetArmorType() <= armor2->GetArmorType();
}
// 아이템 추가
void InvenUI::AddItem(string inname)
{
	if (itemstatus->GetItem(inname).type == Item::ARMOR)
	{
		FOR(inven_armors.size())
		{
			if (inven_armors[i]->GetStatus().name == inname)
				return;
		}
		inven_armors.push_back(itemstatus->GetArmor(inname));
		sort(inven_armors.begin(), inven_armors.end(), armorComparator);
	}

	else if (itemstatus->GetItem(inname).type == Item::WEAPON)
	{
		FOR(inven_weapons.size())
		{
			if (inven_weapons[i]->GetStatus().name == inname)
				return;
		}
		inven_weapons.push_back(itemstatus->GetWeapon(inname));
	}

	else if (itemstatus->GetItem(inname).type == Item::ARROW)
	{
		FOR(inven_arrows.size())
		{
			if (inven_arrows[i]->GetStatus().name == inname)
			{
				inven_arrows[i]->GetCount()++;
				return;
			}
		}
		inven_arrows.push_back(itemstatus->GetArrow(inname));
	}

	else if (itemstatus->GetItem(inname).type == Item::POTION)
	{
		FOR(inven_potions.size())
		{
			if (inven_potions[i]->GetStatus().name == inname)
			{
				inven_potions[i]->GetCount()++;
				return;
			}
		}
		inven_potions.push_back(itemstatus->GetPotion(inname));
	}

	else if (itemstatus->GetItem(inname).type == Item::MISC)
	{
		FOR(inven_misces.size())
		{
			if (inven_misces[i]->GetStatus().name == inname)
			{
				inven_misces[i]->GetCount()++;
				return;
			}
		}
		inven_misces.push_back(itemstatus->GetMisc(inname));
	}

	else
		return;
}
// 아이템 사용(장비(갑옷,무기)->착용 / 화살->착용 or 같은이름시 소모 / 포션->소모)
void InvenUI::UseItem(Player* player, string inname)
{
	if (itemstatus->GetItem(inname).type == Item::ARMOR)
	{
		FOR(inven_armors.size())
		{
			if (inven_armors[i]->GetStatus().name == inname)
			{
				if (inven_armors[i]->GetArmorType() == Armor::shield)
				{
					player_shield->ChangeEquipState();
					inven_armors[i]->ChangeEquipState();

					player->GetStatus().atk -= player_shield->GetDef();
					player->GetStatus().atk += inven_armors[i]->GetDef();

					player_shield = inven_armors[i];
					return;
				}

				else
				{
					for (int j = 0; j < inven_armors.size(); j++)
					{
						if (inven_armors[i]->GetArmorClass() == inven_armors[j]->GetArmorClass())
						{
							if (inven_armors[j]->GetArmorType() == Armor::helmet)
								temp_armors.push_back(inven_armors[j]);
							else if (inven_armors[j]->GetArmorType() == Armor::cuirass)
								temp_armors.push_back(inven_armors[j]);
							else if (inven_armors[j]->GetArmorType() == Armor::gauntlet)
								temp_armors.push_back(inven_armors[j]);
							else if (inven_armors[j]->GetArmorType() == Armor::boots)
								temp_armors.push_back(inven_armors[j]);
						}
					}
				}

				if (temp_armors.size() == 4)
				{

					for (int i = 0; i < temp_armors.size(); i++)
					{
						temp_armors[i]->ChangeEquipState();
						player_armors[i]->ChangeEquipState();

						player->GetStatus().def -= player_armors[i]->GetDef();
						player->GetStatus().def += temp_armors[i]->GetDef();

						if (temp_armors[i]->GetArmorType() == Armor::helmet)
							player_armors[0] = temp_armors[i];
						if (temp_armors[i]->GetArmorType() == Armor::cuirass)
							player_armors[1] = temp_armors[i];
						if (temp_armors[i]->GetArmorType() == Armor::gauntlet)
							player_armors[2] = temp_armors[i];
						if (temp_armors[i]->GetArmorType() == Armor::boots)
							player_armors[3] = temp_armors[i];
					}
				}

				temp_armors.clear();
				/*
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
				*/
			}
		}
	}

	else if (itemstatus->GetItem(inname).type == Item::WEAPON)
	{
		FOR(inven_weapons.size())
		{
			if (inven_weapons[i]->GetStatus().name == inname)
			{
				player_weapon->ChangeEquipState();
				inven_weapons[i]->ChangeEquipState();

				player->GetStatus().atk -= player_weapon->GetAtk();
				player->GetStatus().atk += inven_weapons[i]->GetAtk();

				player_weapon = inven_weapons[i];
				break;
			}
		}
	}

	else if (itemstatus->GetItem(inname).type == Item::ARROW)
	{
		if (player_arrow->GetStatus().name != itemstatus->GetArrow(inname)->GetStatus().name)
		{
			FOR(inven_arrows.size())
			{
				if (inven_arrows[i]->GetStatus().name == inname)
				{
					player_arrow->ChangeEquipState();
					inven_arrows[i]->ChangeEquipState();

					player->GetStatus().atk -= player_arrow->GetAtk();
					player->GetStatus().atk += inven_arrows[i]->GetAtk();

					player_arrow = inven_arrows[i];
					break;
				}
			}	
		}

		else
		{
			player_arrow->GetCount()--;
			FOR(inven_arrows.size())
			{
				if (inven_arrows[i]->GetStatus().name == player_arrow->GetStatus().name)
					inven_arrows[i]->GetCount() = player_arrow->GetCount();

				if (inven_arrows[i]->GetCount() < 1)
					inven_arrows.erase(inven_arrows.begin() + i);

				if (inven_arrows.size() == 0)
					equiped_icon_arrow->SetActive(false);
			}
			
		}
	}

	else if (itemstatus->GetItem(inname).type == Item::POTION)
	{
		FOR(inven_potions.size())
		{
			if (inven_potions[i]->GetStatus().name == inname)
			{
				if (inven_potions[i]->GetPotionType() == Potion::POTION_HP)
				{
					player->GetStatus().curHp += (float)inven_potions[i]->GetAmount();
					inven_potions[i]->GetCount() -= 1;
				}
				else if (inven_potions[i]->GetPotionType() == Potion::POTION_SP)
				{
					player->GetStatus().curstamina += (float)inven_potions[i]->GetAmount();
					inven_potions[i]->GetCount() -= 1;
				}

				if (inven_potions[i]->GetCount() < 1)
					inven_potions.erase(inven_potions.begin() + i);
			}
		}
	}

	else return;
}
// 벡터로된 인벤에서 아이템 타입에 맞쳐서 아이템 나열
void InvenUI::ListingItem()
{
	if (inven_armors.size() > 0 || inven_weapons.size() > 0 || inven_arrows.size() > 0 || inven_potions.size() > 0 || inven_misces.size() > 0)
	{
		if (selectedTitleNum == InvenUI::ALL)
		{
			for (int i = 0; i < inven_armors.size(); i++)
			{
				if (inven_armors[i]->GetEquip() == true)
				{
					if (inven_armors[i]->GetArmorType() == Armor::shield)
					{
						equiped_icon_armor.back()->SetActive(true);
						equiped_icon_armor.back()->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)(i)) };
					}

					else
					{
						for (int j = 0; j < equiped_icon_armor.size() - 1; j++)
						{
							equiped_icon_armor[j]->SetActive(true);
							equiped_icon_armor[j]->Pos() = { 260 , WIN_HEIGHT - 45 - (20 * (float)(i + j)) };
						}
					}
					
				}

				Font::Get()->RenderText(inven_armors[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::helmet)
					Font::Get()->RenderText("helmet", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::cuirass)
					Font::Get()->RenderText("cuirass", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::gauntlet)
					Font::Get()->RenderText("gauntlet", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::boots)
					Font::Get()->RenderText("boots", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::shield)
					Font::Get()->RenderText("shield", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}

			for (int i = 0; i < inven_weapons.size(); i++)
			{
				if (inven_weapons[i]->GetEquip() == true)
				{
					equiped_icon_weapon->SetActive(true);
					equiped_icon_weapon->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)(i + inven_armors.size())) };
				}


				Font::Get()->RenderText(inven_weapons[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size())) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size())) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size())) });
			}

			for (int i = 0; i < inven_arrows.size(); i++)
			{
				if (inven_arrows[i]->GetCount() > 0)
				{
					if (inven_arrows[i]->GetEquip() == true)
					{
						equiped_icon_arrow->SetActive(true);
						equiped_icon_arrow->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) };
					}
					

					Font::Get()->RenderText(inven_arrows[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
					if (inven_arrows[i]->GetType() == Arrow::IRON)
						Font::Get()->RenderText("iron", { 400,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
					if (inven_arrows[i]->GetType() == Arrow::EBONY)
						Font::Get()->RenderText("ebony", { 400,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
					Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
					Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size())) });
				}
				else
					equiped_icon_arrow->SetActive(false);
			}

			for (int i = 0; i < inven_potions.size(); i++)
			{
				if (inven_potions[i]->GetCount() > 0)
				{
					Font::Get()->RenderText(inven_potions[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
					if (inven_potions[i]->GetPotionType() == Potion::POTION_HP)
						Font::Get()->RenderText("hp", { 400,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
					if (inven_potions[i]->GetPotionType() == Potion::POTION_SP)
						Font::Get()->RenderText("sp", { 400,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
					Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
					Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size())) });
				}
			}

			for (int i = 0; i < inven_misces.size(); i++)
			{
				Font::Get()->RenderText(inven_misces[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)(i + inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())) });
			}
		}

		if (selectedTitleNum == InvenUI::ARMOR)
		{
			equiped_icon_weapon->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			for (int i = 0; i < inven_armors.size(); i++)
			{
				if (inven_armors[i]->GetEquip() == true)
				{

					if (inven_armors[i]->GetArmorType() == Armor::shield)
					{
						equiped_icon_armor.back()->SetActive(true);
						equiped_icon_armor.back()->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)(i)) };
					}

					else
					{
						for (int j = 0; j < equiped_icon_armor.size() - 1; j++)
						{
							equiped_icon_armor[j]->SetActive(true);
							equiped_icon_armor[j]->Pos() = { 260 , WIN_HEIGHT - 45 - (20 * (float)(i + j)) };
						}
					}
					
				}

				Font::Get()->RenderText(inven_armors[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::helmet)
					Font::Get()->RenderText("helmet", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::cuirass)
					Font::Get()->RenderText("cuirass", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::gauntlet)
					Font::Get()->RenderText("gauntlet", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::boots)
					Font::Get()->RenderText("boots", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_armors[i]->GetArmorType() == Armor::shield)
					Font::Get()->RenderText("shield", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_armors[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}

		if (selectedTitleNum == InvenUI::ARMOR_IRON)
		{
			for (int i = 0; i < inven_armors.size(); i++)
			{
				if (inven_armors[i]->GetArmorClass() == Armor::DRAGONBONE && inven_armors[i]->GetEquip() == true)
				{
					if (inven_armors[i]->GetArmorType() == Armor::helmet)
					{
						for (int j = 0; j < equiped_icon_armor.size() - 1; j++)
							equiped_icon_armor[j]->SetActive(false);
					}
					else if (inven_armors[i]->GetArmorType() == Armor::shield)
						equiped_icon_armor.back()->SetActive(false);

					else
						continue;
				}
			}
			equiped_icon_weapon->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			int tmp = 0;
			for (Armor* armor : inven_armors)
			{
				if (armor->GetArmorClass() == Armor::IRON)
				{
					if (armor->GetEquip() == true)
					{
						if (armor->GetArmorType() == Armor::shield)
						{
							equiped_icon_armor.back()->SetActive(true);
							equiped_icon_armor.back()->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)(tmp)) };
						}
						else
						{
							for (int j = 0; j < equiped_icon_armor.size() - 1; j++)
							{
								equiped_icon_armor[j]->SetActive(true);
								equiped_icon_armor[j]->Pos() = { 260 , WIN_HEIGHT - 45 - (20 * (float)(tmp + j)) };
							}
						}
					}

					Font::Get()->RenderText(armor->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::helmet)
						Font::Get()->RenderText("helmet", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::cuirass)
						Font::Get()->RenderText("cuirass", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::gauntlet)
						Font::Get()->RenderText("gauntlet", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::boots)
						Font::Get()->RenderText("boots", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::shield)
						Font::Get()->RenderText("shield", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::ARMOR_DRAGONBONE)
		{
			for (int i = 0; i < inven_armors.size(); i++)
			{
				if (inven_armors[i]->GetArmorClass() == Armor::IRON && inven_armors[i]->GetEquip() == true)
				{
					if (inven_armors[i]->GetArmorType() == Armor::helmet)
					{
						for (int j = 0; j < equiped_icon_armor.size() - 1; j++)
							equiped_icon_armor[j]->SetActive(false);
					}
					else if (inven_armors[i]->GetArmorType() == Armor::shield)
						equiped_icon_armor.back()->SetActive(false);

					else
						continue;
				}
			}
				
			equiped_icon_weapon->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			int tmp = 0;
			for (Armor* armor : inven_armors)
			{
				if (armor->GetArmorClass() == Armor::DRAGONBONE)
				{
					if (armor->GetEquip() == true)
					{
						if (armor->GetArmorType() == Armor::shield)
						{
							equiped_icon_armor.back()->SetActive(true);
							equiped_icon_armor.back()->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)(tmp)) };
						}

						else
						{
							for (int j = 0; j < equiped_icon_armor.size() - 1; j++)
							{
								equiped_icon_armor[j]->SetActive(true);
								equiped_icon_armor[j]->Pos() = { 260 , WIN_HEIGHT - 45 - (20 * (float)(tmp + j)) };
							}
						}
						
					}
					Font::Get()->RenderText(armor->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::helmet)
						Font::Get()->RenderText("helmet", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::cuirass)
						Font::Get()->RenderText("cuirass", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::gauntlet)
						Font::Get()->RenderText("gauntlet", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::boots)
						Font::Get()->RenderText("boots", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					if (armor->GetArmorType() == Armor::shield)
						Font::Get()->RenderText("shield", { 400,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(armor->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::WEAPON)
		{
			FOR(equiped_icon_armor.size())
				equiped_icon_armor[i]->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			for (int i = 0; i < inven_weapons.size(); i++)
			{
				if (inven_weapons[i]->GetEquip() == true)
				{
					equiped_icon_weapon->SetActive(true);
					equiped_icon_weapon->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)(i)) };
				}
				Font::Get()->RenderText(inven_weapons[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_weapons[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}

		if (selectedTitleNum == InvenUI::WEAPON_IRON)
		{
			FOR(equiped_icon_armor.size())
				equiped_icon_armor[i]->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			int tmp = 0;
			for (Weapon* weapon : inven_weapons)
			{
				if (weapon->GetWeaponClass() == Weapon::IRON)
				{
					if (weapon->GetEquip() == true)
					{
						equiped_icon_weapon->SetActive(true);
						equiped_icon_weapon->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)tmp) };
					}

					Font::Get()->RenderText(weapon->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::WEAPON_EBONY)
		{
			FOR(equiped_icon_armor.size())
				equiped_icon_armor[i]->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			int tmp = 0;
			for (Weapon* weapon : inven_weapons)
			{
				if (weapon->GetWeaponClass() == Weapon::EBONY)
				{
					if (weapon->GetEquip() == true)
					{
						equiped_icon_weapon->SetActive(true);
						equiped_icon_weapon->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)tmp) };
					}
					Font::Get()->RenderText(weapon->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					Font::Get()->RenderText(to_string(weapon->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)tmp) });
					tmp++;
				}
			}
		}

		if (selectedTitleNum == InvenUI::ARROW)
		{
			FOR(equiped_icon_armor.size())
				equiped_icon_armor[i]->SetActive(false);
			equiped_icon_weapon->SetActive(false);
			for (int i = 0; i < inven_arrows.size(); i++)
			{
				if (inven_arrows[i]->GetCount() > 0)
				{
					if (inven_arrows[i]->GetEquip() == true)
					{
						equiped_icon_arrow->SetActive(true);
						equiped_icon_arrow->Pos() = { 260 , WIN_HEIGHT - 105 - (20 * (float)i) };
					}
					
					Font::Get()->RenderText(inven_arrows[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
					Font::Get()->RenderText(to_string(inven_arrows[i]->GetCount()), { 350,WIN_HEIGHT - 100 - (20 * (float)i) });
					if (inven_arrows[i]->GetType() == Arrow::IRON)
						Font::Get()->RenderText("iron", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
					if (inven_arrows[i]->GetType() == Arrow::EBONY)
						Font::Get()->RenderText("evony", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
					Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
					Font::Get()->RenderText(to_string(inven_arrows[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
				}
				else
					equiped_icon_arrow->SetActive(false);
			}
		}

		if (selectedTitleNum == InvenUI::POTION)
		{
			FOR(equiped_icon_armor.size())
				equiped_icon_armor[i]->SetActive(false);
			equiped_icon_weapon->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			for (int i = 0; i < inven_potions.size(); i++)
			{
				Font::Get()->RenderText(inven_potions[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_potions[i]->GetCount()), { 350,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_potions[i]->GetPotionType() == Potion::POTION_HP)
					Font::Get()->RenderText("hp", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				if (inven_potions[i]->GetPotionType() == Potion::POTION_SP)
					Font::Get()->RenderText("sp", { 400,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_potions[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}

		if (selectedTitleNum == InvenUI::MISC)
		{
			FOR(equiped_icon_armor.size())
				equiped_icon_armor[i]->SetActive(false);
			equiped_icon_weapon->SetActive(false);
			equiped_icon_arrow->SetActive(false);
			for (int i = 0; i < inven_misces.size(); i++)
			{
				Font::Get()->RenderText(inven_misces[i]->GetStatus().name, { 275,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetCount()), { 350,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().value), { 515,WIN_HEIGHT - 100 - (20 * (float)i) });
				Font::Get()->RenderText(to_string(inven_misces[i]->GetStatus().weight), { 555,WIN_HEIGHT - 100 - (20 * (float)i) });
			}
		}
	}
}
// 선택된 아이템 상세정보
void InvenUI::ListingDetailed()
{
	item_detail_frame->Render();
	
	Font::Get()->RenderText("Weight", { item_detail_frame->Pos().x - 40, item_detail_frame->Pos().y - 30 });
	Font::Get()->RenderText("Value", { item_detail_frame->Pos().x + 60, item_detail_frame->Pos().y - 30 });

	if (selectedTitleNum == InvenUI::ALL)
	{
		if (selectedItemNum < inven_armors.size())
		{
			Font::Get()->RenderText("Deffense", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->RenderText(inven_armors[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
			Font::Get()->RenderText(to_string(inven_armors[selectedItemNum]->GetDef()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_armors[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_armors[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura");
		}

		if (selectedItemNum >= inven_armors.size() && selectedItemNum < inven_armors.size() + inven_weapons.size())
		{
			Font::Get()->RenderText("Attack", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->RenderText(inven_weapons[selectedItemNum - inven_armors.size()]->GetStatus().name, { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y + 40 });
			Font::Get()->RenderText(to_string(inven_weapons[selectedItemNum - inven_armors.size()]->GetAtk()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_weapons[selectedItemNum - inven_armors.size()]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_weapons[selectedItemNum - inven_armors.size()]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura");
		}


		if (selectedItemNum >= inven_armors.size() + inven_weapons.size() && selectedItemNum < inven_armors.size() + inven_weapons.size() + inven_arrows.size())
		{
			Font::Get()->RenderText("Attack", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->RenderText(inven_arrows[selectedItemNum - inven_armors.size() - inven_weapons.size()]->GetStatus().name, { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y + 40 });
			Font::Get()->RenderText(to_string(inven_arrows[selectedItemNum - inven_armors.size() - inven_weapons.size()]->GetAtk()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_arrows[selectedItemNum - inven_armors.size() - inven_weapons.size()]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_arrows[selectedItemNum - inven_armors.size() - inven_weapons.size()]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura");
		}
			

		if (selectedItemNum >= inven_armors.size() + inven_weapons.size() + inven_arrows.size() && selectedItemNum < inven_armors.size() + inven_weapons.size() + inven_arrows.size() + inven_potions.size())
		{
			Font::Get()->RenderText("Amount", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->RenderText(inven_potions[selectedItemNum - inven_armors.size() - inven_weapons.size() - inven_arrows.size()]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
			Font::Get()->RenderText(to_string(inven_potions[selectedItemNum - inven_armors.size() - inven_weapons.size() - inven_arrows.size()]->GetAmount()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_potions[selectedItemNum - inven_armors.size() - inven_weapons.size() - inven_arrows.size()]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
			Font::Get()->RenderText(to_string(inven_potions[selectedItemNum - inven_armors.size() - inven_weapons.size() - inven_arrows.size()]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
			Font::Get()->SetStyle("Futura");
		}																	
	}

	if (selectedTitleNum == InvenUI::ARMOR)
	{
		if (selectedItemNum >= inven_armors.size())
			return;
		Font::Get()->RenderText("Deffense", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(inven_armors[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(inven_armors[selectedItemNum]->GetDef()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_armors[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_armors[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");
	}

	if (selectedTitleNum == InvenUI::ARMOR_IRON)
	{
		for (Armor* armor : inven_armors)
		{
			if (armor->GetArmorClass() == Armor::IRON)
			{
				temp_armors.push_back(armor);
			}
		}

		if (selectedItemNum >= temp_armors.size())
			return;
		Font::Get()->RenderText("Deffense", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(temp_armors[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(temp_armors[selectedItemNum]->GetDef()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_armors[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_armors[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");

		temp_armors.clear();
	}

	if (selectedTitleNum == InvenUI::ARMOR_DRAGONBONE)
	{
		for (Armor* armor : inven_armors)
		{
			if (armor->GetArmorClass() == Armor::DRAGONBONE)
			{
				temp_armors.push_back(armor);
			}
		}
		if (selectedItemNum >= temp_armors.size())
			return;
		Font::Get()->RenderText("Deffense", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(temp_armors[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(temp_armors[selectedItemNum]->GetDef()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_armors[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_armors[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");

		temp_armors.clear();
	}

	if (selectedTitleNum == InvenUI::WEAPON)
	{
		if (selectedItemNum >= inven_weapons.size())
			return;
		Font::Get()->RenderText("Attack", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(inven_weapons[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(inven_weapons[selectedItemNum]->GetAtk()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_weapons[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_weapons[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");
	}

	if (selectedTitleNum == InvenUI::WEAPON_IRON)
	{
		for (Weapon* weapon : inven_weapons)
		{
			if (weapon->GetWeaponClass() == Weapon::IRON)
			{
				temp_weapons.push_back(weapon);
			}
		}
		if (selectedItemNum >= temp_weapons.size())
			return;
		Font::Get()->RenderText("Deffense", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(temp_weapons[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(temp_weapons[selectedItemNum]->GetAtk()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_weapons[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_weapons[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");

		temp_weapons.clear();
	}

	if (selectedTitleNum == InvenUI::WEAPON_EBONY)
	{
		for (Weapon* weapon : inven_weapons)
		{
			if (weapon->GetWeaponClass() == Weapon::EBONY)
			{
				temp_weapons.push_back(weapon);
			}
		}
		if (selectedItemNum >= temp_weapons.size())
			return;
		Font::Get()->RenderText("Deffense", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(temp_weapons[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(temp_weapons[selectedItemNum]->GetAtk()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_weapons[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(temp_weapons[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");

		temp_weapons.clear();
	}

	if (selectedTitleNum == InvenUI::ARROW)
	{
		if (selectedItemNum >= inven_arrows.size())
			return;
		Font::Get()->RenderText("Attack", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(inven_arrows[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(inven_arrows[selectedItemNum]->GetAtk()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_arrows[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_arrows[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");
	}

	if (selectedTitleNum == InvenUI::POTION)
	{
		if (selectedItemNum >= inven_potions.size())
			return;
		Font::Get()->RenderText("Amount", { item_detail_frame->Pos().x - 160,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura_big");
		Font::Get()->RenderText(inven_potions[selectedItemNum]->GetStatus().name, { item_detail_frame->Pos().x - 100 ,item_detail_frame->Pos().y + 40 });
		Font::Get()->RenderText(to_string(inven_potions[selectedItemNum]->GetAmount()), { item_detail_frame->Pos().x - 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_potions[selectedItemNum]->GetStatus().weight), { item_detail_frame->Pos().x + 10,item_detail_frame->Pos().y - 30 });
		Font::Get()->RenderText(to_string(inven_potions[selectedItemNum]->GetStatus().value), { item_detail_frame->Pos().x + 100,item_detail_frame->Pos().y - 30 });
		Font::Get()->SetStyle("Futura");
	}
}