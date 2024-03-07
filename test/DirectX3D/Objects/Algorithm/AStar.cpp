#include "Framework.h"
#include "AStar.h"

AStar::AStar(UINT width, UINT height)
    : width(width), height(height)
{
    heap = new Heap();

    //SetNode(); //�⺻ ��� ������ �ִٸ� ���⼭ ���߿� ȣ��
                 //������ ������ ������ų �Ŷ� �����ڿ����� ��� ��ġ �� ��
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;
    delete heap;
}

void AStar::Update()
{
    if (KEY_PRESS(VK_LSHIFT)) // ����Ʈ Ű�� ���� ���¶��
    {
        if (KEY_DOWN(VK_RBUTTON)) // ��Ŭ��
        {
            Ray ray = CAM->ScreenPointToRay(mousePos);

            for (Node* node : nodes)
            {
                if (node->IsRayCollision(ray, nullptr))
                {
                    node->SetState(Node::OBSTACLE); // ��ֹ��� ����
                    AddObstacle(node); //��ֹ� ��Ͽ��� ����ϱ�
                    break; // �ݺ�����
                }
            }
        }
    }
}

void AStar::Render()
{
    for (Node* node : nodes)
        node->Render(); //��忡 �浹ü ������ ���� ������ ����
}

void AStar::SetNode(Terrain* terrain)
{
    // ������ ũ�� (��带 ��ġ�� �Ը�)
    //Vector2 mapSize = terrain->GetMaterial()->GetDiffuseMap()->GetSize(); //������ ũ��
    Vector2 mapSize = terrain->GetSize(); //���� Ŭ������ ���� ������ ���μ��� �ޱ�

    // ��� ��ġ ���� ���ϱ�
    interval.x = mapSize.x / width;
    interval.y = mapSize.y / height;

    // ��� ���� �ڸ��� ���Ϳ��� ����
    nodes.reserve((width + 1) * (height + 1)); //���ʹ� 0���� ����ϱ�

    for (UINT z = 0; z <= height; ++z)
    {
        for (UINT x = 0; x <= width; ++x)
        {
            Vector3 pos = Vector3(x * interval.x, 0, z * interval.y);
            //pos.y = 0; // �⺻��
            pos.y = terrain->GetHeight(pos); // A*�� �����̵��� �ƴ϶� ������ �����ϱ� ������
                                             // ������ ������ ���� ��ȭ���� ���� ����

            //��� �߰�
            nodes.push_back(new Node(pos, nodes.size())); //��ġ��, ������ ���� ������ ������ ���ʷ� �ο�
            nodes.back()->Scale() = { interval.x, 50, interval.y }; //������ �����ϰ�, ���Ʒ��� ���
            nodes.back()->UpdateWorld();

            // ���̿� ��ȭ�� ���� ���, �� �ؿ� �ڵ带 �߰��ϸ� �ȴ�
            // ���� �ó����� : ���� ���� �� ��ֹ��̴�
            if (pos.y > 0)
            {
                nodes.back()->SetState(Node::OBSTACLE); //��ֹ��� �����ϰ�
                AddObstacle(nodes.back()); //��ֹ� �߰� �Լ� ȣ��
            }
        }
    }
    // ������� ���� ���μ��� ������ ���鼭 ��� ��ġ�� ������

    SetEdge(); // ������ ������ ���ָ� ���⼭ �� �۾��� ��
}

int AStar::FindCloseNode(Vector3 pos)
{
    float minDist = FLT_MAX;
    int result = -1;

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->state == Node::OBSTACLE)
            continue; //��ֹ��̰ų�, (����) ���̰� 0���� ũ�� ��� �� �Ѵ�

        float distance = Distance(pos, nodes[i]->GlobalPos());
        if (distance < minDist) //�ּҰŸ��� ���ŵ� ������
        {
            minDist = distance; //���Ű�� �ݿ�
            result = i; //����� �ε��� ���
        }
    }
    return result;
}

