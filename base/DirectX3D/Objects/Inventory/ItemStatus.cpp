#include "Framework.h"

ItemStatus::ItemStatus()
{
	armors.push_back(new Armor("ironhelmet", Item::ARMOR, 10, 11, Armor::IRON ,Armor::helmet, 12));
	armors.push_back(new Armor("ironcuirass", Item::ARMOR, 10, 11, Armor::IRON ,Armor::cuirass, 12));
	armors.push_back(new Armor("irongauntlet", Item::ARMOR, 10, 11, Armor::IRON ,Armor::gauntlet, 12));
	armors.push_back(new Armor("ironboots", Item::ARMOR, 10, 11, Armor::IRON ,Armor::boots, 12));
	armors.push_back(new Armor("ironshield", Item::ARMOR, 10, 11, Armor::IRON ,Armor::shield, 12));


	armors.push_back(new Armor("dragonhelmet", Item::ARMOR, 20, 21, Armor::DRAGONBONE ,Armor::helmet, 22));
	armors.push_back(new Armor("dragoncuirass", Item::ARMOR, 20, 21, Armor::DRAGONBONE ,Armor::cuirass, 22));
	armors.push_back(new Armor("dragongauntlet", Item::ARMOR, 20, 21, Armor::DRAGONBONE ,Armor::gauntlet, 22));
	armors.push_back(new Armor("dragonboots", Item::ARMOR, 20, 21, Armor::DRAGONBONE ,Armor::boots, 22));
	armors.push_back(new Armor("dragonshield", Item::ARMOR, 20, 21, Armor::DRAGONBONE ,Armor::shield, 22));

	weapons.push_back(new Weapon("irondagger", Item::WEAPON, 30, 31, Weapon::IRON ,Weapon::dagger, 32));
	weapons.push_back(new Weapon("ebonydagger", Item::WEAPON, 40, 41, Weapon::EBONY ,Weapon::dagger, 42));

	arrows.push_back(new Arrow("ironarrow", Item::ARROW, 1, 2, Arrow::IRON, 100));
	arrows.push_back(new Arrow("dragonarrow", Item::ARROW, 1, 2, Arrow::DRAGONBONE, 100));

	potions.push_back(new Potion("hp_potion", Item::POTION, 1, 2, Potion::POTION_HP, 10));
	potions.push_back(new Potion("sp_potion", Item::POTION, 1, 2, Potion::POTION_SP, 10));

	misces.push_back(new Misc("misc1", Item::MISC, 1, 1));
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
	case Item::MISC:
		return GetMisc(inname)->GetStatus();
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

Misc* ItemStatus::GetMisc(string inname)
{
	for (Misc* misc : misces)
	{
		if (misc->GetStatus().name == inname)
		{
			return misc;
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

	for (Misc* misc : misces)
	{
		if (misc->GetStatus().name == inname)
		{
			type = misc->GetStatus().type;
			return type;
		}
	}
}
