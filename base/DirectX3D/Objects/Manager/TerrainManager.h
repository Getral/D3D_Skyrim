#pragma once
class TerrainManager : public Singleton<TerrainManager>
{
private:
	UINT WIDTH = 1;
	UINT HEIGHT = 1;

public:
	TerrainManager();
	~TerrainManager();

	void Update();
	void Render();
	void GUIRender();

	void SetPlayerData(Player* player) { if (player != playerData) playerData = player; }

private:
	Player* playerData;
	Terrain* terrain;

	int test = 0;

	float gravity = 50.0f;
};

