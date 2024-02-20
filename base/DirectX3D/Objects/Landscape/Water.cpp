#include "Framework.h"

Water::Water(wstring normalFile, float width, float height)
    : size(width, height)
{
    SetTag("Water");
    material->SetShader(L"Environment/Water.hlsl");

    // 일렁임과 반사 만들기
    reflection = new Reflection(this); // 지금 만든 물(=나) 자신을 연산의 대상, 반사의 주체로
    refraction = new Refraction(normalFile);

    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true);

    mesh = new Mesh<VertexUV>();
    MakeMesh();
    mesh->CreateMesh();
}

Water::~Water()
{
    FOR(2) delete blendState[i];

    delete reflection;
    delete refraction;

    delete mesh;
}

void Water::Update()
{
    refraction->Update();
    reflection->Update();

    UpdateWorld(); //나 자신도 업데이트
}

void Water::Render()
{
    SetRender();

    reflection->SetRender();
    refraction->SetRender();

    //혼합투명 상태 적용 후 실제 렌더
    blendState[1]->SetState();
    mesh->Draw();

    blendState[0]->SetState(); //원상복구
}

void Water::GUIRender()
{
    Transform::GUIRender();
    refraction->GUIRender(); // 물결 옵션 출력하고 활용
}

void Water::SetRefraction()
{
    refraction->SetRefraction();
}

void Water::SetReflection()
{
    reflection->SetReflection();
}

void Water::MakeMesh()
{
    // 우선 물의 화면효과를 보기 위해, 메쉬는 쿼드로 단순화해서 구현

    float left = -size.x * 0.5f;
    float right = size.x * 0.5f;
    float top = size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    //정점 데이터
    vector<VertexUV>& vertices = mesh->GetVertices();

    vertices.emplace_back(left, 0, top, 0, 0); // x, y, z, u, v 순으로 축값 넣기
    vertices.emplace_back(right, 0, top, 1, 0);
    vertices.emplace_back(left, 0, bottom, 0, 1);
    vertices.emplace_back(right, 0, bottom, 1, 1);

    //정점 인덱스
    vector<UINT>& indices = mesh->GetIndices();
    indices = {
        0, 1, 2, 2, 1, 3 //=쿼드
    };
}
