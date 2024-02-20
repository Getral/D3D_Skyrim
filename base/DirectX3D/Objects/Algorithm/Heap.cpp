#include "Framework.h"

Heap::Heap(){}
Heap::~Heap(){}

void Heap::Insert(Node* node)
{
    heap.push_back(node); //벡터 추가...후
    UpdateUpper(heap.size() - 1); //트리 갱신
}

Node* Heap::DeleteRoot()
{
    Node* root = heap.front(); // 인덱스 0번 준비

    Swap(0, heap.size() - 1); //처음과 끝 바꾸기
    heap.pop_back(); //벡터에서 요소 빼내기 (root 포인터에 데이터는 계속 보존)

    UpdateLower(0); //새로운 0번 인덱스를 기준으로 재정렬(->하면 0번은 다시 제자리 찾아 내려갈 것)

    return root; //빼낸 root 요소 반환
}

void Heap::UpdateUpper(int index)
{
    //인덱스와 부모 구하기
    int curIndex = index; //내 인덱스
    int parent = (curIndex - 1) / 2; // 내 부모 : 2진트리라고 치고
                                     // 이 인덱스의 윗칸에 있는 인덱스 구하기
                                     // * 2진트리는 한 데이터에서 두 가지가 뻗어서
                                     // 밑에 두 데이터가 붙는 모양을 개념적으로 흉내

    //인덱스를 거슬러 올라가면서 각 요소들을 바꾸면서 진행
    while (curIndex != 0) //처음으로=트리의 가장 위로 올 때까지
    {
        if (heap[parent]->GetCost() <= heap[curIndex]->GetCost())
            return; //부모 요소로 등록된 노드의 이동비용이 더 적다면
                    // = 내 노드가 제자리 찾아온 것 -> 종료

        // 그렇지 않다면 (부모 요소보다 내 이동비용이 낮다면)
        // 내 노드가 데이터 안에서 우선권을 가져야 맞다 (길찾기라면)

        Swap(curIndex, parent); // 벡터 내 요소를 교체해주고
        curIndex = parent; //부모의 인덱스를 물려받는다

        parent = (curIndex - 1) / 2; // 다음 부모의 인덱스를 도출
    }

    // -> 여기까지 오면 벡터가 데이터 기준(현재 : 노드의 이동비용)에 맞추어 정렬될 것
}

void Heap::UpdateLower(int index)
{
    // 2진트리라고 치고, 인덱스를 기준으로 트리상 아래를 업데이트

    int curIndex = index;

    //위 함수에 부모가 있듯 여기에는 두 자식이 필요하다 (2진트리 모양에 따름)
    int lChild = (index * 2) + 1; // 2진 트리상의 형제(index+n범위)지나서 다음 줄로 넘어가기
    int rChild = lChild + 1; //왼쪽에서 +1 하면 오른쪽

    // 모양으로 치면
    // 0
    // 1            2
    // 3     4      5    6
    // 7 8   9 10   ...이대로 쭉

    int minNode = curIndex; // 현재 이동비용이 가장 낮은 곳을 지금 인덱스인 것으로 간주하고 시작
                            // 이후 갱신하면서 진행


    while (true) // 종료 코드가 나올 때까지 계속 진행
    {
        if (lChild < heap.size() && heap[lChild]->GetCost() < heap[minNode]->GetCost())
            //lChild로 지칭된 인덱스가 벡터에 있고, 해당 인덱스 노드의 이동비용이 지금까지 중에 제일 낮다면
        {
            minNode = lChild;
        }

        if (rChild < heap.size() && heap[rChild]->GetCost() < heap[minNode]->GetCost())
            //rChild로 지칭된 인덱스가 벡터에 있고, 해당 인덱스 노드의 이동비용이 지금까지 중에 제일 낮다면
        {
            minNode = rChild;
        }

        //이렇게 두 번 비교를 했는데 갱신이 되지 않았으면 = 부모가 제자리 찾은 것
        if (minNode == curIndex) return; // 반복문 종료의 조건

        // 그렇지 않다면 갱신이 필요한 상황
        Swap(curIndex, minNode); //위에서 찾아낸 최소비용 노드(lChild 혹은 rChild)와 교체
        curIndex = minNode; //조사할 인덱스 갱신
        lChild = (curIndex * 2) + 1; //자식도 갱신
        rChild = lChild + 1;
    }
}

void Heap::Swap(int n1, int n2)
{
    swap(heap[n1], heap[n2]);
    //swap : C++벡터 제공 함수 중 하나. 벡터 안에 있는 두 요소를 교체
    //       지정된 인덱스끼리의 내용을 바꾼다고 해석 가능
    //       두 데이터의 인덱스를 바꾼다고 해석해도 가능
}
