#include "Framework.h"

Trail::Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed)
    : start(start), end(end), width(width), speed(speed)
{
    material->SetShader(L"Basic/Texture.hlsl"); // 기본만 읽어도 텍스처는 돌아간다
                                                // ->빌보드 옵션 등을 활용할 수는 없다 (파티클 셰이더의)
                                                //   -> 이 클래스에서는 어차피 안 쓰는 건데...

    material->SetDiffuseMap(imageFile); //디퓨즈맵

    //메쉬 만들기
    CreateMesh();

    //출력상태 설정
    FOR(2) rasterizerState[i] = new RasterizerState();
    FOR(2) blendState[i] = new BlendState();

    rasterizerState[1]->CullMode(D3D11_CULL_NONE); // 앞이든, 뒤든 모두 출력하기
    //blendState[1]->Alpha(true); // 투명색 지정
    blendState[1]->Additive();

}

Trail::~Trail()
{
    delete mesh;

    FOR(2) delete rasterizerState[i];
    FOR(2) delete blendState[i];

    // start, end는 다른 곳에서 만든 것을 받으므로, 여기서는 삭제 안 함
}

void Trail::Update()
{
    //if (!Active()) return; // <- 비활성화시 업데이트 안 함
    // 위 코드를 끄면 궤적이 안 보이는 중이더라도 항상 정점 갱신을 진행할 것
    // -> 최적화 문제 발생하지만, 궤적이 항상 모델과 일치하는 효과를 얻을 수 있다

    //정점 갱신 (메쉬에서 여기 함수로)
    vector<VertexUV>& vertices = mesh->GetVertices();

    //각 정점의 위치(pos) 재구성
    for (UINT i = 0; i <= width; ++i)
    {
        //시작, 끝 정점의 현재 값 구하기
        Vector3 startPos = vertices[i * 2 + 0].pos;
        Vector3 endPos   = vertices[i * 2 + 1].pos;

        //두 정점이 가야 할 곳 준비하기
        Vector3 startDestPos;
        Vector3 endDestPos;

        if (i == 0) // 이미지 제일 왼쪽일 때
        {
            startDestPos = start->GlobalPos(); // 지정된 위치 그 자체
            endDestPos = end->GlobalPos();
        }
        else //이미지가 다음 구간 중 어딘가일 때
        {
            startDestPos = vertices[(i - 1) * 2 + 0].pos; // 내 왼쪽 정점의 위치
                                                          // =나보다 먼저 가는 놈이
                                                          //  방금까지 있었던 곳
            endDestPos   = vertices[(i - 1) * 2 + 1].pos;
        }

        // 도출된 목적지와 지금 내 위치를 시간 경과(+속도)에 따라 보간 수행
        startPos = Lerp(startPos, startDestPos, speed * DELTA);
        endPos   = Lerp(endPos, endDestPos, speed * DELTA);

        //수행된 결과 정점에 피드백
        vertices[i * 2 + 0].pos = startPos;
        vertices[i * 2 + 1].pos = endPos;
    }
    // 이렇게 반복문을 돌리면
    // 1. 제일 왼쪽 정점들은 지정된 시작, 끝 트랜스폼을 따라갈 것이다
    // 2. 그 다음 정점들은 모두 자기보다 한 칸 왼쪽 정점이 방금까지 있었던 곳을 따라갈 것이다
    
    // -> 이 과정이 반복되면 줄줄이 이어지는 궤적이 그려질 것이다. Profit!!!

    mesh->UpdateVertex(); // 메쉬에 바뀐 정점 데이터를 업데이트

}

void Trail::Render()
{
    if (!Active()) return;

    // 메쉬는 있어도 별도의 메쉬 포함 클래스(=큐브, 쿼드 등)가 없어서
    // 해당 정점 개체의 렌더 과정을 다시 직접 거쳐야 한다

    worldBuffer->SetVS(0); // 정점이 가져야 할(트랜스폼이 가져야 할) 공간의 정보를
                           // 정점 셰이더에서 세팅한다 (가장 기본 순위로)

    // 설정된 공간 안에서 보여야 할 이미지 데이터를 세팅
    material->Set();

    // 출력준비 (상태 설정)
    rasterizerState[1]->SetState();
    blendState[1]->SetState();

    // 메쉬를 그리기 (본론)
    mesh->Draw(); // Draw 밑에 DrawInstanced는 외부 데이터를 빌려와서 그릴 때 사용

    // 상태 원상복구
    rasterizerState[0]->SetState();
    blendState[0]->SetState();

    // 위 과정으로 트랜스폼으로 설정된 개별 공간 속, 정점을 가진 이미지 데이터가 출력
}

void Trail::CreateMesh()
{
    mesh = new Mesh<VertexUV>(); // 아직 형태가 없는 메쉬 준비하기

    vector<VertexUV>& vertices = mesh->GetVertices(); // 벡터 받아오기

    vertices.reserve((width + 1) * 2); // + 1 : 이미지 픽셀의 시작과 끝을 모두 포함하기 위함
                                       // * 2 : 각 이펙트 구간별 시작점과 끝점을 넣기 위함

    for (UINT i = 0; i <= width; ++i) // width에 i가 도달해도 마지막 한 번 더 진행
    {
        //정점 준비 후 벡터에 넣기
        VertexUV vertex;

        vertex.uv = { (float)i / width, 0 }; // 잘린 구간을 u, 위를 v로 하는 UV로 지정 후
        vertices.push_back(vertex);          // 정점을 벡터에 추가

        vertex.uv = { (float)i / width, 1 }; // 잘린 구간을 u, 아래를 v로 하는 UV를 지정
        vertices.push_back(vertex);          // 바뀐 별개의 정점을 벡터에 또 추가

        // -> 이렇게 반복하면 픽셀의 가로 0부터 끝까지 구간 간격으로 반복하면서
        //    텍스처의 UV값을 벡터에 넣을 수 있게 된다 (반복문이 끝나면 그림 한 장)
    }

    // 인덱스 벡터 받기
    vector<UINT>& indices = mesh->GetIndices();
    indices.reserve(width * 6);

    for (int i = 0; i < width; ++i) // 가로 끝까지 안 가고 평범하게 i < width 조건 마무리
    {
        indices.push_back((i * 2) + 0); // 0 : 본래 인덱스
        indices.push_back((i * 2) + 2); // 2
        indices.push_back((i * 2) + 1); // 1

        indices.push_back((i * 2) + 1); // 1
        indices.push_back((i * 2) + 2); // 2
        indices.push_back((i * 2) + 3); // 3

        // 0 - 2 - 1, 1 - 2 - 3 : 뒷면 텍스처 그리기 조합
        // * 원래는 쓰면 안 되지만... 지금은 컬링 모드가 앞뒤 구분 없이 모두 출력이니까 가능
    }

    // 여기까지 오면 정점과, 정점 목록에 의한 렌더 준비 완료

    // 데이터를 메쉬에 대입
    mesh->CreateMesh();








}
