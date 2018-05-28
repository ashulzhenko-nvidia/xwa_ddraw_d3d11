float4 main(uint vIdx : SV_VertexID) : SV_POSITION
{
	float2 tex = float2(vIdx % 2, vIdx % 4 / 2);
	return float4((tex.x - 0.5f) * 2, -(tex.y - 0.5f) * 2, 0, 1);
}
