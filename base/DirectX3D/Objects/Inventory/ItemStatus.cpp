#include "Framework.h"

ItemStatus::ItemStatus()
{
	// 이름,타이틀타입,무게,가치,아이템타입,아이템부위,방어력
	armors.push_back(new Armor("ironcuirass",  Item::ARMOR, 30, 125, Armor::IRON,  Armor::cuirass,  25));
	armors.push_back(new Armor("irongauntlets", Item::ARMOR, 5, 25,   Armor::IRON,  Armor::gauntlet, 10));
	armors.push_back(new Armor("ironboots",    Item::ARMOR, 6, 25,   Armor::IRON,  Armor::boots,    10));
	armors.push_back(new Armor("ironhelmet",   Item::ARMOR, 5, 60,   Armor::IRON,  Armor::helmet,   15));
	armors.push_back(new Armor("ironshield",   Item::ARMOR, 12, 60,  Armor::IRON,  Armor::shield,   20));

	armors.push_back(new Armor("dragoncuirass",  Item::ARMOR, 38, 1500, Armor::DRAGONBONE ,Armor::cuirass,  43));
	armors.push_back(new Armor("dragongauntlets", Item::ARMOR, 7, 275,   Armor::DRAGONBONE ,Armor::gauntlet, 16));
	armors.push_back(new Armor("dragonboots",    Item::ARMOR, 7, 275,   Armor::DRAGONBONE ,Armor::boots,    16));
	armors.push_back(new Armor("dragonhelmet",   Item::ARMOR, 10, 750,  Armor::DRAGONBONE ,Armor::helmet,   21));
	armors.push_back(new Armor("dragonshield",   Item::ARMOR, 14, 750,  Armor::DRAGONBONE ,Armor::shield,   32));

	// 이름,타이틀타입,무게,가치,아이템타입,아이템부위,공격력
	weapons.push_back(new Weapon("irondagger",    Item::WEAPON, 2,  10, Weapon::IRON ,Weapon::dagger,    4));  // 단검
	weapons.push_back(new Weapon("ironclaymore",  Item::WEAPON, 9,  25, Weapon::IRON ,Weapon::claymore,  7));  // 한손검
	weapons.push_back(new Weapon("ironwaraxe",    Item::WEAPON, 11, 30, Weapon::IRON ,Weapon::waraxe,    8));  // 한손도끼
	weapons.push_back(new Weapon("ironmace",	  Item::WEAPON, 13, 35, Weapon::IRON ,Weapon::mace,      9));  // 한손둔기
	weapons.push_back(new Weapon("ironlongsword", Item::WEAPON, 16, 50, Weapon::IRON ,Weapon::longsword, 15)); // 양손검
	weapons.push_back(new Weapon("ironbattleaxe", Item::WEAPON, 20, 55, Weapon::IRON ,Weapon::battleaxe, 16)); // 양손도끼
	weapons.push_back(new Weapon("ironwarhammer", Item::WEAPON, 24, 60, Weapon::IRON ,Weapon::warhammer, 18)); // 양손둔기
	weapons.push_back(new Weapon("ironbow",       Item::WEAPON, 20, 30, Weapon::IRON ,Weapon::bow,       10)); // 활

	weapons.push_back(new Weapon("ebonydagger",    Item::WEAPON, 5,  290,  Weapon::EBONY, Weapon::dagger,    10));
	weapons.push_back(new Weapon("ebonyclaymore",  Item::WEAPON, 15, 720,  Weapon::EBONY, Weapon::claymore,  13));
	weapons.push_back(new Weapon("ebonywarAxe",    Item::WEAPON, 17, 865,  Weapon::EBONY, Weapon::waraxe,    14));
	weapons.push_back(new Weapon("ebonymace",      Item::WEAPON, 19, 1000, Weapon::EBONY, Weapon::mace,      15));
	weapons.push_back(new Weapon("ebonylongsword", Item::WEAPON, 22, 1440, Weapon::EBONY, Weapon::longsword, 22));
	weapons.push_back(new Weapon("ebonybattleaxe", Item::WEAPON, 26, 1485, Weapon::EBONY, Weapon::battleaxe, 23));
	weapons.push_back(new Weapon("ebonywarhammer", Item::WEAPON, 30, 1725, Weapon::EBONY, Weapon::warhammer, 25));
	weapons.push_back(new Weapon("ebonybow",       Item::WEAPON, 16, 1440, Weapon::EBONY, Weapon::bow,       0));

	arrows.push_back(new Arrow("ironarrow",   Item::ARROW, 0, 1, Arrow::IRON,       10));
	arrows.push_back(new Arrow("dragonarrow", Item::ARROW, 0, 7, Arrow::EBONY,		20));

	//potions.push_back(new Potion("hp_potion", Item::POTION, 1, 1, Potion::POTION_HP, 100));
	//potions.push_back(new Potion("sp_potion", Item::POTION, 1, 1, Potion::POTION_SP, 100));

	misces.push_back(new Misc("coin", Item::MISC, 1, 1));
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
