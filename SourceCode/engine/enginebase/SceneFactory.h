#pragma once
#include"AbstractSceneFactory.h"

//���̃Q�[���p�̃V�[���H��
class SceneFactory :
	public AbstractSceneFactory
{
public:
	//�V�[������
	BaseScene* CreateScene(const std::string& sceneName) override;
};
