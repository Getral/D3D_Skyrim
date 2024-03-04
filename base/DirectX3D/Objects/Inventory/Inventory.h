#pragma once

class Inventory
{
public:
	struct classification
	{
		string name;
		float type;
		float weaght;	// ����
		float gold;		// ȭ��
		float value;	// ����
	};

	struct Type
	{
		float Weapon;			// ����
		float Armor;			// ��
		float ArmorSet;			// �� ��Ʈ�� ������ �����ϸ� ���
		float Expendables;		// �Ҹ�ǰ
		float Miscellaneous;	// ����
	};


public:
	Inventory(string name);
	~Inventory();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

private:

	Model* model;
	SphereCollider* collider;
};

