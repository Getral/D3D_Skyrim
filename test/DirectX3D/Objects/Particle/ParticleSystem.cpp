#include "Framework.h"

// 사전에 설정된 파일로부터 파티클 생성하기
ParticleSystem::ParticleSystem(string file)
{
    LoadData(file); // 매개변수를 전달하여 파일로부터 파티클 데이터 만들기

    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //출력 준비
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true); // 배경색 일단 적용 (혼합 투명은 옵션 봐서 따로 적용)
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // 안 가려짐
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    quad->SetActive(false); // 이미지 일단은 끄기
}

// 텍스처 파일로부터 직접 파티클 생성하기
ParticleSystem::ParticleSystem(wstring file)
{
    LoadData(file); // 파일로부터 파티클의 데이터를 구성한다

    // 인스턴스를 담은 버퍼 준비
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //출력 준비
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true); // 배경색 일단 적용 (혼합 투명은 옵션 봐서 따로 적용)
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // 안 가려짐
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    quad->SetActive(false); // 이미지 일단은 끄기
}

ParticleSystem::~ParticleSystem()
{
    delete quad;
    delete instanceBuffer;
    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];
}

void ParticleSystem::Update()
{
    // 파티클이 업데이트되는 과정

    if (!quad->Active()) return; // 그림이 비활성화라면 종료

    lifeSpan += DELTA; // 생애주기 진행

    UpdatePhysical(); //물리적 대상=정점 업데이트
    UpdateColor();    //색상 업데이트
    quad->UpdateWorld(); //업데이트 결과를 이미지에 반영

    if (lifeSpan >= data.duration) // 진행된 생애 주기가 파티클에서 설정된 지속시간에 다다르면
    {
        if (data.isLoop) Init(); // 반복 옵션이 켜진 경우, 재시작
        else Stop(); // 반복 옵션이 꺼진 경우, 멈추기
    }
}

void ParticleSystem::Render()
{
    if (!quad->Active()) return;

    // 인스턴스 준비
    instanceBuffer->Set(1); // 1 : 조건문으로 쓰기도 하지만, 원래는 결국 출력우선순위

    quad->SetRender(); //쿼드 렌더 준비 (미리 함수가 정해진 대로 진행)
                       // -> 이 경우, 렌더 준비 과정에서 빠진 부분이 있어서 
                       //    쿼드 내에 추가

    //출력 상태 준비
    blendState[1]->SetState();
    depthState[1]->SetState();

    DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0); // 마지막 매개변수 3개는 다른 곳에서 설정을 해두고
                                                     // 여기선 0, 0, 0 하면 가장 속이 편하다
        //DrawIndexedInstanced : 준비된 하나의 출력 데이터를 렌더 절차가 받은 인덱스에 따라 (버퍼로 준비됨)
        //                       반복해서 출력하는 기능을 담당
        // 매개변수 : 한 번에 그릴 정점 = 출력할 인스턴스의 단위 (현재 : 한 번에 정점 6개씩)
        //                              , 출력할 횟수 (드로우 콜 횟수만큼)
        //                              , 어디부터, 어디로 (기준 값 없음 = 정해진 설정이 있으면 설정대로)
        //                              , 추가 참조할 자료가 있다면 어디에 있는가 (=는 지금은 없음)

    // 원상복구
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void ParticleSystem::GUIRender()
{
    quad->GUIRender(); // 그림을 디버그에서 출력
}

void ParticleSystem::Play(Vector3 pos, Vector3 rot)
{
    //파티클의 시작
    quad->SetActive(true);

    quad->Pos() = pos;
    quad->Rot() = rot;

    Init(); // 시작 함수 호출 (파티클 생성)
}

void ParticleSystem::Stop()
{
    quad->SetActive(false); // 그냥 비활성화하고 끝
}

