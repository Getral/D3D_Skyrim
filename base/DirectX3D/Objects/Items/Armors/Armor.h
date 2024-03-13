#pragma once

class Armor : public Item
{
public:
	enum ArmorType
	{
		 helmat,
		 cuirass,
		 gauntlets,
		 boots,
		 shield,
	};

	enum ArmorClass
	{
		IRON,
		DRAGONBONE
	};
public:
	Armor(string name, int type, int weight, int value, int armor_class, int armor_type, int def);
	
	int GetArmorClass() { return armor_class; }
	int GetDef() { return def; }
	
private:
	int armor_class;
	int armor_type;
	int def;
};
