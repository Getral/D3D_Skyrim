#pragma once

class AStar
{
    // A* 알고리즘 : 실제 길 찾기에 활용될 주 정렬-검색 알고리즘
public:

    AStar(UINT width = 10, UINT height = 10); //규격을 받으면서 생성
    ~AStar();

    void Update();
    void Render();

    void SetNode(){} // 기본형 (지형을 보지 않는 노드 설치) - 비워두기
    void SetNode(class Terrain* terrain); //지형을 당겨 받아 노드 설치 (지형 대응 함수) - 작성대상
                                          //왜 지형을 쓰려고 하느냐? -> 게임에서 쓸 생각이니까
                                          //왜 class냐? -> 지형도 씬에서 길찾기를 써야 하니까
                                          //가능성과 상관없이 상호참조를 막으려고.

    int FindCloseNode(Vector3 pos); //지정받은 좌표에 따른 정확한 노드 출력
    int FindRandomPos(Vector3 pos, float range); //랜덤노드 출력

    void GetPath(IN int start, IN int end, OUT vector<Vector3>& path); //경로 도출 후 path에 저장하기
    void MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path);
                            // 직선경로 도출
                            // (더 정확히는 장애물 판정을 통한 간접도출)
                            // 3D에서는 필수 과정

    bool IsCollisionObstacle(Vector3 start, Vector3 end);
                            //시작에서 끝까지 직선으로 이었을 때, 장애물과 부딪치는가?

    void AddObstacle(Collider* collider); //장애물 수동추가 (클래스 내 호출도 가능)

private:
    void SetEdge(); // 인접지 추가
    int GetMinNode(); //최소비용 노드 구하기
    void Extend(int center, int end); //지정된 좌표에서 주변 좌표 경로계산을 진행하기

    void Reset();

    float GetManhattanDistance(int start, int end);         // 맨해튼 거리
    float GetDiagonalManhattanDistance(int start, int end); // 사선을 포함한 맨해튼 거리
    
    // 맨해튼 거리 (or 택시 거리)
    // : 규격이 있는 지형에서 거리를 계산할 때, 지리/지정상의 거리를 무시하고(직선거리 계산 안 함)
    //   대신 지도 규격에 맞추어서 가로와 세로 (경우에 따라 사선 포함) 총합으로 거리를 내는 것
    //   혹은 그렇게 낸 거리 수치를 지칭한다

private:

    vector<Node*> nodes;
    Heap* heap;

    vector<Collider*> obstacles;

    UINT width, height;
    Vector2 interval; //노드 간격. Vector3여도 되지만 지금은 2차원 노드 배치를 할 거라서 Vector2


};

