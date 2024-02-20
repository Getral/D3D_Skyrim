#pragma once

// 로봇 캐릭터 : 모델은 인스턴싱 기준
//              씬에서 인스턴싱으로 만든 모델을 주고 여러 대 호출하고 표적을 주면 움직일 것

class Robot
{
private:
    enum State
    {
        STAND_UP,
        WALK,
        RUN,
        HIT,
        DYING
    };

public:
    // Robot(); // 기본 형태
    Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Robot();

    //씬 출력
    void Update();
    void Render();
    void PostRender();

    //액션 : 얻어맞기
    void Hit();

    //액션 : 생성되기
    void Spawn(Vector3 pos);

    //표적 설정
    void SetTarget(Transform* target);

    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

private:
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    void EndStandUp();
    void EndHit();
    void EndDying();

    void SetState(State state);

    void Move();
    void UpdateUI(); //캐릭터 UI가 있으면 이후 업데이트


private:

    Transform* transform;
    CapsuleCollider* collider;

    // TODO : 모델, 혹은 모델의 인스턴싱
    //        개별 모션 저장용

    // 샘플 : 인스턴싱
    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    Transform* target;

    float speed = 50; //속력 : 기본 스탯
    float maxHP = 100;
    float curHP = 100;

    Vector3 velocity; //속력 : 실제 움직임

    UINT index; //로봇의 개별 인덱스 (인스턴싱이 있다면 이걸로 서로 구분 가능)
    State curState = STAND_UP;

    //스테이트 혹은 움직임에 따른 이벤트 지정
    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;

    ProgressBar* hpBar;
    Vector3 barPos; //체력바가 위치할 곳
};

