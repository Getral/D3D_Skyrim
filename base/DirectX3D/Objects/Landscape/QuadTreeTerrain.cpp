#include "Framework.h"

QuadTreeTerrain::QuadTreeTerrain(wstring heightFile)
{
    terrainData = new TerrainData(heightFile);
    width = terrainData->GetSize().x;
    height = terrainData->GetSize().y;

    //매티리얼 (디퓨즈맵) 할당
    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png"); //필요하면 매개변수로

    //지형 데이터에서 정리된 정점 받기
    vertices = terrainData->GetVertices(); 

    //정점과 삼각형 미리 준비
    UINT vertexCount = vertices.size();
    triangleCount = vertexCount / 3;

    float centerX = 0;
    float centerZ = 0;
    float size = 0;

    CalcMeshDimension(vertexCount, centerX, centerZ, size);

    root = new Node(); // 루트 노드 만들기
    CreateTreeNode(root, centerX, centerZ, size); //트리를 실제로 만들기
}

QuadTreeTerrain::~QuadTreeTerrain()
{
    DeleteNode(root); // 루트 밑에 있는 트리 데이터를 모두 지우고
    delete root; // 그 다음에 루트를 지워서 마무리
}

void QuadTreeTerrain::Render()
{
    // 노드를 렌더...하는 함수는 따로 있으니까 호출
    // 해당 함수를 비롯한 전체 렌더 과정만 간단히 호출

    drawCount = 0; //드로우 콜 횟수 초기화 (계산은 렌더 노드 중에 할 것)
    SetRender(); //게임오브젝트로서
    RenderNode(root); //루트부터 렌더 시작하기
}

void QuadTreeTerrain::GUIRender()
{
    ImGui::Text("Draw Count : %d", drawCount);

}

void QuadTreeTerrain::RenderNode(Node* node)
{
    // 노드의 중심 데이터 받기
    Vector3 center(node->x, 0, node->z);
    float radius = node->size * 0.5f;

    // 절두체 적용
    if (!CAM->ContainPoint(center, radius)) // 중심과 반경까지 절두체 검사를 해서
    {
        //절두체 안에 없으면
        return; //렌더 안함
    }

    UINT count = 0;
    FOR(4)
    {
        //자식 노드 유무 판별
        if (node->children[i])
        {
            count++;
            RenderNode(node->children[i]); // 재귀 수행
        }
    }

    if (count != 0)
    {
        return; //자식 노드로 쪼개진 노드였으면 렌더 더 이상 수행 안함
        //반대로 부모 노드를 독립수행시킬 분은 여기서 코드를 추가 작성
    }

    //여기까지 오면 자식 노드라고 가정하고, 해당 자식 노드로서의 렌더 수행
    node->mesh->Draw(); // 메쉬를 출력
    //노드가 갖고 있었던 삼각형 개수를 드로우콜 합산에 추가 (테스트용)
    drawCount += node->triangleCount;
}

void QuadTreeTerrain::DeleteNode(Node* node)
{
    FOR(4) //노드 밑에 있는 자식 수만큼 반복을 먼저
    {
        if (node->children[i]) // 노드 밑에 자식이 할당되어 있는 경우
        {
            DeleteNode(node->children[i]); // 해당 자식에게 재귀함수 실행을 먼저 하고
            delete node->children[i]; // 해당 자식의 메모리 할당을 해제
        }
    }

    // 먼저 자식이 있는 경우 자식부터 하나하나 추적하면서 삭제 내용을 선행

    // 더 자식이 없으면 자기 노드의 내부 데이터 삭제
    delete node->mesh; // 노드 구조체 안에 있었던 메쉬 데이터 삭제

    // * 지금은 소멸자용이지만 나중에 노드에 수동 편집이 이루어질 수 있다면
    //   이 함수를 다른 곳에서도 호출해야 할 수 있다 (노드 삭제니까)
}

void QuadTreeTerrain::CalcMeshDimension(UINT vertexCount, float& centerX, float& centerZ, float& size)
{
    //받은 정점만큼 반복문을 돌리면서 정점의 위치를 통해 중간값 내기
    FOR(vertexCount)
    {
        centerX += vertices[i].pos.x; // 위치의 x값 모조리 더하기
        centerZ += vertices[i].pos.z; // 위치의 z값 모조리 더하기
    }
    //개수로 나누어서 중간값 내기
    centerX /= (float)vertexCount;
    centerZ /= (float)vertexCount;

    // 검산 겸, 정점의 실제 위치를 재반영

    float maxX = 0;
    float maxZ = 0;

    FOR(vertexCount)
    {
        float width = abs(vertices[i].pos.x - centerX); // 정점값에 중간값을 뺀 결과를 받으면서
        float depth = abs(vertices[i].pos.z - centerZ); // 결과 확인 + 정점 실제 위치에서 도출되는
                                                        // 가로 세로를 다시 도출

        if (width > maxX) maxX = width; // 큰 쪽을 "max"값에 계속 갱신
        if (depth > maxZ) maxZ = depth;
    }

    // 여기까지 오면
    // 1. 센터값 구함
    // 2. 센터값이 적절한지 정점에 다시 빼면서 연산
    // 3. 2.의 결과로 최대 범위 구함
    // 4. 3.의 결과에서 가로 세로의 크기 범위까지 예측 가능

    // ......그래서 나온 4.의 결과를 size에 저장

    size = max(maxX, maxZ) * 2;
            // 현재 지형의 최대 크기 범위 (더 큰 쪽 변이 얼마나 긴가?)



}

