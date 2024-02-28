#pragma once

//���� �н��� ���� ���� ������ �ϴ��� �׳� �ִϸ����ͷ�

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

    Transform* mainHand; //�ַ� ���� ��, �������� ��� ������
    
    SphereCollider* tmpCollider; //�ӽ� �浹ü
    
    Model* kunai; // <-���� ���������� ���� �� ���

    State curState = IDLE;

    float moveSpeed = 500;
    float rotSpeed = 1;
    float deceleration = 5; //����

    Vector3 velocity;
    Vector3 targetPos;

    bool isTarget;

    POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT >> 1 }; //<- �����ڴ� ����

    Quad* crosshair;
    Quad* compass;

    vector<Quad*> CompassDir;

    Quad* quest;
    Quad* quest2;
    Quad* quest3;
    Quad* quest4;

    float questf;
    float questf2;
    float questf3;
    float questf4;

    float tmp;
    float tmp2;
    float tmp3;
    float tmp4;

    float compass_degree;
    bool isRot = true;
};
