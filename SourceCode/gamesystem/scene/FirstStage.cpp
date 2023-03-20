#include "FirstStage.h"
//������
void FirstStage::Initialize(DirectXCommon* dxCommon)
{
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//�v���C�V�[���̃A�N�^�[
	BaseActor* actor_;
	actor_ = new PlaySceneActor();
	actor_->Initialize(dxCommon,camera,lightGroup);
	actor.reset(actor_);
}
//�X�V
void FirstStage::Update(DirectXCommon* dxCommon)
{	
	shadowcamera->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void FirstStage::Draw(DirectXCommon* dxCommon)
{
	actor->Draw(dxCommon);
}
//�e�p�`��
void FirstStage::ShadowDraw(DirectXCommon* dxCommon) {
	actor->ShadowDraw(dxCommon);
}
//���
void FirstStage::Finalize()
{
	actor->Finalize();
}