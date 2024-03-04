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
    UpdateWorld(); //정점갱신 (광선하고 비교 확실하게 하기)

    //캡슐의 방향과 옆면을 구하기
    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - (direction * Height() * 0.5f);
    Vector3 pb = GlobalPos() + (direction * Height() * 0.5f);

    float r = Radius();

    //광원과 광선 방향
    Vector3 ro = ray.pos;
    Vector3 rd = ray.dir;

    Vector3 ba = pb - pa; //a에서 b로
    Vector3 oa = ro - pa; //a에서 광원으로

    //캡슐의 옆, 광원, 이들의 위치 관계를 모두 서로 점곱
    float baba = Dot(ba, ba);
    float bard = Dot(ba, rd);
    float baoa = Dot(ba, oa);
    float rdoa = Dot(rd, oa);
    float oaoa = Dot(oa, oa);

    //이들 위치 관계를 공식에 따라 서로 빼거나 곱하면서 다음 값을 구한다
    //한 벡터를 제곱하면서, 인접한 다른 벡터도 제곱한 다음 뺀다
    // -> 해당 두 변을 기준으로 하는 좌표상의 빗변(의 제곱)
    float a = baba - bard * bard;
    float b = baba * rdoa - baoa * bard;
    float c = baba * oaoa - baoa * baoa - r * r * baba;

    // 판단에 참고가 되기 위한 위치 관계 도출
    float h = b * b - a * c;

    if (h >= 0)
    {
        float t = (-b - sqrt(h)) / a; // 이전값 혹은 상대적 위치
        float distance = baoa + t * bard;

        if (distance > 0 && distance < baba)
        {
            //상대적 위치와 다른 쪽 벡터 빗변과도 비교했는데, 좌표상 안쪽이면
            //-> 이 점은 상자의 안까지 왔다
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }
            //위 처럼 접점을 기록하고
            return true;
        }

        // 이 경우까지 왔다면 캡슐의 옆, 레이의 점을 구성할 중간 부분이 어긋난 것

        Vector3 oc = (distance <= 0) ? oa : ro - pb;
        //광원에서 캡슐의 위와 가깝냐 아래에 가깝냐 -> 해다 옆면 경계와 광원의 거리를 다시 구한 것
        b = Dot(rd, oc);
        c = Dot(oc, oc) - r * r;
        
        h = b * b - c;

        if (h > 0) // 아래쪽(-) 벡터 비교 중인데 휴리스틱값은 +면...
        {
            //빗변을 구성하기 위한 안쪽 어딘가에 들어왔다
            //=접점의 거리가 캡슐 반지름 안이다

            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }

            return true;
        }

    }
    // 여기까지 왔다 = 위쪽 경계로 가봐도 반지름 안이 아니고... 아래쪽 경계로 비교해도 안이 아니고...

    return false;
}

bool CapsuleCollider::IsBoxCollision(BoxCollider* collider)
{  
    //구체 vs 박스처럼, 박스 입장에서 캡슐로 가기 위한 가장 가까운 접점 혹은 접점 후보를 찾는다

    //박스의 상황 기록
    BoxCollider::ObbDesc box;
    collider->GetObb(box);

    //캡슐의 방향과 옆면을 구하기
    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - (direction * Height() * 0.5f);
    Vector3 pb = GlobalPos() + (direction * Height() * 0.5f);

    Vector3 closestPointToCapsuleArc = box.pos; // 박스 입장에서 보는, "동그란 부분"으로 가는 접점 후보
    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, box.pos);

    //-> 접점 후보가 나왔다

    FOR(3) // x > y > z 축
    {
        Vector3 direction = pointOnLine - box.pos;  // 위치관계
        float length = Dot(box.axis[i], direction); //점곱으로 만든 거리
        float mult = (length < 0) ? -1 : 1;         // 6면 방향 지정을 위한 계수
        length = min(abs(length), box.halfSize[i]); // 박스의 메쉬를 못 넘도록 제한
        closestPointToCapsuleArc += box.axis[i] * length * mult; // 접점 후보의 최종 위치 벡터 도출 (x, y, z)
    }

    //->벡터로 정리된 접점 후보를 다시 상대쪽과 거리를 내기
    float distance = Distance(pointOnLine, closestPointToCapsuleArc);

    //이 접점 후보가 캡슐의 반지름 안에 들어와 있으면 충돌
    return distance <= Radius();


    return false;
}

