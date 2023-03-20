#include "ClearScene.h"
//������
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//�N���A�̃A�N�^�[
	BaseActor* actor_;
	actor_ = new ClearSceneActor();
	actor_->Initialize(dxCommon, camera, lightGroup);
	actor.reset(actor_);
}
//�X�V
void ClearScene::Update(DirectXCommon* dxCommon) {
	lightGroup->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void ClearScene::Draw(DirectXCommon* dxCommon) {
	actor->Draw(dxCommon);
}
//�e�p�`��
void ClearScene::ShadowDraw(DirectXCommon* dxCommon) {
	actor->ShadowDraw(dxCommon);
}
//���
void ClearScene::Finalize() {
	actor->Finalize();
}