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
		float dagger;	 // �ܰ�

		float claymore;	 // �Ѽհ�

		float longsword; // ��հ�

		float mace;		 // �Ѽյб�

		float warhammer; // ��յб�

		float waraxe;	 // �Ѽյ���

		float battleaxe; // ��յ���

		float bow;		 // Ȱ		// ȭ�����̶� ���� ������ؾ��ҵ�
		float arrow;	 // ȭ��
		float quiver;	 // ȭ����
	};


};

