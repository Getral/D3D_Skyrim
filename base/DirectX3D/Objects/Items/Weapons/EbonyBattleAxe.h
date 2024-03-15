#pragma once
class EbonyBattleAxe : public Model
{
public:
    EbonyBattleAxe();
    ~EbonyBattleAxe();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    BoxCollider* collider;
    bool isWeapon = true;
};

