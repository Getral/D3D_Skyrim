#pragma once

class Trail : public GameObject
{
    // 궤적 파티클 : 파티클의 일종, 실제로는 다른 파티클과 같은 프로그램 범주에 들어가지 않는다
    //              다른 파티클이 그림을 랜덤한 데이터에 의해서 순차 재생하는 것과 다르게
    //              궤적은 정해진 데이터(이미지)를 정해진 규칙에 따라서 부분 순차 재생을 하기 때문

public:
    Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed);
    ~Trail();

    void Update();
    void Render();

private:
    void CreateMesh(); // 만들어진 이미지를 위한 메쉬가 필요해서

private:
    Mesh<VertexUV>* mesh; // 궤적의 (기본) 형태)

    Transform* start; //궤적이 시작되는 곳
    Transform* end;   //궤적이 끝나는 곳
    //Transform* offset, * origin; // 궤적의 중간 경유 연산지가 들어갈 수 있지만 여기서는 생략

    UINT width; //궤적에 들어가는 단위 파티클의 그림 내 이미지 가로 크기
    float speed; //궤적의 진행, 재생 속도

    // 이미지 출력을 위한 상태 설정
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];

};

