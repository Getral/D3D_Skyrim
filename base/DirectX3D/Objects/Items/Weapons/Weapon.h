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

		float claymore;	 // �Ѽհ�

		float claymore;	 // �ܰ�

		float mace;		 // �б�

		float longsword; // ��հ�

		float waraxe;	 // ����

		float warhammer; // �б�

		float bow;		 // Ȱ		// ȭ�����̶� ���� ������ؾ��ҵ�
		float arrow;	 // ȭ��
		float quiver;	 // ȭ����
	};


};

