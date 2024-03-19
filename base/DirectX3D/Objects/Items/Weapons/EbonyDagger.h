#pragma once

class EbonyDagger : public Model
{
public:
    EbonyDagger();
    ~EbonyDagger();

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

