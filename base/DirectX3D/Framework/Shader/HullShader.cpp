#include "Framework.h"

HullShader::HullShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    // 윈도우 옵션 설정 : 1. Dx3D에서 리소스가 있을 때 사전 설정을 준수하라고 되어 있으면 그대로 따르기
    //                   2. 디버그로 설정이 되어 있어도 시킨 대로 하기

    D3DCompileFromFile(file.c_str(),            // 컴파일할 셰이더 코드
        nullptr,                                // 추가 옵션 코드
        D3D_COMPILE_STANDARD_FILE_INCLUDE,      // 컴파일할 때 추가로 포함(참조)할 DX 파일
        "HS",                                   // 진입점(셰이더 코드 입장에서의 main함수 비슷한 것)
        "hs_5_0",                               // 사용할 셰이더(종류와 버전)
        flags,                                  // 컴파일 시에 적용할 윈도우 옵션
        0,                                      // 추가 윈도우 옵션이 있다면 여기서
        &blob,                                  // 블롭 데이터 : 아직 셰이더나 수학처리 등을 거치지 않은 원형 미디어 데이터를 총칭
        nullptr                                 // 추가로 블롭을 처리하다가 오류가 났을 경우 대처할 행동 지정
    );

    DEVICE->CreateHullShader(blob->GetBufferPointer(), //블롭 내에 있었던(지정된) 버퍼의 메모리 포인터
        blob->GetBufferSize(),                         //블롭을 처리하기 위한 버퍼 크기
        nullptr,                                       //추가로 적용할 셰이더 옵션
        &shader);                                      //셰이더 데이터
}

HullShader::~HullShader()
{
    shader->Release();
}

void HullShader::Set()
{
    //출력장치에서 불러와진 셰이더를 (옵션 그대로) 설정
    DC->HSSetShader(shader, nullptr, 0); // shader의 지정 옵션대로, 추가 옵션은 없이
                                         // -> 외부에서 불렀더라면 shader에 들어갔을
                                         // 다른 옵션도 미리 준비한 후, 매개변수는
                                         // nullptr, nullptr, 0으로 했을 것
}
