#pragma once

class EbonyQuiver : public Model
{
public:
    EbonyQuiver();
    ~EbonyQuiver();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonyquiver;
    BoxCollider* collider;
    bool isWeapon = true;
};