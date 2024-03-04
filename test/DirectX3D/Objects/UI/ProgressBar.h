#pragma once
class ProgressBar : public Quad
{
    // 프로그레스 바 (진행상황 표시기) : 특정 연산의 비중, 달성치 등을 그림의 비율로 나타내는 UI
    //                         생김새의 특성상 (색깔이 채워지는 막대기) 체력바 등에도 응용 가능

public:
    ProgressBar(wstring frontImageFile, wstring backImageFile);
    ~ProgressBar();

    void Render();

    void SetAmount(float value); //amount : (전체 양에 대한) 현재 비중치

private:
    Texture* backImage; // 배경 이미지.
                        // 이 클래스가 쿼드이기 때문에 결과적으로 이미지 2장을 갖는 것

    float fillAmount = 1; // 기본 비중치 = 1 = "전체, 꽉 찼음"

    // 위 변수만 있어도 사실 괜찮지만... 연산 속도를 높이기 위해서
    // 데이터를 데이터 영역(혹은 다른 유닛)으로 옮기고자 한다

    FloatValueBuffer* valueBuffer; // 소수 연산용 버퍼 : 무엇이든지 버퍼로 만들 수 있다!
                                   // 버퍼가 많을수록 해당 데이터는 연산이 빨라지고,
                                   // 전체 앱은 느려지고, 메모리 부담은 커진다.
};

