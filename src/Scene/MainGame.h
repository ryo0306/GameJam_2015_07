
#pragma once
#include "SceneBase.hpp"
#include "../Objects/Stage.h"
#include "../Objects/Player.h"
#include "../Objects/Gimmick.h"

namespace frameworks {
namespace scene {

class MainGame : public SceneBase {
public:
  MainGame();

  void Update() override;
  void Draw() override;

private:
	object::Player player;
  object::Stage stage;
  std::vector<object::StageGimmick> gimmicks;

  std::vector<u_int> mediaID;
};

}  // end scene
}  // end frameworks
