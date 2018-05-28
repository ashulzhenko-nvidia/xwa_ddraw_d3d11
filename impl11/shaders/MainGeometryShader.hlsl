struct GeomShaderInput
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

struct GeomShaderOutput
{
	float4 pos    : SV_POSITION;
	float2 tex    : TEXCOORD;
	uint arrayIdx : SV_RenderTargetArrayIndex;
};


[instance(2)]
[maxvertexcount(3)]
void main(triangle GeomShaderInput In[3], inout TriangleStream<GeomShaderOutput> TriStream, uint gsInstanceId : SV_GSInstanceID)
{
	GeomShaderOutput output;
	output.arrayIdx = gsInstanceId;
	[unroll] for (int v = 0; v < 3; v++)
	{
		output.pos = In[v].pos;
		output.tex = In[v].tex;

		TriStream.Append(output);
	}
}
