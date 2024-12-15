// Description: base fx file for standard object rendering

// Scope:
// Wave pattern
// A Texture (blue)

cbuffer TransformBuffer : register(b0)
{
    matrix wvp; // World View Projection
    matrix world; // World Position
    float3 viewPosition; // Camera position
}

cbuffer SettingsData : register(b1)
{
    float amplitude1;
    float amplitude2;
    float waveLength1;
    float waveLength2;
    float speed;
    float waveTime;
}

Texture2D waterTexture : register(t0);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float3 worldNormal : NORMAL;
    float3 worldTangent : TANGENT;
    float2 texCoord : TEXCOORD;
    float3 dirToView : TEXCOORD1;
};

VS_OUTPUT VS(VS_INPUT input)
{
    //float w = 2 * 3.141592f / waveLength1;
    
    // Maybe lerp in between
    
    // Make it semi transparent
    
    float w1 = 2 / waveLength1;
    float w2 = 2 / waveLength2;
    float phi1 = speed * 2 / waveLength1;
    float phi2 = speed * 2 / waveLength2;
    
    float3 localPosition = input.position;
    VS_OUTPUT output;
    output.position = mul(float4(localPosition, 1.0f), wvp);
    
    float wave1 = amplitude1 * abs(sin(localPosition * w1 + (waveTime * phi1)));
    float wave2 = amplitude2 * abs(sin(localPosition * w2 + (waveTime * phi2)));
    
    output.position.y += wave1 + wave2;
    output.texCoord = input.texCoord;
    output.dirToView = normalize(viewPosition - (mul(float4(localPosition, 1.0f), world).xyz));
    output.worldNormal = mul(input.normal, (float3x3) world);
    output.worldTangent = mul(input.tangent, (float3x3) world);
    
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    return waterTexture.Sample(textureSampler, input.texCoord);
}