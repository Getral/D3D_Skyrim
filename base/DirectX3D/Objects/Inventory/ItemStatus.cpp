#include "Framework.h"

ItemStatus::ItemStatus()
{
	armors.push_back(new Armor("ironhelmet", Item::ARMOR, 10, 11, Armor::IRON ,Armor::helmat, 111));
	armors.push_back(new Armor("dragonhelmet", Item::ARMOR, 20, 22, Armor::DRAGONBONE ,Armor::helmat, 222));

	weapons.push_back(new Weapon("irondagger", Item::WEAPON, 10, 11, Weapon::IRON ,Weapon::dagger, 111));
	weapons.push_back(new Weapon("ebonydagger", Item::WEAPON, 20, 22, Weapon::EBONY ,Weapon::dagger, 222));

	potions.push_back(new Potion("hp_potion", Item::POTION, 1, 2, Potion::POTION_HP, 100));
	potions.push_back(new Potion("sp_potion", Item::POTION, 1, 2, Potion::POTION_SP, 100));

	arrows.push_back(new Arrow("iron_arrow", Item::ARROW, 1, 2, Arrow::IRON, 100));
	arrows.push_back(new Arrow("dragonbone_arrow", Item::ARROW, 1, 2, Arrow::DRAGONBONE, 100));
}

ItemStatus::~ItemStatus()
{
}

Item::Status ItemStatus::GetItem(string inname)
{
	CheckType(inname);
	switch (type)
	{
	case Item::ARMOR:
		return GetArmor(inname)->GetStatus();
		break;
	case Item::WEAPON:
		return GetWeapon(inname)->GetStatus();
		break;
	case Item::ARROW:
		return GetArrow(inname)->GetStatus();
		break;
	case Item::POTION:
		return GetPotion(inname)->GetStatus();
		break;
	default:
		break;
	}
}

Armor* ItemStatus::GetArmor(string inname)
{
	for (Armor* armor : armors)
	{
		if (armor->GetStatus().name == inname)
		{
			return armor;
		}
	}
}

Weapon* ItemStatus::GetWeapon(string inname)
{
	for (Weapon* weapon : weapons)
	{
		if (weapon->GetStatus().name == inname)
		{
			return weapon;
		}
	}
}

Arrow* ItemStatus::GetArrow(string inname)
{
	for (Arrow* arrow : arrows)
	{
		if (arrow->GetStatus().name == inname)
		{
			return arrow;
		}
	}
}

Potion* ItemStatus::GetPotion(string inname)
{
	for (Potion* potion : potions)
	{
		if (potion->GetStatus().name == inname)
		{
			return potion;
		}
	}
}



int ItemStatus::CheckType(string inname)
{
	for (Armor* armor : armors)
	{
		if (armor->GetStatus().name == inname)
		{
			type = armor->GetStatus().type;
			return type;
		}
	}

	for (Weapon* weapon : weapons)
	{
		if (weapon->GetStatus().name == inname)
		{
			type = weapon->GetStatus().type;
			return type;
		}
	}

	for (Arrow* arrow : arrows)
	{
		if (arrow->GetStatus().name == inname)
		{
			type = arrow->GetStatus().type;
			return type;
		}
	}

	for (Potion* potion : potions)
	{
		if (potion->GetStatus().name == inname)
		{
			type = potion->GetStatus().type;
			return type;
		}
	}
}
