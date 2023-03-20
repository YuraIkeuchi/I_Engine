#include "LoadScene.h"

//������
void LoadScene::Initialize(DirectXCommon* dxCommon) {
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//���[�h�̃A�N�^�[
	BaseActor* actor_;
	actor_ = new LoadSceneActor();
	actor_->Initialize(dxCommon,camera,lightGroup);
	actor.reset(actor_);
}
//�X�V
void LoadScene::Update(DirectXCommon* dxCommon) {
	lightGroup->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void LoadScene::Draw(DirectXCommon* dxCommon) {
	actor->Draw(dxCommon);
}
//�e�p�`��
void LoadScene::ShadowDraw(DirectXCommon* dxCommon) {
	actor->ShadowDraw(dxCommon);
}
//���
void LoadScene::Finalize() {
	actor->Finalize();
}