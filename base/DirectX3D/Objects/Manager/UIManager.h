#pragma once
class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	void Update(Player* player, vector<EnemySpawn*> enemies);
	void Render();
	void PostRender();
	void GUIRender();

	void TargetCompassEnemy(Player* player, vector<EnemySpawn*> enemies);

	//float GetEnemyDegree() { return final_angle; }

private:
	Quad* compass;
	vector<Quad*> compass_dir;
	vector<Quad*> enemies_dir;

	Quad* enemy_dir;

	Quad* HP_bar_background;
	Quad* HP_bar;
	float maxHpBar;
	float HP_ratio;

	Quad* SP_bar_background;
	ProgressBar* SP_bar;

	Quad* enemy_HP_bar_background;
	ProgressBar* enemy_HP_bar;
	float enemy_maxHpBar;
	float enemy_HP_ratio;


	float tmp_N;
	float tmp_S;
	float tmp_W;
	float tmp_E;

	float dirX_tmp[4];


	float cal_dot;
	float angle;

	float final_angle;
	vector<float> final_angles;

	int monsterCount = 3;

	
};