bool QuadTreeTerrain::IsTriangleContained(UINT index, float x, float z, float size)
{
    // 제시된 영역 안에, 인덱스로 제시된 정점을 기준으로 하는 삼각형이 과연 있는가? 여부 판별

    UINT vertexIndex = index * 3; // 삼각형의 정점의 인덱스
    float halfSize = size * 0.5f; //찾을 곳은 제시된 숫자의 절반 (중심에서 시작되는 영역의 최대거리)

    // 각 정점을 가져와서 검사할 준비

    float x1 = vertices[vertexIndex].pos.x; // 정리된 지형 데이터에 있던 정점 데이터의 위치
    float z1 = vertices[vertexIndex].pos.z;
    
    vertexIndex++; // 다음 인덱스 검사
    float x2 = vertices[vertexIndex].pos.x;
    float z2 = vertices[vertexIndex].pos.z;

    vertexIndex++; // 다음 인덱스 검사
    float x3 = vertices[vertexIndex].pos.x;
    float z3 = vertices[vertexIndex].pos.z;

    // -> 각 정점별 x, z를 소수로 추출

    // 지금 이 값들이 영역(중심 x, z로부터 최대 거리 half) 내에 있으면 -> 삼각형은 영역 안

    float minX = min(x1, min(x2, x3)); // x1, x2, x3 중에 가장 작은 값
    if (minX > (x + halfSize)) return false;
    // 가장 왼쪽에 있어야 할 점이 가장 오른쪽보다 오른쪽이면 -> 삼각형은 여기 없음

    float minZ = min(z1, min(z2, z3));
    if (minZ > (z + halfSize)) return false;

    float maxX = max(x1, max(x2, x3));
    if (maxX < (x - halfSize)) return false;

    float maxZ = max(z1, max(z2, z3));
    if (maxZ < (z - halfSize)) return false;

    // 여기까지 오면 영역에 삼각형을 구성하는 점이 하나도 없는 상황
    // -> 위 경우, 무조건 삼각형은 영역 속에 없다.

    // 여기까지 오면 일단 삼각형의 각 점 중 하나는 영역 내에 있는 것
    // 그 다음, 부분 포함 여부를 살펴볼 수 있다

    bool countBoundary = true; // 경계면을 포함하기 옵션

    if (!countBoundary) // 경계면을 포함하지 않겠다면
    {
        // 이 안에서 보는 옵션 : 삼각형 중 점 하나라도 영역을 나가 있는가? (위에서는 모든 점)

        float maxX = max(x1, max(x2, x3));
        if (maxX > (x + halfSize)) return false; // 가장 큰 값이 영역 밖이다 = 점 하나는 영역 밖이다

        float maxZ = max(z1, max(z2, z3));
        if (maxZ > (z + halfSize)) return false;

        float minX = min(x1, min(x2, x3));
        if (minX < (x - halfSize)) return false;

        float minZ = min(z1, min(z2, z3));
        if (minZ < (z - halfSize)) return false;
    }

    // 경계면을 포함을 했든, 하지 않았든.... 여기까지 왔다면,
    // 삼각형을 이루는 세 점이 영역에 들어가는지 여부의 판단 기준에 완전히 부합한 것
    // -> false가 한 번도 뜨지 않았다

    return true; // 따라서....

    // 경계면을 따진다면 : 적어도 하나 이상의 점은 영역 안에 있다
    // 경계면을 제외하면 : 모든 점이 영역 안에 있다
}

UINT QuadTreeTerrain::ContainedTriangleCount(float x, float z, float size)
{
    // size로 받은 영역 내에, 삼각형 단위가 몇 개 존재하는가?

    // 방법 1 : 지형 데이터 안에 상세한 삼각형 좌표 및 인덱스 정보를 기록해 뒀다가, 나뉜 규격에 따라 읽는다
    // 방법 2 : 무식하게 모든 삼각형을 직접 돌려보면서 조건에 맞는지 안 맞는지 본다. 맞으면 +1

    // -> 어쨌든 정점도, 지형 데이터도, 하나하나 직접 만들어 쓰고 있는 지금은 방법 1은 힘드니까
    //    방법 2를 통해서 삼각형 개수를 영역에서 구한다 (->헤더가 더 상세해지는 환경이 있다면 거기선 정보를 호출)

    // -> 빙고와 원리가 동일

    UINT count = 0; // 삼각형 개수 초기화

    FOR(triangleCount) // 현재 클래스 내에 등록된 삼각형 목록을 모두 반복문으로 돌려서
    {
        if (IsTriangleContained(i, x, z, size)) // i번째 삼각형이 제시된 영역 안에 있었으면
            count++; // 개수 +1
    }

    //처음부터 끝까지 싹 다 돌면 영역 안에 삼각형이 몇 개 있는지 판별 가능
    // -> 메모리를 엄청나게 먹지만, 무식한 방법이지만, 의외로 느리진 않다
    // -> 더구나 이 과정을 통해서 나중에 "생략될 노드" 등을 판별할 수도 있다면 오히려 속도론 이득
    // -> 그래서 쿼드트리에서는 (비단 삼각형 개수만이 아니라) 노드 전체를 대상으로 하는 여러 판별 함수 이용

    return count; // 판별된 삼각형 개수를 그대로 반환
}

