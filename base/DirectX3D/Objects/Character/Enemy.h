#pragma once

class Enemy : public Character
{
private:
	


public:
	Enemy(string name, Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 }, float trackRange = 1000.0f);
	~Enemy();

	void Update();
	void Render();
	void GUIRender();

	SphereCollider* GetTrackCollider() { return trackCollider; }

private:
	float trackTime = 0.0f;
	float trackRange = 0.0f;
	
	SphereCollider* trackCollider;
};

