#pragma once

class Heap
{
    // 힙 : 메모리의 힙 영역을 흉내내서, 자료가 들어오면 쌓거나 관리하거나 지우는 역할 담당
    //      A* 알고리즘에서는 길찾기에 쓰일 노드의 관리에 사용될 수 있다
    //      하는 행동을 비슷하게 만들 거라서 힙이란 이름이 붙은 것. 진짜 힙과는 상관없다

public:
    Heap();
    ~Heap();

    void Insert(Node* node); // "힙"에 새로운 노드 추가하기
    Node* DeleteRoot();      // "힙"을 구성하는 요소 중 가장 밑에 있는 루트 요소를 빼내고,
                             // 빼낸 결과를 반환받기

    void UpdateUpper(int index); // 지정된 벡터의 "트리상 위쪽"을 업데이트
    void UpdateLower(int index); // 지정된 벡터의 "트리상 아래"를 업데이트
                                 // "트리상" 혹은 "트리인 걸로 쳤을 때" :
                                 // 자료는 벡터로 만들 거지만, 실제 관리는 (인덱스 배부)
                                 // 마치 이진 트리인 것처럼 사용할 거라서 (= 힙 흉내)

    void Swap(int n1, int n2); // 매개변수로 받은 두 요소의 내용 교환

    void Clear() { heap.clear(); } //벡터 기능 적용
    bool Empty() { return heap.empty(); } //벡터의 판별함수 적용

private:
    vector<Node*> heap; // 노드를 활용한 벡터(=자료 집합 구조)
                        // 이 클래스의 목적
};

