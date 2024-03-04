#include "Framework.h"

Spark::Spark(wstring imageFile, bool isAdditive)
{
    //material->SetShader(L"Basic/Texture.hlsl"); //텍스처가 최우선일 때
    //material->SetShader(L"Effect/Particle.hlsl"); // 범용 셰이더
    material->SetShader(L"Geometry/Spark.hlsl"); //지오메트리 셰이더 맞춤 스파크 셰이더

    material->SetDiffuseMap(imageFile);

    geometryShader = Shader::AddGS(L"Geometry/Spark.hlsl"); //지오메트리 셰이더 설정

    buffer = new FloatValueBuffer();
    startColorBuffer = new ColorBuffer();
    endColorBuffer = new ColorBuffer();

    if (isAdditive) blendState[1]->Additive(); // 혼합 투명 설정일 경우 출력상태에 반영

    Create(); // 정점 및 텍스처 정보 만들기
}

Spark::~Spark()
{
    delete buffer;
    delete startColorBuffer;
    delete endColorBuffer;
}

void Spark::Update()
{
    if (!isActive) return;

    buffer->Get()[0] += DELTA; // 소수 버퍼에 등록한 데이터 0번에 누적경과시간 더하기

    if (buffer->Get()[0] > buffer->Get()[1]) Stop();
                            //소수버퍼 0번과 1번을 비교해서 0번이 더 크면 이펙트 종료
                            // = 0번은 경과시간, 1번은 기준시간
}

void Spark::Render()
{
    //각각 소수버퍼로 설정된 데이터는 함수처럼 써서 진행

    buffer->SetVS(10); // 각각 정해진 매개변수를 줘서 조건문을 셰이더 안에서 달성
    buffer->SetPS(10); // * 왜 하필 10인가? : 정해진 이유는 없고, 그냥 이 숫자가 만만하다
                       // 보통 0~2 정도는 화면 출력에서 쓰니까, 10 정도면 보통은 침범하지 않는다

    startColorBuffer->SetPS(11);
    endColorBuffer->SetPS(12);
                        // 왜 여긴 또 11이고 12인가? -> 10으로 슬롯을 준 셰이더가 계산한 결과를
                        //                             지금 쓰고 싶어서

    Particle::Render(); //부모 함수 수행 (=렌더)
}

void Spark::GUIRender()
{
    ImGui::Text("Spark Option");
    ImGui::SliderInt("ParticleCount", (int*)&particleCount, 1, MAX_COUNT);

    ImGui::SliderFloat("Duration", &buffer->Get()[1], 0.0f, 10.0f); //지속시간
    ImGui::SliderFloat("MinRadius", &minRadius, 1.0f, maxRadius);   //최소 반경
    ImGui::SliderFloat("MaxRadius", &maxRadius, minRadius, 50.0f);  //최대 반경
    ImGui::SliderFloat("MinSize", &minSize, 0.1f, maxSize);         //최소 크기 (입자)
    ImGui::SliderFloat("MaxSize", &maxSize, minSize, 10.0f);        //최대 크기 (입자)

    ImGui::ColorEdit4("StartColor", (float*)&startColorBuffer->Get());  // 시작시 색깔
    ImGui::ColorEdit4("EndColor", (float*)&endColorBuffer->Get());    // 종료시 색깔
}

void Spark::Play(Vector3 pos)
{
    buffer->Get()[0] = 0; //재생된 시간 리셋
    Particle::Play(pos); //매개변수를 전달해서 부모 함수 실행

    UpdateParticle();      //파티클 (정점) 업데이트 후
    vertexBuffer->Update(vertices.data(), particleCount); //업데이트를 버퍼에서 반영
}

void Spark::Create()
{
    vertices.resize(MAX_COUNT); // 메모리가 급하게 변동되지 않도록 최대 예약
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexParticle), MAX_COUNT);

    //particleCount = MAX_COUNT; //실제 파티클 입자 개수
    particleCount = 500; //수동으로 값을 바꿔주면 입자 개수 조절 가능

    //지속 시간 설정
    buffer->Get()[1] = 1.0f; //다른 곳에서 받아오거나, 직접 입력하거나
}

void Spark::UpdateParticle()
{
    //모든 입자를 반복문으로 진행
    FOR(particleCount)
    {
        vertices[i].position = position;

        float size = Random(minSize, maxSize);
        vertices[i].size = { size, size };

        float radius = Random(minRadius, maxRadius); //반경계산

        Float3 rot; //방향계산
        rot.x = Random(0.0f, XM_2PI); // XM_2PI : 호도로 계산된, "반경x원주율"의 2배 = 360도
        rot.y = Random(0.0f, XM_2PI);
        rot.z = Random(0.0f, XM_2PI);
        // -> 3차원 360도 완전랜덤

        //속력 기준 만들기
        Vector3 velocity = Vector3(0, 0, radius); //반경만한 속력의 "앞"으로

        //위에서 나온 반경-방향-속력기준으로 "속도"를 만들기 (=방향과 힘을 모두 가진 벡터)
        Matrix matRot = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z); // 방향과 크기를 가진 공간부터 만들기
                        // XMMatrix~~ : 벡터를 크기를 갖춘 공간으로 만드는 DX 제공 함수
                        // ~~~RollPitchYaw : Z축, X축, Y축 회전을 반영하는 행렬 회전
        XMStoreFloat3(&vertices[i].velocity, XMVector3TransformCoord(velocity, matRot));
                    // XMStoreFloat3 : 행렬과 벡터 정보를 새로운 벡터 정보로 바꿔서 담아주는 함수
                    // XMVector3TransformCoord : 벡터와(속력기준) 행렬정보(방향과 크기가 있는 공간)를 합쳐서 새 벡터로 저장해주는 함수
                    // -> XMVector3TransformCoord 실행의 결과를 &vertices[i].velocity 데이터에 담아준다
        
        // 위 과정으로 각 정점이 다음 순간에 (혹은 다음 틱에) 가야 할 곳을 지정
    }
}
