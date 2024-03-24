#pragma once

class IronDagger : public Weapon
{
public:
    IronDagger(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~IronDagger();

    void Update();
    void Render();
    void GUIRender();

    BoxCollider* GetCollider() { return collider; }
    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonydagger;
    BoxCollider* collider;
    bool isWeapon = true;
};

