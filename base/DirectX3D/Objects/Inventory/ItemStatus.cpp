#include "Framework.h"

ItemStatus::ItemStatus()
{
	armors.push_back(new Armor("dragonboneboots", Item::AROMOR, 10, 11, Armor::helmat, 30));
	armors.push_back(new Armor("dragonbonecuirassplate", Item::AROMOR, 10, 10, Armor::helmat, 10));
}

ItemStatus::~ItemStatus()
{
}

Item::Status ItemStatus::GetItem(string inname)
{
	CheckType(inname);
	switch (type)
	{
	case Item::AROMOR:
		return GetArmor(inname)->GetStatus();
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
}
