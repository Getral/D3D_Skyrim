#pragma once

class TerrainScene : public Scene
{
private:
	UINT terrainSize = 10;

	vector<string> objectName =
	{
		"rock_large1", "rock_large2", "rock_large3", "rock_large4", "rock_large5",
		"rock_medium1", "rock_medium2", "rock_medium3", "rock_medium4",
		"rock_small1", "rock_small2"
	};

	vector<vector<Vector3>> objectPos =
	{
		{ Vector3(178, 12, 200), Vector3(200, 0, 200), Vector3(210, 15, 230), Vector3(300, 3, 225), Vector3(300, 5, 175),
			Vector3(300, 1, 310), Vector3(257, 0.1, 357) }, // rock_large1
		{ Vector3(300, 0, 200), Vector3(270, 0, 228.5), Vector3(227.5, 0, 263), Vector3(213, 0, 345), Vector3(227.3, 0, 329.5),
			Vector3(200, 0, 100), Vector3(288.9, 0.5, 154.3), Vector3(168.8, 0.5, 163.6) }, // rock_large2
		{ Vector3(188, 0, 125.5), Vector3(246, 0, 203), Vector3(278, -1, 189.5), Vector3(277.8, 6.5, 205.3), Vector3(307.5, 1, 208),
			Vector3(303.6, 1.5, 215.2), Vector3(296.6, -0.3, 246.4), Vector3(256.7, -0.5, 240.5), Vector3(273.7, -0.5, 307.9) }, // rock_large3
		{ Vector3(0, 0, 0) }, // rock_large4
		{ Vector3(0, 0, 0) }, // rock_large5
		{ Vector3(0, 0, 0) }, // rock_medium1
		{ Vector3(0, 0, 0) }, // rock_medium2
		{ Vector3(0, 0, 0) }, // rock_medium3
		{ Vector3(0, 0, 0) }, // rock_medium4
		{ Vector3(0, 0, 0) }, // rock_small1
		{ Vector3(0, 0, 0) } // rock_small2
	};

public:
	TerrainScene();
	~TerrainScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	Model* testModel;

	Model* tree01;
	Model* tree02;
	//Terrain* terrain;
};

