#pragma once

class ItemStatus
{
public:
	ItemStatus();
	~ItemStatus();

	Item::Status GetItem(string inname);

	class Armor* GetArmor(string inname);
	class Weapon* GetWeapon(string inname);
	class Arrow* GetArrow(string inname);
	class Potion* GetPotion(string inname);
	class Misc* GetMisc(string inname);
private:
	int CheckType(string inname);
private:
	vector<class Armor*> armors;
	vector<class Weapon*> weapons;
	vector<class Arrow*> arrows;
	vector<class Potion*> potions;
	vector<class Misc*> misces;

	int type;
};

