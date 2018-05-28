
Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
	float2 tex : TEXCOORD;
};

float4 packDepth(float depth)
{
	uint uiDepth = asuint(depth);
	return float4((uiDepth & 255) / 255.0f, ((uiDepth >> 8) & 255) / 255.0f, ((uiDepth >> 16) & 255) / 255.0f, (uiDepth >> 24) / 255.0f);
}

float4 main(PixelShaderInput input, uint rtIndex : SV_RenderTargetArrayIndex)  : SV_TARGET
{
	float4 outColor = input.color;
#ifdef PS_TEXTURE
	float4 texColor = texture0.Sample(sampler0, input.tex);
#ifdef PS_ALPHA_TEST_NO_ALPHA
	if (texColor.a < 1 || input.color.a == 0) discard;
#endif
	outColor *= texColor;
#ifdef PS_ALPHA_TEST
	if (outColor.a == 0) discard;
#endif
#else //PS_TEXTURE
	//outColor = float4(0, 0, 1, 1);
#endif//PS_TEXTURE

	return (rtIndex == 2) ? packDepth(input.pos.w) : outColor;
}
