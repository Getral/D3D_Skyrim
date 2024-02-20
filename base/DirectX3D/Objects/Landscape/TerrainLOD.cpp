#include "Framework.h"
#include "TerrainLOD.h"

TerrainLOD::TerrainLOD(wstring heightFile)
{
    //매티리얼 세팅
    material->SetShader(L"TS/TerrainLOD.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    //셰이더 준비
    hullShader = Shader::AddHS(L"TS/TerrainLOD.hlsl");
    domainShader = Shader::AddDS(L"TS/TerrainLOD.hlsl");

    //높이 맵 준비
    heightMap = Texture::Add(heightFile);

    //버퍼준비
    terrainBuffer = new FloatValueBuffer();
    heightBuffer = new FloatValueBuffer();

    //버퍼에 미리 의미를 가진 수치를 넣어주기
    // -> 지형버퍼에는 LOD 선별을 할 거리를 넣기
    // -> + 같은 버퍼에 LOD에 의한 묘사 수준 차이 설정하기 
    // -> 높이 (재구성) 버퍼에는 상수를 넣기

    terrainBuffer->Get()[0] = 1.0f;        // 선별거리 최소 (여기서 세부묘사 최대)
    terrainBuffer->Get()[1] = 1000.0f;     // 선별거리 최대 (여기서 세부묘사 최소)

    terrainBuffer->Get()[2] = 1.0f;        // 묘사 단위 최소 (여기서 묘사 수 최대)
    terrainBuffer->Get()[3] = 64.0f;       // 묘사 단위 최대 (여기서 묘사 수 최소)

    heightBuffer->Get()[0] = 20.0f;        // 상수

    // * 위 설정은 실제 현실적인 수준은 절대 아닙니다. (어디까지나 이해를 돕기 위한 직관적 설정)
    // -> 이 설정대로면 LOD 계산은 정확히 카메라 바로 앞에서부터 시작된다 (지형의 99%가 생략 연산 거침)
    //    그리고 거리가 1000만 되어도 묘사 수준은 최소 수준
    // -> 세부묘사가 최소 1/64까지 : 사양이 높다기에도 애매, 낮다기에도 애매
    //    = 정점이 형태가 달라지는 것을 시각화해서 강의 중에 보고 쉽게 알아보는 것이 목적

    // 메쉬 만들기
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

TerrainLOD::~TerrainLOD()
{
    delete terrainBuffer;
    delete heightBuffer;

    delete mesh;
    
}

void TerrainLOD::Render()
{
    //게임오브젝트의 공간 버퍼 세팅 (업데이트월드)
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    //지형의 값을 셰이더에 넣고 계산을 준비하기
    terrainBuffer->SetHS(10); // 헐 셰이더에서 정점 일부 연산 분담해서 진행
    heightBuffer->SetDS(10); // 도메인 셰이더로 정점 출력 시에 높이 계산 분담

    heightMap->DSSet(); // 텍스처는 텍스처가 분담해야 할 조건문 등은 따로 없음

    //렌더 준비
    material->Set();
    hullShader->Set();
    domainShader->Set();

    //그리기 (영역 단위)
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
            //출력 옵션 : 규칙적 원형, 코드로 설정된 4개의 정점을 갖는 영역의 목록을 따름

    //모니터에 셰이더를 적용하면서 출력
    DC->HSSetShader(nullptr, nullptr, 0); // 연산
    DC->DSSetShader(nullptr, nullptr, 0); // 출력
}

void TerrainLOD::GUIRender()
{
    //씬 내 옵션
    ImGui::Text("Terrain LOD Option");
    ImGui::DragFloat("MinDistance", &terrainBuffer->Get()[0]);
    ImGui::DragFloat("MaxDistance", &terrainBuffer->Get()[1]);
    ImGui::DragFloat("MinQuality", &terrainBuffer->Get()[2]);
    ImGui::DragFloat("MaxQuality", &terrainBuffer->Get()[3]);
    ImGui::DragFloat("Height", &heightBuffer->Get()[0]);

    GameObject::GUIRender();
    ImGui::Text("width : %d", width);
    ImGui::Text("height : %d", height);
}

void TerrainLOD::MakeMesh()
{
    // 기본 메쉬 (전체 크기와 바탕 설정)

    // 전체 지형의 크기
    width = heightMap->GetSize().x;
    height = heightMap->GetSize().y;

    // 전체 크기에서 호출되는 셀 UV 지정
    // + 이 과정에서 셀의 형태도 지정이나 추측 가능

    cellUV = { 1.0f / width, 1.0f / height };
            // 가장 단순한 정점단위당 UV : 텍스처를 가로 세로로 쪼갠 수만큼
            // -> 위 식에서 추측 가능한 셀의 형태 : 렉트

    // 한 영역당 가지게 될 가로, 세로도 계산
    // -> 현재는 셀 = 직사각형이므로, 영역도 직사각형으로
    patchWidth = ((width - 1) / cellsPerPatch) + 1;
    patchHeight = ((height - 1) / cellsPerPatch) + 1;
                // 위 두 식의 의미 : 한 영역은 cellsPerPatch만큼 잘린 직사각형이고
                // 따라서 한 영역 안에는 cell 만큼의 텍스처 픽셀이 들어갈 것

    // 이렇게 만든 바탕 설정....을 토대로 메쉬를 만들기

    //정점 데이터
    vector<VertexType>& vertices = mesh->GetVertices();
    vertices.resize(patchWidth * patchHeight); // 영역 수에 의해 정점 초기화

    //정점 탐색 진행용 변수 만들기
    float halfWidth = width * cellSpacing * 0.5f; //가로에 간격을 곱하고 반으로 나눈 것
    float halfHeight = height * cellSpacing * 0.5f;

    // 임시 가로, 세로 만들기
    float tempWidth = width * cellSpacing / patchWidth; // 전체크기 ÷ 영역에 대응하는 기준값
    float tempHeight = height * cellSpacing / patchHeight;

    // 각 단위 내에서 참조해야 할 텍스처 UV의 단위값
    float du = 1.0f / patchWidth; // float임을 확실히 하기 위해서 1.0f를 다 적어주면 좋다
    float dv = 1.0f / patchHeight;

    //영역별 단위를 돌아가면서 정점 정보 내기
    for (UINT z = 0; z < patchHeight; ++z)
    {
        float tempZ = halfHeight - z * tempHeight; // 현재 봐야 할 z 좌표 내기
        for (UINT x = 0; x < patchWidth; ++x)
        {
            float tempX = -halfHeight + x * tempWidth; // 현재 봐야 할 x 좌표 내기

            //현재 봐야 할 정점의 인덱스를 보기
            UINT index = patchWidth * z + x; //그냥 텍스처/영역에 따른 x, z 좌표

            //위 식에서 생기는, index에 쓰이는 x,z와 tempX, tempZ가
            // 반복문 수행 시마다 동일하지 않게 바뀌는 것을 이용해서

            // 정점의 인덱스(꾸준히 올라가는 데이터)에, 변동성 있는 temp좌표를 지정
            vertices[index].pos = { tempX, 0, tempZ }; // 인덱스는 반복문 수행 시마다 무조건 +1
            vertices[index].uv = { x * du, z * dv };   // 그러나 temp는 다를 수도 있다...
        }

    }

    // 여기까지 오면 정점 정보는 내었다
    // -> 출력용 정점 인덱스 필요

    vector<UINT>& indices = mesh->GetIndices();
    indices.reserve((patchWidth - 1)* (patchHeight - 1) * 4); // 

    for (UINT z = 0; z < patchHeight - 1; ++z)
    {
        for (UINT x = 0; x < patchWidth - 1; ++x)
        {
            // 직사각형을 구성할 수 있는 정점 4개 1세트

            indices.push_back(patchWidth * (z + 0) + (x + 0)); // 0
            indices.push_back(patchWidth * (z + 0) + (x + 1)); // 1
            indices.push_back(patchWidth * (z + 1) + (x + 0)); // 2
            indices.push_back(patchWidth * (z + 1) + (x + 1)); // 3
        }
    }

}
