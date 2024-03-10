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
	// 왼쪽에서 오른쪽으로 갈수록 투명도 증가
	float transparency = input.uv.x * 0.5;

	// 텍스처 샘플링
	float4 color = diffuseMap.Sample(samp, input.uv);

	// 투명도 적용
	color.a *= transparency;

return color;
}