#include "Framework.h"

Heap::Heap(){}
Heap::~Heap(){}

void Heap::Insert(Node* node)
{
    heap.push_back(node); //���� �߰�...��
    UpdateUpper(heap.size() - 1); //Ʈ�� ����
}

Node* Heap::DeleteRoot()
{
    Node* root = heap.front(); // �ε��� 0�� �غ�

    Swap(0, heap.size() - 1); //ó���� �� �ٲٱ�
    heap.pop_back(); //���Ϳ��� ��� ������ (root �����Ϳ� �����ʹ� ��� ����)

    UpdateLower(0); //���ο� 0�� �ε����� �������� ������(->�ϸ� 0���� �ٽ� ���ڸ� ã�� ������ ��)

    return root; //���� root ��� ��ȯ
}

void Heap::UpdateUpper(int index)
{
    //�ε����� �θ� ���ϱ�
    int curIndex = index; //�� �ε���
    int parent = (curIndex - 1) / 2; // �� �θ� : 2��Ʈ����� ġ��
                                     // �� �ε����� ��ĭ�� �ִ� �ε��� ���ϱ�
                                     // * 2��Ʈ���� �� �����Ϳ��� �� ������ ���
                                     // �ؿ� �� �����Ͱ� �ٴ� ����� ���������� �䳻

    //�ε����� �Ž��� �ö󰡸鼭 �� ��ҵ��� �ٲٸ鼭 ����
    while (curIndex != 0) //ó������=Ʈ���� ���� ���� �� ������
    {
        if (heap[parent]->GetCost() <= heap[curIndex]->GetCost())
            return; //�θ� ��ҷ� ��ϵ� ����� �̵������ �� ���ٸ�
                    // = �� ��尡 ���ڸ� ã�ƿ� �� -> ����

        // �׷��� �ʴٸ� (�θ� ��Һ��� �� �̵������ ���ٸ�)
        // �� ��尡 ������ �ȿ��� �켱���� ������ �´� (��ã����)

        Swap(curIndex, parent); // ���� �� ��Ҹ� ��ü���ְ�
        curIndex = parent; //�θ��� �ε����� �����޴´�

        parent = (curIndex - 1) / 2; // ���� �θ��� �ε����� ����
    }

    // -> ������� ���� ���Ͱ� ������ ����(���� : ����� �̵����)�� ���߾� ���ĵ� ��
}

void Heap::UpdateLower(int index)
{
    // 2��Ʈ����� ġ��, �ε����� �������� Ʈ���� �Ʒ��� ������Ʈ

    int curIndex = index;

    //�� �Լ��� �θ� �ֵ� ���⿡�� �� �ڽ��� �ʿ��ϴ� (2��Ʈ�� ��翡 ����)
    int lChild = (index * 2) + 1; // 2�� Ʈ������ ����(index+n����)������ ���� �ٷ� �Ѿ��
    int rChild = lChild + 1; //���ʿ��� +1 �ϸ� ������

    // ������� ġ��
    // 0
    // 1            2
    // 3     4      5    6
    // 7 8   9 10   ...�̴�� ��

    int minNode = curIndex; // ���� �̵������ ���� ���� ���� ���� �ε����� ������ �����ϰ� ����
                            // ���� �����ϸ鼭 ����


    while (true) // ���� �ڵ尡 ���� ������ ��� ����
    {
        if (lChild < heap.size() && heap[lChild]->GetCost() < heap[minNode]->GetCost())
            //lChild�� ��Ī�� �ε����� ���Ϳ� �ְ�, �ش� �ε��� ����� �̵������ ���ݱ��� �߿� ���� ���ٸ�
        {
            minNode = lChild;
        }

        if (rChild < heap.size() && heap[rChild]->GetCost() < heap[minNode]->GetCost())
            //rChild�� ��Ī�� �ε����� ���Ϳ� �ְ�, �ش� �ε��� ����� �̵������ ���ݱ��� �߿� ���� ���ٸ�
        {
            minNode = rChild;
        }

        //�̷��� �� �� �񱳸� �ߴµ� ������ ���� �ʾ����� = �θ� ���ڸ� ã�� ��
        if (minNode == curIndex) return; // �ݺ��� ������ ����

        // �׷��� �ʴٸ� ������ �ʿ��� ��Ȳ
        Swap(curIndex, minNode); //������ ã�Ƴ� �ּҺ�� ���(lChild Ȥ�� rChild)�� ��ü
        curIndex = minNode; //������ �ε��� ����
        lChild = (curIndex * 2) + 1; //�ڽĵ� ����
        rChild = lChild + 1;
    }
}

void Heap::Swap(int n1, int n2)
{
    swap(heap[n1], heap[n2]);
    //swap : C++���� ���� �Լ� �� �ϳ�. ���� �ȿ� �ִ� �� ��Ҹ� ��ü
    //       ������ �ε��������� ������ �ٲ۴ٰ� �ؼ� ����
    //       �� �������� �ε����� �ٲ۴ٰ� �ؼ��ص� ����
}
