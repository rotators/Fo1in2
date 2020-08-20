///////////////////////////////////////////////////////////////////////////////
// Blur filter setting
//
// min: blurFalloff 8, sharpness 10/8
// mid: blurFalloff 6, sharpness 8
// max: blurFalloff 4, sharpness 6
///////////////////////////////////////////////////////////////////////////////
#define blurFalloff 4.0
#define sharpness   6.0

///////////////////////////////////////////////////////////////////////////////
// Sharpen filter setting
//
// min: Sharpen 0.5,  EdgeSharpen  1.0
// mid: Sharpen 1.0,  EdgeSharpen -0.25
// max: Sharpen 1.75, EdgeSharpen -0.5  (1.5, -0.25)
///////////////////////////////////////////////////////////////////////////////
#define Sharpen      0.5
#define EdgeSharpen  1.0


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

// Variables that set the width and height of the current game resolution from sfall
float w;
float h;

static const float2 resolution = float2(w, h);
static const float2 wPass = float2(1, 0);
static const float2 hPass = float2(0, 1);

float Brightness(float3 color)
{
	return 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
}

float3 BlurFunction(float2 uv, float brightness, inout float totalWeight)
{
	float3 pointColor = (tex2Dlod(s0, float4(uv, 0, 0)).rgb);

	float diff = abs(brightness - Brightness(pointColor));
	float weight = exp2((-0.25 * blurFalloff) - (diff * sharpness));
	totalWeight += weight;

	return pointColor * weight;
}

float4 BlurDeltaPassPS(float2 uv : TEXCOORD0, uniform float2 delta) : COLOR0
{
	float3 sumColor = (tex2D(s0, uv).rgb);
	float brightness = Brightness(sumColor);

	delta *= (1 / resolution);
	float totalWeight = 1;

	float2 pointUV = uv + delta;
	sumColor += BlurFunction(pointUV, brightness, totalWeight);

	pointUV = uv - delta;
	sumColor += BlurFunction(pointUV, brightness, totalWeight);

	return float4((sumColor / totalWeight), 1);
}

static const float2 wDelta = float2(1, 0) * (1 / resolution);
static const float2 hDelta = float2(0, 1) * (1 / resolution);

float4 BlurPS(float4 color : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	float totalWeight = 1;

	float3 sumColor = (tex2D(s0, uv).rgb);
	float brightness = Brightness(sumColor);

	float2 pointUV = uv + wDelta;
	sumColor += BlurFunction(pointUV, brightness, totalWeight);

	pointUV = uv - wDelta;
	sumColor += BlurFunction(pointUV, brightness, totalWeight);

	pointUV = uv + hDelta;
	sumColor += BlurFunction(pointUV, brightness, totalWeight);

	pointUV = uv - hDelta;
	sumColor += BlurFunction(pointUV, brightness, totalWeight);

	return float4((sumColor / totalWeight), 1);
}

///////////////////////////////////////////////////////////////////////////////
// Bloom effect setting
//
// min: BloomIntensity .8
// mid: BloomIntensity .85
// max: BloomIntensity .9
///////////////////////////////////////////////////////////////////////////////
#define BaseIntensity   1.2
#define BaseSaturation  1.0

#define BloomIntensity  0.8
#define BloomSaturation 0.35

#define BloomThreshold  0.35
#define BlurPower       0.002

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

float4 AdjustSaturation(float4 color, float saturation)
{
	float grey = dot(color, float3(0.3, 0.59, 0.11));
	return lerp(grey, color, saturation);
}

