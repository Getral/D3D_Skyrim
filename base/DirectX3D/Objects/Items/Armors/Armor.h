#pragma once

class Armor : public Item
{
public:
	enum ArmorType
	{
		 helmet,
		 cuirass,
		 gauntlet,
		 boots,
		 shield,
	};

	enum ArmorClass
	{

		IRON,
		DRAGONBONE
	};

public:
	Armor(string name, int type, int weight,
		int value, int armor_type, int armor_class, int def);
	
	int GetArmorClass() { return armor_class; }
	int GetArmorType() { return armor_type; }
	int GetDef() { return def; }

	void ChangeEquipState() { isEquiped = !isEquiped; }
	int GetEquip() { return isEquiped; }

private:
	int armor_class;
	int armor_type;
	int def;

	bool isEquiped = false;
};
