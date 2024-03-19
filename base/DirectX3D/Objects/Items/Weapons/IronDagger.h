#pragma once

class IronDagger : public Model
{
public:
    IronDagger();
    ~IronDagger();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonydagger;
    BoxCollider* collider;
    bool isWeapon = true;
};

