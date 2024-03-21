#pragma once

class EbonyBow : public ModelAnimator
{
public:

    enum EbonyBowAction
    {
        DRAW,
        DRAW_IDLE,
        RELEASE
    };

    EbonyBow();
    ~EbonyBow();

    void Update();
    void Render();
    void GUIRender();

    bool GetIsWeapon() { return isWeapon; }
    void SetIsCollider(bool value) { isWeapon = value; }

    void ColliderManager(bool isWeaponColl);

private:
    ModelAnimator* ebonybow;
    BoxCollider* collider;
    bool isWeapon = true;
};