int AStar::FindRandomPos(Vector3 pos, float range)
{
    // ������ ��ǥ���� ����� ���� �� ���� ��ǥ�� ã�Ƴ���
    vector<Node*> findNodes;

    for (Node* node : nodes)
    {
        float distance = Distance(pos, node->GlobalPos());
        if (distance < range) findNodes.push_back(node); // ���� �� ��� ���Ϳ� �߰��ϱ�
    }
    //������� ���� ���� ���� ��� ��带 ���ͷ� �޴´�
    //���⼭ �ƹ��ų� �������� �ϳ� �̱�

    Node* findNode = findNodes[Random(0, findNodes.size())];

    return findNode->index; // �������� ���� ����� �ε���
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector3>& path)
{
    // ��� �Է��� ���� ������ �� �״�� ����
    if (start == -1 || end == -1) return;

    //������� �ʾҴٸ� = �� ���, ������� �������� �� ���� ��

    //->��θ� ã�Ƴ��� ���� ���� "�տ� Ȥ�� ���� �˰����� ������ ���� ������"
    //  �ش� ����� �ʱ�ȭ�ϴ� �ͺ��� ����

    Reset(); // �˰��� ����
    path.clear(); //�Ű������� ���� (����� ����Ǿ�� ��) ���͵� ������ ��� ����

    //��� ��� �߿� ����� ���� �����͵� �غ��ϸ鼭 �ʱ�ȭ
    float _g = 0; //���� ������
    float _h = GetDiagonalManhattanDistance(start, end); // �޸���ƽ
                                // ���⼭�� �޸���ƽ(�Ǵܱ���) = ���� ��ǥ ��������
                                // �������� ���� ���� �ִ� ��� (����, ����, ���� �밢�� ����)

    //���������� ��� ������ ����
    nodes[start]->f = _g + _h; //������� = ���� + �޸���ƽ
    nodes[start]->g = _g;
    nodes[start]->h = _h;
    nodes[start]->via = start; // -1(����) Ȥ�� �ڱ� �ڽ�����
    nodes[start]->state = Node::OPEN; // �� ���� ��� ���꿡 �� �غ� �ƴ�

    //���� ��带 ���� �־��ش�
    heap->Insert(nodes[start]); // ��� ������ "�����"��° ��Ҹ� ���� �߰�

    while (nodes[end]->state != Node::CLOSED)
            // �������� ���°� ��������(����)�� �� ������ ��� Ž��
    {
        if (heap->Empty()) return; // �ݺ��� ���� �߿�(Ȥ�� ���۽�) ���� ��� ������ �״�� ����
                                   // 

        int curIndex = GetMinNode(); //�ֺ����� �ּҺ�� ��� ����

        Extend(curIndex, end); //Ž�� Ȯ�� (���� ã�� �ּҺ�� ��忡��, �������� ����)
        nodes[curIndex]->state = Node::CLOSED; // �ݺ��� �߿� ���Ž���� ������
                                               // �� ��带 Ž�� ���� ���·�
    }

    // ������� ���� -> ���������� �� �� ���Ž���� ���� �����̹Ƿ�
    int curIndex = end; //�ε����� �������� �ε�����

    // �ٽ� �ڿ������� ������ ã�ư��鼭 �ִܰ�ο� ���� ��带 ��ο� ����
    while (curIndex != start) // �ε����� ������� ���ƿ� ������
    {
        nodes[curIndex]->state = Node::USING; // ��η� ����
        path.push_back(nodes[curIndex]->GlobalPos()); // ������ ��ġ�� ��� ���Ϳ� �߰�
        curIndex = nodes[curIndex]->via; //�����ߴ� ����� �������� �Ѿ�� ��� �߰� ���
                                         // -> ��� Ž�� �������� ������ �������� �Ѵٴ� ��
    }

    // �Ʒ� �ڵ�� ���� �˰���(���ͽ�Ʈ��)�� ���������� ���� �ʴ´�
    // ���� 1. ��� �� ����̶�
    //      2. ���� �� �˰����� �� ĳ���Ͱ� 3D�� �־
    //         =��ΰ� �����ϸ� ����, ���� ������ ���� ���� "���"�� ����� �ʿ䰡 ����
    //          (Pos() �ְ� �������� ���� ��Ű�� �׸�)
    // path.push_back(nodes[start]->GlobalPos());
}

