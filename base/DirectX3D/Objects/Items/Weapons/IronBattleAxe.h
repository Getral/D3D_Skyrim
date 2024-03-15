#pragma once
class IronBattleAxe : public Model
{
public:
    IronBattleAxe();
    ~IronBattleAxe();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    Model* ironbattleaxe;
    BoxCollider* collider;
    bool isWeapon = true;
};

