
#include "MainGame.h"

using namespace frameworks::object;
using namespace frameworks::scene;
using namespace frameworks::utility;


// ������������
MainGame::MainGame() :
SceneBase(SceneName::Main, SceneName::Result) {
  Asset().Delete().All();
  GameData::Get().CountReset();
  player.Setup();
  stage.Setup();

  const auto& stageID = GameData::Get().GetStageID();

  // �M�~�b�N�摜�̃e�[�u��
  const std::string TextureTable[] = {
    "res/png/button_A.png",     // [0]�ԃX�C�b�`
    "res/png/button_D.png",     // [1]�X�C�b�`
    "res/png/button_B.png",     // [2]���F�X�C�b�`
    "res/png/button_C.png",     // [3]�΃X�C�b�`
    "res/png/button_A_B.png",   // [4]�ԉ�����
    "res/png/button_D_B.png",   // [5]������
    "res/png/button_B_B.png",   // [6]���F������
    "res/png/button_C_B.png",   // [7]�Ή�����
  };

  // �e�[�u������f�[�^��o�^�A�֘A�t�����ꂽ ID ��ێ�
  auto& gimmickID = GameData::Get().GimmickID();
  gimmickID.clear();
  for (auto& data : TextureTable) {
    gimmickID.push_back(Asset().Append().Texture(data));
  }

  // �M�~�b�N�T�C�Y
  std::shared_ptr<const float> gimmickSize;

  // �M�~�b�N�ݒu
  switch (stageID) {
  
    case StageID::Stage1:
      gimmickSize = std::make_shared<const float>(80.0f);


      gimmicks.push_back(StageGimmick(GravityDirection::Top,
                        Vec2f(-5, 2.5f), Vec2f::Ones() * 0.8f));
      gimmicks.push_back(StageGimmick(GravityDirection::Bottom,
        Vec2f(-5, -0.5f), Vec2f::Ones() * 0.8f));
      gimmicks.push_back(StageGimmick(GravityDirection::Right,
                   Vec2f(0, -2.5f), Vec2f::Ones() * 0.8f));
      gimmicks.push_back(StageGimmick(GravityDirection::Top,
                    Vec2f(3, -3.5f), Vec2f::Ones() * 0.8f));
      gimmicks.push_back(StageGimmick(GravityDirection::Left,
        Vec2f(0, 1.5f), Vec2f::Ones() * 0.8f));
      break;
    default:;
    case StageID::Stage2:
      gimmickSize = std::make_shared<const float>(50.0f);

      gimmicks.push_back(StageGimmick(GravityDirection::Right,
        Vec2f(-6.5, -0.5f), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Top,
        Vec2f(-4.5, -3.5f), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Bottom,
        Vec2f(-1.5, 2.5f), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Bottom,
        Vec2f(-0.5, -2.5f), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Right,
        Vec2f(3.5, 4.5f), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Top,
        Vec2f(1.5, -2.5f), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Left,
        Vec2f(6.5, -0.5f), Vec2f::Ones() * 1));
      break;
    
    case StageID::Stage3:
      gimmickSize = std::make_shared<const float>(50.0f);

      gimmicks.push_back(StageGimmick(GravityDirection::Bottom,
        Vec2f(-7, 3.5), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Right,
        Vec2f(-10.5, 4.5), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Bottom,
        Vec2f(-4.5, 4.5), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Right,
        Vec2f(-4.5, -0), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Right,
        Vec2f(-9, -7), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Left,
        Vec2f(-2, -7), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Left,
        Vec2f(8.5, 5), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Left,
        Vec2f(0, 0), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Top,
        Vec2f(7.5, 0), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Right,
        Vec2f(6.5, -5), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Bottom,
        Vec2f(5.5, 2.5), Vec2f::Ones() * 1));
      gimmicks.push_back(StageGimmick(GravityDirection::Top,
        Vec2f(6.5, -7), Vec2f::Ones() * 1));
      break;
  }

  // �M�~�b�N�T�C�Y�𔽉f
  for (auto& gimmick : gimmicks) {
    gimmick.GetTransform().pos *= (*gimmickSize);
    gimmick.GetTransform().scale *= (*gimmickSize);
  }

  // BGM, SE �̃e�[�u��
  const std::string MediaTable[] = {
    "res/wav/stage1.wav",
    "res/wav/stage2.wav",
    "res/wav/stage3.wav",
    "res/wav/switch.wav",
    "res/wav/goal.wav",
    "res/wav/fall.wav",
    "res/wav/crash.wav",
  };

  // �e�[�u������f�[�^��o�^�A�֘A�t�����ꂽ ID ��ێ�
  for (auto& data : MediaTable) {
    mediaID.push_back(Asset().Append().Media(data));
  }

  // ���ʂ��ꊇ�Œ���
  const float gain = 0.5f;
  for (auto& id : mediaID) {
    Asset().Find().Media(id)->gain(gain);
  }

  // BGM �̂݁A���[�v�Đ�������
  auto bgm1 = Asset().Find().Media(mediaID[0]);
  bgm1->looping(true);
  auto bgm2 = Asset().Find().Media(mediaID[1]);
  bgm2->looping(true);
  auto bgm3 = Asset().Find().Media(mediaID[2]);
  bgm3->looping(true);

  // �v���C���[�ƃS�[���̍��W��ݒ�
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

      player.Start(Vec2f(-5.5,-3.5) * playerScale, playerScale);
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
}


// �X�V
void MainGame::Update() {
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
      ++GameData::Get().GimmickCounter();
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
}


// �`��
void MainGame::Draw() {
  stage.BackDraw();
  stage.Draw();
  stage.GoalDraw();
  for (auto& gimmick : gimmicks) { gimmick.Draw(); }
  player.Draw();
}
