#pragma once

class Weapon : public Item
{
	struct WeaponAbility
	{
		float power = 0;
		float atkSpeed = 0;
	};

	struct ArmorType
	{
		// 1hd
		float dagger;		// �ܰ�
		float claymore;		// �Ѽհ�
		float waraxe;		// �Ѽյ���
		float mace;			// �Ѽյб�

		// 2hd
		float longsword;	// ��հ�
		float battleaxe;	// ��յ���
		float warhammer;	// ��յб�

		// 
		float bow;			// Ȱ
	};
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