#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <vector>
#include<windows.h>
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
	void PlaySceneInitialize();//プレイシーンのみの初期化
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
	XMFLOAT3 SplinePosition(const std::vector<XMFLOAT3>& points, size_t startindex, float t);
private:
	//スプライト
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