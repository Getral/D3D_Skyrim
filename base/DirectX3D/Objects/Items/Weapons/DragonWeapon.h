#pragma once

class DragonWeapon
{
public:

	struct DragonWeaponAbility
	{
		float power;
		float atkSpeed;
		float weight;
		float gold;
	};


public:
	DragonWeapon();
	~DragonWeapon();

	void Update();
	void Render();
	void GUIRender();


private:


};

