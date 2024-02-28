#pragma once

class DNode
{
    // D-노드 : 데익스트라 알고리즘에서 위치 정보를 담당하는 클래스

private:
    friend class Dijkstra; // 연관 클래스 : 데익스트라 알고리즘

    //위치 정보와 함께 있어야 하는 부가 정보
    struct Edge // 인접 지역
    {
        DNode* node; // 인접 지역은 그래서 무슨 D-노드인가?
        float cost;  // 그 지역으로 가려면 비용이 얼마나 드는가?
    };

public:
    DNode(Vector3 pos); // 이 노드는 그래서 어디에 있는가? (매개변수 필수)
    ~DNode();

    void Render(); // 필요는 없지만 이용할 때 편하려고 추가하는 렌더 함수
    void AddEdge(DNode* node); //다른 지역을 매개변수로 이어서 인접 지역으로 삼기

private:
    Vector3 pos; //이 노드가 있는 위치

    bool isClosed = false; // "이 노드는 닫혔다" 여부 : 탐색의 적절성 여부 설정
                           // = 길찾기 과정 중에 , 연산이 이 노드까지 왔을 때,
                           // 중복이거나, 다른 이유가 있어서 연산하지 말아야 할 수 있으므로
                           // 그 때 빠르게 연산 여부를 판단하기 위해 따로 변수를 선언, 저장

    int index = 0; // 노드가 여러 곳일 때 각 노드가 가지고 있어야 할 식별번호
    int via = -1;  // 경로 탐색 중, 이 노드에 이르기까지, 거쳐온 가장 마지막 노드
                   // = 경로 탐색 중 설정된 "이 노드 직전의 노드" : 기본값은 "그런 거 없다"

    float cost = FLT_MAX; // 이동비용

    vector<Edge*> edges;  // 인접지역의 벡터

    SphereCollider* collider; //시각 확인용 + 입력할 때 마우스 입력 받기 위한 용도
};

