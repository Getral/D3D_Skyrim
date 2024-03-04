#pragma once
class dragonManager 
{
public:

	dragonManager();
	~dragonManager();
	void Update();
	void Render();
	void PostRender();



private:

	float hp;
	float moveSpeed;
	float altitude;

	float attackPow;
	float strAttackPow;
	float breathAttackPow;
	float attackWingPow;
	float fireBallPow;




};

