#include "ShadowMap.hlsli"

Texture2D<float> tex : register(t0);	//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);		//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	float texColor = tex.Sample(smp, input.uv);

	return float4(texColor,texColor,texColor,1);
}