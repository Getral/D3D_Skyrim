#pragma once

class Monster : public Character
{
public:
	Monster(Transform* transform, Status status, float trackRange = 1000.0f);
	~Monster();

	void Update();
	void Render();
	void GUIRender();

	void Spawn(Vector3 pos);

	SphereCollider* GetTrackCollider() { return trackCollider; }

private:
	float trackTime = 0.0f;
	float trackRange = 0.0f;
	
	SphereCollider* trackCollider;
};

