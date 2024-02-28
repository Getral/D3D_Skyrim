#include "Framework.h"

SkyBox::SkyBox(wstring file)
{
    //텍스처와 셰이더 적용
    skyMap = Texture::Add(file);
    //material->SetShader(L"Basic/Texture.hlsl"); //기본
    material->SetShader(L"Landscape/Skybox.hlsl"); //맞춤 셰이더

    FOR(2)
    {
        rasterizerState[i] = new RasterizerState();
        depthStencilState[i] = new DepthStencilState();
    }
    rasterizerState[1]->FrontCounterClockwise(true); // 래스터에서 "앞" = 양면
                                                     // = 양면을 모두 앞으로 치겠다
    depthStencilState[1]->DepthEnable(false);        // 화소 우선순위 무시 =
                                    //"이거보다 앞에 있는 그림은 무조건 앞에 있는 걸로 친다"

    // -> 안에서 텍스처가 보이고, 배경이 있으면 하늘은 무조건 가려지는 결과
}

SkyBox::~SkyBox()
{
    FOR(2)
        delete rasterizerState[i];

    FOR(2)
        delete depthStencilState[i];
}

void SkyBox::Render()
{
    skyMap->PSSet(10); // 이미지로서 연산할 슬롯 (셰이더에서 10에 지정된 조건이 있으면 따르고,
                       //                       10보다 낮은 우선순위가 있으면 먼저 연산된다)

    // 스카이박스용 옵션이 적용된 상태를 호출
    rasterizerState[1]->SetState();
    depthStencilState[1]->SetState();

    Sphere::Render(); // 구체로서 자신을 렌더

    //상태 복구
    rasterizerState[0]->SetState();
    depthStencilState[0]->SetState();

}
