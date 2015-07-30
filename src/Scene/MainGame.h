
#pragma once
#include "SceneBase.hpp"
#include "../Objects/Player.h"
#include "../Objects/Stage.h"


namespace frameworks {
namespace scene {

class MainGame : public SceneBase {
public:
  MainGame();

  void Update() override;
  void Draw() override;

private:
	//object::Player player;
  object::Stage  stage;

  std::vector<u_int> mediaID;
  void MediaSetup();
};

}  // end scene
}  // end frameworks
