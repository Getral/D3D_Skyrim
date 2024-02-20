#pragma once
class Human : public ModelAnimator
{
private:
    enum class ACTION
    {
        IDLE,
        RUN,
        JUMP
    };

public:
    Human();
    ~Human();

    void Update();
    void Render();
    void GUIRender();

private:
    void ClipSync();
    void Control();
    void Jump();

private:
    Crowbar* crowbar;
    Transform* mainHand;

    ACTION action;
    
    float moveSpeed = 0;
    float jumpVelocity = 0;
    float jumpForce = 0.5f;
    float gravityMult = 0.5f;
    bool isJump = false;


    Trail* trail;         // ���� ��ƼŬ
    Transform* startEdge; // ������ ���۵� ������
    Transform* endEdge;   // ������ ���� ������

    bool trailToggle = false;
};