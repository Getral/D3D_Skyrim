#pragma once

class IronBow : public ModelAnimator
{
public:

    enum IronBowAction
    {
        IDLE,
        DRAW,
        DRAW_IDLE,
        RELEASE
    };
        
    IronBow();
    ~IronBow();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }
    
    void ColliderManager(bool isWeaponColl);

    void SetState(IronBowAction action);

private:
    ModelAnimator* ironbow;
    BoxCollider* collider;
    bool isWeapon = true;

    IronBowAction curState = IDLE;
};