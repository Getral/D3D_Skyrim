#include "Framework.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
    : data(data), dataSize(dataSize)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.ByteWidth = dataSize;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &buffer);
}

ConstBuffer::~ConstBuffer()
{
    buffer->Release();
}

void ConstBuffer::SetVS(UINT slot)
{
    //DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    memcpy(subResource.pData, data, dataSize);
    DC->Unmap(buffer, 0);

    DC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetPS(UINT slot)
{
    //DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    memcpy(subResource.pData, data, dataSize);
    DC->Unmap(buffer, 0);

    DC->PSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetCS(UINT slot)
{
    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    memcpy(subResource.pData, data, dataSize);
    DC->Unmap(buffer, 0);

    DC->CSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetGS(UINT slot)
{
    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    memcpy(subResource.pData, data, dataSize);
    DC->Unmap(buffer, 0);

    DC->GSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetHS(UINT slot)
{
    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
        //Map : 버퍼를 출력용 맵으로 등록하는 함수
        //매개변수 : 출력대상, 추가자료(없음), 옵션(쓰고 폐기(discard)), 추가옵션, 정보 저장
    memcpy(subResource.pData, data, dataSize); //저장된 정보 피드백(연속 사용)
    DC->Unmap(buffer, 0); //출력등록 해제

    DC->HSSetConstantBuffers(slot, 1, &buffer); //버퍼를 셰이더에 등록하고 준비
}

void ConstBuffer::SetDS(UINT slot)
{
    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    memcpy(subResource.pData, data, dataSize);
    DC->Unmap(buffer, 0);
    DC->DSSetConstantBuffers(slot, 1, &buffer);
}
