sampler s0;

static const float2 rcpres =
{
	0.0015625,
	0.0020833333333333333333333333333333
};

float4 Blur(float2 Tex : TEXCOORD0) : COLOR0
{
	float4 Color = 0;

	Color += tex2D( s0, float2(Tex.x, Tex.y));
	Color += tex2D(s0, float2(Tex.x + rcpres.x, Tex.y));
	Color += tex2D(s0, float2(Tex.x - rcpres.x, Tex.y));
	Color += tex2D(s0, float2(Tex.x, Tex.y + rcpres.y));
	Color += tex2D(s0, float2(Tex.x, Tex.y - rcpres.y));

	return Color * 0.2;
}

float4 Blind(float2 Tex : TEXCOORD0) : COLOR0
{
	float4 Color = tex2D(s0, Tex);
	return Color * saturate(1.5 - (length(Tex - 0.5)*2));
}

Technique blur
{
	Pass P0 { PixelShader = compile ps_2_0 Blur(); }
	Pass P1 { PixelShader = compile ps_2_0 Blur(); }
	Pass P2 { PixelShader = compile ps_2_0 Blur(); }
	Pass P3 { PixelShader = compile ps_2_0 Blur(); }
	Pass P4 { PixelShader = compile ps_2_0 Blur(); }
	Pass P5 { PixelShader = compile ps_2_0 Blind(); }
}