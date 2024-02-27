#pragma once
class BillboardScene : public Scene
{
    //빌보드 : 간판, 특히 거리에 크게 세워두는 간판
    //        프로그래밍에서는 언제나 100% 출력되는 이미지 UI를 지칭 (2D)
    //        혹은 카메라의 방향, 위치에 상관없이 정면을 확인 가능한 이미지 출력을 지칭(3D)

private:
    UINT COUNT = 100;

public:
    BillboardScene();
    ~BillboardScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    vector<Quad*> trees; //예시 이미지 = 나무

    // 빌보드 구현을 위한 방법
    // A : 벡터를 이용한 방향 제어 : 단순, 평면 표현 외에 완전한 고정이나 각도제어 등은 힘들다
    // B : 카메라와 방향 동기화    : 보이는 건 안정적, 카메라에 의존한다
    // C : 캔버싱                 : 표현의 결과가 안정적, 실제 월드와 투사 결과 위치가 꼭 같진 않다
    //                          //허공에 나무가 떠 있거나.. 나무가 있는 곳에 가도 거기에 실체가 있다는 보장은 없다
    //                          //순수하게 보이는 것만이 목적일 때 쓰면 좋다
    // 
    // D : 지오메트리(모형) 셰이더를 활용한 실시간 렌더링 : 빠르다. 안정적. 단점은 C와 같다 (실체가 없다)

    // C 방법을 위한 추가 변수
    vector<Transform*> origins; //나무 위치의 원점을 기록한 벡터
    BlendState* blendState[2];

    // D 방법을 위한 추가 변수

    // 지오메트리 셰이더를 변수로 선언하기
    GeometryShader* geometryShader; // DX의 G셰이더를 편하게 쓰기 위한 객체
                                    // *DX 제공 기능들은 마이크로소프트 학습 페이지에서 검색 가능

    Material* material; // 셰이더에 맞추기 위한 별도의 매티리얼
    VertexBuffer* vertexBuffer; //정점 버퍼들 (사각형 모형과는 별개)

    //그림 데이터를 "다른 곳"에 투사하기 위한 준비
    DepthStencilState* depthState[2]; //깊이 스테이트 2개
    vector<VertexUV> vertices; //정점 벡터 (텍스처 정보 빼기 + 버퍼에 넣기 위한 데이터의 원본)

    // -> 매티리얼을 스테이트에서 준비 -> 버퍼와 셰이더에 접근 -> 그대로 출력
};

