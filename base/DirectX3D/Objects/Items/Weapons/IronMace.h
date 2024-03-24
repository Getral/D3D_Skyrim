#pragma once
class IronMace : public Weapon
{
public:
    IronMace(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~IronMace();

    void Update();
    void Render();
    void GUIRender();

    BoxCollider* GetCollider() { return collider; }
    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironmace;
    BoxCollider* collider;
    bool isWeapon = false;
};
