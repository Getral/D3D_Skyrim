#include "Framework.h"

Refraction::Refraction(wstring normalFile)
{
    waterBuffer = new WaterBuffer();

    normalMap = Texture::Add(normalFile);

    renderTarget = new RenderTarget(2048, 2048); // 수동으로 투사할 공간의 크기 지정
    depthStencil = new DepthStencil(2048, 2048);

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 }; // 사각형을 (실제보다)살짝 당기는 이유 = 실제 위치가 사각형 중심이도록
    Texture* texture = Texture::Add(L"Refraction", renderTarget->GetSRV());
                        // 실시간으로 생성되는 이미지를 텍스처화해서 "일렁임"이라는 이름으로 할당

    quad->GetMaterial()->SetDiffuseMap(texture); // 방금 위에서 만든 텍스처를 디퓨즈맵으로
    quad->UpdateWorld(); //위치(와 매티리얼) 적용

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
    //물 버퍼에서 물결의 (시작) 시간을 증가시켜 누적 시간으로 활용하기
    waterBuffer->Get().waveTime += DELTA;
}

void Refraction::SetRefraction()
{
    // 일렁임 준비
    renderTarget->Set(depthStencil); // <- 스텐실 스테이트와 이후 이 클래스가
                                     // 쓸 셰이더에서 실질 연산이 진행될 것
}

void Refraction::SetRender()
{
    // 일렁임 연산 할당
    waterBuffer->SetPS(10);
    DC->PSSetShaderResources(11, 1, &renderTarget->GetSRV()); // 11번 슬롯에 접근
    normalMap->PSSet(12); // 노멀맵을 셰이더의 12번 슬롯에 할당(=노멀맵 데이터를 연산에 대입)
}

void Refraction::PostRender()
{
    quad->Render(); //(다른 함수 등에서) 준비가 끝난 쿼드를 출력만 하면 그만
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
