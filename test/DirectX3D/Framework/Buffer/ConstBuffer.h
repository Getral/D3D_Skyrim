#pragma once

class ConstBuffer
{
public:
    ConstBuffer(void* data, UINT dataSize);
    ~ConstBuffer();

    void SetVS(UINT slot);
    void SetPS(UINT slot);
    void SetCS(UINT slot);
    void SetGS(UINT slot);

private:
    ID3D11Buffer* buffer;

    void* data;
    UINT dataSize;

    D3D11_MAPPED_SUBRESOURCE subResource;
};