#pragma once

class Character
{
protected:
	struct Status
	{
		int level;
		float curHp;
		float maxHp;
		float curStam;
		float maxStam;
		float atk;
		float speed;
	};

public:
	Character(Transform* transform, string name, Vector3 spawnPos);
	~Character();

	void Update();
	void Render();

	void SetStatus(int level, float hp, float stam, float atk, float speed);
	void SetStatus(Status status) { status = status; }
	void SetName(string val) { name = val; }
	void SetSpawnPos(Vector3 pos) { spawnPos = pos; }

	Transform* GetTransform() { return transform; }
	Status GetStatus() { return status; }
	CapsuleCollider* GetCollier() { return collider; }
	string GetName() { return name; }

	void Spawn();

protected:
	Status status;
	string name;
	Transform* transform;
	CapsuleCollider* collider;
	Vector3 spawnPos;
};

