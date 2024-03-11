#pragma once

class ItemStatus
{
public:
	ItemStatus();
	~ItemStatus();

	Item::Status GetItem(string inname);

	class Armor* GetArmor(string inname);
	class Weapon* ReturnWeapon();
private:
	int CheckType(string inname);


private:
	class Armor* armor1;
	vector<Armor*> armors;
	vector<class Weapon*> weapons;

	int type;
};

