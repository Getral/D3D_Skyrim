#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

PixelInput VS(VertexUV input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;

	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	// ���ʿ��� ���������� ������ ���� ����
	float transparency = 1 - input.uv.x;

	// �ؽ�ó ���ø�
	float4 color = diffuseMap.Sample(samp, input.uv);

	// ���� ����
	color.a *= transparency * 0.5f;

return color;
}