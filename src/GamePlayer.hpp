
#pragma once
#include "Common.hpp"
#include "Scene/SceneManager.h"


namespace frameworks {

class GamePlayer {
public:
  GamePlayer(const scene::SceneName scene) : manager(scene) {}

  // �Q�[���̍X�V
  void Update() {
    manager.Update();
  }

  // �Q�[���̕`��
  void Draw() {
    Env().begin();   // �`�揀��
    manager.Draw();
    Env().end();     // ��ʍX�V
  }

  // �Q�[���N�������ǂ���
  const bool IsRunning() {
    return Env().isOpen() && !Env().isPushKey(ESCAPE);
  }

private:
  SceneManager manager;
};

}  // end frameworks
