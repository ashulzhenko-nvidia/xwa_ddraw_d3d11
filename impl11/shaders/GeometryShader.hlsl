Texture2D textureDepth : register(t0);

cbuffer ConstantBuffer : register(b0)
{
	float4 StereoParamsArray[3];
	float4 ObjCenter;
};

struct GeomShaderInput
{
	float4 pos   : SV_POSITION;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD;
};

struct GeomShaderOutput
{
	float4 pos    : SV_POSITION;
	float4 color  : COLOR0;
	float2 tex    : TEXCOORD;
	uint arrayIdx : SV_RenderTargetArrayIndex;
};

float4 GetStereoPos(float4 pos, float4 stereoParams)
{
	if (stereoParams.z == 1)
	{
		float2 absSrcPos = abs((pos.xy / pos.w) - float2(0.0f, 0.16f));
		if (absSrcPos.x < 0.15f & absSrcPos.y < 0.2f)
		{
			//move to infinity
			stereoParams[1] = 0.0f;
		}
		else
		{
			//move to screen (convergence) depth = make mono
			stereoParams[0] = 0.0f;
			stereoParams[1] = 0.0f;
		}
	}
	else
	if (stereoParams.z == 2)
	{
		float centerDepth = textureDepth.Load(int3(ObjCenter.xy, 0)).r;
		// place pos at depth
		if (isfinite(centerDepth))
		{
			stereoParams[1] = 0.0f;
		}
		else
		{
			pos.xyz *= centerDepth / pos.w;
			pos.w = centerDepth;
		}
	}

	pos *= stereoParams.w; // scale depth
	return float4(pos.x + stereoParams[0] * (pos.w - stereoParams[1]), pos.yzw);
}

[instance(3)]
[maxvertexcount(3)]
void main(triangle GeomShaderInput In[3], inout TriangleStream<GeomShaderOutput> TriStream, uint gsInstanceId : SV_GSInstanceID)
{
	GeomShaderOutput output;
	output.arrayIdx = gsInstanceId;
	[unroll] for (int v = 0; v < 3; v++)
	{
		output.pos   = GetStereoPos(In[v].pos, StereoParamsArray[gsInstanceId]);
		output.color = In[v].color;
		output.tex   = In[v].tex;

		TriStream.Append(output);
	}
}