void AStar::MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path)
{
    // ���� ��� ����
    // �� �Լ��� ��¥ �ϴ� ���� ���� ������, ���������� �߰� ������ �ϳ� �� ���� �� �־ �̷��� ���

    // ����� ��θ� ���� ���ų�, ���� ���� ��ο��� ���������� ���� �Ÿ��� �����ٰ� ������ ��
    // �ش� ���⿡�� �߻��� "��ֹ��� ���� �̵� �Ұ��� ���"�� �Ÿ��� ���� ���� �ۼ�
    // -> �� ����� ���ؼ�.... 1. ��ֹ� ���
    //                        2. (1���� ��������) ��� �������� ��ֹ��� �� ���� ���°�
    // ... �̷��� �� �� �� ���� ������ ���� �� �ִ�

    //�ڸ� �ε��� (����) �غ�
    int cutNodeNum = 0;

    Ray ray;
    ray.pos = start; //������ ������� �ϴ� ����

    FOR(path.size()) //��θ� �˻��ؼ�
    {
        if (!IsCollisionObstacle(start, path[i])) // ��ֹ��� �ش� ����� i��°���� �� �ôٸ�
        {
            cutNodeNum = path.size() - i - 1;
            break;

            //-> ��ֹ��� ������ �ڸ� �� ����
            //-> ��ֹ��� ó������ �־����� �� �ڸ�
        }
    }

    //�� �ݺ������� ã�Ƴ� cutNodeNum�� �̿��ؼ� ��ֹ��� �ش�Ǵ� ��带 ����������
    // ���� �� ���ǹ��� ���� ������ �ſ����� ��ֹ��� �� �����ٴ� ��带 �ڸ���

    FOR(cutNodeNum) //��ϵ�, �߶�� �� �ε����� ������ŭ
    {
        path.pop_back(); // ��θ� �ڸ��� (�ڿ�������)
    }

    //���� ����� ������ ���������� �ٽ� �����Ѵ�
    cutNodeNum = 0;
    ray.pos = end; // ������ ���� ����

    FOR(path.size()) // ������� ��꿡�� �پ��������� �𸣴� ��� ������ŭ �ٽ� �ݺ�
    {
        if (!IsCollisionObstacle(end, path[path.size() - i - 1])) //������ �ڿ������� �˻�
        {
            cutNodeNum = path.size() - i - 1;
            break;
        }
    }

    FOR(cutNodeNum)
    {
        path.erase(path.begin()); // �տ������� �� ��� �����
    }

    // ������� ����
    // �� �ݺ��� �� ���ǹ��� ������ ��(��ֹ��� �ε�ħ)�̸� -> ��ֹ��� �� �ε�ģ ��带 ����
    // ������ �����̸� -> ��ֹ��� �ε�ģ ��ŭ�� ��带 ����
    
    // ��� ���̵� (��ֹ��� ��ε�, ��ֹ��� �� ���� ��ε�) �� �����
    // ���� ������ ��ο� �����ϸ� �� ���� ������ ��� ���� �� �ִ�

    // -> �ٸ� ��� ���꿡�� �켱������ �� ����� �����̳Ŀ� ���� ���� ������ ����
}

bool AStar::IsCollisionObstacle(Vector3 start, Vector3 end)
{
    // ��ֹ� ������ �浹�� ����

    //�����غ�
    Ray ray(start, (end - start).GetNormalized());
    // ������ ���� ����, ������ ���ۿ��� ������ ���� ����

    float distance = Distance(start, end); //���ۿ��� �������� �Ÿ�

    Contact contact; //���� ����

    for (Collider* obstacle : obstacles) // ��ϵ� ��ֹ��� ó������ �˻��ؼ�
    {
        if (obstacle->IsRayCollision(ray, &contact)) // ������ ��ֹ��� �ε��ƴٸ�
        {
            //������ ������ �Ÿ��� �� �����
            if (contact.distance < distance) // ������ ���������� �Ÿ���, �� ��ġ ���� �Ÿ����� ª����
            {
                return true; // �������� ���� ���߿� ��ֹ��� �����ٴ� �̾߱Ⱑ �ȴ�
            }
        }
    }
    // �ݺ��� ���� ������ �׷� �浹�� ��������
    return false; // �ƹ� �ϵ�.... ������!
}

void AStar::AddObstacle(Collider* collider)
{
    obstacles.push_back(collider);
}

