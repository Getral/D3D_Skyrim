#pragma once
class IronMace : public Model
{
public:
    IronMace();
    ~IronMace();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironmace;
    BoxCollider* collider;
    bool isWeapon = true;
};
