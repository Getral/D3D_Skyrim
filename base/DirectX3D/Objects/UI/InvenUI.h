#pragma once
class InvenUI
{
private:
	enum Title
	{
		ALL,
		ARMOR,
		ARMOR_IRON,
		ARMOR_DRAGONBONE,
		WEAPON,
		WEAPON_IRON,
		WEAPON_EBONY,
		ARROW,
		POTION,
		MISC
	};
public:
	InvenUI();
	~InvenUI();

	void Update(class Player* player);
	void Render();
	void GUIRender();

	void SelectedTitlePosing();
	void SelectedItemPosing();
	
	
	void RenderTitle();
	void AddItem(string inname);

	void UseItem(class Player* player, string inname);
	
	void ListingItem();

	void ListingDetailed(string inname);

private:
	Quad* frame;
	Quad* framebar;
	Quad* framebar2;
	Quad* framebar3;
	Quad* detailedframebar;

	Quad* item_detail_frame;

	Quad* selected_bar;
	Quad* selectedItem_bar;
	int title_inven_size;
	vector<Quad*> equiped_icon_armor;

	Quad* equiped_icon_weapon;

	Quad* title_all;
	Quad* title_weapon;
	Quad* title_armor;
	Quad* title_arrow;
	Quad* title_potion;
	Quad* title_misc;
	
	int selectedTitleNum = 0;
	int selectedItemNum = 0;
	bool isSelectingItem = false;

	vector<class Armor*> inven_armors;
	vector<class Weapon*> inven_weapons;
	vector<class Arrow*> inven_arrows;
	vector<class Potion*> inven_potions;
	vector<class Misc*> inven_misces;

	vector<class Armor*> temp_armors;
	vector<Armor*> player_armors;
	Armor* player_shield;

	Weapon* player_weapon;
	Arrow* player_arrow;


	class ItemStatus* itemstatus;
};

