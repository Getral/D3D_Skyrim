#pragma once
class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	void Update(Player* player, Model* enemy);
	void Render();
	void PostRender();
	void GUIRender();

	float TargetCompassEnemy(Player* player, Model* model);

	float GetEnemyDegree() { return final_angle; }

private:
	Quad* compass;
	vector<Quad*> compass_dir;
	Quad* enemy_dir;

	Quad* HP_bar_background;
	Quad* HP_bar;
	float maxHpBar;
	float HP_ratio;

	Quad* SP_bar_background;
	ProgressBar* SP_bar;

	float tmp_N;
	float tmp_S;
	float tmp_W;
	float tmp_E;

	float dirX_tmp[4];


	float cal_dot;
	float angle;

	float final_angle;
};

