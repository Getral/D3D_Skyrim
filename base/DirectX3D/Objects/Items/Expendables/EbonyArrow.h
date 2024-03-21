#pragma once

class EbonyArrow : public Arrow
{
public:

	EbonyArrow(string name, int type, int weight, int value,
		int arrow_type, int atk);
	~EbonyArrow();

	void Update();
	void Render();
	void GUIRender();


	int GetType() { return arrow_type; }
	int GetAtk() { return atk; }
	int& GetCount() { return count; }

	bool& GetEquip() { return isEquiped; }
	void ChangeEquipState() { isEquiped = !isEquiped; }

	bool GetIsBow() { return isBow; }
	void SetIsCollider(bool value) { isBow = value; }
	void ColliderManager(bool isBowCollider);

private:
	int arrow_type;
	int atk;
	int count = 1;

	bool isEquiped = false;
	bool isBow = false;

	BoxCollider* collider;
	Model* ebonyarrow;
};