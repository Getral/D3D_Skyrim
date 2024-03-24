#pragma once

class EbonyWarHammer : public Weapon
{
public:
    EbonyWarHammer(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~EbonyWarHammer();

    void Update();
    void Render();
    void GUIRender();

    BoxCollider* GetCollider() { return collider; }
    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonywarhammer;
    BoxCollider* collider;
    bool isWeapon = true;
};
