#pragma once
class IronQuiver : public Model
{
    IronQuiver();
    ~IronQuiver();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironquiver;
    BoxCollider* collider;
    bool isWeapon = true;
};

