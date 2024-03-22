#pragma once

class Character
{
public:
	struct Status
	{
		Status() {}
		Status(int level, float hp, float stam, float atk, float speed)
			: level(level), curHp(hp), maxHp(hp), curStam(stam), maxStam(stam), atk(atk), speed(speed) {}

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
	void GUIRender();

	void SetStatus(int level, float hp, float stam, float atk, float speed);
	void SetStatus(Status status) { this->status = status; }
	void SetName(string val) { name = val; }
	void SetSpawnPos(Vector3 pos) { spawnPos = pos; }

	Transform* GetTransform() { return transform; }
	Status& GetStatus() { return status; }
	SphereCollider* GetCollider() { return collider; }
	string GetName() { return name; }

	bool IsBattle() { return isBattle; }

	void Spawn();

protected:
	Status status;
	string name;
	Transform* transform;
	SphereCollider* collider;
	Vector3 spawnPos;

	bool isBattle = false;
};

