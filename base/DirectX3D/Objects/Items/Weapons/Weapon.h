#pragma once

class Weapon : public Inventory
{
public:

	struct WeaponAbility
	{
		float power = 0;
		float atkSpeed = 0;
	};

	struct WeaponType
	{
		float battleaxe;

		float claymore;	 // 한손검

		float claymore;	 // 단검

		float mace;		 // 둔기

		float longsword; // 양손검

		float waraxe;	 // 도끼

		float warhammer; // 둔기

		float bow;		 // 활		// 화살통이랑 같이 모델출력해야할듯
		float arrow;	 // 화살
		float quiver;	 // 화살통
	};


};

