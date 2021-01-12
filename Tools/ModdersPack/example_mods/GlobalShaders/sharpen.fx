// Shader from Media Player Classic - Home Cinema
// Adapted to sfall by Mr.Stalin

///////////////////////////////////////////////////////////////////////////////
// Sharpen filter setting
//
// min: Sharpen 0.5,  EdgeSharpen  1.0
// mid: Sharpen 1.0,  EdgeSharpen -0.25
// max: Sharpen 1.75, EdgeSharpen -0.5  (1.5, -0.25)
///////////////////////////////////////////////////////////////////////////////
#define Sharpen      0.5
#define EdgeSharpen  1.1

sampler s0;

// Variables that set the width and height of the current game resolution from sfall
float w;
float h;
float2 rcpres; // pixel size

static const float CoefBlur = (Sharpen * 0.5);
static const float CoefOrig = (1 + CoefBlur);

// for the sharpen edge
#define SharpenEdge 0.4
static const float sharpenVal0 = (Sharpen * (1.5 + EdgeSharpen));
static const float sharpenVal1 = ((sharpenVal0 - 1) / 8.0);

// pixel "width"
static const float px = rcpres.x;
static const float py = rcpres.y;

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

technique SharpenT
{
	pass P0 { PixelShader = compile ps_2_0 SharpenComplexPS(); }
}
