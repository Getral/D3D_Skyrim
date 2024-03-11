#include "Framework.h"

ItemStatus::ItemStatus()
{
	armors.push_back(new Armor("armor1", Item::AROMOR, 10, 10, Armor::helmat, 10));

	
}

ItemStatus::~ItemStatus()
{
}

void ItemStatus::Update()
{
	switch (type)
	{
	case Item::AROMOR:
			ReturnArmor();
			break;
	default:
		break;
	}
}

Armor* ItemStatus::ReturnArmor()
{
	return armors.back();
}

void ItemStatus::CheckType(string inname)
{
	for (Armor* armor : armors)
	{
		if (armor->GetStatus().name == inname)
		{
			type = armor->GetStatus().type;
		}
	}

	for (Weapon* weapon : weapons)
	{
		if (weapon->GetStatus().name == inname)
		{
			type = weapon->GetStatus().type;
		}
	}
}
