
#include "MainGame.h"

using namespace frameworks::scene;
using namespace frameworks::object;
using namespace frameworks::utility;


MainGame::MainGame() :
SceneBase(SceneName::Main, SceneName::Result) {
  const auto stageID = GameData::Get().GetStageID();
  Asset().Delete().All();

  GameData::Get().CountReset();

  //player.Setup(stageID);
  stage.Setup(stageID);

  MediaSetup();
  Asset().Find().Media(mediaID[stageID])->play();

  /*


  // プレイヤーとゴールの座標を設定
  float playerScale;
  float goalScale;
  switch (stageID) {
    default:;
    case StageID::Stage1:
      playerScale = 50.0f;
      goalScale = 150.0f;
      bgm1->play();

      player.Start(Vec2f(-2, -2.5) * playerScale, playerScale);
      stage.GoalSetup({ Vec2f(-2.0, -1) * goalScale, Vec2f::Ones() * goalScale, 0 },
                      GravityDirection::Bottom);
      break;

    case StageID::Stage2:
      playerScale = 50.0f;
      goalScale = 80.0f;
      bgm2->play();

      player.Start(Vec2f(-5.5, -3.5) * playerScale, playerScale);
      stage.GoalSetup({ Vec2f(2.2, -2.5) * goalScale, Vec2f::Ones() * goalScale * 1.5, 0 },
                      GravityDirection::Right);
      break;

    case StageID::Stage3:
      playerScale = 50.0f;
      goalScale = 80.0f;
      bgm3->play();

      player.Start(Vec2f(1, 0) * playerScale, playerScale);
      stage.GoalSetup({ Vec2f(0, -2) * goalScale, Vec2f::Ones() * goalScale * 1.5, 0 },
                      GravityDirection::Top);
      break;
  }

  player.CollisionSetup(stage.GetTransforms());
  */
}


void MainGame::Update() {
  stage.Update();
  /*
  player.Update();

  const auto& playerPos = player.GetTransform().pos;
  const auto& playerSize = player.GetTransform().scale;

  for (auto& gimmick : gimmicks) {
    const auto& gimmickPos = gimmick.GetTransform().pos;
    const auto& gimmickSize = gimmick.GetTransform().scale;

    const auto hit = IsHitRectToRect(playerPos, playerSize,
                                     gimmickPos, gimmickSize);
    if (!hit) { continue; }

    if (player.IsKeyActive()) {
      player.SetGravityDirection(gimmick.GetDirection());
      player.GravityReset();
      ++GameData::Get().GimmickCount();
      Asset().Find().Media(mediaID[5])->play();
    }
  }

  const auto goal = stage.GetGoalPos();
  if (IsHitRectToRect(playerPos, playerSize, goal.pos, goal.size)) {
    isFinish = true;
    Asset().Find().Media(mediaID[0])->stop();
    Asset().Find().Media(mediaID[1])->stop();
    Asset().Find().Media(mediaID[2])->stop();
  }

  const auto Enter = Env().isPressKey(ENTER);
  if (Env().isPushKey('R') && Enter) {
    next = SceneName::Title;
    isFinish = true;
    Asset().Find().Media(mediaID[0])->stop();
    Asset().Find().Media(mediaID[1])->stop();
    Asset().Find().Media(mediaID[2])->stop();
  }
  */
}


void MainGame::Draw() {
  stage.Draw();
  //player.Draw();
}


void MainGame::MediaSetup() {
  const std::string MediaTable[] = {
    "res/wav/stage1.wav",
    "res/wav/stage2.wav",
    "res/wav/stage3.wav",
    "res/wav/switch.wav",
    "res/wav/goal.wav",
    "res/wav/fall.wav",
    "res/wav/crash.wav",
  };

  // テーブルからデータを登録、関連付けされた ID を保持
  for (auto& data : MediaTable) {
    mediaID.push_back(Asset().Append().Media(data));
  }

  // 音量を一括で調整
  const float gain = 0.5f;
  for (auto& id : mediaID) { Asset().Find().Media(id)->gain(gain); }

  // BGM のみ、ループ再生を許可
  auto bgm1 = Asset().Find().Media(mediaID[0]);
  bgm1->looping(true);
  auto bgm2 = Asset().Find().Media(mediaID[1]);
  bgm2->looping(true);
  auto bgm3 = Asset().Find().Media(mediaID[2]);
  bgm3->looping(true);
}
