#pragma once
class EbonyLongSword : public Model
{
public:
    EbonyLongSword();
    ~EbonyLongSword();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonylongsword;
    BoxCollider* collider;
    bool isWeapon = true;
};