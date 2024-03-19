#pragma once
class EbonyWarHammer : public Model
{
public:
    EbonyWarHammer();
    ~EbonyWarHammer();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonyhammer;
    BoxCollider* collider;
    bool isWeapon = true;
};