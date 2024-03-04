#pragma once

class Armor : public Inventory
{
	struct ArmorAbility
	{
		float defense = 0;

		// 마법부여는 필요하면 추가
	};

	struct ArmorType
	{
		float hamet;
		float cuirass;
		float gauntlets;
		float boots;
		
		float shield;
	};
};

