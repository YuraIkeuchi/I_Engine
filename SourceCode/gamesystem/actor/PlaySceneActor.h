#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <vector>
#include<windows.h>
/// �^�C�g���V�[��
class PlaySceneActor : public BaseActor {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;
	void PlaySceneInitialize();//�v���C�V�[���݂̂̏�����
	void ModelDraw(DirectXCommon* dxCommon);
	void FrontDraw(DirectXCommon* dxCommon);
	void BackDraw(DirectXCommon* dxCommon);
	void NormalDraw(DirectXCommon* dxCommon);//���ʂ̕`��
	void BossAppDraw(DirectXCommon* dxCommon);//�{�X�o��V�[���̕`��
	void BossEndDraw(DirectXCommon* dxCommon);//�{�X�o��V�[���̕`��
	void NormalUpdate();//���ʂ̍X�V
	void BossAppUpdate();//�{�X�o��V�[���̍X�V
	void BossEndUpdate();//�{�X�I���V�[���̍X�V
	void ImGuiDraw(DirectXCommon* dxCommon);
	XMFLOAT3 SplinePosition(const std::vector<XMFLOAT3>& points, size_t startindex, float t);
private:
	//�X�v���C�g
	unique_ptr<IKESprite> PlaySprite;
	//OBJ
	unique_ptr<IKEObject3d> objGround;
	unique_ptr<IKEObject3d> objCube;
	IKEModel* modelGround = nullptr;
	IKEModel* modelCube = nullptr;
	int m_Pointsindex = 6;
	XMFLOAT3 m_Start = { 0, 0, 0 };
	XMFLOAT3 m_P2 = { -10, 0, 0 };
	XMFLOAT3 m_P3 = { 0, 0, 10 };
	XMFLOAT3 m_End = { 10, 0, -10};
	size_t m_Startindex = 1;
	vector<XMFLOAT3>m_Points{m_Start,m_Start,m_P2,m_P3,m_End,m_End};
	long long m_StartCount = 0;
	long long m_NowCount = 0;
	long long m_ElapsedCount = 0;
	float m_Maxtime = 5;
	float m_Timerate;
};