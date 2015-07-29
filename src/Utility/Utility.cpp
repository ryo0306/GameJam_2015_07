
#include "DrawTexture.h"
#include <map>


namespace frameworks {
namespace utility {

const Vec2f& OffsetTextureOrigin(const Origin info) {
  static std::map<Origin, Vec2f> offsetTable = {
    { Origin::LeftTop,      Vec2f(0.0f, 1.0f) },
    { Origin::Left,         Vec2f(0.0f, 0.5f) },
    { Origin::LeftBottom,   Vec2f(0.0f, 0.0f) },
    { Origin::CenterTop,    Vec2f(0.5f, 1.0f) },
    { Origin::Center,       Vec2f(0.5f, 0.5f) },
    { Origin::CenterBottom, Vec2f(0.5f, 0.0f) },
    { Origin::RightTop,     Vec2f(1.0f, 1.0f) },
    { Origin::Right,        Vec2f(1.0f, 0.5f) },
    { Origin::RightBottom,  Vec2f(1.0f, 0.0f) },
  };

  return offsetTable.find(info)->second;
}

void DrawTexture(const Transform& transform,
                 const Sprite& sprite,
                 const Vec2f& offset) {
  const Vec2f& scale = transform.scale;
  const auto origin = Vec2f(scale.x() * offset.x(),
                            scale.y() * offset.y());

  drawTextureBox(transform.pos.x(), transform.pos.y(), 1, 1,
                 sprite.start.x(), sprite.start.y(),
                 sprite.size.x(), sprite.size.y(),
                 sprite.texture, sprite.color,
                 transform.rotate, transform.scale, origin);
}

bool IsHitRectToRect(const Vec2f& pos1, const Vec2f& size1,
                     const Vec2f& pos2, const Vec2f& size2) {
  const bool hitL = pos1.x() + size1.x() > pos2.x();
  const bool hitR = pos1.x() < pos2.x() + size2.x();
  const bool hitB = pos1.y() + size1.y() > pos2.y();
  const bool hitT = pos1.y() < pos2.y() + size2.y();

  return (hitL && hitR && hitB && hitT);
}

}  // end utility
}  // end frameworks