void QuadTreeTerrain::CreateTreeNode(Node* node, float x, float z, float size)
{
    // 노드에 매개변수로 받은 위치와 크기 정보를 기입
    node->x = x;
    node->z = z;
    node->size = size;

    //해당 size로 지칭되는 노드 범위 내에 삼각형이 얼마나 있는지 판별
    UINT triangles = ContainedTriangleCount(x, z, size);

    if (triangles == 0) return; //이 자리에 삼각형이 하나도 없으면 연산할 의미 없음

    //여기에 삼각형이 있다 = 연산할 가치가 있는 노드다

    // -> 이 다음에 해야 할 계산 : 이 노드가 분할될 필요가 있는가?
    //    분할되어야 한다면, 먼저 쪼개어놓고 자식에게 이 함수를 재귀시켜야 한다

    // * 현재 샘플 시나리오 : 삼각형의 개수가 일정 개수이기만 하면
    //    (=지형 크기가 일정 이상이면) 쪼갤 것

    //해당 조건을 표현한 조건문
    if (triangles > MIN_TRIANGLE) // 만약 트리 구분의 조건이 달라지면 여기서 수정
        // 예 : 높이가 급격하게 달라진다든가.....
    {

        FOR(4) // 자식 트리를 위한 분할 반복
        {
            float offsetX = (((i % 2) == 0) ? -1 : +1) * (size / 4); // 가로 보정치
            float offsetZ = ((i < 2) ? -1 : +1) * (size / 4);

            // 보정치 계산 후, 새로운 노드를 배열 내 각 자식 자리에 할당해주고
            node->children[i] = new Node(); //생성
            CreateTreeNode(node->children[i], x + offsetX, z + offsetZ, size * 0.5f);
        }

        return; // 자식이 다 쪼개졌으면 부모는 할 일이 없으므로 이대로 종료
                // (밑에서 노드 작성 다 됐음)
    }

    // 여기까지 오면, 조건이 어쨌든 부모가 자식 4개로 쪼개질 수 없었다는 이야기
    // -> 조건 충족 실패



    // * 지금의 경우, 영역 내에 있는 삼각형(렌더 대상) 개수가 정해진 수에 미치지 못했다

    // 그럴 때 작성해야 할 잎사귀 노드(가장 끄트머리 노드)의 내용을 작성 진행

    node->triangleCount = triangles; // 노드가 갖고 있었던 삼각형을 기입
                                     // 처음 작성 : 클래스 내 멤버 (triangleCount)
                                     // 수정 -> triangles : 지금 도출한 삼각형 개수
    UINT vertexCount = triangles * 3; //총 정점 개수 구하기

    //이 노드가 갖고 있는 메쉬 데이터 준비
    node->mesh = new Mesh<VertexType>();
    vector<VertexType>& vertices = node->mesh->GetVertices();
    vertices.resize(vertexCount);

    //인덱스를 두 개 만들기
    UINT index = 0;
    UINT vertexIndex = 0;
    FOR(triangleCount)
    {
        if (IsTriangleContained(i, x, z, size)) // 반복문 속 인덱스 i로 지칭된 삼각형이 영역에 있는가?
        {
            // 있으면 해당 삼각형의 인덱스를 정점 인덱스에 받기
            vertexIndex = i * 3 + 0;
            // 터레인 데이터에 있었던 정리된 정점 데이터로부터 정보를 얻어와
            // 현재 노드 내 벡터의 index 순번에 집어넣기
            vertices[index] = this->vertices[vertexIndex];
            index++; // 인덱스 +1 (뒤로 진행)

            //위 계산을 삼각형의 나머지 두 점에도 똑같이 적용
            vertexIndex++;
            //vertexIndex = i * 3 + 1;
            vertices[index] = this->vertices[vertexIndex];
            index++;

            vertexIndex++;
            //vertexIndex = i * 3 + 2;
            vertices[index] = this->vertices[vertexIndex];
            index++;

            //이 반복문을 삼각형 개수만큼 돌려주면 각 정점의 정보를
            //따로 쪼개어서 각 노드에 나눠 넣을 수 있게 될 것
        }
    }

    // 여기까지 오면 자식 노드 내에서 쪼개진 지형을 렌더해주기 위한
    // 정점의 데이터를 분할된 벡터로 가질 수 있다

    // 그 분할된 정점 벡터로 메쉬를 각각 만든다
    node->mesh->CreateMesh();

}
