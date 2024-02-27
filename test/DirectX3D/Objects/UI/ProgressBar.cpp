#include "Framework.h"

ProgressBar::ProgressBar(wstring frontImageFile, wstring backImageFile)
    : Quad(frontImageFile)
{
    // 쿼드 설정 진행
    material->SetShader(L"UI/ProgressBar.hlsl"); // 2D만 계산하는 셰이더

    // 후면 이미지 생성
    backImage = Texture::Add(backImageFile);

    valueBuffer = new FloatValueBuffer(); // 소수 연산용 버퍼 만들기
    valueBuffer->Get()[0] = fillAmount; // valueBuffer->Get() : 현 프레임워크의 버퍼 호출 인터페이스
                                        // [0] : 버퍼의 첫 번째 값
                                        // fillAmount : 버퍼에 대입할 데이터
}

ProgressBar::~ProgressBar()
{
    delete valueBuffer;
}

void ProgressBar::Render()
{
    valueBuffer->SetPS(10); // GPU가 연산하도록 지시 + 슬롯(출력우선순위) 10
    backImage->PSSet(10);   // 후면 이미지 데이터도 픽셀 셰이더에 준비

    Quad::Render(); //쿼드 렌더
}

void ProgressBar::SetAmount(float value)
{
    valueBuffer->Get()[0] = value; //버퍼에 매개변수로 받은 값을 그대로 대입
}
