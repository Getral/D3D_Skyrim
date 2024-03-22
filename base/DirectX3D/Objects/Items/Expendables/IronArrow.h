#pragma once

class IronArrow : public Arrow
{
public:

	IronArrow(string name, int type, int weight, int value,
		int arrow_type, int atk);
	~IronArrow();

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

	void Shoot(Vector3 pos, Vector3 dir);
	Transform* GetTransform() { return transform; }
	BoxCollider* GetCollider() { return collider; }

private:
	float LIFE_SPAN = 7;

private:
	int arrow_type;
	int atk;
	int count = 1;

	bool isEquiped = false;
	bool isBow = false;

	Model* ironarrow;
	Transform* transform;
	BoxCollider* collider;

	float speed = 1000;
	float time = 0;

	Vector3 direction;
};

