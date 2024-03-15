#pragma once
class IronWarAxe : public Model
{
public:
    IronWarAxe();
    ~IronWarAxe();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironwaraxe;
    BoxCollider* collider;
    bool isWeapon = true;
};