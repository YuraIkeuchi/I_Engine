#include "PlaySceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "ParticleEmitter.h"
#include "ModelManager.h"
#include <algorithm>

//初期化
void PlaySceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	dxCommon->SetFullScreen(true);
	//共通の初期化
	BaseInitialize(dxCommon);
	//オーディオ
	Audio::GetInstance()->LoadSound(1, "Resources/Sound/BGM/Boss.wav");
	//ポストエフェクトのファイル指定
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/NewToneMapPS.hlsl");

	PlayPostEffect = true;

	//タイトル
	IKESprite* PlaySprite_;
	PlaySprite_ = IKESprite::Create(ImageManager::PLAY, { 0.0f,0.0f });
	PlaySprite.reset(PlaySprite_);

	modelGround = ModelManager::GetInstance()->GetModel(ModelManager::Ground);
	modelCube = ModelManager::GetInstance()->GetModel(ModelManager::Cube);

	objCube = make_unique<IKEObject3d>();
	objCube->Initialize();
	objCube->SetModel(modelCube);
	objCube->SetPosition({ 0.0f,5.0f,0.0f });

	objGround = make_unique<IKEObject3d>();
	objGround->Initialize();
	objGround->SetModel(modelGround);
	objGround->SetPosition({ 0.0f,0.0f,0.0f });
}
//更新
void PlaySceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	Input* input = Input::GetInstance();
	if (input->TriggerButton(input->Button_A)) {
		m_StartCount = GetTickCount();
		m_Startindex = 1;
		//SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
		//Audio::GetInstance()->StopWave(1);
	}
	//音楽の音量が変わる
	Audio::GetInstance()->VolumChange(0, VolumManager::GetInstance()->GetBGMVolum());
	camerawork->Update(camera);


	m_NowCount = GetTickCount();
	m_ElapsedCount = m_NowCount - m_StartCount;
	float l_ElapsedTime = static_cast<float>(m_ElapsedCount) / 1000.0f;

	m_Timerate = l_ElapsedTime / m_Maxtime;
	if (m_Timerate >= 1) {
		if (m_Startindex < m_Points.size() - 3)
		{
			m_Startindex++;
			m_Timerate -= 1;

			m_StartCount = GetTickCount();
		}
		else
		{
			m_Timerate = 1;
		}

	}
	lightgroup->Update();

	objCube->SetPosition(SplinePosition(m_Points, m_Startindex, m_Timerate));
	objCube->Update();
	objGround->Update();

}
//普通の更新
void PlaySceneActor::NormalUpdate() {
	VolumManager::GetInstance()->Update();
}
//ボス登場の更新
void PlaySceneActor::BossAppUpdate() {
}
//ボス終了の更新
void PlaySceneActor::BossEndUpdate() {
}
//描画
void PlaySceneActor::Draw(DirectXCommon* dxCommon)
{
	//描画方法
	//ポストエフェクトをかけるか
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		BackDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());

		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		FrontDraw(dxCommon);
		ImGuiDraw(dxCommon);
		postEffect->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		BackDraw(dxCommon);
		FrontDraw(dxCommon);
		dxCommon->PostDraw();
	}
}
//解放
void PlaySceneActor::Finalize()
{
}
//モデルの描画
void PlaySceneActor::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	objCube->Draw();
	objGround->Draw();
	IKEObject3d::PostDraw();
}
//後ろの描画
void PlaySceneActor::BackDraw(DirectXCommon* dxCommon)
{
#pragma endregion
	ModelDraw(dxCommon);
}
//ポストエフェクトがかからない
void PlaySceneActor::FrontDraw(DirectXCommon* dxCommon) {
	//完全に前に書くスプライト
	IKESprite::PreDraw();
	//PlaySprite->Draw();
	IKESprite::PostDraw();
}
//IMGuiの描画
void PlaySceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
	ImGui::Begin("Pos");
	ImGui::Text("POSX:%f", objCube->GetPosition().x);
	ImGui::Text("POSY:%f", objCube->GetPosition().y);
	ImGui::Text("POSZ:%f", objCube->GetPosition().z);
	ImGui::End();
	camerawork->ImGuiDraw();
}
//普通の描画
void PlaySceneActor::NormalDraw(DirectXCommon* dxCommon) {
}
//ボス登場シーンの描画
void PlaySceneActor::BossAppDraw(DirectXCommon* dxCommon) {
}
//ボス終了シーンの描画
void PlaySceneActor::BossEndDraw(DirectXCommon* dxCommon) {
	ParticleEmitter::GetInstance()->FlontDrawAll();
}
//スプライン補完
XMFLOAT3 PlaySceneActor::SplinePosition(const std::vector<XMFLOAT3>& points, size_t startindex, float t)
{
	size_t n = points.size() - 2;
	if (startindex > n)return points[n];
	if (startindex < 1)return points[1];

	XMFLOAT3 p0 = points[startindex - 1];
	XMFLOAT3 p1 = points[startindex];
	XMFLOAT3 p2 = points[startindex + 1];
	XMFLOAT3 p3 = points[startindex + 2];

	XMFLOAT3 a, b, c, d, e, f, g, h, i = {};
	XMFLOAT3 a1, b1, c1, d1, b4 = {};
	float ext, ext2;
	ext = (t * t);
	ext2 = (t * t * t);
	a = XMFLOAT3(p1.x * 2, p1.y * 2, p1.z * 2);
	b = XMFLOAT3((-p0.x + p2.x) * t, (-p0.y + p2.y) * t, (-p0.z + p2.z) * t);
	c = XMFLOAT3(2 * p0.x, 2 * p0.y, 2 * p0.z);
	d = XMFLOAT3(5 * p1.x, 5 * p1.y, 5 * p1.z);
	e = XMFLOAT3(4 * p2.x, 4 * p2.y, 4 * p2.z);
	f = XMFLOAT3(-p0.x, -p0.y, -p0.z);
	g = XMFLOAT3(3 * p1.x, 3 * p1.y, 3 * p1.z);
	h = XMFLOAT3(3 * p2.x, 3 * p2.y, 3 * p2.z);

	a1 = { a.x + b.x,a.y + b.y,a.z + b.z };
	b1 = { c.x - d.x,c.y - d.y ,c.z - d.z };
	c1 = { (b1.x + e.x - p3.x) * ext ,(b1.y + e.y - p3.y) * ext  ,(b1.z + e.z - p3.z) * ext };

	d1 = { (f.x + g.x - h.x + p3.x) * ext2,(f.y + g.y - h.y + p3.y) * ext2,(f.z + g.z - h.z + p3.z) * ext2 };
	b4 = { (a1.x + c1.x),(a1.y + c1.y)  ,(a1.z + c1.z) };
	XMFLOAT3 ys;
	ys = { b4.x + d1.x,b4.y + d1.y ,b4.z + d1.z };
	XMFLOAT3 position = { 0.5f * ys.x,0.5f * ys.y ,0.5f * ys.z };
	return position;
}