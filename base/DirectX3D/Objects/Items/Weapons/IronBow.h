#pragma once

class IronBow : public Model
{
public:
    IronBow();
    ~IronBow();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironbow;
    BoxCollider* collider;
    bool isWeapon = true;
};