
#pragma once
#include "Object.hpp"


namespace frameworks {
namespace object {

class Gimmick {
public:
  Gimmick(const int, const Vec2f&);

  void Draw(const std::vector<u_int>&, const float);

  void IconStateShift() { pushState = !pushState; }
  const bool IsPushed() const { return pushState; }

  Vec2f& GetPos() { return pos; }
  const int GetDirection() const { return direction; }

private:
  Vec2f pos;
  int direction;
  bool pushState;
};

}
}
