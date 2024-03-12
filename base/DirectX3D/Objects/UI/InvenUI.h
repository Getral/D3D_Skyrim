#pragma once
class InvenUI
{
private:
	enum Title
	{
		ALL,
		WEAPON,
		WEAPON_IRON,
		WEAPON_EBONY,
		ARMOR,
		ARMOR_IRON,
		ARMOR_DRAGONBONE,
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

	void listingItem(string inname);
	
private:
	Quad* frame;
	Quad* framebar;
	Quad* framebar2;
	Quad* framebar3;
	Quad* selectedBar;

	Quad* title_all;
	Quad* title_weapon;
	Quad* title_armor;
	Quad* title_clothing;
	Quad* title_expendable;
	Quad* title_misc;
	
	int selectedTitleNum = 0;

	vector<class Armor*> inven_armors;

	//vector<Item::Status*> inven_items;
	class ItemStatus* itemstatus;
};

