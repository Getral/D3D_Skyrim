#pragma once

class DragonBoneWeapon
{
public:

	struct DragonBoneWeaponAbility
	{
		float power;
		float atkSpeed;
		float weight;
		float gold;
	};


public:
	DragonBoneWeapon();
	~DragonBoneWeapon();

	void Update();
	void Render();
	void GUIRender();


private:


};

