#include "Framework.h"

CapsuleCollider::CapsuleCollider(float radius, float height, UINT stackCount, UINT sliceCount)
    : radius(radius), height(height), stackCount(stackCount), sliceCount(sliceCount)
{
    type = CAPSULE;
    MakeMesh();
    mesh->CreateMesh();
}

bool CapsuleCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
    UpdateWorld(); //�������� (�����ϰ� �� Ȯ���ϰ� �ϱ�)

    //ĸ���� ����� ������ ���ϱ�
    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - (direction * Height() * 0.5f);
    Vector3 pb = GlobalPos() + (direction * Height() * 0.5f);

    float r = Radius();

    //������ ���� ����
    Vector3 ro = ray.pos;
    Vector3 rd = ray.dir;

    Vector3 ba = pb - pa; //a���� b��
    Vector3 oa = ro - pa; //a���� ��������

    //ĸ���� ��, ����, �̵��� ��ġ ���踦 ��� ���� ����
    float baba = Dot(ba, ba);
    float bard = Dot(ba, rd);
    float baoa = Dot(ba, oa);
    float rdoa = Dot(rd, oa);
    float oaoa = Dot(oa, oa);

    //�̵� ��ġ ���踦 ���Ŀ� ���� ���� ���ų� ���ϸ鼭 ���� ���� ���Ѵ�
    //�� ���͸� �����ϸ鼭, ������ �ٸ� ���͵� ������ ���� ����
    // -> �ش� �� ���� �������� �ϴ� ��ǥ���� ����(�� ����)
    float a = baba - bard * bard;
    float b = baba * rdoa - baoa * bard;
    float c = baba * oaoa - baoa * baoa - r * r * baba;

    // �Ǵܿ� ���� �Ǳ� ���� ��ġ ���� ����
    float h = b * b - a * c;

    if (h >= 0)
    {
        float t = (-b - sqrt(h)) / a; // ������ Ȥ�� ����� ��ġ
        float distance = baoa + t * bard;

        if (distance > 0 && distance < baba)
        {
            //����� ��ġ�� �ٸ� �� ���� �������� ���ߴµ�, ��ǥ�� �����̸�
            //-> �� ���� ������ �ȱ��� �Դ�
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }
            //�� ó�� ������ ����ϰ�
            return true;
        }

        // �� ������ �Դٸ� ĸ���� ��, ������ ���� ������ �߰� �κ��� ��߳� ��

        Vector3 oc = (distance <= 0) ? oa : ro - pb;
        //�������� ĸ���� ���� ������ �Ʒ��� ������ -> �ش� ���� ���� ������ �Ÿ��� �ٽ� ���� ��
        b = Dot(rd, oc);
        c = Dot(oc, oc) - r * r;
        
        h = b * b - c;

        if (h > 0) // �Ʒ���(-) ���� �� ���ε� �޸���ƽ���� +��...
        {
            //������ �����ϱ� ���� ���� ��򰡿� ���Դ�
            //=������ �Ÿ��� ĸ�� ������ ���̴�

            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }

            return true;
        }

    }
    // ������� �Դ� = ���� ���� ������ ������ ���� �ƴϰ�... �Ʒ��� ���� ���ص� ���� �ƴϰ�...

    return false;
}

bool CapsuleCollider::IsBoxCollision(BoxCollider* collider)
{  
    //��ü vs �ڽ�ó��, �ڽ� ���忡�� ĸ���� ���� ���� ���� ����� ���� Ȥ�� ���� �ĺ��� ã�´�

    //�ڽ��� ��Ȳ ���
    BoxCollider::ObbDesc box;
    collider->GetObb(box);

    //ĸ���� ����� ������ ���ϱ�
    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - (direction * Height() * 0.5f);
    Vector3 pb = GlobalPos() + (direction * Height() * 0.5f);

    Vector3 closestPointToCapsuleArc = box.pos; // �ڽ� ���忡�� ����, "���׶� �κ�"���� ���� ���� �ĺ�
    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, box.pos);

    //-> ���� �ĺ��� ���Դ�

    FOR(3) // x > y > z ��
    {
        Vector3 direction = pointOnLine - box.pos;  // ��ġ����
        float length = Dot(box.axis[i], direction); //�������� ���� �Ÿ�
        float mult = (length < 0) ? -1 : 1;         // 6�� ���� ������ ���� ���
        length = min(abs(length), box.halfSize[i]); // �ڽ��� �޽��� �� �ѵ��� ����
        closestPointToCapsuleArc += box.axis[i] * length * mult; // ���� �ĺ��� ���� ��ġ ���� ���� (x, y, z)
    }

    //->���ͷ� ������ ���� �ĺ��� �ٽ� ����ʰ� �Ÿ��� ����
    float distance = Distance(pointOnLine, closestPointToCapsuleArc);

    //�� ���� �ĺ��� ĸ���� ������ �ȿ� ���� ������ �浹
    return distance <= Radius();


    return false;
}

bool CapsuleCollider::IsSphereCollision(SphereCollider* collider)
{
    //ĸ�� ���� ���ϱ� (= ��ü�κ��� �ִ� ���� ���ϱ�)
    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - (direction * Height() * 0.5f);
    Vector3 pb = GlobalPos() + (direction * Height() * 0.5f);

    Vector3 P = collider->GlobalPos();

    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, P);

    float distance = Distance(P, pointOnLine);

    return distance <= (Radius() + collider->Radius());

    return false;
}

