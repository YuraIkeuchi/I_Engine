#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>

//補助クラス
class Helper
{
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//計算系
	bool CheckMax(float& Num, const float Max, const float Add);
	bool CheckMin(float& Num, const float Min, const float Add);
	//Clampを返す関数
	void IntClamp(int& Num, const int Min, const int Max);
	void FloatClamp(float& Num, const float Min, const float Max);
	//XMFLOAT3とfloatを加算する関数
	XMFLOAT3 Float3AddFloat(const XMFLOAT3& Num, const float Add);
	//XMFLOAT3とXMFLOAT3を加算する関数
	XMFLOAT3 Float3AddFloat3(const XMFLOAT3& Num, const XMFLOAT3& Add);
	//XMFLOAT3とfloatを減算する関数
	XMFLOAT3 Float3SubFloat(const XMFLOAT3& Num, const float Sub);
	//XMFLOAT3とXMFLOAT3を減算する関数
	XMFLOAT3 Float3SubFloat3(const XMFLOAT3& Num, const XMFLOAT3& Sub);
};