void ParticleSystem::UpdatePhysical()
{
    // 개별 정점 업데이트

    drawCount = 0; // 드로우 콜 횟수 초기화 (=파티클보다는 개발자 확인용)

    //진짜는 아래 반복문
    FOR(data.count) //각 입자에 코드 반영
    {
        if (lifeSpan < particleInfo[i].startTime) continue;
                // 아직 생애주기가 시작할 때조차 되지 않은 것 = 시작할 때가 안 된 것

        //주기 진행 중인 파티클만 연산
        particleInfo[i].velocity += particleInfo[i].acceleration * DELTA;
                    //속력 기준에 가속력과 추가 방향을 더해서 속도(길이 + 방향)로 만들기
        particleInfo[i].transform.Pos() += particleInfo[i].velocity
            * particleInfo[i].speed * DELTA; // 속도와, 속력과, 경과시간을 모두 반영, 위치 갱신

        particleInfo[i].transform.Rot().z += particleInfo[i].angularVelocity * DELTA;
                                // 시계/반시계 회전 값이 있으면 반영

        //빌보드 옵션이 켜져 있었을 경우, 그림을 빌보드 출력이 되도록
        if (data.isBillboard)
        {
            particleInfo[i].transform.Rot().x = CAM->Rot().x; // 카메라 방향과 동기화
            particleInfo[i].transform.Rot().y = CAM->Rot().y;
        }
        // * 왜 카메라인가 (벡터가 아니고) -> 벡터를 쓰면 카메라와 방향을 맞추기보다
        //   이미지가 카메라*를* 바라보게 된다 -> 보는 입장에서 꼭 정면 100%라는 보장이 없어서

        //경과 시간의 비율 구하기
        float t = (lifeSpan - particleInfo[i].startTime) // 진행된 주기
            / (data.duration - particleInfo[i].startTime); // 지속시간


        // 비율에 따라 크기가 혹시 달라져야 하면 보간
        particleInfo[i].transform.Scale() =
            Lerp(particleInfo[i].startScale, particleInfo[i].endScale, t);

        particleInfo[i].transform.UpdateWorld(); //지금까지 계산된 위치, 회전, 크기 업데이트

        //-> 여기까지 진행하면 각 인스턴스가 갖고 있는 옵션에 따라,
        //   해당 옵션이 시간에 의해 반영된 트랜스폼 결과가 정보 구조체 안에 들어간다

        // -> 이 구조체의 정보를 인스턴스에 넣는다
        instances[drawCount++].transform = // 이 호출이 끝나면 드로우 콜 횟수에 +1
            XMMatrixTranspose(particleInfo[i].transform.GetWorld());
                                              // 공간을 나타내는 행렬 데이터를 전이

        // * 인스턴스를 먼저 계산하고 정보 구조체에 넣는 것도 가능하고,
        //   설계상으로는 그 편이 직관적이겠지만, 정보에서 계산을 다 해두고
        //   실제 인스턴스를 한 번에 고치면 좀 더 실행이 안정적이다
    }

    // 여기까지 오면 파티클을 위한 정점의 인스턴스 정보가 완전히 갱신된다
    // 갱신 끝난 인스턴스 정보를 버퍼에도 반영
    instanceBuffer->Update(instances.data(), drawCount);
                                            // 업데이트 횟수는 드로우 콜 횟수만큼만
}

void ParticleSystem::UpdateColor()
{
    float t = lifeSpan / data.duration; // 진행을 하고 말고, 시작 시간을 포함을 하고 말고는
                                        // 위쪽 함수에서 끝나서, 여기선 생략

    //구한 t를 활용해서 각 색상 보간 진행
    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t); // R
    color.y = Lerp(data.startColor.y, data.endColor.y, t); // G
    color.z = Lerp(data.startColor.z, data.endColor.z, t); // B
    color.w = Lerp(data.startColor.w, data.endColor.w, t); // A

    // 보간된 색상을 쿼드에 적용
    quad->GetMaterial()->GetData().diffuse = color;
                        //GetData() : 이미지 데이터에 접근하기 위한 함수
                        //diffuse : 이미지 데이터에서 색상값
}

