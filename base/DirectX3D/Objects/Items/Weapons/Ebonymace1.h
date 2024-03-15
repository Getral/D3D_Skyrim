#pragma once
class EbonyMace1 :public Model
{
public:
    EbonyMace1();
    ~EbonyMace1();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonymace1;
    BoxCollider* collider;
    bool isWeapon = true;
};

