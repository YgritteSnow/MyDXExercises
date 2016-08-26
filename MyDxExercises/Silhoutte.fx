//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Silhouette
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string NPR_Silhouette_Pass_0_Teapot : ModelData = "..\\Media\\models\\Teapot.3ds";

texture RT_Tex : RenderColorTarget
<
   float2 ViewportRatio={1.0,1.0};
   string Format="D3DFMT_A8R8G8B8";
   float  ClearDepth=1.000000;
   int    ClearColor=0;
>;
float4x4 view_proj_matrix : ViewProjection;
struct VS_OUTPUT
{
   float4 Pos: POSITION;
};

VS_OUTPUT NPR_Silhouette_Pass_0_Vertex_Shader_vs_main( float4 Pos: POSITION )
{
   VS_OUTPUT Out = (VS_OUTPUT) 0; 
   Out.Pos = mul( view_proj_matrix, Pos );
   return Out;
}

float4 NPR_Silhouette_Pass_0_Pixel_Shader_ps_main( float4 Diff: COLOR0 ) : COLOR
{
    float4 c; 
    c[0] = 1.0;
    c[1] = 1.0;
    c[2] = 0.0;
    c[3] = 1.0;

    return c;
}

//--------------------------------------------------------------//
// Pass 1
//--------------------------------------------------------------//
string NPR_Silhouette_Pass_1_ScreenAlignedQuad : ModelData = "..\\Media\\Models\\ScreenAlignedQuad.3ds";

float4x4 NPR_Silhouette_Pass_1_Vertex_Shader_view_proj_matrix;
struct VS_INPUT
{
   float4 Pos      : POSITION;
   float2 TexCoord : TEXCOORD0;
};

struct NPR_Silhouette_Pass_1_Vertex_Shader_VS_OUTPUT
{
   float4 Pos      : POSITION;
   float2 TexCoord : TEXCOORD0;
};

NPR_Silhouette_Pass_1_Vertex_Shader_VS_OUTPUT NPR_Silhouette_Pass_1_Vertex_Shader_vs_main( VS_INPUT In )
{
   NPR_Silhouette_Pass_1_Vertex_Shader_VS_OUTPUT Out; 

   In.Pos.xy = sign(In.Pos.xy);
   Out.Pos       = float4(In.Pos.xy, 0.0, 1.0);
   // Image-space
   Out.TexCoord.x = 0.5 * (1 + In.Pos.x);
   Out.TexCoord.y = 0.5 * (1 + In.Pos.y);
   //Out.TexCoord = (In.Pos.xy);

   return Out;
}

sampler RT = sampler_state
{
   Texture = (RT_Tex);
   ADDRESSU = CLAMP;
   ADDRESSV = CLAMP;
};
// One pixel offset
const float off = 1.0 / 512.0;


struct PS_INPUT
{
   float2 TexCoord : TEXCOORD0;
};

struct PS_OUTPUT
{
   float4 Color    : COLOR0;
};


PS_OUTPUT NPR_Silhouette_Pass_1_Pixel_Shader_ps_main( PS_INPUT In)
{
   PS_OUTPUT Out;

   // Sample neighbor pixels
   float s00 = tex2D(RT, In.TexCoord + float2(-off, -off)).r;
   float s01 = tex2D(RT, In.TexCoord + float2( 0,   -off)).r;
   float s02 = tex2D(RT, In.TexCoord + float2( off, -off)).r;

   float s10 = tex2D(RT, In.TexCoord + float2(-off,  0)).r;
   float s12 = tex2D(RT, In.TexCoord + float2( off,  0)).r;

   float s20 = tex2D(RT, In.TexCoord + float2(-off,  off)).r;
   float s21 = tex2D(RT, In.TexCoord + float2( 0,    off)).r;
   float s22 = tex2D(RT, In.TexCoord + float2( off,  off)).r;

   // Sobel filter in X direction
   float sobelX = s00 + 2 * s10 + s20 - s02 - 2 * s12 - s22;
   // Sobel filter in Y direction
   float sobelY = s00 + 2 * s01 + s02 - s20 - 2 * s21 - s22;

   // Find edge, skip sqrt() to improve performance ...
   float edgeSqr = (sobelX * sobelX + sobelY * sobelY);

   // ... and threshold against a squared value instead.
   Out.Color = 0.8-(edgeSqr > 0.07 * 0.07)/3.0;
   //Out.Color = saturate( edgeSqr);
   //Out.Color = float4(s00,s01,s02, 1.0);
   //Out.Color = float4(In.TexCoord.x, In.TexCoord.y, 0.0, 1.0);
   return Out;
}


//--------------------------------------------------------------//
// Technique Section for Effect Workspace.NPR.Silhouette
//--------------------------------------------------------------//
technique Silhouette
{
   pass Pass_0
   <
      string Script = "RenderColorTarget0 = RT_Tex;"
                      "ClearColor = (0, 0, 0, 0);"
                      "ClearDepth = 1.000000;";
   >
   {
      VertexShader = compile vs_1_1 NPR_Silhouette_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 NPR_Silhouette_Pass_0_Pixel_Shader_ps_main();
   }

   //pass Pass_1
   //{
   //   CULLMODE = CW;

   //   VertexShader = compile vs_1_1 NPR_Silhouette_Pass_1_Vertex_Shader_vs_main();
   //   PixelShader = compile ps_2_0 NPR_Silhouette_Pass_1_Pixel_Shader_ps_main();
   //}

}

