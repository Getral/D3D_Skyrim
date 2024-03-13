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
		CLOTHING,
		EXPENDABLE,
		MISC
	};
public:
	InvenUI();
	~InvenUI();

	void Update();
	void Render();
	void GUIRender();

	void SelectedBarPosing();
	void RenderTitle();
	void AddItem(string inname);

	
	void ListingItem();
	
private:
	Quad* frame;
	Quad* framebar;
	Quad* framebar2;
	Quad* framebar3;

	Quad* item_detail_frame;

	Quad* selectedBar;

	Quad* title_all;
	Quad* title_weapon;
	Quad* title_armor;
	Quad* title_clothing;
	Quad* title_expendable;
	Quad* title_misc;
	
	int selectedTitleNum = 0;

	vector<class Armor*> inven_armors;
	vector<class Weapon*> inven_weapons;
	vector<class Arrow*> inven_arrows;
	vector<class Potion*> inven_potions;

	
	class ItemStatus* itemstatus;
};

