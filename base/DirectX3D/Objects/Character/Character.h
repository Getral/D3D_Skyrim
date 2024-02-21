#pragma once

class Character
{
public:
	struct Status
	{
		float curHp;
		float maxHp;
		float atk;
		float speed;
	};

public:
	Character(Transform* transform, Status status);
	~Character();

	void Update();
	void Render();

	Transform* GetTransform() { return transform; }
	Status GetStatus() { return status; }
	CapsuleCollider* GetCollier() { return collider; }

protected:
	Transform* transform;

	Status status;
	CapsuleCollider* collider;
};

