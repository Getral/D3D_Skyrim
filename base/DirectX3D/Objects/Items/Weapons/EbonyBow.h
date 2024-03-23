#pragma once

class EbonyBow : public ModelAnimator
{
public:

    enum EbonyBowAction
    {
        IDLE,
        DRAW,
        DRAW_IDLE,
        RELEASE
    };

    EbonyBow();
    ~EbonyBow();

    void Update();
    void Render();
    void GUIRender();

    //bool GetIsWeapon() { return isWeapon; }
    //void SetIsCollider(bool value) { isWeapon = value; }

    //void ColliderManager(bool isWeaponColl);

    void SetState(EbonyBowAction action);

private:
    ModelAnimator* ebonybow;
    BoxCollider* collider;
    //bool isWeapon = true;

    EbonyBowAction curState = IDLE;
};
