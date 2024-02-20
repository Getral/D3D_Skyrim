#pragma once

//여러 분신이 있을 수도 있지만 일단은 그냥 애니메이터로

class Naruto : public ModelAnimator
{
private:
    enum State
    {
        IDLE, RUN_F, RUN_B, RUN_L, RUN_R, THROW, PUNCH
    };

public:
    Naruto();
    ~Naruto();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

private:
    void Control();
    void Move();
    void Rotate();
    void Attack();
    void SetAnimation();

    void SetState(State state);

    void Throw();
    void EndThrow();

private:

    Transform* mainHand; //주로 쓰는 손, 나루토의 경우 오른손
    
    SphereCollider* tmpCollider; //임시 충돌체
    
    Model* kunai; // <-별도 아이템으로 제작 후 사용

    State curState = IDLE;

    float moveSpeed = 500;
    float rotSpeed = 1;
    float deceleration = 5; //감속

    Vector3 velocity;
    Vector3 targetPos;

    bool isTarget;

    POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT >> 1 }; //<- 연산자는 샘플

    Quad* crosshair;
};