bool CapsuleCollider::IsSphereCollision(SphereCollider* collider)
{
    //캡슐 위쪽 구하기 (= 구체부분이 있는 방향 구하기)
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
    // 캡슐끼리의 충돌을 확인하는 법
    // 경우의 수를 나눈다 (2D의 원-렉트 충돌처럼)
    // 1. 구체 부분끼리 부딪치면 -> 반지름 합을 거리와 비교한다
    // 2. 옆 끼리 부딪치면 -> 마찬가지
    // 3. 구체 vs 옆이다 ->
    //    옆의 입장에서 도출 가능한 접점을 도출해서 해당 점이 구체 반지름 안인지 확인한다

    // 두 캡슐의 위쪽 방향을 구하고 (이유 : 만들 때 위아래 부분에 구체가 붙으니까)
    // 이어서 두 캡슐의 위치를 기준으로, 옆면이 시작되고 끝나는 높이를 구한다
    Vector3 aDirection = Up();
    Vector3 aA = GlobalPos() - aDirection * Height() * 0.5f;
    Vector3 aB = GlobalPos() + aDirection * Height() * 0.5f;
    Vector3 bDirection = collider->Up();
    Vector3 bA = collider->GlobalPos() - bDirection * collider->Height() * 0.5f;
    Vector3 bB = collider->GlobalPos() + bDirection * collider->Height() * 0.5f;

    //두 캡슐의 옆면이 시작되는 높이를 서로 비교해서 4개의 거리 벡터를 구한다
    Vector3 v0 = bA - aA;
    Vector3 v1 = bB - aA;
    Vector3 v2 = bA - aB;
    Vector3 v3 = bB - aB;

    //해당 거리를 넓이인 것처럼 계산해서 서로 간의 거리관계 구하기
    float d0 = Dot(v0, v0);
    float d1 = Dot(v1, v1);
    float d2 = Dot(v2, v2);
    float d3 = Dot(v3, v3);

    //어느 쪽이 "위"와 부딪쳤는지 구한다
    Vector3 bestA;
    if (d2 < d0 || d2 < d1 || d3 < d0 || d3 > d1)
        bestA = aB;
    else
        bestA = aA;

    //위에서 구한 bestA를 기준으로 다시 가장 가까운 가까운 점들을 각 옆에 대해 구한다
    Vector3 bestB = ClosestPointOnLine(bA, bB, bestA);
    bestA = ClosestPointOnLine(aA, aB, bestB);
    bestB = ClosestPointOnLine(bA, bB, bestA);

    // bestA와 bestB를 구한다
    // -> 이 과정에서 어느 쪽이 어느 쪽의 "위" 혹은 "옆"과 부딪쳤는지도 알 수 있지만,
    // -> 동시에 어느 쪽이든, 해당 접점 간의 거리도 구할 수 있다
    // -> 왜? 캡슐끼리면 옆과 충돌을 해도 결국은 두 캡슐의 반지름 거리에서 부딪쳤을 테니까

    // 그러므로 도출된 두 "접점"의 거리를 내어서 반지름의 합과 비교하면 충돌 여부 판별 끝
    float distance = Distance(bestA, bestB);
    return distance <= (Radius() + collider->Radius());
}

void CapsuleCollider::MakeMesh()
{
    // 캡슐의 모양 = 실린더의 옆면 + 구체의 위아래
    //              조금 더 정확하게는... 구체를 반으로 쪼갠 후,
    //              쪼개진 부분을 위아래로 이어서 잡아 늘린 것.

    // 그래서 구체를 그릴 때 필요한 각도 2종이 필요하다 :  가로면용 세타 각도, Y축 파이 각도
    float thetaStep = XM_2PI / sliceCount;
    float phiStep = XM_PI / stackCount;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.reserve((sliceCount + 1) * (stackCount + 1));

    // 구체 그리기.....
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

            //.....여야 하는데, 구체의 파이 각도가 -냐 +냐에 따라
            // Y축 정점 높이에 추가 보정을 가한다 (= 구체를 위아래로 쪼갠다)
            if (vertex.pos.y > 0)
                vertex.pos.y += height * 0.5f;
            else if(vertex.pos.y < 0)
                vertex.pos.y -= height * 0.5f;

            // 위아래로 쪼개진 구체의 정점을 정점 벡터에 담고...
            vertices.push_back(vertex);
        }
    }

    //인덱스에서...
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(sliceCount * stackCount * 6);

    for (UINT i = 0; i < stackCount; i++)
    {
        for (UINT j = 0; j < sliceCount; j++)
        {
            // 정점의 정보를 서로 이어준다 = 쪼개진 부분의 정점들은 서로 이어져서 옆면이 된다
            indices.push_back((sliceCount + 1) * i + j);//0
            indices.push_back((sliceCount + 1) * (i + 1) + j);//1

            indices.push_back((sliceCount + 1) * i + j);//0            
            indices.push_back((sliceCount + 1) * i + j + 1);//2            
        }
    }
}
