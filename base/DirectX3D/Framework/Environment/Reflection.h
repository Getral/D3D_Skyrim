#pragma once

class Reflection
{
    // 반사 클래스

public:
    Reflection(Transform* target); //target : 반사 대상x, 주체(="연산의 대상")
    ~Reflection();

    void Update();
    void SetReflection();

    void SetRender();
    void PostRender();

    void GUIRender();

private:
    Transform* target; //반사 연산의 대상

    //이미지 투사를 위한 데이터
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    //이미지 출력 상태 지정용 데이터 (필수x 보험으로 준비만)
    RasterizerState* rasterizerState[2];

    //반사할 자리를 캡처할 카메라
    Camera* camera;

    //본체 이미지
    class Quad* quad; //렌더 클래스라서 이쪽이 먼저 읽혀야 하지만,
                      //쿼드도 필수라서 부득이 선행 선언
};

