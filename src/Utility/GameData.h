
#pragma once
#include "../Common.hpp"


namespace frameworks {

enum StageID {
  Stage1,
  Stage2,
  Stage3,
  All_Stage,
  None,
};

typedef std::vector<u_int>  TextureList;

class GameData {
public:
  static GameData& Get() {
    static GameData gameData;
    return gameData;
  }

  // �M�~�b�N�摜�� ID ���X�g��Ԃ�
  TextureList& GimmickID() { return gimmickID; }

  // �M�~�b�N���N�������񐔂�Ԃ�
  // TIPS: �e�X�e�[�W���Ƃ̃J�E���^��Ԃ�
  u_int& GimmickCounter() { return gimmickCounter[stage]; }

  // �M�~�b�N�̃J�E���^�����Z�b�g����
  void CountReset() { gimmickCounter[stage] = 0; }

  // �O��̋L�^���X�V�ł��邩�m�F
  void RankingUpdate() {
    if (rankingCounter[stage] < gimmickCounter[stage])
      rankingCounter[stage] = gimmickCounter[stage];
  }

  // �S�ẴX�e�[�W�̋L�^��Ԃ�
  std::vector<u_int>& RankingCounter() { return rankingCounter; }

  // �I�������X�e�[�W�� ID ��Ԃ�
  const StageID GetStageID() const { return stage; }

  // �X�e�[�W�� ID ��ێ�
  void SetStageID(const StageID id) { stage = id; }

private:
  StageID stage;
  TextureList gimmickID;

  std::vector<u_int> gimmickCounter;
  std::vector<u_int> rankingCounter;

  GameData() : stage(StageID::None) {
    gimmickCounter.resize(All_Stage);
    for (auto& count : gimmickCounter) { count = 0; }

    rankingCounter.resize(All_Stage);
    for (auto& count : rankingCounter) { count = 0; }
  }
};

}
