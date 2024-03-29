#pragma once

class Weapon : public Item
{
public:
	enum WeaponType
	{
		// 1hd
		dagger,		// �ܰ� 
		claymore,	// �Ѽհ�
		waraxe,		// �Ѽյ���
		mace,		// �Ѽյб�	
		// 2hd
		longsword,	// ��հ�
		battleaxe,	// ��յ���
		warhammer,	// ��յб�
		bow			// Ȱ
	};

	enum WeaponClass
	{
		IRON,
		EBONY
	};

	Weapon(string name, int type, int weight, int value, 
		int weapon_class ,int weapon_type, int atk);

	
	int GetWeaponClass() { return weapon_class; }
	int GetAtk() { return atk; }
	void ChangeEquipState() { isEquiped = !isEquiped; }
	bool GetEquip() { return isEquiped; }


private:
	int weapon_class;
	int weapon_type;
	int atk;
	bool isEquiped = false;
	
private:
	BoxCollider* collider;
	Model* model;
	Transform* transfrom;
};

/*
IronWeapon
irondagger		// �ܰ�
ironclaymore	// �Ѽհ�
ironwaraxe   	// �Ѽյ���
ironmace	    // �Ѽյб�
ironlongsword	// ��հ�
ironbattleaxe	// ��յ���
ironwarhammer	// ��յб�
ironbow			// Ȱ 

EbonyWeapon
ebonydageer     // �ܰ�
ebonysword   	// �Ѽհ�
ebonymace	    // �Ѽյб�
ebonywaraxe		// �Ѽյ���?
ebonygreatsword	// ��հ�
ebonybattleaxe  // ��յ���
ebonywarhammer   // ��յб�
ebonybow		// Ȱ
*/