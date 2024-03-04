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

cbuffer ValueBuffer : register(b10)
{
	float fillAmount;
}

Texture2D backImage : register(t10);

float4 PS(PixelInput input) : SV_TARGET
{	
	float flippedUV = 1.0f - input.uv.x;
	if (flippedUV < fillAmount)
		return diffuseMap.Sample(samp, float2(flippedUV, input.uv.y));

	return backImage.Sample(samp, input.uv);
}