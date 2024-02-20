#include "Framework.h"

Particle::Particle()
{
    material = new Material();

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true); //�̹��� ���� ����ȭ ����
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); //������ �ʰ� ����Ʈ ���� ���
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

    //��»��� ����
    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

    //���� �غ�
    material->Set();
    geometryShader->Set();

    DC->Draw(particleCount, 0); //�󸶳�, � �������� �׸� ���ΰ�
    DC->GSSetShader(nullptr, nullptr, 0); //�߰� �ɼ� ���� (������ ���ٿ��� �� ����)

    //��»��� ���󺹱�
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
