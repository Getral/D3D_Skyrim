#pragma once

class Particle
{
    // 파티클 : 같은 텍스처 여러 장, 혹은 쪼개진 여러 부분을 이용해
    //          특수한 그래픽 효과를 재현하기 위한 도구 (스파크, 불, 날씨 등)

    // -> 작게 만들어진 입자 표현 여러 개를 동시에 쓴다는 특징
    //    + 많은 경우 랜덤으로 효과의 재생을 만들어낸다(무작위)는 특성도 있다

    // 더불어 이 파티클 클래스는 개별 특수 파티클 효과를 위한 범용 인터페이스이다
    // = 진짜 범용 파티클 아님, 스파크나 불 같은 구체적인 파티클 아님

protected: //이 클래스를 상속받아야 할 진짜 개별 파티클이 있으므로 여기선 상속 접근으로

    UINT MAX_COUNT = 1000; // 파티클이 앱에서 허용될 최대 입자 개수

public:
    Particle();
    ~Particle();

    // 상속을 전제로 한 부모 함수 (virtual은 쓰는데 가상함수는 아님)
    virtual void Update() {}
    virtual void Render();          // 별도 작성 없으면 부모의 함수가 실행은 되게
    virtual void GUIRender() {}

    virtual void Play(Vector3 pos); // 별도 작성 없으면 부모의 함수가 실행은 되게
    void Stop();                    // 멈춤 기능은 부모를 기본으로

protected:
    bool isActive = false; // 트랜스폼이 없어서 활성화 여부는 따로 지정
    UINT particleCount = 0; // 생성시 입자는 없음
    Vector3 position;       // 재생위치

    Material* material;
    VertexBuffer* vertexBuffer;

    GeometryShader* geometryShader; // 지오메트리 셰이더로 직접 점에 그림 그리기

    //그림 그리기용 출력상태설정
    BlendState* blendState[2];
    DepthStencilState* depthState[2];

};

