// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt


cbuffer ConstantBuffer : register(b0)
{
	float4 StereoParams;
};


struct GeomShaderInput
{
	float4 pos   : SV_POSITION;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD;
	float depth  : TEXCOORD1;
};

struct GeomShaderOutput
{
	float4 pos    : SV_POSITION;
	float4 color  : COLOR0;
	float2 tex    : TEXCOORD;
	float depth   : TEXCOORD1;
	uint viewport : SV_ViewportArrayIndex;
};

float4 GetStereoPos(float4 pos, float eyeSign)
{
	float4 spos = pos;
	spos.x += eyeSign * StereoParams[0] * (spos.w - StereoParams[1]);
	return spos;
}

[instance(2)]
[maxvertexcount(3)]
void main(triangle GeomShaderInput In[3], inout TriangleStream<GeomShaderOutput> TriStream, uint gsInstanceId : SV_GSInstanceID)
{
	GeomShaderOutput output;
	output.viewport = gsInstanceId;
	[unroll] for (int v = 0; v < 3; v++)
	{
		output.pos   = GetStereoPos(In[v].pos, -1.0f + 2.0f * gsInstanceId);
		output.color = In[v].color;
		output.tex   = In[v].tex;
		output.depth = In[v].depth;

		TriStream.Append(output);
	}
}
