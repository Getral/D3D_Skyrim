#pragma once
class IronWarHammer : public Weapon
{
public:
    IronWarHammer(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~IronWarHammer();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironwarhammer;
    BoxCollider* collider;
    bool isWeapon = true;
};