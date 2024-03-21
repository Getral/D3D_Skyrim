#pragma once

class TerrainScene : public Scene
{
private:
	UINT terrainSize = 10;

	vector<string> objectName =
	{
		"rock_large1", "rock_large2", "rock_large3", "rock_large4", "rock_large5",
		"rock_medium1", "rock_medium2", "rock_medium3", "rock_medium4",
		"rock_small1", "rock_small2","tree"
	};

	vector<vector<Vector3>> objectPos =
	{
		{ Vector3(178, 12, 200), Vector3(200, 0, 200), Vector3(210, 15, 230), Vector3(300, 3, 225), Vector3(300, 5, 175),
			Vector3(300, 1, 310), Vector3(257, 0.1, 357) }, // rock_large1
		{ Vector3(300, 0, 200), Vector3(270, 0, 228.5), Vector3(227.5, 0, 263), Vector3(213, 0, 345), Vector3(227.3, 0, 329.5),
			Vector3(200, 0, 100), Vector3(288.9, 0.5, 154.3), Vector3(168.8, 0.5, 163.6) }, // rock_large2
		{ Vector3(188, 0, 125.5), Vector3(246, 0, 203), Vector3(278, -1, 189.5), Vector3(277.8, 6.5, 205.3), Vector3(307.5, 1, 208),
			Vector3(303.6, 1.5, 215.2), Vector3(296.6, -0.3, 246.4), Vector3(256.7, -0.5, 240.5), Vector3(273.7, -0.5, 307.9) }, // rock_large3
		{ Vector3(284.5, 0, 196.5), Vector3(307.5, 184), Vector3(296.8, 0, 235.7), Vector3(220.9, -2.4, 256.4), Vector3(172.3, 25.3, 241.7),
			Vector3(178.9, 7.5, 282.3), Vector3(193.3, 7.5, 336.1), Vector3(229.9, -0.7, 342.2), Vector3(265.6, -0.7, 344.3) }, // rock_large4
		{ Vector3(0, 0, 0) }, // rock_large5
		{ Vector3(0, 0, 0) }, // rock_medium1
		{ Vector3(0, 0, 0) }, // rock_medium2
		{ Vector3(0, 0, 0) }, // rock_medium3
		{ Vector3(0, 0, 0) }, // rock_medium4
		{ Vector3(0, 0, 0) }, // rock_small1
		{ Vector3(0, 0, 0) }, // rock_small2
		{ Vector3(157, 18, 146), Vector3(159, 16, 113), Vector3(179, 9, 102), Vector3(162, 12, 184), Vector3(189, 10, 199),Vector3(214, 12, 199),
			Vector3(233, 9, 217),Vector3(262, 6, 198), Vector3(292, 12, 164), Vector3(297, 17, 210), Vector3(299, 15, 231), Vector3(292, 6, 262), Vector3(239, 0, 305)}

	};

	vector<vector<float>> objectRot =
	{
		{ 0, 0, 0, 0, 0, 0, 0 }, // rock_large1
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // rock_large2
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // rock_large3
		{ 0, 0, 0, -87, -52, 53, 53, -53, 158 }, // rock_large4
		{ 0 }, // rock_large5
		{ 0 }, // rock_medium1
		{ 0 }, // rock_medium2
		{ 0 }, // rock_medium3
		{ 0 }, // rock_medium4
		{ 0 }, // rock_small1
		{ 0 }, // rock_small2
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0 }
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

