#pragma once

class Spark : public Particle
{
private:
    //스파크가 가져야 할 데이터의 내부집합 : 각 입자의 데이터
    struct VertexParticle // 각 스파크 입자의 정점
    {
        Float3 position = {}; // 벡터가 아닌 Float3 (DX, 혹은 셰이더 계산에 바로 쓴다)
        Float2 size = {};
        Float3 velocity = {};
    };

public:
    Spark(wstring imageFile, bool isAdditive = false);
                             // Additive : 컴퓨터에서 그림을 그리는 방식 중 하나
                             //            배경 화소 위에 이미지 화소의 색을 "더해서" 렌더
                             //            -> 대략 이미지가 밝아지면서 반투명해지는 효과가 나온다
    ~Spark();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos);

private:
    void Create();
    void UpdateParticle();

private:

    float minRadius = 5;  //최소 반경
    float maxRadius = 10; //최대 반경

    float minSize = 0.1f; //최소 크기
    float maxSize = 1.0f; //최대 크기

    FloatValueBuffer* buffer;
    ColorBuffer* startColorBuffer; //시작시 색깔
    ColorBuffer* endColorBuffer;   //종료시 색깔

    // -> 파티클로 만들어지는 대상들의 특징 : 옵션이 하나로 정해지지 않고 범위 내에서 랜덤으로
    //                                     취급되는 경우가 많다

    VertexUV vertex; //계산에 사용할 임시 데이터가 들어갈 정점

    vector<VertexParticle> vertices; //이 클래스가 가질 정점들
};

