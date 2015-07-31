
#include "MainGame.h"

using namespace frameworks;
using namespace frameworks::scene;
using namespace frameworks::object;
using namespace frameworks::utility;


MainGame::MainGame() :
SceneBase(SceneName::Main, SceneName::Result) {
  const auto stageID = GameData::Get().GetStageID();

  Asset().Delete().All();
  GameData::Get().CountReset();

  float stageScale = 0.0f;

  player.Setup();

  back.Setup(stageID);
  prickle.Setup();

  switch (stageID) {
    default:;
    case StageID::Stage1:
      stageScale = 80.0f;

      player.Start(Vec2f(-1, -1) * stageScale, 60.0f);
      goal.Setup(Vec2f(-3.6f, -1.6f) * stageScale, stageScale * 1.5f,
                 GravityDirection::Bottom);
      break;

    case StageID::Stage2:
      stageScale = 50.0f;

      player.Start(Vec2f(-6, -3) * stageScale, 40.0f);
      goal.Setup(Vec2f(4.1f, -3) * stageScale, stageScale * 1.5f,
                 GravityDirection::Right);
      break;

    case StageID::Stage3:
      stageScale = 50.0f;

      player.Start(Vec2f(1, 1) * stageScale, 40.0f);
      goal.Setup(Vec2f(0.25f, -2.4f) * stageScale, stageScale * 1.5f,
                 GravityDirection::Top);
      break;
  }

  block.Setup(stageID, stageScale);
  gimmick.Setup(stageID, stageScale);

  MediaSetup();
  Asset().Find().Media(mediaID[stageID])->play();
}


void MainGame::Update() {
  back.Update();
  gimmick.Update();
  goal.Update();
  player.Update();

  /*

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

  */

  // タイトルに戻る
  const auto Enter = Env().isPressKey(ENTER);
  if (Env().isPushKey('R') && Enter) {
    next = SceneName::Title;
    isFinish = true;
    Asset().Find().Media(mediaID[0])->stop();
    Asset().Find().Media(mediaID[1])->stop();
    Asset().Find().Media(mediaID[2])->stop();
  }
}


void MainGame::Draw() {
  back.Draw();
  prickle.Draw(player.GetDirection());
  block.Draw();
  gimmick.Draw();
  goal.Draw();
  player.Draw();
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
