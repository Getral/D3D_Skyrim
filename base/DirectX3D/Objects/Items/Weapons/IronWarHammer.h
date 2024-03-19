#pragma once
class IronWarHammer : public Model
{
public:
    IronWarHammer();
    ~IronWarHammer();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironwarhammer;
    BoxCollider* collider;
    bool isWeapon = true;
};