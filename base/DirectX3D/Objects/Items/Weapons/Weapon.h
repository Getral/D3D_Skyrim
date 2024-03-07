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
		float dagger;	 // 단검

		float claymore;	 // 한손검

		float longsword; // 양손검

		float mace;		 // 한손둔기

		float warhammer; // 양손둔기

		float waraxe;	 // 한손도끼

		float battleaxe; // 양손도끼

		float bow;		 // 활		// 화살통이랑 같이 모델출력해야할듯
		float arrow;	 // 화살
		float quiver;	 // 화살통
	};


};

