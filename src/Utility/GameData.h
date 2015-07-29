
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

  // ギミック画像の ID リストを返す
  TextureList& GimmickID() { return gimmickID; }

  // ギミックを起動した回数を返す
  // TIPS: 各ステージごとのカウンタを返す
  u_int& GimmickCounter() { return gimmickCounter[stage]; }

  // ギミックのカウンタをリセットする
  void CountReset() { gimmickCounter[stage] = 0; }

  // 前回の記録を更新できるか確認
  void RankingUpdate() {
    if (rankingCounter[stage] < gimmickCounter[stage])
      rankingCounter[stage] = gimmickCounter[stage];
  }

  // 全てのステージの記録を返す
  std::vector<u_int>& RankingCounter() { return rankingCounter; }

  // 選択したステージの ID を返す
  const StageID GetStageID() const { return stage; }

  // ステージの ID を保持
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
