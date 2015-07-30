
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
      goal.Setup(Vec2f(-3.6f, -1.6f) * (*stageScale), *stageScale * 1.5f,
                 GravityDirection::Bottom);
      break;

    case StageID::Stage2:
      stageScale = std::make_unique<const float>(50.0f);
      goal.Setup(Vec2f(4.1f, -3) * (*stageScale), *stageScale * 1.5f,
                 GravityDirection::Right);
      break;

    case StageID::Stage3:
      stageScale = std::make_unique<const float>(50.0f);
      goal.Setup(Vec2f(0.25f, -2.4f) * (*stageScale), *stageScale * 1.5f,
                 GravityDirection::Top);
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
