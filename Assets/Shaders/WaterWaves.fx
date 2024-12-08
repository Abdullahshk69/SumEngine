// Description: base fx file for standard object rendering

cbuffer TransformBuffer : register(b0)
{
    matrix wvp; // World View Projection
}

cbuffer SettingsData : register(b1)
{
    float strength;
    float speed;
    float frequency;
    float waveTime;
}

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float3 position : SV_Position;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.position = input.position;
    
    //float waveValue = input.texCoord.x * (3.141592f * strength) + waveTime;
    //float2 texCoord = input.texCoord;
    //output.position.y += sin(waveValue);
    
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}