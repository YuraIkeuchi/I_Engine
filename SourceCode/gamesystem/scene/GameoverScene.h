#pragma once
#include "IKESprite.h"
#include "BaseScene.h"
/// �^�C�g���V�[��
class GameoverScene : public BaseScene {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;
	//�e�p�`��
	void ShadowDraw(DirectXCommon* dxCommon) override;
};

