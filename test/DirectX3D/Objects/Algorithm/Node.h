#pragma once

class Node : public BoxCollider // 지역의 규격화, 타일화 (A* 알고리즘의 중요 요소)
                                // 상속을 안 받을 거라면 멤버 변수 안에서라도 규격이 있어야 한다
{
    // 노드 : 구역 데이터. A* 알고리즘에서 장소를 나타내기 위해서 쓴다

public:
    friend class AStar;

    struct Edge //인접 지역
    {
        int index;
        float cost;
    };

    enum State // 이 지역(이 노드)의 상태를 변수로 따로 구분
    {
        NONE, //아무 상태 없음
        OPEN, //검색 가능한 상태
        CLOSED, //검색을 마쳤거나, 하면 안 되는 상태
        USING,  //현재 검색에 사용하는 중
        OBSTACLE // 장애물, 비용에 추가 연산을 하거나
                 // 애초에 검색도 하면 안 되는 상태 (현재 기본 설정)
    };

    Node(Vector3 pos, int index);
    ~Node();

    void Render();

    void AddEdge(Node* node);

    float GetCost() { return f; } //이 노드의 (최종) 이동 비용 (A*에서는 이 겟터가 필수)
    void SetState(State state) { this->state = state; }

private:
    int index = 0; //이 노드의 인덱스
    int via = -1;  //이 노드의 경유지

    State state;   //이 노드의 현재 상태
    vector<Edge*> edges; //경유지들

    //이동비용 (A* 혹은 규격지형을 사용하는 다수의 알고리즘에서 이렇게 복수의 이동비용 사용)
    //         ...특히 빠른 속도를 지향하는 알고리즘일수록 오히려 비용 관련 변수가 많을 것
    float f = 0; // f : Final. 최종 비용
    float g = 0; // g : Geometry. 정점의 위치, 혹은 지형의 좌표 등 모양을 지칭하는 데이터
    float h = 0; // h : Huristic. 계산 기준은 알고리즘에 따라 다르며, G와 F를 연산할 때 추가 연산
                 //     -> G 혹은 F에 변화를 줘서 재계산 여부 판단, 혹은 n차 계산에 활용하는 등
                 //        이동비용 연산에 추가 속도를 더하려고 만드는 변수
};

