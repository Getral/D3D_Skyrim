#pragma once
class EbonyLongSword : public Weapon
{
public:
    EbonyLongSword(string name, int type, int weight, int value,
        int weapon_class, int weapon_type, int atk);
    ~EbonyLongSword();

    void Update();
    void Render();
    void GUIRender();

    BoxCollider* GetCollider() { return collider; }
    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonylongsword;
    BoxCollider* collider;
    bool isWeapon = true;
};