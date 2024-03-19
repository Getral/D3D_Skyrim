#pragma once

class BladeSword : public Model
{
public:
    BladeSword();
    ~BladeSword();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    BoxCollider* collider;

    //bool isWeapon = true;   // 수정할려고 true로 설정해둠 후에 삭제
    bool isWeapon = false;

};