#pragma once

class IronLongSword : public Weapon
{
public:
    IronLongSword(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~IronLongSword();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironlongsword;
    BoxCollider* collider;
    bool isWeapon = true;
};