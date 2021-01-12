/*************************************************************
   LumaSharpen version 1.5.0 for Reshade 3.x
   by Christian Cann Schuldt Jensen ~ CeeJay.dk

   It blurs the original pixel with the surrounding pixels and then subtracts this blur to sharpen the image.
   It does this in luma to avoid color artifacts and allows limiting the maximum sharpning to avoid or lessen halo artifacts.
   This is similar to using Unsharp Mask in Photoshop.

   Adapted to sfall by Mr.Stalin
*************************************************************/

// Strength of the sharpening
// min 0.1, max 3.0
#define sharp_strength 0.75

// Limits maximum amount of sharpening a pixel receives. This helps avoid "haloing" artifacts which would otherwise occur when you raised the strength too much
// min 0.0, max 1.0, step 0.005
#define sharp_clamp 0.035

// Offset bias adjusts the radius of the sampling pattern. I designed the pattern for an offset bias of 1.0, but feel free to experiment
// min 0.0, max 6.0
#define offset_bias 1.0

//------------------------------------------------------//
//                  Developer settings                  //
//------------------------------------------------------//

#define CoefLuma float3(0.2126, 0.7152, 0.0722)      // BT.709 & sRBG luma coefficient (Monitors and HD Television)
//#define CoefLuma float3(0.299, 0.587, 0.114)       // BT.601 luma coefficient (SD Television)
//#define CoefLuma float3(1.0/3.0, 1.0/3.0, 1.0/3.0) // Equal weight coefficient

sampler s0;

float2 rcpres; // pixel size

float4 LumaSharpenPS(float4 color : COLOR0, float2 tex : TEXCOORD) : COLOR0
{
	// Get the original pixel
	float3 ori = tex2D(s0, tex).rgb; // ori = original pixel

	// Combining the strength and luma multipliers
	float3 sharp_strength_luma = (CoefLuma * sharp_strength); // I'll be combining even more multipliers with it later on

	//------------------------------------------------------//
	//                   Sampling patterns                  //
	//------------------------------------------------------//
	float3 blur_ori;

	//   [ NW,   , NE ] Each texture lookup (except ori)
	//   [   ,ori,    ] samples 4 pixels
	//   [ SW,   , SE ]

	// -- Pattern 2 -- A 9 tap gaussian using 4+1 texture fetches.
	//
	// -- Gaussian filter --
	//   [ .25, .50, .25]     [ 1 , 2 , 1 ]
	//   [ .50,   1, .50]  =  [ 2 , 4 , 2 ]
	//   [ .25, .50, .25]     [ 1 , 2 , 1 ]

	blur_ori  = tex2D(s0, tex + float2(rcpres.x, -rcpres.y) * 0.5 * offset_bias).rgb; // South East
	blur_ori += tex2D(s0, tex - rcpres * 0.5 * offset_bias).rgb;                      // South West
	blur_ori += tex2D(s0, tex + rcpres * 0.5 * offset_bias).rgb;                      // North East
	blur_ori += tex2D(s0, tex - float2(rcpres.x, -rcpres.y) * 0.5 * offset_bias).rgb; // North West
	blur_ori *= 0.25;  // Divide by 4 the number of texture fetches

	// -- Pattern 3 -- An experimental 17 tap gaussian using 4+1 texture fetches.
	// Wider is less sensitive to noise but also to fine details.
	// -- Gaussian filter --
	//   [   , 4 , 6 ,   ,   ]
	//   [   ,16 ,24 ,16 , 4 ]
	//   [ 6 ,24 ,   ,24 , 6 ]
	//   [ 4 ,16 ,24 ,16 ,   ]
	//   [   ,   , 6 , 4 ,   ]

	//blur_ori  = tex2D(s0, tex + rcpres * float2(0.4, -1.2) * offset_bias).rgb; // South South East
	//blur_ori += tex2D(s0, tex - rcpres * float2(1.2, 0.4) * offset_bias).rgb;  // West South West
	//blur_ori += tex2D(s0, tex + rcpres * float2(1.2, 0.4) * offset_bias).rgb;  // East North East
	//blur_ori += tex2D(s0, tex - rcpres * float2(0.4, -1.2) * offset_bias).rgb; // North North West
	//blur_ori *= 0.25;  // Divide by the number of texture fetches
	//sharp_strength_luma *= 0.51;

	// -- Pattern 4 -- A 9 tap high pass (pyramid filter) using 4+1 texture fetches.
	// Pyramid has a slightly more aggresive look
	// -- Gaussian filter --
	//   [ .50, .50, .50]     [ 1 , 1 , 1 ]
	//   [ .50,    , .50]  =  [ 1 ,   , 1 ]
	//   [ .50, .50, .50]     [ 1 , 1 , 1 ]

	//blur_ori  = tex2D(s0, tex + float2(0.5 * rcpres.x, -rcpres.y * offset_bias)).rgb;  // South South East
	//blur_ori += tex2D(s0, tex + float2(offset_bias * -rcpres.x, 0.5 * -rcpres.y)).rgb; // West South West
	//blur_ori += tex2D(s0, tex + float2(offset_bias * rcpres.x, 0.5 * rcpres.y)).rgb;   // East North East
	//blur_ori += tex2D(s0, tex + float2(0.5 * -rcpres.x, rcpres.y * offset_bias)).rgb;  // North North West
	////blur_ori += (2 * ori); // Probably not needed. Only serves to lessen the effect.
	//blur_ori /= 4.0;  // Divide by the number of texture fetches
	//sharp_strength_luma *= 0.666; // Adjust strength to aproximate the strength of pattern 2

	//------------------------------------------------------//
	//                        Sharpen                       //
	//------------------------------------------------------//

	// Calculate the sharpening --
	float3 sharp = ori - blur_ori; // Subtracting the blurred image from the original image

	// Adjust strength of the sharpening and clamp it
	float4 sharp_strength_luma_clamp = float4(sharp_strength_luma * (0.5 / sharp_clamp), 0.5); // Roll part of the clamp into the dot

	//sharp_luma = saturate((0.5 / sharp_clamp) * sharp_luma + 0.5); // scale up and clamp
	float sharp_luma = saturate(dot(float4(sharp, 1.0), sharp_strength_luma_clamp)); // Calculate the luma, adjust the strength, scale up and clamp
	sharp_luma = (sharp_clamp * 2.0) * sharp_luma - sharp_clamp; // scale down

	// Combining the values to get the final sharpened pixel
	float3 outputcolor = ori + sharp_luma; // Add the sharpening to the the original.

	//------------------------------------------------------//
	//                 Returning the output                 //
	//------------------------------------------------------//

	// Show sharpening pattern
	// Visualize the strength of the sharpen\nThis is useful for seeing what areas the sharpning affects the most
	//outputcolor = saturate(0.5 + (sharp_luma * 4.0)).rrr; //outputcolor = abs(sharp * 4.0);

	return float4(saturate(outputcolor), 1);
}

technique LumaSharpen
{
	pass P0 { PixelShader = compile ps_2_0 LumaSharpenPS(); }
}
