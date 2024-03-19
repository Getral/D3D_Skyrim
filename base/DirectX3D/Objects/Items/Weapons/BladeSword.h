#pragma once

class BladeSword : public Model
{
public:
    BladeSword();
    ~BladeSword();

    void Update();
    void Render();
    void GUIRender();

    BoxCollider* GetCollider() { return collider; }
    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    BoxCollider* collider;
    bool isWeapon = false;

};