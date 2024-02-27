#pragma once

class ParticleSystem
{
    // 파티클 시스템 (혹은 범용 파티클) 클래스
    // 그림 데이터를 쿼드로 받아서 옵션에 따라 사용하는 범용 클래스

    // -> 개별 파티클에 비해 느리지만, 원하는 옵션에 따른 파티클을 적용해서 쓸 수 있다

private:
    struct InstanceData // 파티클 내에서 생성된 개별 입자의 데이터
    {
        Matrix transform = XMMatrixIdentity();
    };

    struct ParticleData //파티클 자체의 데이터 = 전체의 옵션
    {
        // 일반적으로 파티클에 적용되는 다양한 옵션 중, 비교적 공통적으로 쓰이는 핵심 부분을 작성
        // 추가로 필요한 옵션이 있으면 여기서 작성


        bool isLoop = false; // 반복하는가?
        bool isAdditive = true; //혼합 투명인가?
        bool isBillboard = true; //빌보드 출력인가(카메라에 상관없이 정면이 무조건 보이는가?)
        UINT count = 100; //파티클의 허용 개수 혹은 파티클 내 입자 인스턴스의 개수 (기본은 후자)
        float duration = 1; //파티클=이펙트의 지속시간
        Vector3 minVelocity = { -1, -1, -1 }; // 최소 속력 기준 (혹은 방향 범위의 - 극)
        Vector3 maxVelocity = { +1, +1, +1 }; // 최대 속력 기준 (혹은 방향 범위의 + 극)
        Vector3 minAcceleration; //최소 가속력 (혹은 속도의 변화량)
        Vector3 maxAcceleration; //최대 가속력 (혹은 속도의 변화량)
        Vector3 minStartScale = { 1, 1, 1 }; // 파티클 생성 시 최소 크기
        Vector3 maxStartScale = { 1, 1, 1 }; // 파티클 생성 시 최대 크기
        Vector3 minEndScale = { 1, 1, 1 }; // 파티클 종료 시 최소 크기
        Vector3 maxEndScale = { 1, 1, 1 }; // 파티클 종료 시 최대 크기
        float minSpeed = 1; //최소 입자 이동 속력 (혹은 속력의 계산 계수)
        float maxSpeed = 3; //최대 입자 이동 속력 (혹은 속력의 계산 계수)
        float minAngularVelocity = -10.0f; //최소 각도 수정량
        float maxAngularVelocity = +10.0f; //최대 각도 수정량
        float minStartTime = 0; //최소 지연 시작 시간
        float maxStartTime = 0; //최대 지연 시작 시간
        Float4 startColor = { 1, 1, 1, 1 }; //시작 시 출력할 색상 범위(혹은 색상 보정)
        Float4 endColor = { 1, 1, 1, 1 }; //종료 시 출력할 색상 범위(혹은 색상 보정)

        // -> 물리 현상, 셰이더 연산 등을 고려하지 않고 의도 가능한 최소한의 옵션을 작성
        // -> 위 옵션의 범위에서 각 입자가 만들어질 때 랜덤으로 옵션을 결정
    };

    //...그렇게 위에서 만들어진 각 입자의 (혹은 파티클 전체 평균의)
    // 실제 생성 정보를 확인하기 위한 구조체
    struct ParticleInfo
    {
        Transform transform; // 각 입자 혹은 전체 중심의 트랜스폼
        Vector3 velocity; //위 데이터에서 랜덤으로 나온 속력 기준 (=방향, 기준속도)
        Vector3 acceleration; // 위 데이터에서 랜덤으로 나온 가속력
        Vector3 startScale; //...시작시 크기
        Vector3 endScale;   //...종료시 크기

        //기본값 있는 소수들 (위는 생성만 하면 기본값은 있으니까)
        float speed = 1;
        float angularVelocity = 0;
        float startTime = 0;

        // -> 만들어진 뒤의 옵션 확인 혹은 (필요하면) 변경 등에 쓰인다
        // 각 입자가 대상이면 -> 입자 하나하나를 제어하는 역할
        // 평균이 대상이면 -> 파티클 전체를 대변하는 역할
    
        //우선은 이 구조체를 각 입자의 정보로 활용
    };

public:
    ParticleSystem(string file);  // 사전 설정이든, 이미지 직접 로딩이든,
    ParticleSystem(wstring file); // 이미지 없이 파티클이 존재할 수는 없다.
    ~ParticleSystem();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos, Vector3 rot = Vector3()); // 파티클을 재생할 장소와, 회전정보
                                    // 회전정보가 필요한 이유 = 빌보드가 아닐 수도 있어서
                                    // 매개변수 기본이 {0,0,0}인 이유 = 빌보드가 기본이라서

    void Stop(); // 단독 클래스라서 멈추는 것도 함수가 따로 필요하다

    bool IsActive() { return quad->Active(); } //쿼드의 활성화 여부에서 파티클의 활성화를 판단

private:
    void UpdatePhysical(); // 물리적 대상 = 정점 등을 업데이트
    void UpdateColor();    // 색상 업데이트
    void Init();           // 기능의 시작

    void LoadData(string file);  // C++에 의한 파일 읽기
                                 // : 텍스트 읽기 클래스로 사전 설정된 파일 읽기 (있다 치고)
    void LoadData(wstring file); // 윈도우에 의한 파일 읽기
                                 // : 이미지 리소스를 직접 읽기

private:
    //파티클에 필요한 것

    // 가장 먼저 : 이미지 그 자체
    Quad* quad; // 왜 이미지를 따로 받는가? -> 빌보드가 아닐 수도 있어서 (정점 렌더가 필요)
                // = 지오메트리 셰이더는 쓰지 않는다

    // 파티클 내 인스턴스의 벡터와 정보
    vector<InstanceData> instances; // 인스턴스들
    vector<ParticleInfo> particleInfo; // 만들어진 각 인스턴스의 개별 값

    // 인스턴스의 행렬 정보를 정점으로서 관리하기 위한 버퍼
    VertexBuffer* instanceBuffer; // 버퍼가 빠질 수는 없다

    ParticleData data; //이 파티클의 본래의 옵션(과 그 범위)

    // 파티클의 공통 변수
    float lifeSpan = 0; //입자들의 생애 주기 (지속시간의 다른 표현)
    UINT drawCount = 0; //드로우 콜 횟수
    UINT particleCount = 100; // 파티클 내 입자 개수

    //이미지 출력용....
    BlendState* blendState[2];        //이미지 혼합용(다른 렌더 이미지와 병용하기 위함)
    DepthStencilState* depthState[2]; //이미지 선별용(겹치기 등의 상황에서 이미지 제어를 위함)

};

