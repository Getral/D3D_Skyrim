#pragma once

class ItemStatus
{
public:
	ItemStatus();
	~ItemStatus();

	void Update();

	

	class Armor* ReturnArmor();
	class Weapon* ReturnWeapon();
private:
	void CheckType(string inname);


private:
	class Armor* armor1;
	vector<Armor*> armors;
	vector<class Weapon*> weapons;

	int type;
};

