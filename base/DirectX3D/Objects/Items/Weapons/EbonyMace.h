#pragma once
class EbonyMace : public Weapon
{
public:
    EbonyMace(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~EbonyMace();

    void Update();
    void Render();
    void GUIRender();

    BoxCollider* GetCollider() { return collider; }
    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonymace;
    BoxCollider* collider;
    bool isWeapon = true;
};