float4 BloomPS(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : COLOR0
{
	float4 original = tex2D(s0, texCoord);
	original = AdjustSaturation(original, BaseSaturation) * BaseIntensity;
	float sum = (original.r + original.g + original.b) * 0.333;
	if (sum >= 0.95) return original;

	// bloom blur
	float4 bloomBlur = tex2D(s0, texCoord);
	for(int i = 0; i < 12; i++)
	{
		bloomBlur += tex2D(s0, texCoord + BlurPower * offsets[i]);
	}
	bloomBlur *= 0.085;

	float intensity = BloomIntensity - lerp(0.0, 0.2, sum);
	bloomBlur = AdjustSaturation(bloomBlur, BloomSaturation) * intensity;
	bloomBlur = saturate((bloomBlur - BloomThreshold) / (1 - BloomThreshold));

	return bloomBlur + original;
}

static const float CoefBlur = (Sharpen * 0.5);
static const float CoefOrig = (1 + CoefBlur);

// for the sharpen edge
#define SharpenEdge 0.4
static const float sharpenVal0 = (Sharpen * (1.5 + EdgeSharpen));
static const float sharpenVal1 = ((sharpenVal0 - 1) / 8.0);

// pixel "width"
static const float px = (1.0 / w);
static const float py = (1.0 / h);

// for the blur filter
#define mean 1.0
static const float dx = (mean * px);
static const float dy = (mean * py);

float4 SharpenComplexPS(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : COLOR0
{
	float4 c0 = tex2D(s0, texCoord); // get original pixel

	// edge detection
	// Get neighbor points
	// [ c1, c2, c3 ]
	// [ c4, c0, c5 ]
	// [ c6, c7, c8 ]
	float4 c1 = tex2D(s0, texCoord + float2(-px, -py));
	float4 c2 = tex2D(s0, texCoord + float2(  0, -py));
	float4 c3 = tex2D(s0, texCoord + float2( px, -py));
	float4 c4 = tex2D(s0, texCoord + float2(-px,   0));
	float4 c5 = tex2D(s0, texCoord + float2( px,   0));
	float4 c6 = tex2D(s0, texCoord + float2(-px,  py));
	float4 c7 = tex2D(s0, texCoord + float2(  0,  py));
	float4 c8 = tex2D(s0, texCoord + float2( px,  py));

	// using Sobel filter
	// horizontal gradient
	// [ -1, 0, 1 ]
	// [ -2, 0, 2 ]
	// [ -1, 0, 1 ]
	float delta1 = (c3 + 2 * c5 + c8) - (c1 + 2 * c4 + c6);

	// vertical gradient
	// [ -1, - 2, -1 ]
	// [  0,   0,  0 ]
	// [  1,   2,  1 ]
	float4 c13 = c1 + c3;
	float4 c68 = c6 + c8;
	float delta2 = (c68 + 2 * c7) - (c13 + 2 * c2);

	// computation
	if (sqrt(mul(delta1, delta1) + mul(delta2, delta2)) > SharpenEdge) {
		// if we have an edge, use sharpen
		return c0 * sharpenVal0 - (c13 + c2 + c4 + c5 + c68 + c7) * sharpenVal1;

		// Display edges in red...
		//return float4( 1.0, 0.0, 0.0, 0.0 );
	} else {
		// else return corrected image

		// compute blurred image (gaussian filter)
		c1 = tex2D(s0, texCoord + float2(-dx, -dy));
		c2 = tex2D(s0, texCoord + float2(  0, -dy));
		c3 = tex2D(s0, texCoord + float2( dx, -dy));
		c4 = tex2D(s0, texCoord + float2(-dx,   0));
		c5 = tex2D(s0, texCoord + float2( dx,   0));
		c6 = tex2D(s0, texCoord + float2(-dx,  dy));
		c7 = tex2D(s0, texCoord + float2(  0,  dy));
		c8 = tex2D(s0, texCoord + float2( dx,  dy));

		// gaussian filter
		// [ 1, 2, 1 ]
		// [ 2, 4, 2 ]
		// [ 1, 2, 1 ]
		// to normalize the values, we need to divide by the coeff sum
		float4 flou = (c1 + c3 + c6 + c8 + 2 * (c2 + c4 + c5 + c7) + 4 * c0) * 0.0625; // 1 / (1+2+1+2+4+2+1+2+1) = 1 / 16 = 0.0625

		// substract blurred image from original image
		return (CoefOrig * c0 - CoefBlur * flou);
	}
}

technique BlurBloom
{
	//pass P0 { PixelShader = compile ps_3_0 BlurDeltaPassPS(wPass); }
	//pass P1 { PixelShader = compile ps_3_0 BlurDeltaPassPS(hPass); }

	pass P0 { PixelShader = compile ps_3_0 BlurPS(); }
	pass P3 { PixelShader = compile ps_2_0 BloomPS(); }
	pass P2 { PixelShader = compile ps_2_0 SharpenComplexPS(); }
}
