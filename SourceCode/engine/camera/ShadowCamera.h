#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include "DirectXCommon.h"


class ShadowCamera
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: //�����o�֐�
	ShadowCamera();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const XMFLOAT3& eye, const XMFLOAT3& target = { 0, 0, 0 });
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �r���[�s����X�V
	/// </summary>
	void UpdateViewMatrix();

	/// <summary>
	/// �ˉe�s����X�V
	/// </summary>
	void UpdateProjectionMatrix();

	/// <summary>
/// �r���[�s��̎擾
/// </summary>
/// <returns>�r���[�s��</returns>
	inline const XMMATRIX& GetViewMatrix() {
		return matView;
	}

	/// <summary>
	/// �ˉe�s��̎擾
	/// </summary>
	/// <returns>�ˉe�s��</returns>
	inline const XMMATRIX& GetProjectionMatrix() {
		return matProjection;
	}

	/// <summary>
	/// �r���[�ˉe�s��̎擾
	/// </summary>
	/// <returns>�r���[�ˉe�s��</returns>
	inline const XMMATRIX& GetViewProjectionMatrix() {
		return matViewProjection;
	}

	/// <summary>
	/// �r���{�[�h�s��̎擾
	/// </summary>
	/// <returns>�r���{�[�h�s��</returns>
	inline const XMMATRIX& GetBillboardMatrix() {
		return matBillboard;
	}

	/// <summary>
	/// ���_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	inline const XMFLOAT3& GetEye() {
		return eye;
	}

	/// <summary>
	/// ���_���W�̐ݒ�
	/// </summary>
	/// <param name="eye">���W</param>
	inline void SetEye(const XMFLOAT3& eye) {
		this->eye = eye; viewDirty = true;
	}

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	inline const XMFLOAT3& GetTarget() {
		return target;
	}

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="target">���W</param>
	inline void SetTarget(const XMFLOAT3& target) {
		this->target = target; viewDirty = true;
	}

	/// <summary>
	/// ������x�N�g���̎擾
	/// </summary>
	/// <returns>������x�N�g��</returns>
	inline const XMFLOAT3& GetUp() {
		return up;
	}

	/// <summary>
	/// ������x�N�g���̐ݒ�
	/// </summary>
	/// <param name="up">������x�N�g��</param>
	inline void SetUp(const XMFLOAT3& up) {
		this->up = up; viewDirty = true;
	}

protected: // �����o�ϐ�
	// �r���[�s��
	XMMATRIX matView = DirectX::XMMatrixIdentity();
	// �r���{�[�h�s��
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	// Y�����r���{�[�h�s��
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();
	// �ˉe�s��
	XMMATRIX matProjection = DirectX::XMMatrixIdentity();
	// �r���[�ˉe�s��
	XMMATRIX matViewProjection = DirectX::XMMatrixIdentity();
	// �r���[�s��_�[�e�B�t���O
	bool viewDirty = false;
	// �ˉe�s��_�[�e�B�t���O
	bool projectionDirty = false;
	// ���_���W
	XMFLOAT3 eye = { 0, 0, -20 };
	// �����_���W
	XMFLOAT3 target = { 0, 0, 0 };
	// ������x�N�g��
	XMFLOAT3 up = { 0, 1, 0 };
	// �A�X�y�N�g��
	float aspectRatio = 1.0f;
};