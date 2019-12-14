// Status: WIP

texture bloomMap;
sampler s0;

sampler BloomSampler : samplerstate
{
	Texture = bloomMap;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

// pseudo gauss blur
static const float2 offsets[12] = {
	-0.326212, -0.405805,
	-0.840144, -0.073580,
	-0.695914,  0.457137,
	-0.203345,  0.620716,
	 0.962340, -0.194983,
	 0.473434, -0.480026,
	 0.519456,  0.767022,
	 0.185461, -0.893124,
	 0.507431,  0.064425,
	 0.896420,  0.412458,
	-0.321940, -0.932615,
	-0.791559, -0.597705,
};

float w;
float h;
static const float2 resolution = float2(w, h);

// blur setting
static const float blurFalloff = 8;
static const float sharpness = 4;

float4 AdjustSaturation(float4 color, float saturation) {
	float grey = dot(color, float3(0.3, 0.59, 0.11));

	return lerp(grey, color, saturation);
}

float Brightness(float3 color)
{
	return color.r * color.g - 0.75 * color.b;
}

float3 BlurFunction(float2 uv, float brightness, inout float totalWeight)
{
	float3 pointColor =(tex2Dlod(s0, float4(uv, 0, 0)).rgb);
	float diff = abs(brightness - Brightness(pointColor));
	float weight = exp2(-0.25 * blurFalloff - diff * sharpness);
	totalWeight += weight;

	return pointColor * weight;
}

float4 BlurPS(float2 uv : TEXCOORD0, uniform float2 delta) : COLOR0
{
	float3 sumColor = (tex2D(s0, uv).rgb);
	float totalWeight = 1;
	float brightness = Brightness(sumColor);
	delta *= (1 / resolution);
	float radius = 1;

		float2 pointUV = uv + delta * radius;
		  sumColor += BlurFunction(pointUV, brightness, totalWeight);
		pointUV = uv - delta * radius;
		  sumColor += BlurFunction(pointUV, brightness, totalWeight);

	return float4((sumColor / totalWeight),1);
//	return AdjustSaturation(Color, 0.5);
}

float4 BloomT(float2 texCoord : TEXCOORD0) : COLOR0 {
	float4 c = tex2D(s0, texCoord);
	float BloomThreshold = 0.2;

	return saturate((c - BloomThreshold) / (1 - BloomThreshold));
}

float4 Bloom(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : COLOR0 {
	float BaseIntensity = 1.0;
	float BaseSaturation = 1;
	float BloomIntensity = 1; // 0.4
	float BloomSaturation = 0.5;
	float BlurPower = 0.01;
	float BloomThreshold = 0.5;

	float4 original = tex2D(s0, texCoord);

	// blur
	float4 sum = tex2D(s0, texCoord);
	for(int i = 0; i < 12; i++){
		sum += tex2D(s0, texCoord + BlurPower * offsets[i]);
	}
	sum /= 13;

	original = AdjustSaturation(original, BaseSaturation) * BaseIntensity;
	sum = AdjustSaturation(sum, BloomSaturation) * BloomIntensity;

	sum = saturate((sum - BloomThreshold) / (1 - BloomThreshold));

	return sum + original;
//	return sum;
}

technique Blur
{
//	pass P2 { PixelShader = compile ps_2_0 BloomT(); }
//	pass P3 { PixelShader = compile ps_2_0 Bloom();  }
	Pass P0 { PixelShader = compile ps_3_0 BlurPS(float2(1, 0)); }
	Pass P1 { PixelShader = compile ps_3_0 BlurPS(float2(0, 1)); }
}
