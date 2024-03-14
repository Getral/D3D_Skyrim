#pragma once

class Weapon : public Item
{
public:
	enum WeaponType
	{
		// 1hd
		dagger,		// 단검
		claymore,		// 한손검
		waraxe,		// 한손도끼
		mace,			// 한손둔기

		
		longsword,	// 양손검
		battleaxe,	// 양손도끼
		warhammer,	// 양손둔기

		
		bow			// 활
	};

	enum WeaponClass
	{
		IRON,
		EBONY
	};
	Weapon(string name, int type, int weight, int value, int weapon_class ,int weapon_type, int atk);

	
	int GetWeaponClass() { return weapon_class; }
	int GetAtk() { return atk; }
	void ChangeEquipState() { isEquiped = !isEquiped; }
private:
	int weapon_class;
	int weapon_type;
	int atk;
	bool isEquiped = false;
};

/*
IronWeapon
irondagger		// 단검
ironclaymore	// 한손검
ironwaraxe   	// 한손도끼
ironmace	    // 한손둔기
ironlongsword	// 양손검
ironbattleaxe	// 양손도끼
ironwarhammer	// 양손둔기
ironbow			// 활 

EbonyWeapon
ebonydageer     // 단검
ebonysword   	// 한손검
ebonymace	    // 한손둔기
ebonywaraxe		// 한손도끼?
ebonygreatsword	// 양손검
ebonybattleaxe  // 양손도끼
ebonywarhammer   // 양손둔기
ebonybow		// 활
*/