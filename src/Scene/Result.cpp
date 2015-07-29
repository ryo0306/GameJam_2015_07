
#include "Result.h"

using namespace frameworks::scene;


// ������������
Result::Result() :
SceneBase(SceneName::Result, SceneName::Title) {
  Asset().Delete().All();

  const std::string TextureTable[] = {
    "res/png/result_0.png",
    "res/png/result_1.png",
    "res/png/result_2.png",
    "res/png/result_3.png",
    "res/png/result_4.png",
    "res/png/result_5.png",
    "res/png/result_6.png",
    "res/png/result_7.png",
    "res/png/result_8.png",
    "res/png/result_9.png",
    "res/png/result_newton1.png",
    "res/png/result_newton2.png",
    "res/png/result_medal.png",
  };

  for (const auto& data : TextureTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }

  const std::string MediaTable[] = {
    "res/wav/result.wav",
    "res/wav/start.wav",
    "res/wav/select.wav",
  };

  for (const auto& data : MediaTable) {
    mediaID.push_back(Asset().Append().Media(data));
  }

  const float gain = 0.5f;
  for (const auto& id : mediaID) {
    Asset().Find().Media(id)->gain(gain);
  }

  auto bgm = Asset().Find().Media(mediaID[0]);
  bgm->looping(true);
  bgm->play();
}


// �X�V
void Result::Update() {
  if (Env().isPushKey(SPACE)) {
    isFinish = true;
    Asset().Find().Media(mediaID[0])->stop();
  }
}


// �`��
void Result::Draw() {

  // �N���A���M�~�b�N�g�p��
  u_int count = GameData::Get().GimmickCounter();

  bool get_medal = false;

  // �X�e�[�W���ƂɃ��_���l�����������𒲂ׂ�
  switch (GameData::Get().GetStageID()) {
    default:;
    case StageID::Stage1:
      get_medal = count <= 4;
      break;

    case StageID::Stage2:
      get_medal = count <= 4;
      break;

    case StageID::Stage3:
      get_medal = count <= 9;
      break;
  }

  // ���_���L�����𔻒�
  if (get_medal) {
    const auto result_medal = Asset().Find().Texture(textureID[11]);
    drawTextureBox(-800, -450, 1600, 900, 0, 0, 1600, 900, *result_medal);
    const auto medal = Asset().Find().Texture(textureID[12]);
    drawTextureBox(-170, -325, 512, 512, 0, 0, 512, 512, *medal);
  }
  else {
    const auto result_no_medal = Asset().Find().Texture(textureID[10]);
    drawTextureBox(-800, -450, 1600, 900, 0, 0, 1600, 900, *result_no_medal);
  }

  // ����
  const auto num_1 = Asset().Find().Texture(textureID[count % 10]);
  drawTextureBox(-580, -500, 480, 480, 0, 0, 512, 512, *num_1);


  if (count / 10) {
    const auto num_2 = Asset().Find().Texture(textureID[count / 10]);
    drawTextureBox(-760, -500, 480, 480, 0, 0, 512, 512, *num_2);
  }
}
