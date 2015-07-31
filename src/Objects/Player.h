
#pragma once
#include "Object.hpp"
#include <vector>


namespace frameworks {
namespace object {

class Player : public Object {
public:
  Player();
  void Setup();

  void Update() override;
  void Draw() override;

  void Start(const Vec2f&, const float);

  void GravityUpdate();
  void GravityReset() { velocity = 0.0f; }
  void SetGravityDirection(const int dir) { gravityState = dir; }

  const bool IsKeyActivate() const { return keyActiveTime > 0; }
  const int GetDirection() const { return gravityState; }

private:
  enum {
    KeyActiveCount = 1,
    MoveSpeed = 10,
  };

  Vec2f start;
	
	int keyActiveTime;
  int gravityState;
	int direction;

  float acceleration;
	float velocity;

  std::vector<u_int> textureID;

  void Move(const Vec2f&);
  const bool DisableMove();
};

}  // end object
}  // end frameworks
