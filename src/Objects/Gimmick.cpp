
#include "Gimmick.h"

using namespace frameworks::object;


Gimmick::Gimmick(const int direction,
                 const Vec2f& pos) :
direction(direction),
pos(pos) {
  pushState = (direction == GravityDirection::Bottom);
}


void Gimmick::Draw(const std::vector<u_int>& idList,
                   const float gimmickSize) {
  const auto id = idList[pushState ? direction + 4 : direction];
  const auto texture = Asset().Find().Texture(id);

  const float offset = gimmickSize * 0.5f;
  const Vec2f drawPos = pos + (Vec2f::Ones() * offset);
  const float cutSize = 128.0f;

  drawTextureBox(drawPos.x(), drawPos.y(),
                 gimmickSize, gimmickSize,
                 0, 0, cutSize, cutSize,
                 *texture, Color::white,
                 0, Vec2f::Ones(),
                 Vec2f::Ones() * offset);
}
