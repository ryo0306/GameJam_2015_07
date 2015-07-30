
#pragma once
#include "BackGround.h"
#include "Block.h"
#include "GimmickController.h"
#include "Goal.h"


namespace frameworks {
namespace object {

class Stage {
  typedef std::unique_ptr<const float>  Size;
  typedef std::vector<Gimmick>  Gimmicks;

public:
  Stage() {}

  void Setup(const StageID);

  void Update();
  void Draw();

private:
  StageID stage;
  std::unique_ptr<const float> stageScale;

  BackGround back;
  Block block;
  GimmickController gimmick;
  Goal goal;
};

}
}
