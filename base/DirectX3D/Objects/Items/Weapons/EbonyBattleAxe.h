#pragma once

class EbonyBattleAxe : public Weapon
{
public:
    EbonyBattleAxe(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~EbonyBattleAxe();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);


private:
    Model* ebonybattleaxe;
    BoxCollider* collider;
    bool isWeapon = true;    
};

