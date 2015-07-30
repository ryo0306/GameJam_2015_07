
#include "Stage.h"

using namespace frameworks;
using namespace frameworks::object;


void Stage::Setup(const StageID stage) {
  this->stage = stage;

  back.Setup(stage);

  switch (stage) {
    default:;
    case StageID::Stage1:
      stageScale = std::make_unique<const float>(80.0f);
      goal.Setup(Vec2f(-3, -2) * (*stageScale), *stageScale,
                 GravityDirection::Bottom);
      break;

    case StageID::Stage2:
      stageScale = std::make_unique<const float>(50.0f);
      goal.Setup(Vec2f(-3, -2) * (*stageScale), *stageScale,
                 GravityDirection::Bottom);
      break;

    case StageID::Stage3:
      stageScale = std::make_unique<const float>(50.0f);
      goal.Setup(Vec2f(-3, -2) * (*stageScale), *stageScale,
                 GravityDirection::Bottom);
      break;
  }

  block.Setup(stage, *stageScale);
  gimmick.Setup(stage, *stageScale);
}


void Stage::Update() {
  back.Update();
  goal.Update();
}


void Stage::Draw() {
  back.Draw();
  block.Draw();
  gimmick.Draw();
  goal.Draw();
}
