
#include "Title.h"

using namespace frameworks::scene;
using namespace frameworks::object;


// 初期化をする
Title::Title() :
SceneBase(SceneName::Title, SceneName::Main),
select(0),
angle(0.0f),
generateTime(0) {
  Asset().Delete().All();

  const std::string TextureTable[] = {
    "res/png/title_0.png",
    "res/png/title_1.png",
    "res/png/title_2.png",
    "res/png/title_3.png",
    "res/png/title_4.png",
    "res/png/title_5.png",
    "res/png/title_6.png",
    "res/png/title_7.png",
    "res/png/title_8.png",
    "res/png/title_9.png",

    "res/png/title_back.png",     //[10]背景
    "res/png/title_logo.png",     //[11]
    "res/png/stage1.png",         //[12]アイコン
    "res/png/stage2.png",         //[13]
    "res/png/stage3.png",         //[14]
    "res/png/title_cursor.png",   //[15]葉っぱカーソル
    "res/png/title_start.png",    //[16]スタート操作

    "res/png/ochirukun_red.png",      //[17]
    "res/png/ochirukun_blue.png",     //[18]
    "res/png/ochirukun_green.png",    //[19]
    "res/png/ochirukun_yellow.png",   //[20]
  };

  for (const auto& data : TextureTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }

  // ステージ選択のアイコン ID を取り出す
  icons.push_back(textureID[12]);
  icons.push_back(textureID[13]);
  icons.push_back(textureID[14]);

  const std::string MediaTable[] = {
    "res/wav/op.wav",
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


// 更新
void Title::Update() {
  angle += 0.02f;
  if (angle > M_PI) { angle = 0.0f; }

  if (Env().isPushKey(SPACE)) {
    isFinish = true;
    Asset().Find().Media(mediaID[0])->stop();
    GameData::Get().SetStageID(StageID(select));
  }

  if (Env().isPushKey(KEY_L) && select > 0) { --select; }
  if (Env().isPushKey(KEY_R) && select < 2) { ++select; }

  // パーティクル
  auto itr = particles.begin();
  while (itr != particles.end()) {
    itr->Update();
    itr->GetPos().y() > (-HEIGHT / 2 - 100) ?
      ++itr : itr = particles.erase(itr);
  }

  ++generateTime;
  if (generateTime < FPS || particles.size() > ParticleMax) { return; }

  generateTime = 0;

  Transform temp;
  temp.pos = Vec2f(Rand()() * WIDTH - (WIDTH / 2), HEIGHT / 2);
  temp.scale = Vec2f::Ones() * Rand()(20.0f, 100.0f);
  temp.rotate = 0.0f;
  temp.angle = Rand()(-0.1f, 0.1f);

  const u_int id = textureID[17 + Rand()(4)];
  particles.push_back(Particle(temp, id, Rand()(1.0f, 2.0f) + 0.5f));
}


// 描画
void Title::Draw() {
  // 背景
  const auto back = Asset().Find().Texture(textureID[10]);
  const Vec2f backSize(1600, 900);
  drawTextureBox(-backSize.x() / 2, -backSize.y() / 2,
                 backSize.x(), backSize.y(),
                 0, 0, backSize.x(), backSize.y(),
                 *back, Color::white);

  // パーティクル
  for (auto& particle : particles) { particle.Draw(); }

  // ロゴ
  const auto logo = Asset().Find().Texture(textureID[11]);
  const Vec2f logoSize(2048, 512);
  drawTextureBox(0, 0, logoSize.x(), logoSize.y() + 20,
                 0, 0, logoSize.x(), logoSize.y(),
                 *logo, Color::white,
                 0, Vec2f::Ones() * 0.8f,
                 Vec2f(logoSize.x() / 2, 0));

  // アイコン
  const Vec2f scale = Vec2f::Ones() * 1.2f;
  const Vec2f iconSize = Vec2f::Ones() * 280.0f;
  int count = 0;

  // カーソル
  const auto cursor = Asset().Find().Texture(textureID[15]);
  const Vec2f cursorSize(100, 160);

  for (auto& icon : icons) {
    // それぞれのアイコン
    const auto texture = Asset().Find().Texture(icon);

    // 選択状態
    const bool selected = (count == select);

    // 座標計算
    const float posX = (iconSize.x() + 180) * (count - 1);
    const float posY = -HEIGHT / 2 + 140;

    // 回転エフェクト
    const float rotate = selected ? std::sin(angle * 2) / 4 : 0.0f;

    drawTextureBox(posX, posY, iconSize.x(), iconSize.y(),
                   0, 0, 480, 480,
                   *texture, Color::white, rotate,
                   selected ? scale : Vec2f::Ones(),
                   iconSize * 0.5f);

    if (selected) {
      drawTextureBox(posX, posY + 200, cursorSize.x(), cursorSize.y(),
                     0, 0, cursorSize.x(), cursorSize.y(),
                     *cursor, Color::white, rotate,
                     Vec2f::Ones() * 0.8f, cursorSize * 0.5f);
    }

    ++count;
  }

  // スタート
  const auto start = Asset().Find().Texture(textureID[16]);
  const Vec2f startSize(400, 70);
  const float offset = std::abs(std::sin(angle)) * 40.0f;
  drawTextureBox(0, -60 + offset, startSize.x(), startSize.y(),
                 0, 0, startSize.x(), startSize.y(),
                 *start, Color::white, 0,
                 Vec2f::Ones() * 2.0f,
                 startSize * 0.5f);
}
