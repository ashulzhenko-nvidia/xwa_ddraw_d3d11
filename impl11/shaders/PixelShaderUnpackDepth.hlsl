#ifdef MULTI_SAMPLING
Texture2DMS<float4> texture0 : register(t0);
#else
Texture2D<float4> texture0 : register(t0);
#endif

float unpackDepth(float4 packedDepth)
{
	uint uiDepth = uint(packedDepth.r * 255) | (uint(packedDepth.g * 255) << 8) | (uint(packedDepth.b * 255) << 16) | (uint(packedDepth.a * 255) << 24);
	return asfloat(uiDepth);
}

float main(float4 pos : SV_POSITION) : SV_TARGET
{
#ifdef MULTI_SAMPLING
	float4 packedDepth = texture0.Load(int2(pos.xy), 0); // fetch sample 0
#else
	float4 packedDepth = texture0.Load(int3(pos.xy, 0));
#endif
	return unpackDepth(packedDepth);
}