void AStar::SetEdge()
{
    //���� ������ ���� ���� "����" ������ �ǹ� ������
    UINT width = this->width + 1;

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        if (i % width != width - 1) // ������ ���� �ƴ϶��
        {
            nodes[i]->AddEdge(nodes[i + 1]); // �ڱ� ������ ���� ������ ���� ��ȯ
            nodes[i + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width) //�� �Ʒ��� �ƴ϶��
        {
            nodes[i]->AddEdge(nodes[i + width]); // �ڱ� �Ʒ��� ���� ������ ��ȯ
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != width - 1) //�� �Ʒ��� �ƴѵ� ������ ���� �ƴ϶��
        {
            nodes[i]->AddEdge(nodes[i + width + 1]); //�ڱ� �밢�� ������ �Ʒ��� ������ ��ȯ
            nodes[i + width + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != 0) //�� �Ʒ��� �ƴϰ�, ���� ���� �ƴϴ�
        {
            nodes[i]->AddEdge(nodes[i + width - 1]); //�ڱ� �밢�� ���� �Ʒ��� ������ ��ȯ
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
    }
}

int AStar::GetMinNode()
{
    return heap->DeleteRoot()->index;

    //�ּ� ��� ��带 ���� �ϴµ�.....
    //������ �̹� ���͸� �ּ� ��� ������ ������ �׻� �ϰ� �־���
    // -> �׷��Ƿ� �� �� ������ 0�� �ε����� ������ ���� ������?

    // -> �׷��� ���� ��Ʈ(0�� �ε���)�� �޾Ƽ� �ش� ����� �ε����� ����
}

void AStar::Extend(int center, int end)
{
    // �ּ� �̵������ ����Ǵ� ���� ���� �Ѿ��, �ٽ� ���⼭ ���� ��θ� ã��

    for (Node::Edge* edge : nodes[center]->edges) //�Ű������� ���� ������ ������ �˻�
    {
        int index = edge->index;

        if (nodes[index]->state == Node::CLOSED) continue; // ��尡 ����� ���� ���¸� ��ġ��
        if (nodes[index]->state == Node::OBSTACLE) continue; //��ֹ� �� ��ü���� ��ġ��

        //���� �˻� ���� ����� ������ �޸���ƽ �ٽ� ���
        // -> �� �������� �� ����� G�� H ��� ����

        float _g = nodes[center]->g + edge->cost;
        float _h = GetDiagonalManhattanDistance(index, end);

        float _f = _g + _h;

        if (nodes[index]->state == Node::OPEN) // ��尡 ���� ���� ���̶��
        {
            if (_f < nodes[index]->f) // �̵� ����� ���ϰ� �ּұ���� �����ϸ�
            {
                //�ش� ����� �����͸� �ݿ��Ѵ�
                nodes[index]->g = _g; //���� ����
                nodes[index]->f = _f; //������� ����
                nodes[index]->via = center; //�� ����� �������� ���� �����
            }
            //�̷��� �ݺ����� �����ϸ� ���Ϳ��� �� "�ּҺ�� �ĺ���"�� ���� ���� ���� �� ������ ���� ����
        }
        else if (nodes[index]->state == Node::NONE) // ���꿡 ���� ���� �����ٸ�
        {
            //��带 ���� ��� ���꿡 �߰�
            nodes[index]->g = _g;
            nodes[index]->h = _h;
            nodes[index]->f = _f;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN;

            //���� �ٷ� �߰��ؼ� �̵���뿡 ���� ���ı��� ����
            heap->Insert(nodes[index]);

            //�׷� �� ��嵵 Ʈ�� �ȿ��� ������ ����, �ּҺ������ �ƴ���, Ʈ�� �� ���� �� ����
            // ���ķ� ����� �� �� �ִ�
        }
    }

    // ������� ����Ǹ� ���Ϳ��� �������� ���� �ּҺ�� ����� �ĺ����� ������ �ȴ�
    // -> ������ �ش� ���� ���� ���� (Ȯ�� ����)
}

void AStar::Reset()
{
    // �����ߴ� �ִܰ�� ���� ���� ����� �����

    for (Node* node : nodes)
    {
        if (node->state != Node::OBSTACLE) //��ֹ��� ��� ��ֹ��̰�, �׷� ��찡 �ƴ϶��
        {
            node->state = Node::NONE; // ��� ���� ���·� �ǵ�����
        }
    }
    heap->Clear(); // �� ���͵� ��� �����
}

float AStar::GetManhattanDistance(int start, int end)
{
    //���� �ε����� �����ϴ� ����� ��ġ
    Vector3 startPos = nodes[start]->GlobalPos();
    Vector3 endPos = nodes[end]->GlobalPos();

    //������ ���� �� ��ġ�� ���踦 "�Ÿ�"��� �̸����� ���Ѵ�
    Vector3 distance = endPos - startPos; //���ۿ��� ������ ���� ���� �� ��ü

    return abs(distance.x) + abs(distance.z);
            //��� ������ x���� z���� �״�� ���ؼ� ���� �Ÿ��� �����
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    //���� �ε����� �����ϴ� ����� ��ġ
    Vector3 startPos = nodes[start]->GlobalPos();
    Vector3 endPos = nodes[end]->GlobalPos();

    //������ ���� �� ��ġ�� ���踦 "�Ÿ�"��� �̸����� ���Ѵ�
    Vector3 distance = endPos - startPos; //���ۿ��� ������ ���� ���� �� ��ü

    float x = abs(distance.x); // ��κ����� x ��ǥ (���� ���� ����)
    float z = abs(distance.z); // ��κ����� z ��ǥ (���� ���� ����)

    // �� �� ���̰� ��� ������ ���ϱ� (������ ���� ��� ���� ����� ���� ��)
    float maxDist = max(x, z); // �� �� ��ǥ ����
    float minDist = min(x, z); // �� ª�� ��ǥ ����

    return (maxDist - minDist) + sqrt(minDist * minDist * 2);
        //�밢���� �� �� ���� �κ��� ���� �Ÿ��� �밢�� ���̸� ��ģ��
}
