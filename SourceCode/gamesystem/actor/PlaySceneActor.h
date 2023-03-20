#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "IKEObject3d.h"
#include "IKEModel.h"

/// タイトルシーン
class PlaySceneActor : public BaseActor {
public:
	/// 初期化
	void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// 終了
	void Finalize() override;
	/// 毎フレーム更新
	void Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// 描画
	void Draw(DirectXCommon* dxCommon) override;
	//影用描画
	void ShadowDraw(DirectXCommon* dxCommon) override;
	void ModelDraw(DirectXCommon* dxCommon);
	void FrontDraw(DirectXCommon* dxCommon);
	void BackDraw(DirectXCommon* dxCommon);
	void NormalDraw(DirectXCommon* dxCommon);//普通の描画
	void BossAppDraw(DirectXCommon* dxCommon);//ボス登場シーンの描画
	void BossEndDraw(DirectXCommon* dxCommon);//ボス登場シーンの描画
	void NormalUpdate();//普通の更新
	void BossAppUpdate();//ボス登場シーンの更新
	void BossEndUpdate();//ボス終了シーンの更新
	void ImGuiDraw(DirectXCommon* dxCommon);
private:
	//スプライト
	unique_ptr<IKESprite> PlaySprite;
	//OBJ
	unique_ptr<IKEObject3d> objGround;
	unique_ptr<IKEObject3d> objCube;
	IKEModel* modelGround = nullptr;
	IKEModel* modelCube = nullptr;
};