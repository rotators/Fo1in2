string texname1 = "weather\\mask-map.png";
texture tex1;
string texname2 = "";
texture tex2;

static const float tscale=3;
int tickcount;
float multi;
float speed;

sampler s0;
sampler s1 = sampler_state {
	texture = <tex1>;
};
sampler s2 = sampler_state {
	texture = <tex2>;
	addressu=wrap;
	addressv=wrap;
};

float4 ps_p0(float2 tex : TEXCOORD0) : COLOR0
{
	float3 r1=tex2D(s0, tex);

	float offset=(float)tickcount/speed;
	float2 y={0.342, 0.940};
	y*=offset;
	float3 r2=tex2D(s2, tex*tscale-y)*tex2D(s1, tex)*multi;
	float alpha=r2.g;
	r1=r1*(1-alpha) + r2*alpha;
	return float4(saturate(r1), 1);
}


technique T0
{
	pass P0 { PixelShader = compile ps_2_0 ps_p0(); }
}