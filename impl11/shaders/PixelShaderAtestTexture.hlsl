// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt


Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
	float2 tex : TEXCOORD;
	float depth : TEXCOORD1;
};

void main(PixelShaderInput input, out float4 outColor : SV_TARGET, out float outDepth : SV_TARGET1)
{
	float4 texelColor = texture0.Sample(sampler0, input.tex);
	texelColor *= input.color;
	if (texelColor.a == 0) discard;

	outColor = texelColor;
	outDepth = input.depth;
}
