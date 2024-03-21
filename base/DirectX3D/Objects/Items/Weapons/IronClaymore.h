#pragma once

class IronClaymore : public Weapon
{
public:
    IronClaymore(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~IronClaymore();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonyclaymore;
    BoxCollider* collider;
    bool isWeapon = true;
};