#pragma once

class Inventory
{
public:
	struct classification
	{
		string name;
		float type;
		float weaght;	// 무게
		float gold;		// 화페
		float value;	// 개수
	};

	struct Type
	{
		float Weapon;			// 무기
		float Armor;			// 방어구
		float ArmorSet;			// 방어구 세트로 입히고 진행하면 사용
		float Expendables;		// 소모품
		float Miscellaneous;	// 잡탬
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

