
#pragma once
#include "SceneBase.hpp"
#include "../Objects/Particle.h"
#include <list>


namespace frameworks {
namespace scene {

class Title : public SceneBase {
public:
  Title();

  void Update() override;
  void Draw() override;

private:
  enum { ParticleMax = 10, };

  std::vector<u_int> textureID;
  std::vector<u_int> mediaID;

  u_int select;
  std::vector<u_int> icons;

  float angle;
  std::list<object::Particle> particles;
  int generateTime;
};

}  // end scene
}  // end frameworks