void ParticleSystem::Init()
{
    // 파티클 시작하기

    // 옵션 중에 혼합 투명이 켜져 있었을 경우, 출력 상태에 반영 필요
    if (data.isAdditive) blendState[1]->Additive(); //혼합 투명 호출
    else blendState[1]->Alpha(true); //배경색 투명화
                                     //(중간에 옵션이 바뀔 수도 있어서 여기서 확인사살)

    //멤버 변수 세팅

    lifeSpan = 0; // 생애 주기....(중에서 지금은 경과된 시간) : 소멸 시점은 duration에서
    drawCount = 0; //드로우 콜 횟수 (0 초기화)
    data.count = particleCount; // 클래스에서 파티클 개수 옵션 바꾼 결과 받아오기

    //data.count와 particleCount가 달랐다면 여기서 초기화
    instances.resize(data.count);
    particleInfo.resize(data.count);

    // 개별 인스턴스의 옵션을 여기서 세팅 (샘플 상황)
    // * 혹시 다른 곳에서 옵션이 바뀌어야 할 수도 있으므로 그런 경우는 적절히 수정

    for (ParticleInfo& info : particleInfo) // 개별 인스턴스 내 정보들을 호출해서 수정
    {
        info.transform.Pos() = {}; // 일단 대기

        //각 파티클의 실체 옵션 설정
        info.velocity = Random(data.minVelocity, data.maxVelocity);
        info.acceleration = Random(data.minAcceleration, data.maxAcceleration);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale, data.maxStartScale);
        info.endScale = Random(data.minEndScale, data.maxEndScale);

        // 옵션 : 속력(빠르기)을 기준속도(길이1 + 방향)로 수정한다면 아래 코드까지
        info.velocity.Normalize(); // = 정규화
    }
    // -> 반복문이 끝나면 파티클 옵션에 따른 각 이미지를 가진 입자 생성
}

void ParticleSystem::LoadData(string file)
{
    // 사전에 설정된 파일이 있을 때, 해당 파일을 읽어서 파티클 설정하기

    BinaryReader* reader = new BinaryReader(file);

    //텍스처 파일 이름을 읽어오기
    wstring textureFile = reader->WString();
    //쿼드 생성 후에 텍스처 적용하기
    quad = new Quad(Vector2(1, 1));
    quad->GetMaterial()->SetDiffuseMap(textureFile);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");

    ParticleData* particleData = new ParticleData();
    reader->Byte((void**)&particleData, sizeof(ParticleData));
    data = *particleData;

    // 파티클 생성 + 재생용
    // 읽어들인 데이터에 의해 벡터 리셋
    instances.resize(data.count);
    particleInfo.resize(data.count);

    //delete particleData;
    delete reader;
}

void ParticleSystem::LoadData(wstring file)
{
    // 그림 파일에서 쿼드 만들기
    quad = new Quad(Vector2(1, 1)); // 표준 크기로 사각형부터 만들기

    // 만든 쿼드에 매티리얼을 세팅 (그림을 바로 안 쓰는 이유 : 바로 쓰면 쿼드 크기가 그림을 따라감)
    quad->GetMaterial()->SetDiffuseMap(file);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl"); // 기본 파티클 셰이더
                                                             // (더 기본으로 가려면 텍스처 셰이더)

    //옵션으로 설정되었던 개수에 맞추어서 인스턴스를 생성(=벡터 예약 및 구성요소 생성)
    //instances.resize(data.count); // 데이터 내의 옵션을 사용할 경우
    instances.resize(particleCount); // 클래스의 멤버 변수를 사용할 경우
                                     // 위쪽 함수에서는 이 줄 대신 data.count만 쓸 것
                                     // (파티클로서의 옵션을 써서)

    //인스턴스의 정보 벡터도 초기화
    //particleInfo.resize(data.count);
    particleInfo.resize(particleCount);

    // -> 그림 파일에서 쿼드 생성 + 인스턴스 생성 + 파티클의 디폴트 옵션 로딩 완료
}