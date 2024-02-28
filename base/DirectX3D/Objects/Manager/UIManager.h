#pragma once
class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	void Update(Naruto* naruto, Model* enemy);
	void Render();
	void PostRender();
	void GUIRender();

	float TargetCompassEnemy(Naruto* naruto, Model* model);

	float GetEnemyDegree() { return final_angle; }

private:
	Quad* compass;
	vector<Quad*> compass_dir;
	Quad* enemy_dir;

	float tmp_N;
	float tmp_S;
	float tmp_W;
	float tmp_E;

	float dirX_tmp[4];


	float cal_dot;
	float angle;

	float final_angle;
};

