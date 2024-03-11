#pragma once

class Armor : public Item
{
public:
	struct ArmorAbility
	{
		float defense = 0;

		// 마법부여는 필요하면 추가
	};

	enum ArmorType
	{
		 helmat,
		 cuirass,
		 gauntlets,
		 boots,
		 shield,
	};

public:
	Armor(string name, int type, int weight, int value, int armortype, int def);

	
private:
	
	int armortype;
	int def;
};

