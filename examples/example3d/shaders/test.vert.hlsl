static float4 gl_Position;
static float3 in_var_TEXCOORD;

struct SPIRV_Cross_Input
{
    float3 in_var_TEXCOORD : TEXCOORD0;
};

struct SPIRV_Cross_Output
{
    float4 gl_Position : SV_Position;
};

void main_inner()
{
    gl_Position = float4(in_var_TEXCOORD, 1.0f);
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    in_var_TEXCOORD = stage_input.in_var_TEXCOORD;
    main_inner();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    return stage_output;
}
