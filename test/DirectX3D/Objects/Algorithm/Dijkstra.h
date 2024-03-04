#pragma once

class Dijkstra
{
    //데익스트라 알고리즘 : 노드로 구분된 지점 간 경로를 탐색해서 최저비용 경로를 찾는
    //                    이진 검색-정렬 트리 알고리즘

private:
    //typedef Terrain LevelData;
    typedef TerrainEditor LevelData;

public:
    Dijkstra();
    ~Dijkstra();

    void Update();
    void Render();

    int FindCloseNode(Vector3 pos); // 입력된 위치에서 가장 가까운 노드(의 인덱스) 찾기
    int FindMinCostNode();          // 조건에 따른 최저 비용 노드(의 인덱스) 찾기
    
    void SetEdgeInfo(int index); // 인접지 정보 입력하기

    void ResetNodes();

    vector<Vector3> GetPath(int start, int end); // 출발지와 목적지를 주면 중간에 가야 할 길을
                                                 // 노드(위치)의 집합으로 알려주는 경로탐색 함수

    void CallCreateNode(Vector3 pos) { CreateNode(pos); } //노드 만들기

    //만들어진 노드를 선택하고 연결하기
    void CallSelectNode();
    void CallLinkNode();

    //3D에서는 필요한 데이터 : 기반 지형 데이터 얻기 (샘플 : 터레인 혹은 터레인 에디터)
    void SetTerrain(LevelData* terrain) { this->terrain = terrain; }

private:
    void CreateNode(Vector3 pos); // 노드 만들기 (멤버함수, 내부용)

private:
    LevelData* terrain; // 지형 (자료형은 샘플)

    vector<DNode*> nodes; //노드 목록

    DNode* selectedNode = nullptr; // 선택 중인 노드 (기본값 : 없음)
};

