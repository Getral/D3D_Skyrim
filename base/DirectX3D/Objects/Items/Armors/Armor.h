#pragma once

class Armor : public Inventory
{
	struct ArmorAbility
	{
		float defense = 0;

		// �����ο��� �ʿ��ϸ� �߰�
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

