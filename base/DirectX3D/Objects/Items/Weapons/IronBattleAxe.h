#pragma once

class IronBattleAxe : public Weapon
{
public:
    IronBattleAxe(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~IronBattleAxe();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironbattleaxe;
    BoxCollider* collider;
    bool isWeapon = true;
};

