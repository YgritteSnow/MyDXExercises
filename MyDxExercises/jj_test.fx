
float4x4 WorldTransform;
float4x4 ViewTransform;
float4x4 ProjTransform;
float4x4 ViewProjTransform;
float4x4 WorldViewProjTransform;

texture DiffuseTexture;

sampler DiffuseTextureSampler = sampler_state
{
    Texture = <DiffuseTexture>;
    MinFilter = LINEAR;  
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU  = WRAP;
    AddressV  = WRAP;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float2 tex : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

VS_OUTPUT vs_main( VS_INPUT vs_in )
{
	VS_OUTPUT vs_out = (VS_OUTPUT)0;
	float w = vs_in.position.w;
	vs_out.position = mul(vs_in.position, ViewProjTransform);
	vs_out.color = float4(vs_in.tex, 0.0, 1.0);

	vs_out.tex = vs_in.tex;
	return vs_out;
}

float4 ps_main( VS_OUTPUT ps_in ) : COLOR
{
	return tex2D(DiffuseTextureSampler, ps_in.tex);
}

Technique Default
{
	Pass pass0
	{
		VertexShader = compile vs_1_0 vs_main();
		PixelShader = compile ps_1_0 ps_main();

		CullMode = CCW;
	}
}