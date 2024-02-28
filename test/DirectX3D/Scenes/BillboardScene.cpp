#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
    //A, B, C 방법으로 빌보드 구현
    //trees.reserve(COUNT);
    //
    //FOR(COUNT)
    //{
    //    //기준 크기 벡터2로 만들기
    //    Vector2 size;
    //    size.x = Random(2.0f, 10.0f);
    //    size.y = Random(2.0f, 10.0f);
    //
    //    Quad* tree = new Quad(size); // 도출된 크기로 흰 사각형부터 만들기
    //    tree->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //디퓨즈맵 입히기
    //    
    //    //위치 랜덤으로 바꾸기
    //    tree->Pos().x = Random(0.0f, 50.0f);
    //    tree->Pos().z = Random(0.0f, 50.0f);
    //    tree->Pos().y = 0;
    //
    //    trees.push_back(tree);
    //
    //    //캔버싱용 트랜스폼과 벡터 준비
    //    Transform* transform = new Transform();
    //    transform->Pos() = tree->Pos();
    //    origins.push_back(transform);
    //}
    //FOR(2) blendState[i] = new BlendState();
    //blendState[1]->AlphaToCoverage(true);

    // D : 지오메트리 셰이더를 활용한 빌보드 구현의 생성자

    //그림 데이터를 처음부터 설정한다
    //material = new Material(L"Basic/Texture.hlsl"); // 텍스처 자체의 출력을 의도한 기본 셰이더
    material = new Material(L"Geometry/Billboard.hlsl"); //빛의 방향을 연산하지 않고 색을 완전히 출력하는 맞춤 셰이더
    material->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //나무

    //그 다음 지오메트리 셰이더 세팅
    geometryShader = Shader::AddGS(L"Geometry/Billboard.hlsl"); // 빌보드로 모형 셰이더 준비

    //* 개별 사각형(쿼드) 만들지 않음

    //사각형 대신 위에서 만든 매티리얼 데이터를 그대로 쓰기 위한 기준 위치를 구한다
    //그 위치를 정점으로 취급 (어차피 컴퓨터 입장에서는 이름이야 어쨌든 똑같은 벡터+UV)

    vertices.resize(COUNT);
    FOR(COUNT)
    {
        //여기서는 기준점
        vertices[i].pos.x = Random(0.0f, 30.0f);
        vertices[i].pos.z = Random(0.0f, 30.0f);
        vertices[i].pos.y = 0;

        //여기서는 그림의 크기
        vertices[i].uv.x = Random(1.0f, 10.0f);
        vertices[i].uv.y = Random(1.0f, 10.0f);
    }
    //위에서 만든 정점 벡터를 원본으로 한 버퍼
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), COUNT);

    //출력상태 설정
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();
    
    // 혼합 스테이트의 투명색 옵션
    //blendState[1]->Alpha(true); //이미지 내에 설정된 투명색이 있으면 알파 적용
    blendState[1]->AlphaToCoverage(true); //투명색 적용 + 배경색 처리가 있으면 역시 적용

    // 뎁스 스테이트의 마스크 옵션
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);  // 다 가리기
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // 안 가리기
}

BillboardScene::~BillboardScene()
{
    for (Quad* tree : trees)
        delete tree;

    for (Transform* origin : origins)
        delete origin;

    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];

    delete material;
    delete vertexBuffer;
}

void BillboardScene::Update()
{
    //이미지를 빌보드로 적용하는 방법

    //....중에서, 직접 제어 방법

    //벡터를 이용한 텍스처 방향 제어
    //for (Quad* tree : trees)
    //{
    //    //아무튼 텍스처가 카메라만 보면 그만
    //    Vector3 dir = tree->Pos() - CAM->Pos(); //카메라가 나무를 보게 만들고
    //    tree->Rot().y = atan2(dir.x, dir.z); //나무에 역탄젠트 적용. 평면상의 xy = DX벡터의 xz
    //    tree->UpdateWorld(); //방향이 바뀐 나무의 사각형 정점 업데이트
    //}

    ////텍스처와 카메라 방향 동기화
    //for (Quad* tree : trees)
    //{
    //    tree->Rot().x = CAM->Rot().x;
    //    tree->Rot().y = CAM->Rot().y;
    //    tree->UpdateWorld();
    //}

    //캔버싱
    //for (Quad* tree : trees)
    //{
    //    //나무와 순번이 일치하는 트랜스폼(원점) 찾기
    //    int index = find(trees.begin(), trees.end(), tree) - trees.begin();
    //    //find : 벡터 내장 함수. 매개변수로 찾을 범위와 대상을 주면 대상 위치를 가진 반복자 반환
    //    //반복자 계산 특징 : 반복자끼리는 숫자처럼 계산 가능. 반복자 자신은 누적 가능 (iter++)
    //    // -> find의 결과에 벡터의 begin()을 빼면 마치 순번에서 0을 뺀 것처럼 숫자 도출 가능
    //    Transform* point = origins.at(index); //나무의 본래 위치가 기록된 트랜스폼
    //
    //    Vector3 pos = point->Pos();
    //    tree->Pos() = CAM->WorldToScreen(pos);
    //    float scale = 100 / (tree->Pos() - CAM->Pos()).Length();
    //    scale = Clamp(10.0f, 10.0f, scale);
    //    tree->Scale() = { scale, scale, scale };
    //    tree->UpdateWorld();
    //}
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
    //for (Quad* tree : trees)
    //    tree->Render();

    // (배경 출력에 적용했던 것처럼) 이미지를 월드상에서 각각 출력

    // 배경색 + 투명색 + 마스크 옵션 적용 상태 설정
    blendState[1]->SetState();
    depthState[1]->SetState();

    //vertexBuffer->Set(); // 기본 출력대기 함수
    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
    // D3D_PRIMITIVE_TOPOLOGY_POINTLIST : DX에서 주는 모형 출력의 기준 옵션 중 하나
    //                                    TRIANGULARLIST = 점 3개를 모아 삼각형 면을 출력
    //                                    LINELIST = 점 2개를 모아 선을 출력
    //                                    POINTLIST = 점 하나에 설정된 시각 데이터를 전부 출력
    //                                    -> 연산량 증가, 데이터량 감소

    //위 버퍼에, 정해진 방식으로, 그려야 할 시각 데이터=매티리얼을 준비
    material->Set();

    //준비된 시각 데이터를 출력할 (데이터에 접근할) 셰이더를 준비
    geometryShader->Set();

    //여기까지 준비된 버퍼+매티리얼+셰이더를 그대로 그래픽 연산(그리기)
    DC->Draw(COUNT, 0); // 매개변수는 "얼마나, (버퍼 정점의) 어디부터"

    //셰이더 설정 직후 출력까지
    DC->GSSetShader(nullptr, nullptr, 0); //매개변수의 의미
                                          // 첫 nullptr : 수동으로(추가) 출력 대기시킬 픽셀, 없음.
                                          // 다음 nullptr : 추가로 연속해서 출력할 다른 객체 없음.
                                          // 0 : 연결된 클래스의 인스턴스 개수
                                          // == "지금 호출로는 다른 지시할 게 더 없고,
                                          // 이 호출 전에 설정해둔 옵션대로 똑같이 출력하라"

    // 스테이트 원상복구
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void BillboardScene::PostRender()
{
    //blendState[1]->SetState();
    //for (Quad* tree : trees)
    //    tree->Render();
    //blendState[0]->SetState();
}

void BillboardScene::GUIRender()
{
}
