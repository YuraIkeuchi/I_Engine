#include "Basic.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	// �e�N�X�`���}�b�s���O
	float2 offsetscroll = float2(offset.x,offset.y);
	//float2 offset = float2(0.0f, );
	float4 texcolor = tex.Sample(smp, input.uv * Tiling + offsetscroll);


	// ����x
	const float shininess = 4.0f;
	// ���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	// �����ˌ�
	float3 ambient = m_ambient;

	// �V�F�[�f�B���O�ɂ��F
	float4 shadecolor = float4(ambientColor * ambient, m_alpha);

	float4 disolvecolor = float4(ambientColor * ambient, m_alpha);
	//���C�g�̉e�����󂯂邩
	if (LightEffect) {
		// ���s����
		for (int i = 0; i < DIRLIGHT_NUM; i++) {
			if (dirLights[i].active) {
				// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
				float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
				// ���ˌ��x�N�g��
				float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
				// �g�U���ˌ�
				float3 diffuse = dotlightnormal * m_diffuse;
				// ���ʔ��ˌ�
				float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

				// �S�ĉ��Z����
				shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
			}
			//�f�B�]���u�̂��߂ɕʌv�Z
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotlightnormal2 = dot(dirLights[i].lightv, input.normal);
			// ���ˌ��x�N�g��
			float3 reflect2 = normalize(-dirLights[i].lightv + 2 * dotlightnormal2 * input.normal);
			// �g�U���ˌ�
			float3 diffuse2 = dotlightnormal2 * m_diffuse;
			// ���ʔ��ˌ�
			float3 specular2 = pow(saturate(dot(reflect2, eyedir)), shininess) * m_specular;
			disolvecolor.rgb = shadecolor.rgb += (diffuse2 + specular2) * dirLights[i].lightcolor;
		}

		// �_����
		for (i = 0; i < POINTLIGHT_NUM; i++) {
			if (pointLights[i].active) {
				// ���C�g�ւ̕����x�N�g��
				float3 lightv = pointLights[i].lightpos - input.worldpos.xyz;
				float d = length(lightv);
				lightv = normalize(lightv);
				float center_x;
				float center_y;
				float center_z;
				float center;
				float Distanse;
				float scalr;
				float add = 3.0f;
				center_x = pointLights[i].lightpos.x - input.worldpos.x;
				center_y = pointLights[i].lightpos.y - input.worldpos.y;
				center_z = pointLights[i].lightpos.z - input.worldpos.z;
				center = center_x * center_x + center_y * center_y + center_z * center_z;
				Distanse = sqrt(center);
				scalr = 1.0 - (Distanse / pointLights[i].lightatten.x);
				// �S�ĉ��Z����
				if (scalr >= 0) {

					shadecolor.rgb += ((add) * pointLights[i].lightcolor) * scalr;
				}
			}
		}

		// �X�|�b�g���C�g
		for (i = 0; i < SPOTLIGHT_NUM; i++) {
			if (spotLights[i].active) {
				// ���C�g�ւ̕����x�N�g��
				float3 lightv = spotLights[i].lightpos - input.worldpos.xyz;
				float d = length(lightv);
				lightv = normalize(lightv);

				// ���������W��
				float atten = saturate(1.0f / (spotLights[i].lightatten.x + spotLights[i].lightatten.y * d + spotLights[i].lightatten.z * d * d));

				// �p�x����
				float cos = dot(lightv, spotLights[i].lightv);
				// �����J�n�p�x����A�����I���p�x�ɂ����Č���
				// �����J�n�p�x�̓�����1�{ �����I���p�x�̊O����0�{�̋P�x
				float angleatten = smoothstep(spotLights[i].lightfactoranglecos.y, spotLights[i].lightfactoranglecos.x, cos);
				// �p�x��������Z
				atten *= angleatten;

				// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
				float3 dotlightnormal = dot(lightv, input.normal);
				// ���ˌ��x�N�g��
				float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
				// �g�U���ˌ�
				float3 diffuse = dotlightnormal * m_diffuse;
				// ���ʔ��ˌ�
				float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

				// �S�ĉ��Z����
				shadecolor.rgb += atten * (diffuse + specular) * spotLights[i].lightcolor;
			}
		}
	}
	else {
		for (int i = 0; i < DIRLIGHT_NUM; i++) {
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
			// ���ˌ��x�N�g��
			float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
			// �g�U���ˌ�
			float3 diffuse = dotlightnormal * m_diffuse;
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

			// �S�ĉ��Z����
			shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;

			//�f�B�]���u�̂��߂ɕʌv�Z
		// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotlightnormal2 = dot(dirLights[i].lightv, input.normal);
			// ���ˌ��x�N�g��
			float3 reflect2 = normalize(-dirLights[i].lightv + 2 * dotlightnormal2 * input.normal);
			// �g�U���ˌ�
			float3 diffuse2 = dotlightnormal2 * m_diffuse;
			// ���ʔ��ˌ�
			float3 specular2 = pow(saturate(dot(reflect2, eyedir)), shininess) * m_specular;
			disolvecolor.rgb = shadecolor.rgb += (diffuse2 + specular2) * dirLights[i].lightcolor;
		}
	}

	// �ۉe
	for (int i = 0; i < CIRCLESHADOW_NUM; i++) {
		if (circleShadows[i].active) {
			// �I�u�W�F�N�g�\�ʂ���L���X�^�[�ւ̃x�N�g��
			float3 casterv = circleShadows[i].casterPos - input.worldpos.xyz;
			// ���������ł̋���
			float d = dot(casterv, circleShadows[i].dir);

			// ���������W��
			float atten = saturate(1.0f / (circleShadows[i].atten.x + circleShadows[i].atten.y * d + circleShadows[i].atten.z * d * d));
			// �������}�C�i�X�Ȃ�0�ɂ���
			atten *= step(0, d);

			// ���C�g�̍��W
			float3 lightpos = circleShadows[i].casterPos + circleShadows[i].dir * circleShadows[i].distanceCasterLight;
			//  �I�u�W�F�N�g�\�ʂ��烉�C�g�ւ̃x�N�g���i�P�ʃx�N�g���j
			float3 lightv = normalize(lightpos - input.worldpos.xyz);
			// �p�x����
			float cos = dot(lightv, circleShadows[i].dir);
			// �����J�n�p�x����A�����I���p�x�ɂ����Č���
			// �����J�n�p�x�̓�����1�{ �����I���p�x�̊O����0�{�̋P�x
			float angleatten = smoothstep(circleShadows[i].factorAngleCos.y, circleShadows[i].factorAngleCos.x, cos);
			// �p�x��������Z
			atten *= angleatten;

			// �S�Č��Z����
			shadecolor.rgb -= atten;
		}
	}

	//�f�B�]���u
	float l_Disolve = Disolve;
	float blackarea = Disolve + 0.2f;
	float a = disolvecolor.r * 0.5 + disolvecolor.g * 0.5 + disolvecolor.b * 0.5;

	//������Ƃ��ɏ��������Ȃ��ď�����
	if (ChangeColor) {
		if (a < blackarea) {
			texcolor.r = texcolor.r - Addcolor.r;
			texcolor.g = texcolor.g - Addcolor.g;
			texcolor.b = texcolor.b - Addcolor.b;
		}
	}

	//���񂾂������
	if (a > l_Disolve) {
		shadecolor.a = 1.0f;
	}
	else {
		shadecolor.a = 0.0f;
	}


	//�t�H�O����
	float4 normalcolor = { 0.1,0.1,0.1,0 };//cameraPos�t�߂̐F
	float4 c = { 0.4,0.4,0.4,0 };//
	//cameraPos�Ƃ��邪���͌Œ���W
	float dist = length(cameraPos - input.worldpos);
	float4 addcol = float4(lerp(normalcolor.rgb, c.rgb, dist / 50), 0.0);
	//�Èłɂ��邽��
	addcol = addcol * -0.5f;

	float4 pixcolor;
	//fog���������Ă邩�������ĂȂ���
	if (Fog) {
		pixcolor = shadecolor * texcolor * color + (addcol);
	}
	else {
		pixcolor = shadecolor * texcolor * color;
	}

	// �V�F�[�f�B���O�ɂ��F�ŕ`��
	return pixcolor;
}