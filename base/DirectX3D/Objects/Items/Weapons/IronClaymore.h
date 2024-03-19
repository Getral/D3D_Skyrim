#pragma once

class IronClaymore : public Model
{
public:
    IronClaymore();
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