bool CapsuleCollider::IsCapsuleCollision(CapsuleCollider* collider)
{
    // ĸ�������� �浹�� Ȯ���ϴ� ��
    // ����� ���� ������ (2D�� ��-��Ʈ �浹ó��)
    // 1. ��ü �κг��� �ε�ġ�� -> ������ ���� �Ÿ��� ���Ѵ�
    // 2. �� ���� �ε�ġ�� -> ��������
    // 3. ��ü vs ���̴� ->
    //    ���� ���忡�� ���� ������ ������ �����ؼ� �ش� ���� ��ü ������ ������ Ȯ���Ѵ�

    // �� ĸ���� ���� ������ ���ϰ� (���� : ���� �� ���Ʒ� �κп� ��ü�� �����ϱ�)
    // �̾ �� ĸ���� ��ġ�� ��������, ������ ���۵ǰ� ������ ���̸� ���Ѵ�
    Vector3 aDirection = Up();
    Vector3 aA = GlobalPos() - aDirection * Height() * 0.5f;
    Vector3 aB = GlobalPos() + aDirection * Height() * 0.5f;
    Vector3 bDirection = collider->Up();
    Vector3 bA = collider->GlobalPos() - bDirection * collider->Height() * 0.5f;
    Vector3 bB = collider->GlobalPos() + bDirection * collider->Height() * 0.5f;

    //�� ĸ���� ������ ���۵Ǵ� ���̸� ���� ���ؼ� 4���� �Ÿ� ���͸� ���Ѵ�
    Vector3 v0 = bA - aA;
    Vector3 v1 = bB - aA;
    Vector3 v2 = bA - aB;
    Vector3 v3 = bB - aB;

    //�ش� �Ÿ��� ������ ��ó�� ����ؼ� ���� ���� �Ÿ����� ���ϱ�
    float d0 = Dot(v0, v0);
    float d1 = Dot(v1, v1);
    float d2 = Dot(v2, v2);
    float d3 = Dot(v3, v3);

    //��� ���� "��"�� �ε��ƴ��� ���Ѵ�
    Vector3 bestA;
    if (d2 < d0 || d2 < d1 || d3 < d0 || d3 > d1)
        bestA = aB;
    else
        bestA = aA;

    //������ ���� bestA�� �������� �ٽ� ���� ����� ����� ������ �� ���� ���� ���Ѵ�
    Vector3 bestB = ClosestPointOnLine(bA, bB, bestA);
    bestA = ClosestPointOnLine(aA, aB, bestB);
    bestB = ClosestPointOnLine(bA, bB, bestA);

    // bestA�� bestB�� ���Ѵ�
    // -> �� �������� ��� ���� ��� ���� "��" Ȥ�� "��"�� �ε��ƴ����� �� �� ������,
    // -> ���ÿ� ��� ���̵�, �ش� ���� ���� �Ÿ��� ���� �� �ִ�
    // -> ��? ĸ�������� ���� �浹�� �ص� �ᱹ�� �� ĸ���� ������ �Ÿ����� �ε����� �״ϱ�

    // �׷��Ƿ� ����� �� "����"�� �Ÿ��� ��� �������� �հ� ���ϸ� �浹 ���� �Ǻ� ��
    float distance = Distance(bestA, bestB);
    return distance <= (Radius() + collider->Radius());
}

void CapsuleCollider::MakeMesh()
{
    // ĸ���� ��� = �Ǹ����� ���� + ��ü�� ���Ʒ�
    //              ���� �� ��Ȯ�ϰԴ�... ��ü�� ������ �ɰ� ��,
    //              �ɰ��� �κ��� ���Ʒ��� �̾ ��� �ø� ��.

    // �׷��� ��ü�� �׸� �� �ʿ��� ���� 2���� �ʿ��ϴ� :  ���θ�� ��Ÿ ����, Y�� ���� ����
    float thetaStep = XM_2PI / sliceCount;
    float phiStep = XM_PI / stackCount;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.reserve((sliceCount + 1) * (stackCount + 1));

    // ��ü �׸���.....
    for (UINT i = 0; i <= stackCount; i++)
    {
        float phi = i * phiStep;

        for (UINT j = 0; j <= sliceCount; j++)
        {
            float theta = j * thetaStep;

            Vertex vertex;
            vertex.pos.x = sin(phi) * cos(theta) * radius;
            vertex.pos.y = cos(phi) * radius;
            vertex.pos.z = sin(phi) * sin(theta) * radius;

            //.....���� �ϴµ�, ��ü�� ���� ������ -�� +�Ŀ� ����
            // Y�� ���� ���̿� �߰� ������ ���Ѵ� (= ��ü�� ���Ʒ��� �ɰ���)
            if (vertex.pos.y > 0)
                vertex.pos.y += height * 0.5f;
            else if(vertex.pos.y < 0)
                vertex.pos.y -= height * 0.5f;

            // ���Ʒ��� �ɰ��� ��ü�� ������ ���� ���Ϳ� ���...
            vertices.push_back(vertex);
        }
    }

    //�ε�������...
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(sliceCount * stackCount * 6);

    for (UINT i = 0; i < stackCount; i++)
    {
        for (UINT j = 0; j < sliceCount; j++)
        {
            // ������ ������ ���� �̾��ش� = �ɰ��� �κ��� �������� ���� �̾����� ������ �ȴ�
            indices.push_back((sliceCount + 1) * i + j);//0
            indices.push_back((sliceCount + 1) * (i + 1) + j);//1

            indices.push_back((sliceCount + 1) * i + j);//0            
            indices.push_back((sliceCount + 1) * i + j + 1);//2            
        }
    }
}
