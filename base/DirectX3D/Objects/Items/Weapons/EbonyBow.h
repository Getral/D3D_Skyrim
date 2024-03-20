#pragma once

class EbonyBow : public Model
{
public:
    EbonyBow();
    ~EbonyBow();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonybow;
    BoxCollider* collider;
    bool isWeapon = true;
};