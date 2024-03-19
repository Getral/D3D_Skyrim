#pragma once

class IronLongSword : public Model
{
public:
    IronLongSword();
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