#pragma once

class QuadTreeTerrain : public GameObject
{
    // 쿼드 트리 터레인 : 쿼드트리 자료 구조를 적용한 터레인 클래스

private:
    float MAX_HEIGHT = 20;
    UINT MIN_TRIANGLE = 2048; // 자료 구조를 나눌 때, 각 단위가 성립하기 위한 최소 삼각 개수
                              // 이 숫자를 못 채우면 지형이 쪼개지지 않도록 할 것

    // * 위 최소 삼각형 외에도 트리를 쪼개는 조건은 개발자가 필요에 따라 제시할 수 있다

    typedef VertexUVNormal VertexType;

    struct Node // 지형이 쿼드트리에 의해 나뉘는 분할단위
                // ...A*에 쓰이는 것과는 다르다
    {
        //분할단위에서 필요한 데이터

        float x, z, size; // 노드의 위치, 노드의 크기
        UINT triangleCount; //이 노드가 갖고 있는 삼각형(=렌더할 대상)의 개수

        Mesh<VertexType>* mesh = nullptr;
                        //이 지형이 갖고 있는(전체 지형의 부분적인) 형태

        Node* children[4] = {}; //트리 구조 = 부모 밑에 동일한 타입의 자식들이 있음
                                // 자식이 넷이라서 쿼드 트리
    };

public:
    QuadTreeTerrain(wstring heightFile);
    ~QuadTreeTerrain();

    void Render();
    void GUIRender();

private:
    void RenderNode(Node* node); //지역을 나누어서 각자 렌더
    void DeleteNode(Node* node);

    // 메쉬의 위치 계산
    void CalcMeshDimension(UINT vertexCount,
        float& centerX, float& centerZ, float& size);

    //매개변수로 제시된 곳에 삼각형이 있는가?
    bool IsTriangleContained(UINT index, float x, float z, float size);
    //그래서 있다면 얼마나 있는가?
    UINT ContainedTriangleCount(float x, float z, float size);

    //노드 만들기(쿼드트리 만들기)
    void CreateTreeNode(Node* node, float x, float z, float size);

private:
    UINT width;
    UINT height;
    UINT triangleCount = 0;
    UINT drawCount = 0;

    TerrainData* terrainData;
    vector<VertexType> vertices;

    Node* root;


};

