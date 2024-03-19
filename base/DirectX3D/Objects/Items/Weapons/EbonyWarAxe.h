#pragma once
class EbonyWarAxe : public Model
{
public:
    EbonyWarAxe();
    ~EbonyWarAxe();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ebonywaraxe;
    BoxCollider* collider;
    bool isWeapon = true;
};