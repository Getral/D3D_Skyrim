#include "Framework.h"

unordered_map<wstring, Shader*> Shader::shaders;

Shader::~Shader()
{
    blob->Release();
}

VertexShader* Shader::AddVS(wstring file)
{   
    if (file.size() == 0)
        file = L"Light/Light.hlsl";

    wstring key = file + L"VS";    

    if (shaders.count(key) > 0)
        return (VertexShader*)shaders[key];

    wstring path = L"Shaders/" + file;    

    shaders[key] = new VertexShader(path);

    return (VertexShader*)shaders[key];
}

PixelShader* Shader::AddPS(wstring file)
{
    if (file.size() == 0)
        file = L"Light/Light.hlsl";

    wstring key = file + L"PS";

    if (shaders.count(key) > 0)
        return (PixelShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new PixelShader(path);

    return (PixelShader*)shaders[key];
}

ComputeShader* Shader::AddCS(wstring file)
{
    wstring key = file;

    if (shaders.count(key) > 0)
        return (ComputeShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new ComputeShader(path);

    return (ComputeShader*)shaders[key];
}

GeometryShader* Shader::AddGS(wstring file)
{
    wstring key = file;

    if (shaders.count(key) > 0)
        return (GeometryShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new GeometryShader(path);

    return (GeometryShader*)shaders[key];
}

HullShader* Shader::AddHS(wstring file)
{
    wstring key = file + L"HS"; // 헐/도메인 셰이더는 절차의 부분이기 때문에
                                // 각각 같은 셰이더의 다른 코드를 쓸 수도 있다
                                // 그 경우 각 셰이더가 이 클래스의 맵 속에서
                                // 어떻게 구분되는지도 키의 구분이 필요하다

    if (shaders.count(key) > 0)
        return (HullShader*)shaders[key];   //중복방지 + 사전에 등록된 키가 있으면 반환

    wstring path = L"Shaders/" + file;
    shaders[key] = new HullShader(path); // 셰이더 실질 생성
    return (HullShader*)shaders[key]; // 생성된 셰이더 반환

    // -> 이 과정으로 앱 속에 셰이더를 만듦과 동시에 객체 속 포인터 변수가 데이터를 가질 수 있다
}

DomainShader* Shader::AddDS(wstring file)
{
    wstring key = file + L"DS";

    if (shaders.count(key) > 0)
        return (DomainShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new DomainShader(path);
    
    return (DomainShader*)shaders[key];
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders)
        delete shader.second;
}
