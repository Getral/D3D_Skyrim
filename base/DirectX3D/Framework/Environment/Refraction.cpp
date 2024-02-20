#include "Framework.h"

Refraction::Refraction(wstring normalFile)
{
    waterBuffer = new WaterBuffer();

    normalMap = Texture::Add(normalFile);

    renderTarget = new RenderTarget(2048, 2048); // �������� ������ ������ ũ�� ����
    depthStencil = new DepthStencil(2048, 2048);

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 }; // �簢���� (��������)��¦ ���� ���� = ���� ��ġ�� �簢�� �߽��̵���
    Texture* texture = Texture::Add(L"Refraction", renderTarget->GetSRV());
                        // �ǽð����� �����Ǵ� �̹����� �ؽ�óȭ�ؼ� "�Ϸ���"�̶�� �̸����� �Ҵ�

    quad->GetMaterial()->SetDiffuseMap(texture); // ��� ������ ���� �ؽ�ó�� ��ǻ�������
    quad->UpdateWorld(); //��ġ(�� ��Ƽ����) ����

}

Refraction::~Refraction()
{
    delete renderTarget;
    delete depthStencil;
    delete waterBuffer;
    delete quad;
}

void Refraction::Update()
{
    //�� ���ۿ��� ������ (����) �ð��� �������� ���� �ð����� Ȱ���ϱ�
    waterBuffer->Get().waveTime += DELTA;
}

void Refraction::SetRefraction()
{
    // �Ϸ��� �غ�
    renderTarget->Set(depthStencil); // <- ���ٽ� ������Ʈ�� ���� �� Ŭ������
                                     // �� ���̴����� ���� ������ ����� ��
}

void Refraction::SetRender()
{
    // �Ϸ��� ���� �Ҵ�
    waterBuffer->SetPS(10);
    DC->PSSetShaderResources(11, 1, &renderTarget->GetSRV()); // 11�� ���Կ� ����
    normalMap->PSSet(12); // ��ָ��� ���̴��� 12�� ���Կ� �Ҵ�(=��ָ� �����͸� ���꿡 ����)
}

void Refraction::PostRender()
{
    quad->Render(); //(�ٸ� �Լ� ���) �غ� ���� ���带 ��¸� �ϸ� �׸�
}

void Refraction::GUIRender()
{
    ImGui::Text("Water Refraction Option");
    ImGui::ColorEdit4("WaveColor", (float*)&waterBuffer->Get().color);

    ImGui::SliderFloat("WaveSpeed", &waterBuffer->Get().waveSpeed, 0, 3);
    ImGui::SliderFloat("WaveScale", &waterBuffer->Get().waveScale, 0, 3);
    ImGui::SliderFloat("WaveShininess", &waterBuffer->Get().waveShininess, 0, 50);
    ImGui::SliderFloat("WaveFrensel", &waterBuffer->Get().frensel, 0, 1);
}
