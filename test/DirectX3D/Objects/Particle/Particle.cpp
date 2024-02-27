#include "Framework.h"

Particle::Particle()
{
    material = new Material();

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true); //이미지 배경색 투명화 적용
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); //가리지 않고 이펙트 전부 재생
}

Particle::~Particle()
{
    delete material;
    delete vertexBuffer;
    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];
}

void Particle::Render()
{
    if (!isActive) return;

    //출력상태 설정
    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

    //렌더 준비
    material->Set();
    geometryShader->Set();

    DC->Draw(particleCount, 0); //얼마나, 어떤 정점부터 그릴 것인가
    DC->GSSetShader(nullptr, nullptr, 0); //추가 옵션 없음 (설정은 윗줄에서 다 했음)

    //출력상태 원상복구
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void Particle::Play(Vector3 pos)
{
    isActive = true;
    position = pos;
}

void Particle::Stop()
{
    isActive = false;
}
